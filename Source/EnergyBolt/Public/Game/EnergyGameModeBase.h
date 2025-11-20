// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnergyGameModeBase.generated.h"

class AEnergyEnemyCharacter;
class UEnergyCharacterClassInfo;


/**
 * 
 */
UCLASS()
class ENERGYBOLT_API AEnergyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEnergyGameModeBase();
	
	UPROPERTY(EditDefaultsOnly, Category="CharacterClassDefault")
	TObjectPtr<UEnergyCharacterClassInfo> CharacterClassInfo;

	UPROPERTY()
	TArray<AEnergyEnemyCharacter*> EnemyList;
	
	UFUNCTION()
	void RegisterEnemy(AEnergyEnemyCharacter* Enemy);

	UFUNCTION()
	void RemoveEnemy(AEnergyEnemyCharacter* Enemy);
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> LevelArray;
	
	UPROPERTY()
	int32 LevelIndex;
	
	UPROPERTY()
	int32 NextLevelIndex;

	UFUNCTION()
	void SaveGameData();

	UFUNCTION()
	void TravelNextLevel();

	UPROPERTY()
	bool bIsStageCleared = false;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> TravelSound;
};
