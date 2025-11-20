// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyItemBase.generated.h"

class UTextRenderComponent;
class UShopItemComponent;

UCLASS()
class ENERGYBOLT_API AEnergyItemBase : public AActor
{
	GENERATED_BODY()

public:
	AEnergyItemBase();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneRoot;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextRenderComponent> PriceText;*/

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UShopItemComponent* ShopItemComponent;
};
