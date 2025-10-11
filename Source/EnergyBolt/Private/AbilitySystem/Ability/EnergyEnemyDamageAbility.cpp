// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnergyEnemyDamageAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UEnergyEnemyDamageAbility::CauseDamage(AActor* Target)
{
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*SpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target));
}
