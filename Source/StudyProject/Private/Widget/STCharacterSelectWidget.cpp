// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/STCharacterSelectWidget.h"
#include "STCharacterSetting.h" // for CharacterAsset List
#include "STGameInstance.h" // for FSTCharacterData
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "STSaveGame.h"
#include "STPlayerState.h"

void USTCharacterSelectWidget::NextCharacter(bool bForward /*= true*/)
{
	bForward ? CurrentIndex++: CurrentIndex--;

	if (CurrentIndex == -1) CurrentIndex = MaxIndex - 1;
	if (CurrentIndex == MaxIndex) CurrentIndex = 0;

	auto CharacterSetting = GetDefault<USTCharacterSetting>();
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];

	auto STGameInstance = GetWorld()->GetGameInstance<USTGameInstance>();
	STCHECK(STGameInstance != nullptr);
	STCHECK(TargetComponent.IsValid());

	USkeletalMesh* Asset = STGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	if (Asset != nullptr)
	{
		TargetComponent->SetSkeletalMesh(Asset);
	}
}

void USTCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CurrentIndex = 0;
	auto CharacterSetting = GetDefault<USTCharacterSetting>();
	MaxIndex = CharacterSetting->CharacterAssets.Num();

	for (TActorIterator<ASkeletalMeshActor> It(GetWorld()); It; ++It)
	{
		TargetComponent = It->GetSkeletalMeshComponent();
		break;
	}

	// Find Widget
	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	STCHECK(PrevButton != nullptr);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	STCHECK(NextButton != nullptr);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));
	STCHECK(TextBox != nullptr);

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	STCHECK(ConfirmButton != nullptr);

	// Bind Function to Widget
	PrevButton->OnClicked.AddDynamic(this, &USTCharacterSelectWidget::OnPrevClicked);

	NextButton->OnClicked.AddDynamic(this, &USTCharacterSelectWidget::OnNextClicked);

	ConfirmButton->OnClicked.AddDynamic(this, &USTCharacterSelectWidget::OnConfirmClicked);

	

}

void USTCharacterSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void USTCharacterSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void USTCharacterSelectWidget::OnConfirmClicked()
{
	FString CharacterName = TextBox->GetText().ToString();
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10)  return;

	USTSaveGame* NewPlayerData = NewObject<USTSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;

	auto STPlayerState = GetDefault<ASTPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, STPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"));
	}
	else
	{
		STLOG(Error, TEXT("SaveGame Error!"));
	}
}
