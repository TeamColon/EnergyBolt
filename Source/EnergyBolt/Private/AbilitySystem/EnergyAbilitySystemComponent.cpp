// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/EnergyAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/EnergyGameplayAbility.h"

void UEnergyAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UEnergyGameplayAbility* EnergyAbility = Cast<UEnergyGameplayAbility>(AbilitySpec.Ability))
		{
			// 여러 태그를 AbilitySpec에 추가
			// ex) 공격 어빌리티 = 4개 (위, 아래, 왼쪽, 오른쪽)
			for (const FGameplayTag& Tag : EnergyAbility->StartupInputTag)	
			{
				if (Tag.IsValid())
				{
					AbilitySpec.DynamicAbilityTags.AddTag(Tag);	// 런타임에 AbilitySpec에 Tag를 붙일 수 있음
				}
			}
	
			GiveAbility(AbilitySpec);						// ASC에 AbilitySpec을 등록만 함
			// GiveAbilityAndActivateOnce(AbilitySpec);		// Ability를 ASC에 등록하면서, 즉시 한 번 실행 (임시형)
		}
	}
}

void UEnergyAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// AbilitySpec이 해당 InputTag를 가지고 있다면
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);	// Pressed 상태 전달
			if (!AbilitySpec.IsActive())				// 아직 실행 중이 아니라면
			{
				TryActivateAbility(AbilitySpec.Handle);	// 실행 시도
			}
		}
	}
}

void UEnergyAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// AbilitySpec이 해당 InputTag를 가지고 있다면
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);	// Released 상태 전달
		}
	}
}
