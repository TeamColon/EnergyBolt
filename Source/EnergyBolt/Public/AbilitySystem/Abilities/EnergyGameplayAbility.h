// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EnergyGameplayAbility.generated.h"


// Base GA 역할
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TArray<FGameplayTag> StartupInputTag;
};
