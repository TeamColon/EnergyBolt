// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EnergyHUD.generated.h"

class UEnergyUserWidget;
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API AEnergyHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UEnergyUserWidget>  OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEnergyUserWidget> OverlayWidgetClass;
};
