// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/EnergyHUD.h"
#include "UI/Widget/EnergyUserWidget.h"


void AEnergyHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
