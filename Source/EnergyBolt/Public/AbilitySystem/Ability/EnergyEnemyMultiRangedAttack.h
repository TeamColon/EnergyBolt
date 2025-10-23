// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/EnergyEnemyRangedAttack.h"
#include "EnergyEnemyMultiRangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyEnemyMultiRangedAttack : public UEnergyEnemyRangedAttack
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& TargetLocation, AActor* Target);

protected:

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpread = 90.f;

	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;

	UPROPERTY(EditDefaultsOnly)
	float MinHomingAcceleration = 1500.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxHomingAcceleration = 3000.f;
};
