// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopItemComponent.generated.h"

class UAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ENERGYBOLT_API UShopItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShopItemComponent();

	// 상점 템인지 여부 true false
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shop")
	bool bIsShopItem;

	// 가격 (Gold)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shop")
	float Cost = 10.f;

protected:
	UFUNCTION(BlueprintCallable, Category="Shop")
	bool TryPurchase(AActor* Buyer);

public:
	// Called every frame
	UAbilitySystemComponent* GetASCFromActor(AActor* Buyer) const;
};
