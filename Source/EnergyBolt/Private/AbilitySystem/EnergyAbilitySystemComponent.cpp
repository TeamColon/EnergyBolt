// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/EnergyAbilitySystemComponent.h"

void UEnergyAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbility(AbilitySpec);					// ASC에 AbilitySpec을 등록만 함
		// GiveAbilityAndActivateOnce(AbilitySpec);	// Ability를 ASC에 등록하면서, 즉시 한 번 실행 (임시형)
	}
}
