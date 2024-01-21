// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class ASTCharacterMovementComponent;


struct FInputActionValue;


DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class STUDYPROJECT_API ASTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTCharacter();
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;
	int32 GetExp() const;
	float GetFinalAttackRange() const;
	float GetFinalAttackDamage() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	enum class EControlMode : uint32
	{
		Orbit,
		TopView,
		NPC,
		ModeCount,
	};

	EControlMode GetControlMode() const;
protected:
	void SetControlMode(EControlMode ControlMode);
	EControlMode CurrentControlMode = EControlMode::Orbit;


	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

	// Relatived Weapon
	bool CanSetWeapon();
	void SetWeapon(class ASTWeapon* NewWeapon);

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	class ASTWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category=Stat)
	class USTCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	// Called Event
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;	

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* Camera;

	UFUNCTION(BlueprintCallable)
	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

private:
	UFUNCTION(BlueprintCallable)
	void CameraMovement(const FVector2D& Value);

	UFUNCTION(BlueprintCallable)
	void ChangeViewMode();
	
	UFUNCTION(BlueprintCallable)
	void JumpCallback();
	
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	void OnAssetLoadCompleted();


private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	int32 PrevCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class USTAnimInstance* STAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta=(AllowPrivateAccess =true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;


	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	int32 AssetIndex = 0;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category=State, Meta=(AllowPrivateAccess=true))
	ECharacterState CurrentState;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category=State, Meta=(AllowPrivateAccess=true))
	bool bIsPlayer;

	UPROPERTY()
	class ASTAIController* STAIController;

	UPROPERTY()
	class ASTPlayerController* STPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State, Meta=(AllowPrivateAccess=true))
	float DeadTimer;

	FTimerHandle DeadTimerHandle = { };

};
