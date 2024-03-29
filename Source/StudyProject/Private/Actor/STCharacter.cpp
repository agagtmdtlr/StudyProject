// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/STCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "STAnimInstance.h"
#include "Component/STCharacterStatComponent.h"
#include "Actor/STWeapon.h"

#include "Components/WidgetComponent.h" // UMG
#include "Widget/STCharacterWidget.h"

#include "Controller/STAIController.h"

#include "DrawDebugHelpers.h"
#include <vector>

#include "STCharacterSetting.h"

#include "STGameInstance.h"
#include "Controller/STPlayerController.h"
#include "STPlayerState.h"

#include "Widget/STHUDWidget.h"

#include "STGameMode.h"

#include "Component/STCharacterMovementComponent.h"

// Sets default values
ASTCharacter::ASTCharacter()
	:
	AttackRange(80.0f),
	AttackRadius(50.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* CapulseComponent = GetCapsuleComponent();
	CapulseComponent->SetCapsuleHalfHeight(85.5f);

	IsAttacking = false;

	MaxCombo = 4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("STCharacter"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);


	// mesh and animation
	USkeletalMeshComponent* SkeletaMeshComponent = GetMesh();
	SkeletaMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.f, 0.f));
	SkeletaMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Quinn(TEXT("/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin"));
	if (SKM_Quinn.Succeeded())
	{
		SkeletaMeshComponent->SetSkeletalMesh(SKM_Quinn.Object);
	}
	else
	{
		STLOG(Warning, TEXT("Not Exist skeletalmesh"));
	}


	SkeletaMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_WarriorAnim(TEXT("/Game/STPlayer/Animation/BP_WarriorAnim.BP_WarriorAnim_C"));
	if (BP_WarriorAnim.Succeeded())
	{
		SkeletaMeshComponent->SetAnimInstanceClass(BP_WarriorAnim.Class);
	}


	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;

	

	GetCharacterMovement()->JumpZVelocity = 800.0f;

	CharacterStat = CreateDefaultSubobject<USTCharacterStatComponent>(TEXT("CHARACTERSTAT"));

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HBBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());

	float HPBarOffsetY = 0.0f;
	{
		FBoxSphereBounds BoxSphereBound = SKM_Quinn.Object->GetBounds();
		HPBarOffsetY = BoxSphereBound.SphereRadius * 2.0f + 5.0f;
	}

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, HPBarOffsetY));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	// BluePrintClass
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}


	AIControllerClass = ASTAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	auto DefaultSetting = GetDefault<USTCharacterSetting>();
	if (DefaultSetting->CharacterAssets.Num() > 0)
	{
		for (auto CharacterAsset : DefaultSetting->CharacterAssets)
		{
			STLOG(Warning, TEXT("Character Asset : %s"), *CharacterAsset.ToString());
		}
	}


	AssetIndex = 4;
	SetActorHiddenInGame(true);
	HPBarWidget->SetHiddenInGame(true);
	SetCanBeDamaged(false);

	DeadTimer = 5.0f;

}

void ASTCharacter::SetCharacterState(ECharacterState NewState)
{
	STCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{
		if (bIsPlayer)
		{

			DisableInput(STPlayerController);

			STPlayerController->GetHUDWidget()->BindCharacterStat(CharacterStat);


			auto STPlayerState = Cast<ASTPlayerState>(GetPlayerState());
			STCHECK(STPlayerState != nullptr);
			CharacterStat->SetNewLevel(STPlayerState->GetCharacterLevel());
		}
		else
		{
			auto STGameMode = Cast<ASTGameMode>(GetWorld()->GetAuthGameMode());
			STCHECK(STGameMode != nullptr);
			int32 TargetLevel = FMath::CeilToInt(((float)STGameMode->GetScore() * 0.8f));

			int32 FinalLevel = FMath::Clamp<int32>(TargetLevel, 1, 20);
			STLOG(Warning, TEXT("New NPC Level : %d"), FinalLevel);
			CharacterStat->SetNewLevel(FinalLevel);
		}


		SetActorHiddenInGame(true);
		HPBarWidget->SetHiddenInGame(true);
		SetCanBeDamaged(false);
		break;
	}
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(false);
		SetCanBeDamaged(true);

		CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
			SetCharacterState(ECharacterState::DEAD);
			});

		auto CharacterWidget = Cast<USTCharacterWidget>(HPBarWidget->GetUserWidgetObject());
		STCHECK(CharacterWidget != nullptr);
		CharacterWidget->BindCharacterStat(CharacterStat);

		if (bIsPlayer)
		{
			SetControlMode(EControlMode::Orbit);
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
			EnableInput(STPlayerController);
		}
		else
		{
			SetControlMode(EControlMode::NPC);
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
			STAIController->RunAI();
		}


		break;
	}
	case ECharacterState::DEAD:
	{

		SetActorHiddenInGame(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		STAnim->SetDeadAnim();
		SetCanBeDamaged(false);

		if (bIsPlayer)
		{
			STPlayerController->ShowResultUI();

			//DisableInput(STPlayerController);
		}
		else
		{
			STAIController->StopAI();
		}

		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			if (bIsPlayer)
			{
				STPlayerController->RestartLevel();
			}
			else
			{
				Destroy();
			}
		}), DeadTimer, false);


		break;
	}
	default:
		break;
	}
}

ECharacterState ASTCharacter::GetCharacterState() const
{
	return CurrentState;
}

int32 ASTCharacter::GetExp() const
{
	return CharacterStat->GetDropExp();
}

float ASTCharacter::GetFinalAttackRange() const
{
	return (CurrentWeapon != nullptr) ? CurrentWeapon->GetAttackRange() : AttackRange;
}

float ASTCharacter::GetFinalAttackDamage() const
{
	float AttackDamage = (CurrentWeapon != nullptr) ? (CharacterStat->GetAttack() + CurrentWeapon->GetAttackDamage()) : CharacterStat->GetAttack();

	float AttackModifier = (CurrentWeapon != nullptr) ? (CurrentWeapon->GetAttackModifier()) : 1.0f;

	return AttackDamage *  AttackModifier;
}

// Called when the game starts or when spawned
void ASTCharacter::BeginPlay()
{
	Super::BeginPlay();

	//FName WeaponSocket(TEXT("hand_rSocket"));
	//auto CurWeapon = GetWorld()->SpawnActor<ASTWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	//if (CurWeapon != nullptr)
	//{
	//	CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	//}

	bIsPlayer = IsPlayerControlled();
	if (bIsPlayer)
	{
		STPlayerController = Cast<ASTPlayerController>(GetController());
		STCHECK(STPlayerController != nullptr);
	}
	else
	{
		STAIController = Cast<ASTAIController>(GetController());
		STCHECK(STAIController != nullptr);
	}

	auto DefaultSetting = GetDefault<USTCharacterSetting>();

	if (bIsPlayer)
	{
		auto STPlayerState = Cast<ASTPlayerState>(GetPlayerState());
		STCHECK(STPlayerState != nullptr);
		AssetIndex = STPlayerState->GetCharacterIndex();
	}
	else
	{
		AssetIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);		
	}

	CharacterAssetToLoad = DefaultSetting->CharacterAssets[AssetIndex];

	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	STCHECK(STGameInstance != nullptr);
	AssetStreamingHandle = STGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ASTCharacter::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);


	// 위젯 초기화 시점이 PostInitializeComponent => BeginPlay로 변경됨
	USTCharacterWidget* CharacterWidget = Cast<USTCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (CharacterWidget != nullptr)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
}

void ASTCharacter::SetControlMode(EControlMode ControlMode)
{
	//if (CurrentControlMode == ControlMode)
	//	return;

	CurrentControlMode = ControlMode;

	UCharacterMovementComponent* characterMovement = GetCharacterMovement();
	switch (ControlMode)
	{
	case EControlMode::Orbit :
	{
		//SpringArm->TargetArmLength = 450.0f;
		//SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 450.0f;

		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;

		characterMovement->bOrientRotationToMovement = true;
		characterMovement->bUseControllerDesiredRotation = true;
		characterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

		break;
	}
	case EControlMode::TopView:
	{
		//SpringArm->TargetArmLength = 800.0f;
		//SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);

		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;

		//bUseControllerRotationYaw = true;
		bUseControllerRotationYaw = false;
		characterMovement->bOrientRotationToMovement = false;
		characterMovement->bUseControllerDesiredRotation = true;
		characterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
	case EControlMode::NPC:
	{
		bUseControllerRotationYaw = false;
		characterMovement->bUseControllerDesiredRotation = false;
		characterMovement->bOrientRotationToMovement = true;
		characterMovement->RotationRate = FRotator(0.0f, 480.0f, 0.0f);		
		break;
	}
	case EControlMode::Shooter:
	{
		SpringArm->SetRelativeLocation(FVector(20, -40, 0));

		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = false;
		SpringArm->bDoCollisionTest = true;

		bUseControllerRotationYaw = true;

		characterMovement->bOrientRotationToMovement = true;
		characterMovement->bUseControllerDesiredRotation = true;
		characterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
	}
	
}

ASTCharacter::EControlMode ASTCharacter::GetControlMode() const
{
	return CurrentControlMode;
}

// Called every frame
void ASTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// camera blending
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	USTCharacterMovementComponent* STCharacterMovement =  Cast<USTCharacterMovementComponent>(GetCharacterMovement());
	STCHECK(STCharacterMovement != nullptr);
	FVector DirectionToMove = STCharacterMovement->GetDirectionToMove();

	switch (CurrentControlMode)
	{
	case ASTCharacter::EControlMode::TopView:
	{
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			FRotator NewRelativeRotation = FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed);
			SpringArm->SetRelativeRotation( NewRelativeRotation );

			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		}
		break;
	}
	}
}

void ASTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	STAnim = Cast<USTAnimInstance>(GetMesh()->GetAnimInstance());
	STCHECK(STAnim != nullptr);

	STAnim->OnMontageEnded.AddDynamic(this, &ASTCharacter::OnAttackMontageEnded);

	// 어택 명령=> IsComboInputOn(true)
	// 노티파이 발생 => check(IsComboInputOn) => Increment(CurrentCombo) => JumpSection
	STAnim->OnNextAttackCheck.AddLambda([this]()->void {
		STLOG(Warning, TEXT("OnNextAttackCheck"));
		CanNextCombo = false;

		if (IsComboInputOn)
		{
			AttackStartComboState();
			STAnim->SetNextAttackMontageSection(PrevCombo, CurrentCombo);
			//STAnim->JumpToAttackMontageSection(CurrentCombo);
		}
		});

	STAnim->OnAttackHitCheck.AddUObject(this, &ASTCharacter::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]()->void {
		STLOG(Warning, TEXT("OnHpIsZero"));
		STAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});


}

// Called to bind functionality to input
void ASTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ASTCharacter::CanSetWeapon()
{
	return true;// CurrentWeapon == nullptr;
}

void ASTCharacter::SetWeapon(ASTWeapon* NewWeapon)
{
	STCHECK(NewWeapon != nullptr);

	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;//
	}


	FName WeaponSocket(TEXT("hand_rSocket"));
	if (NewWeapon != nullptr)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);//
		CurrentWeapon = NewWeapon;
	}
}

void ASTCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
}

float ASTCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	STLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	CharacterStat->SetDamage(FinalDamage);
	if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			auto STPlayerContorller = Cast<ASTPlayerController>(EventInstigator);
			STCHECK(STPlayerContorller != nullptr, 0.0f);
			STPlayerContorller->NPCKill(this);
		}
	}


	return FinalDamage;
}

void ASTCharacter::CameraMovement(const FVector2D& Value)
{
	switch (CurrentControlMode)
	{
	case ASTCharacter::EControlMode::Orbit:
	{
		AddControllerPitchInput(Value.Y);
		AddControllerYawInput(Value.X);
		break;
	}
	case ASTCharacter::EControlMode::TopView:
		break;
	default:
		break;
	}	
}

void ASTCharacter::ChangeViewMode()
{
	switch (CurrentControlMode)
	{
	case EControlMode::Orbit:
	{
		GetController()->SetControlRotation(GetActorRotation());
		break;
	}
	case EControlMode::TopView:
	{

		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		break;
	}
	}

	uint32 ControlModeI = static_cast<uint32>(CurrentControlMode);
	ControlModeI = (ControlModeI + 1) % static_cast<uint32>(EControlMode::ModeCount);
	SetControlMode(static_cast<EControlMode>(ControlModeI));

}

void ASTCharacter::JumpCallback()
{
	Jump();
}

void ASTCharacter::Attack()
{
	//STLOG_S(Warning);
	if (IsAttacking)
	{
		STCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		STCHECK(CurrentCombo == 0);
		AttackStartComboState();
		STAnim->PlayAttackMontage();
		STAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}



void ASTCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	STCHECK(IsAttacking);
	STCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();

	OnAttackEnd.Broadcast();
}

void ASTCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	STCHECK(FMath::IsWithinInclusive(CurrentCombo, 0, MaxCombo - 1));
	PrevCombo = CurrentCombo;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ASTCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void ASTCharacter::AttackCheck()
{
	float FinalAttackRange = GetFinalAttackRange();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult, GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params
		);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * FinalAttackRange;
	FVector CenterVec = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = FinalAttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(), CenterVec, HalfHeight, AttackRadius, CapsuleRot, DrawColor, false, DebugLifeTime);

#endif

	// Collision Channel 에서 필터링 되었으므로 여기선 데미지 이벤트만 호출해주면 된다.
	if (bResult)
	{
		if (AActor* Actor = HitResult.GetActor(); Actor != nullptr)
		{
			STLOG(Warning, TEXT("Hit Actor Name : %s"), *Actor->GetName());

			FDamageEvent DamageEvent;
			Actor->TakeDamage( GetFinalAttackDamage(), DamageEvent, GetController(), this);
		}
	}
}

void ASTCharacter::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset());
	AssetStreamingHandle.Reset();
	STCHECK(AssetLoaded != nullptr);
	//GetMesh()->SetSkeletalMesh(AssetLoaded);

	SetCharacterState(ECharacterState::READY);

}

