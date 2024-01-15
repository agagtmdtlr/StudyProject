// Fill out your copyright notice in the Description page of Project Settings.

#include "STGameMode.h"
#include "StudyProject.h"
#include "STCharacter.h"
#include "STPawn.h"
#include "STPlayerController.h"
#include "STPlayerState.h"

ASTGameMode::ASTGameMode()
{
	//DefaultPawnClass = ASTPawn::StaticClass();
	DefaultPawnClass = ASTCharacter::StaticClass();
	PlayerControllerClass = ASTPlayerController::StaticClass();
	PlayerStateClass = ASTPlayerState::StaticClass();
}

void ASTGameMode::PostLogin(APlayerController* NewPlayer)
{
/*
* 
1. create player controller
2. create player pawn
3. possess controller to pawn
4. begin game
*/
	Super::PostLogin(NewPlayer);

	// BP Pawn Class Asset
	//static ConstructorHelpers::FClassFinder<APawn> bpPawnC(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (bpPawnC.Succeeded())
	//{
	//	DefaultPawnClass = bpPawnC.Class;
	//}

	auto STPlayerState = Cast<ASTPlayerState>(NewPlayer->PlayerState);
	STCHECK(STPlayerState != nullptr);
	STPlayerState->InitPlayerData();

}



