// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Shooter.h"

#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h" 
#include "Engine/SkeletalMesh.h"


// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
	SkeletalMeshComp->SetRelativeRotation(FRotator(0.0f, -90.f, 0.f));
	SkeletalMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Shooter(TEXT("/Game/Characters/Heroes/Mannequin/Meshes/SKM_Quinn.SKM_Quinn"));
	if (SKM_Shooter.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(SKM_Shooter.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_AnimInst(TEXT("/Game/Characters/Heroes/Mannequin/Animations/ABP_Shooter_Base.ABP_Shooter_Base_C"));
	if (BP_AnimInst.Succeeded())
	{
		SkeletalMeshComp->SetAnimInstanceClass(BP_AnimInst.Class);
	}

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
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

}

