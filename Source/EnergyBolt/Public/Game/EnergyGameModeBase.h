// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnergyGameModeBase.generated.h"

class AEnergyEnemyCharacter;
class UEnergyCharacterClassInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, AEnergyEnemyCharacter*, Enemy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDied, AEnergyEnemyCharacter*, Enemy);
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API AEnergyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="CharacterClassDefault")
	TObjectPtr<UEnergyCharacterClassInfo> CharacterClassInfo;

	UPROPERTY()
	TArray<AEnergyEnemyCharacter*> EnemyList;
	
	UFUNCTION()
	void RegisterEnemy(AEnergyEnemyCharacter* Enemy);

	UFUNCTION()
	void DeleteEnemy(AEnergyEnemyCharacter* Enemy);

	UPROPERTY()
	FOnEnemySpawned OnEnemySpawned;

	UPROPERTY()
	FOnEnemyDied OnEnemyDied;

protected:
	virtual void BeginPlay() override;
};
