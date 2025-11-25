// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EnergyEnemySummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyEnemySummonAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSummonLocations();

	UPROPERTY(EditDefaultsOnly, Category="Summon")
	int32 NumMinions = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="Summon")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category="Summon")
	float MinSummonDistance = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Summon")
	float MaxSummonDistance = 70.f;

	UPROPERTY(EditDefaultsOnly)
	float SummonSpread = 90.f;

	UFUNCTION(BlueprintPure)
	TSubclassOf<APawn> GetRandomClass();

	UPROPERTY(EditAnywhere)
	float SpawnDelay = 1.5f;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> SummonSound;

	UPROPERTY(EditAnywhere)
	FVector LocationPivot = FVector::ZeroVector;

};
