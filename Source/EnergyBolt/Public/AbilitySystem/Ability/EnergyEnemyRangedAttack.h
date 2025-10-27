// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/EnergyEnemyDamageAbility.h"
#include "EnergyEnemyRangedAttack.generated.h"

class AEnergyEnemyProjectile;
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyEnemyRangedAttack : public UEnergyEnemyDamageAbility
{
	GENERATED_BODY()


protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AEnergyEnemyProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation, AActor* HomingTarget);

	UFUNCTION(BlueprintCallable)
	void SpawnProjectileMultiTimes(const FVector& TargetLocation, AActor* HomingTarget);

	UPROPERTY(EditDefaultsOnly)
	int32 Times;
	
	UPROPERTY(EditDefaultsOnly)
	float MinHomingAcceleration = 1500.f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHomingAcceleration = 3000.f;

	UPROPERTY(EditDefaultsOnly)
	float MinYawOffset = -15.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxYawOffset = 15.f;

	UPROPERTY(EditDefaultsOnly)
	float MinPitchOffset = -15.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxPitchOffset = 15.f;

	UPROPERTY(EditDefaultsOnly)
	bool bIsHoming = false;
};
