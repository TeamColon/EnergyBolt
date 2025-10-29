// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/EnergyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UEnergyAttributeSet* EnergyAttributeSet = CastChecked<UEnergyAttributeSet>(AttributeSet);

	// 초기 Health 값 UI로 전달
	OnHealthChanged.Broadcast(EnergyAttributeSet->GetCurrentHealth());
	OnMaxHealthChanged.Broadcast(EnergyAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UEnergyAttributeSet* EnergyAttributeSet = CastChecked<UEnergyAttributeSet>(AttributeSet);

	// "GetGameplayAttributeValueChangeDelegate" 사용
	// ASC 자체에서 제공하는 Attribute Change Delegate를 사용해서 값 변경 실시간으로 감지하게 만듦.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EnergyAttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		EnergyAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
