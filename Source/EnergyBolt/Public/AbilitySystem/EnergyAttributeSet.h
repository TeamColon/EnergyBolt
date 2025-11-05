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

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

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
	FGameplayAttributeData BaseSpeed;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, BaseSpeed)				// 기본 이동 속도 (기본 : 600)

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FGameplayAttributeData SpeedMultiplier;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, SpeedMultiplier)		// 이동 속도 배율 (기본 : 1)

	/*
	 * Meta Attribute
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, IncomingDamage)
	

	/**
	 * Attack Stats (임시 / 변경가능)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, AttackPower)			// 기본 공격력 (기본 : 10)

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData DamageMultiplier;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, DamageMultiplier)		// 공격력 배율 (기본 : 1)

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData Range;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Range)					// 사거리 (기본 : 3)

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData FireRate;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, FireRate)				// 연사 배율 (최대 3.5)

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData ProjectileSpeed;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, ProjectileSpeed)		// 탄속 배율 (최대 2.0) // 아직 적용 X

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData ShotCount;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, ShotCount)				// 발사 되는 탄환 수 (기본 : 1)

	// Tag 방식 속성 부여 (추후 고려)
	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayTagContainer AttackEffects; // 예: Burn, Poison, Freeze

	/*
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Gold")
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, Gold)					// 상점 아이템 사는 돈
	

	/*UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, CriticalDamage)*/

	/*UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UEnergyAttributeSet, CriticalChance)*/

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
