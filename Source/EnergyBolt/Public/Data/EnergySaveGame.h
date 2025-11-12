// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EnergySaveGame.generated.h"

class UGameplayEffect;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FGameAbilitySystemData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayEffect>> AttributesData;
};

UCLASS()
class ENERGYBOLT_API UEnergySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UEnergySaveGame();
	
	UPROPERTY(VisibleAnywhere)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere)
	int32 MapIndex;

	UPROPERTY(VisibleAnywhere)
	int32 NextMapIndex;

	UPROPERTY()
	FGameAbilitySystemData GASData;
};
