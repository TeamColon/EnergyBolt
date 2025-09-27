﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EnergyDamageGameplayAbility.h"
#include "EnergyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyProjectile : public UEnergyDamageGameplayAbility
{
	GENERATED_BODY()

public:
	UEnergyProjectile();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AEnergyBoltProjectile> ProjectileClass;
};
