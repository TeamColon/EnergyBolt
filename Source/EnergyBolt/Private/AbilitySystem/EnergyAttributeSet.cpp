// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/EnergyAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnergyGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"

UEnergyAttributeSet::UEnergyAttributeSet()
{
	// 일단 Overlay에 띄울 수치들만
	TagsToAttributes.Add(EnergyGameplayTags::Attributes_Player_SpeedMultiplier, GetSpeedMultiplierAttribute);
	TagsToAttributes.Add(EnergyGameplayTags::Attributes_Attack_AttackPower, GetAttackPowerAttribute);
	TagsToAttributes.Add(EnergyGameplayTags::Attributes_Attack_Range, GetRangeAttribute);
	TagsToAttributes.Add(EnergyGameplayTags::Attributes_Attack_FireRate, GetFireRateAttribute);
	TagsToAttributes.Add(EnergyGameplayTags::Attributes_Attack_ShotSpeed, GetShotSpeedAttribute);

	TagsToAttributes.Add(EnergyGameplayTags::Attributes_Player_Gold, GetGoldAttribute);
}

// GameplayEffect 또는 직접 코드로 Attribute를 변경하기 직전 호출
void UEnergyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}


void UEnergyAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	/* 태영
	 * GameplayEffect 실행 맥락을 정리해서 소스/타겟 정보를 쉽게 가져다 쓰기 위함
	 * Source = 시전자, Target = 피격자
	 */

	// FEffectProperties의 값들을 갱신하는 함수
	// 이후 사용할 때 nullptr이 아닌지 체크 필수
	// Target = Target of Effect (Owner of this AS) Source = Causer of the Effect

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get(); 
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UEnergyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	/**
	* Modifier가 적용되기 직전에 호출되는 델리게이트로 FGameplayEffectModCallbackData가 전달됨.
	* Data를 통해 GameplayEffect의 실제 적용 로직을 커스텀할 수 있다.
	*/
	
	// 방금 적용된 GameplayEffect로부터 얻을 수 있는 정보들 초기화
	FEffectProperties Props;
	SetEffectProperties(Data,Props);
	
	// Health가 음수가 되는 것을 방지
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetAvatarActor->GetName(), GetCurrentHealth());
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetCurrentHealth() - LocalIncomingDamage;
			SetCurrentHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			
			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
				{
					CombatInterface->Die();
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(EnergyGameplayTags::HitReact);
				// 매개변수로 들어온 태그를 가지고 있으면 해당 태그를 가진 능력을 활성화 시키는 함수
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
			
		}
	}
}


