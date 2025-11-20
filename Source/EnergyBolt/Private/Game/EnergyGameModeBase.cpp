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
		
	}
	if (UEnergySaveGame* SaveGameInstance = Cast<UEnergySaveGame>
		(UGameplayStatics::CreateSaveGameObject(UEnergySaveGame::StaticClass())))
	{
		SaveGameInstance->SaveSlotName = TEXT("Slot1");
		SaveGameInstance->PlayerName = TEXT("Player1");
		SaveGameInstance->UserIndex = 0;
		SaveGameInstance->MapIndex = LevelIndex;
		SaveGameInstance->NextMapIndex = NextLevelIndex;

		AEnergyPlayerCharacter* PlayerCharacter = Cast<AEnergyPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		if (PlayerCharacter)
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PlayerCharacter);
			const UEnergyAttributeSet* AS = ASC->GetSet<UEnergyAttributeSet>();
			
			TArray<FGameplayAttribute> ASArray;
			AS->GetAttributesFromSetClass(AS->GetClass(),ASArray);
			/**
			 * FGameplayAttribute는 TMap으로 저장할 수 없기 때문에
			 * TMap<FString, float> Attribute 이름과 수치를 저장.
			 * Attribute -> FString -> 저장 -> 불러오기 -> FString -> Attribute의 과정을 거치게 된다.
			 */
			TMap<FString, float> AttributeData;
			for (const FGameplayAttribute& Attribute : ASArray)
			{
				FString AttrName = Attribute.GetName();
				float Value = ASC->GetNumericAttribute(Attribute);
				AttributeData.Add(AttrName, Value);
			}
			SaveGameInstance->GASData.AttributeData = AttributeData;
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
			AEnergyPlayerCharacter* PlayerCharacter = Cast<AEnergyPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
			if (TravelSound && PlayerCharacter)
			{
				UGameplayStatics::PlaySoundAtLocation(this, TravelSound, PlayerCharacter->GetActorLocation(), FRotator::ZeroRotator);
			}
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
			Portal->StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			
		}
		// 상자 소환 시점
	}
}

