// Fill out your copyright notice in the Description page of Project Settings.

#include "STGameMode.h"
#include "StudyProject/StudyProject.h"
#include "STCharacter.h"
#include "STPawn.h"
#include "STPlayerController.h"

ASTGameMode::ASTGameMode()
{
	//DefaultPawnClass = ASTPawn::StaticClass();
	DefaultPawnClass = ASTCharacter::StaticClass();
	PlayerControllerClass = ASTPlayerController::StaticClass();
}

void ASTGameMode::PostLogin(APlayerController* NewPlayer)
{
	ST_LOG(Warning, TEXT("PostLogin Begin"));
/*
* 
1. create player controller
2. create player pawn
3. possess controller to pawn
4. begin game
*/
	Super::PostLogin(NewPlayer);
	ST_LOG(Warning, TEXT("PostLogin Eng"));

	// BP Pawn Class Asset
	//static ConstructorHelpers::FClassFinder<APawn> bpPawnC(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (bpPawnC.Succeeded())
	//{
	//	DefaultPawnClass = bpPawnC.Class;
	//}
}



