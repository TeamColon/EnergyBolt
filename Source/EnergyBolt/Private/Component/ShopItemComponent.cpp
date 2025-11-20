// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ShopItemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/EnergyAttributeSet.h"


UShopItemComponent::UShopItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UShopItemComponent::TryPurchase(AActor* Buyer)
{
	UAbilitySystemComponent* ASC = GetASCFromActor(Buyer);
	if (!ASC) return false;

	const FGameplayAttribute GoldAttr = UEnergyAttributeSet::GetGoldAttribute();
	const float CurrentGold = ASC->GetNumericAttribute(GoldAttr);

	if (CurrentGold < Cost)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough Gold. Need: %.1f, Have: %.1f"), Cost, CurrentGold);
		return false;
	}

	// gold 차감
	ASC->ApplyModToAttribute(GoldAttr, EGameplayModOp::Additive, -Cost);

	UE_LOG(LogTemp, Log, TEXT("Purchase Success! - Cost: %.1f, New Gold: %.1f"),
		   Cost,
		   ASC->GetNumericAttribute(GoldAttr));

	return true;
}

UAbilitySystemComponent* UShopItemComponent::GetASCFromActor(AActor* Buyer) const
{
	if (!Buyer) return nullptr;
	
	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Buyer);
}

