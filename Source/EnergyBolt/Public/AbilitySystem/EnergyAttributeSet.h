// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "EnergyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UEnergyAttributeSet();


	/**
	 * Character Stats
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Speed)
	

	/**
	 * Attack Stats
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Range")
	FGameplayAttributeData Range;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Range)

	UPROPERTY(BlueprintReadOnly, Category = "FireRate")
	FGameplayAttributeData FireRate;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, FireRate)

	UPROPERTY(BlueprintReadOnly, Category = "ProjectileSpeed")
	FGameplayAttributeData ProjectileSpeed;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, ProjectileSpeed)

	
};
