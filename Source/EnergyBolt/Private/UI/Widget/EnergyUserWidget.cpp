﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/EnergyUserWidget.h"


void UEnergyUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
