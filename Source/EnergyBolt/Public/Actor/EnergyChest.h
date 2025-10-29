// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyChest.generated.h"

class AEnergySpawnActor;
struct FItemData;

UCLASS()
class ENERGYBOLT_API AEnergyChest : public AActor
{
	GENERATED_BODY()

public:
	AEnergyChest();

protected:
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	UDataTable* ItemDataTable; // 데이터 테이블로 하려다가 실패*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	TArray<TSubclassOf<AEnergySpawnActor>> SpawnItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	TArray<TSubclassOf<AEnergySpawnActor>> SpawnHealingPotion;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	TArray<TSubclassOf<AEnergySpawnActor>> SpawnCoin;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	float DropChance = 1.0f;
	

	UFUNCTION(BlueprintCallable)
	void OpenTreasureChest();

	void SpawnLoot(int32 Count, TSubclassOf<AEnergySpawnActor> TargetActor);
};
