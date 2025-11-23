// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/EnergyWidgetController.h"

#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Player/EnergyPlayerController.h"
#include "Player/EnergyPlayerState.h"

void UEnergyWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UEnergyWidgetController::BroadcastInitialValues()
{
	// OverlayWidgetController에서 함수가 실행됨.
}

void UEnergyWidgetController::BindCallbacksToDependencies()
{
	// OverlayWidgetController에서 함수가 실행됨.
}

AEnergyPlayerController* UEnergyWidgetController::GetEnergyPC()
{
	if (EnergyPlayerController == nullptr)
	{
		EnergyPlayerController = Cast<AEnergyPlayerController>(PlayerController);
	}
	return EnergyPlayerController;
}

AEnergyPlayerState* UEnergyWidgetController::GetEnergyPS()
{
	if (EnergyPlayerState == nullptr)
	{
		EnergyPlayerState = Cast<AEnergyPlayerState>(PlayerState);
	}
	return EnergyPlayerState;
}

UEnergyAbilitySystemComponent* UEnergyWidgetController::GetEnergyASC()
{
	if (EnergyAbilitySystemComponent == nullptr)
	{
		EnergyAbilitySystemComponent = Cast<UEnergyAbilitySystemComponent>(AbilitySystemComponent);
	}
	return EnergyAbilitySystemComponent;
}

UEnergyAttributeSet* UEnergyWidgetController::GetEnergyAS()
{
	if (EnergyAttributeSet == nullptr)
	{
		EnergyAttributeSet = Cast<UEnergyAttributeSet>(AttributeSet);
	}
	return EnergyAttributeSet;
}
