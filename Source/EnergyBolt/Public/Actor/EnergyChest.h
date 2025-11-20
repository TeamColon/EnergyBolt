// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/EnergyItemBase.h"
#include "EnergyChest.generated.h"

class AEnergySpawnActor;
struct FItemData;

UCLASS()
class ENERGYBOLT_API AEnergyChest : public AEnergyItemBase
{
	GENERATED_BODY()

public:
	AEnergyChest();

	UFUNCTION(BlueprintCallable)
	void OpenTreasureChest();

protected:
	
	void CheckAndSpawnLoot(const TSubclassOf<AEnergySpawnActor>& TargetActor,const float Probability);
	void SpawnLoot(bool bIsSpawn, const TSubclassOf<AEnergySpawnActor>& TargetActor);
	TSubclassOf<AEnergySpawnActor> GetRandomItemFromList();
	
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	UDataTable* ItemDataTable; // 데이터 테이블로 하려다가 실패*/
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	TArray<TSubclassOf<AEnergySpawnActor>> SpawnItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	TSubclassOf<AEnergySpawnActor> SpawnHealPotion;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Treasure Chest")
	TSubclassOf<AEnergySpawnActor> SpawnGold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Drop Chance")
	float ItemDropChance = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Drop Chance")
	float HealDropChance = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Drop Chance")
	float GoldDropChance = 0.7f;

private:
	int32 SpawnItemCount = 0;
};
