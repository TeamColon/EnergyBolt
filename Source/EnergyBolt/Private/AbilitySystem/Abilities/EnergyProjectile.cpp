// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EnergyProjectile.h"

UEnergyProjectile::UEnergyProjectile()
{
	// 인스턴스 1개 쭉 유지
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UEnergyProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 로직 작성 예정
}
