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


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	// 시전자
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	// 피격자
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class ENERGYBOLT_API UEnergyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UEnergyAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/**
	 * Character Stats (임시 / 변경가능)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Speed)
	

	/**
	 * Attack Stats (임시 / 변경가능)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData Range;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Range)

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData FireRate;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, FireRate)

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData ProjectileSpeed;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, ProjectileSpeed)

	// Tag 방식 속성 부여 (추후 고려)
	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayTagContainer AttackEffects; // 예: Burn, Poison, Freeze

	/*UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, CriticalDamage)*/

	/*UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, CriticalChance)*/

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
