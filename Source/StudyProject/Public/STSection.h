// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/Actor.h"
#include "STSection.generated.h"

UCLASS()
class STUDYPROJECT_API ASTSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTSection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	enum class ESectionState :uint8
	{
		READY = 0,
		BATTLE,
		COMPLETE
	};

	void SetState(ESectionState NewState);
	ESectionState CurrentState = ESectionState::READY;

	void OperateGates(bool bOpen = true);

private:
	UPROPERTY(VisibleAnywhere, Category=Mesh, Meta=(AllowPrivateAccess=true))
	TArray<UStaticMeshComponent*> GateMeshes;

	UPROPERTY(VisibleAnywhere, Category=Trigger, Meta=(AllowPrivateAccess=true))
	TArray<UBoxComponent*> GateTriggers;

	UPROPERTY(VisibleAnywhere, Category=Mesh, Meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category=Trigger, Meta=(AllowPrivateAccess=true))
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category=State, Meta=(AllowPrivateAccess=true))
	bool bNoBattle;

};
