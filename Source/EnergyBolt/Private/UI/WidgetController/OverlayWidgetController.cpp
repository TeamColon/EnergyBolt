// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "EnergyGameplayTags.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Data/AttributeInfo.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UEnergyAttributeSet* EAS = CastChecked<UEnergyAttributeSet>(AttributeSet);

	check(AttributeInfo);

	// 기존 방식
	/*FEnergyAttributeInfoRow Info = AttributeInfo->FindAttributeInfoForTag(EnergyGameplayTags::Attributes_Attack_AttackPower);
	Info.AttributeValue = EAS->GetAttackPower();
	AttributeInfoDelegate.Broadcast(Info);*/

	// 자동화 방식
	for (auto& Pair : EAS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	// 초기 값 UI로 전달
	OnHealthChanged.Broadcast(EAS->GetCurrentHealth());
	OnMaxHealthChanged.Broadcast(EAS->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UEnergyAttributeSet* EAS = CastChecked<UEnergyAttributeSet>(AttributeSet);
	check(AttributeInfo);

	// 모든 공격 관련 Attribute 값이 변하면 자동으로 UI를 업데이트 하도록 델리게이트 등록
	for (auto& Pair : EAS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
	);
	}

	// "GetGameplayAttributeValueChangeDelegate" 사용
	// ASC 자체에서 제공하는 Attribute Change Delegate를 사용해서 값 변경 실시간으로 감지하게 만듦.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EAS->GetCurrentHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EAS->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}


void UOverlayWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FEnergyAttributeInfoRow Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}