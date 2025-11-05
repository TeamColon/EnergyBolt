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
	
	void SpawnMultipleProjectiles(const FVector& SocketLocation, const FRotator& BaseRotation, int32 ShotCount, const UAbilitySystemComponent* SourceASC);
	void SpawnSingleProjectile(const FVector& SocketLocation, const FRotator& Rotation, const UAbilitySystemComponent* SourceASC);


	UFUNCTION()
	void ProjectileCalcRotation(const FGameplayTag &InputTag, FRotator& Rotation) const;

private:
	
};
