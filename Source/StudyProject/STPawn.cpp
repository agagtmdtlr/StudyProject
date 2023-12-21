// Fill out your copyright notice in the Description page of Project Settings.

#include "STPawn.h"
#include "StudyProject/StudyProject.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

// Sets default values
ASTPawn::ASTPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	_movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = _capsule;
	_mesh->SetupAttachment(_capsule);
	_springArm->SetupAttachment(_capsule);
	_camera->SetupAttachment(_springArm);

	_capsule->SetCapsuleHalfHeight(88.0f);
	_capsule->SetCapsuleRadius(34.0f);

	{
		FVector location(0.0f, 0.0f, -88.0f);
		FRotator rotation(0.0f, -90.0f, 0.0f);
		_mesh->SetRelativeLocationAndRotation(location, rotation);
	}	

	{
		_springArm->TargetArmLength = 400.0f; // unit cm
		FRotator rotation(-15.0f, 0.0f, 0.0f);
		_springArm->SetRelativeRotation(rotation);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		_mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Move(TEXT("/Game/ThirdPerson/Input/Actions/IA_Move.IA_Move"));
	if (IA_Move.Succeeded())
	{
		MovementAction = IA_Move.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_StudProject(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/IMC_StudyProject.IMC_StudyProject"));
	if (IMC_StudProject.Succeeded())
	{
		MappingContext = IMC_StudProject.Object;
	}
	

	// p 163
	_mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_WarriorAnim( TEXT("/Game/CloseCombatAnimSet/Animations/InPlace/Locomotion/Run/BP_WarriorAnim.BP_WarriorAnim_C") );
	if (BP_WarriorAnim.Succeeded())
	{
		_mesh->SetAnimInstanceClass(BP_WarriorAnim.Class);
	}
}

// Called when the game starts or when spawned
void ASTPawn::BeginPlay()
{
	Super::BeginPlay();
	

}

void ASTPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	STLOG_S(Warning);
}

void ASTPawn::PossessedBy(AController* NewController)
{
	STLOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Called every frame
void ASTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent)
	{
		enhancedInputComponent->BindAction(MovementAction.Get(), ETriggerEvent::Triggered, this, &ASTPawn::ScrollMovement);
	}
}

void ASTPawn::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (Subsystem != nullptr)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void ASTPawn::ScrollMovement(const FInputActionValue& ActionValue)
{
	ST_LOG(Warning, TEXT("%f %f %f"), ActionValue[0], ActionValue[1], ActionValue[2]);

	AddMovementInput(GetActorForwardVector(), ActionValue[1]);
	AddMovementInput(GetActorRightVector(), ActionValue[0]);

}

