// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnergyGameModeBase.generated.h"

class AEnergyEnemyCharacter;
class UEnergyCharacterClassInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageCleared, bool, bIsCleared);

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
	void RemoveEnemy(AEnergyEnemyCharacter* Enemy);

	UPROPERTY()
	FOnStageCleared OnStageCleared;

protected:
	virtual void BeginPlay() override;
};
