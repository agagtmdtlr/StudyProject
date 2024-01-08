// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/RotatingMovementComponent.h" // for RotateMovenetComponent
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class STUDYPROJECT_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)	
	TObjectPtr<UStaticMeshComponent> _body;
	//UStaticMeshComponent* _body;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> _water;
	//UStaticMeshComponent* _water;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPointLightComponent> _light;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UParticleSystemComponent> _splash;

	UPROPERTY(EditAnywhere, Category=ID)
	int32 _id;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent> _rotateMovement;

private:
	UPROPERTY(EditAnywhere, Category=Stat, Meta=(AllowPrivateAccess=true))
	float _rotateSpeed;
};
