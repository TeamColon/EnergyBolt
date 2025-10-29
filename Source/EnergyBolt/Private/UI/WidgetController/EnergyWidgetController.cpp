// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/EnergyWidgetController.h"

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
