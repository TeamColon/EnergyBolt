// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/EnergyHUD.h"
#include "UI/Widget/EnergyUserWidget.h"
#include "UI/WidgetController/EnergyWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AEnergyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();		// Bind 설정
		
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AEnergyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UEnergyUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	// Overlay 초기 설정 실행 함수
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}