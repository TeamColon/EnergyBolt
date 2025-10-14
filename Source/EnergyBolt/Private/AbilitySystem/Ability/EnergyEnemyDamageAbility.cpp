// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnergyEnemyDamageAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnergyGameplayTags.h"

void UEnergyEnemyDamageAbility::CauseDamage(AActor* Target)
{
	/**
	 * Target에 대해 Damage를 발생시키는 함수
	 * EnergyAttributeSet::PostGameplayEffectExecute을 통해 CurrentHealth 값을 변경
	 */
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	
	// DamageAbility에서 Damage 수치를 설정하면 GameplayEffect의 태그를 통해 Damage를 설정할 수 있도록 구현
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, EnergyGameplayTags::Damage, Damage);
	
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*SpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target));
}
