// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EnergyEnemyDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyEnemyDamageAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* Target);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
