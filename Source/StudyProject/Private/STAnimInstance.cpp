// Fill out your copyright notice in the Description page of Project Settings.


#include "STAnimInstance.h"

USTAnimInstance::USTAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/STPlayer/Animation/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void USTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;


	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		if (UPawnMovementComponent* MovementComponent = Pawn->GetMovementComponent(); MovementComponent != nullptr)
		{
			IsInAir = MovementComponent->IsFalling();
		}

	}
}

void USTAnimInstance::PlayAttackMontage()
{
	STCHECK(!IsDead);
	constexpr float InPlayRate = 1.0f;
	Montage_Play(AttackMontage, InPlayRate);
}

void USTAnimInstance::SetNextAttackMontageSection(int32 PrevSection, int32 NextSection)
{
	STCHECK(!IsDead);

	STCHECK(Montage_IsPlaying(AttackMontage));

	Montage_SetNextSection(GetAttackMontageSectionName(PrevSection),GetAttackMontageSectionName(NextSection));
}

void USTAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	STCHECK(!IsDead);

	STCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

void USTAnimInstance::AnimNotify_AttackHitCheck()
{
	//STLOG_S(Warning);
	OnAttackHitCheck.Broadcast();
}

void USTAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName USTAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	STCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	FString SectionName( FString::Printf(TEXT("Attack%d"), Section) );
	STLOG(Warning, TEXT("Section Name : %s"), *SectionName);
	return FName(*SectionName);
}
