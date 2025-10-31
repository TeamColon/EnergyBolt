// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/EnergyDamageGameplayAbility.h"
#include "EnergyProjectile.generated.h"


class AEnergyBoltProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyProjectile : public UEnergyDamageGameplayAbility
{
	GENERATED_BODY()
protected:
	UEnergyProjectile();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AEnergyBoltProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FGameplayTag &InputTag);

	UFUNCTION()
	void ProjectileCalcRotation(const FGameplayTag &InputTag, FRotator& Rotation) const;

private:
	
};
