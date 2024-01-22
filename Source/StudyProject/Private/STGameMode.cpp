// Fill out your copyright notice in the Description page of Project Settings.

#include "STGameMode.h"
#include "StudyProject.h"
#include "Actor/STCharacter.h"
#include "Actor/STPawn.h"
#include "Controller/STPlayerController.h"
#include "STPlayerState.h"
#include "STGameState.h"
#include "Engine/PawnIterator.h"

ASTGameMode::ASTGameMode()
{
	//DefaultPawnClass = ASTPawn::StaticClass();


	DefaultPawnClass = ASTCharacter::StaticClass();
	PlayerControllerClass = ASTPlayerController::StaticClass();
	PlayerStateClass = ASTPlayerState::StaticClass();
	GameStateClass = ASTGameState::StaticClass();

	ScoreToClear = 2;
}

void ASTGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	STGameState = Cast<ASTGameState>(GameState);
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

void ASTGameMode::AddScore(class ASTPlayerController* ScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto STPlayerController = Cast<ASTPlayerController>(It->Get());
		if ((STPlayerController != nullptr) && (ScoredPlayer == STPlayerController))
		{
			STPlayerController->AddGameScore();
			break;
		}
	}

	STGameState->AddGameScore();


	if (GetScore() >= ScoreToClear)
	{
		STGameState->SetGameCleared();

		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}


		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			const auto STPlayerController = Cast<ASTPlayerController>(It->Get());
			if (STPlayerController != nullptr )
			{
				STPlayerController->ShowResultUI();
			}
		}
	}


}

int32 ASTGameMode::GetScore() const
{
	return STGameState->GetTotalGameScore();
}

