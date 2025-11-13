// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EnergyGameModeBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EngineUtils.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Actor/EnergyPortal.h"
#include "Actor/EnergySpawner.h"
#include "Character/EnergyEnemyCharacter.h"
#include "Character/EnergyPlayerCharacter.h"
#include "Data/EnergySaveGame.h"
#include "Kismet/GameplayStatics.h"

AEnergyGameModeBase::AEnergyGameModeBase()
{
	//LevelIndex = 0;
	//NextLevelIndex = 1;
}

void AEnergyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/**
	 *  World에 있는 <T>ActorIterator를 통해 반복
	 */
	for (TActorIterator<AEnergySpawner> It(GetWorld()); It; ++It)
	{
		AEnergySpawner* Spawner = *It;
		Spawner->OnEnemySpawned.AddDynamic(this, &ThisClass::RegisterEnemy);
	}
	for (TActorIterator<AEnergyPortal> It(GetWorld()); It; ++It)
	{
		AEnergyPortal* Portal = *It;
		Portal->OnPortalOverlap.AddDynamic(this, &ThisClass::TravelNextLevel);
	}
}

void AEnergyGameModeBase::SaveGameData()
{
	if (bool bSavedGameExist = UGameplayStatics::DoesSaveGameExist("Slot1", 0))
	{
		UGameplayStatics::DeleteGameInSlot("Slot1", 0);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Cyan, TEXT("Delete"));
		}
	}
	if (UEnergySaveGame* SaveGameInstance = Cast<UEnergySaveGame>
		(UGameplayStatics::CreateSaveGameObject(UEnergySaveGame::StaticClass())))
	{
		SaveGameInstance->SaveSlotName = TEXT("Slot1");
		SaveGameInstance->PlayerName = TEXT("Player1");
		SaveGameInstance->UserIndex = 0;
		SaveGameInstance->MapIndex = LevelIndex;
		SaveGameInstance->NextMapIndex = LevelIndex + 1;

		AEnergyPlayerCharacter* PlayerCharacter = Cast<AEnergyPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		if (PlayerCharacter)
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PlayerCharacter);
			
			SaveGameInstance->GASData.AttributesData = ASC->GetSet<UEnergyAttributeSet>()->GetPlayerCharacterGF();
		}
		
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	}
}

void AEnergyGameModeBase::TravelNextLevel()
{
	// Portal Overlap => Delegate => GameMode => 모든 몬스터 퇴치 확인, SaveGame, OpenLevel
	if (bIsStageCleared)
	{
		SaveGameData();
		if (!LevelArray.IsEmpty() && 0 <= NextLevelIndex && NextLevelIndex < LevelArray.Num())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelArray[NextLevelIndex]);
		}
	}
}


void AEnergyGameModeBase::RegisterEnemy(AEnergyEnemyCharacter* Enemy)
{
	check(IsValid(Enemy));
	
	EnemyList.Add(Enemy);
	Enemy->OnEnemyDied.AddDynamic(this, &ThisClass::RemoveEnemy);
	
}

void AEnergyGameModeBase::RemoveEnemy(AEnergyEnemyCharacter* Enemy)
{
	if (!Enemy) return;
	EnemyList.Remove(Enemy);
	if (EnemyList.IsEmpty())
	{
		bIsStageCleared = true;
		for (TActorIterator<AEnergyPortal> It(GetWorld()); It; ++It)
		{
			AEnergyPortal* Portal = *It;
			Portal->SetActorHiddenInGame(false);
		}
		// 상자 소환 시점
	}
}

