// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Shooter.h"

#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h" 
#include "Engine/SkeletalMesh.h"
#include "GameFramework/SpringArmComponent.h"
#include "Component/STCharacterStatComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "STInputConfig.h"
#include "Actor/STGun.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
	SkeletalMeshComp->SetRelativeRotation(FRotator(0.0f, -90.f, 0.f));
	SkeletalMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Shooter(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn"));
	if (SKM_Shooter.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(SKM_Shooter.Object);
	}

	// Spring Arm and Cmamera
	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		//SpringArm->SetupAttachment(SkeletalMeshComp, FName(TEXT("upperarm_rSocket")));
		SpringArm->SetupAttachment(GetCapsuleComponent());


		SpringArm->TargetArmLength = 430.0;

		SpringArm->SetRelativeRotation(FRotator(-6.000000, 0, 0));
		SpringArm->TargetOffset = FVector(0, 40, 100);

		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(SpringArm);

		SpringArm->bUsePawnControlRotation = true;

		SpringArm->bInheritRoll = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;

		bUseControllerRotationYaw = true;


		UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
		MovementComponent->bOrientRotationToMovement = true;;
		MovementComponent->bUseControllerDesiredRotation = false;
		MovementComponent->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		

	}
	

	static ConstructorHelpers::FObjectFinder<USTInputConfig> IC_Shooter(TEXT(""));

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	CurrentWeapon = GetWorld()->SpawnActor<ASTGun>(ASTGun::StaticClass(), FTransform(), SpawnParameters);
	
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//if (EnhancedInputComponent != nullptr)
	//{
	//	FName ActionName;
	//	ETriggerEvent KeyEvent = ETriggerEvent::Triggered;
	//	UInputAction* InputAction;
	//	EnhancedInputComponent->BindAction(InputAction, KeyEvent, this, &AShooter::CharacterMovement,);
	//}
}

void AShooter::OnCharacterMovement(const FVector2D& MovementValue)
{
	FVector FowardVector = Camera->GetForwardVector();
	FVector RightVector = Camera->GetRightVector();

	GetCharacterMovement()->AddInputVector(FowardVector * MovementValue.Y);
	GetCharacterMovement()->AddInputVector(RightVector * MovementValue.X);
}

void AShooter::OnCameraMovement(const FVector2D& MovementValue)
{
	AddControllerPitchInput(MovementValue.Y * CameraPitchSpeed);
	AddControllerYawInput(MovementValue.X * CameraYawSpeed);
	
}

