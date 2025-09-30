// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/CombatInterface.h"
#include "EnergyBaseCharacter.generated.h"

class UGameplayAbility;
class UAttributeSet;
class UEnergyAttributeSet;
class UEnergyAbilitySystemComponent;

UCLASS()
class ENERGYBOLT_API AEnergyBaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AEnergyBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.

	//~ Begin ICombatInterface Interface.
	virtual FVector GetCombatSocketLocation() override;
	//~ End ICombatInterface Interface.
	
	UEnergyAttributeSet* GetAttributeSet() const {return EnergyAttributeSet;};

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.
	
	/*UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> EnergyAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> EnergyAttributeSet;*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAbilitySystemComponent* EnergyAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAttributeSet* EnergyAttributeSet;

	/*UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;*/		// 무기 있으면 그 Socket에 부착하기 위한 용도

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	void AddCharacterAbilities();
	
public:
	/*FORCEINLINE UEnergyAbilitySystemComponent* GetEnergyAbilitySystemComponent() const {return EnergyAbilitySystemComponent;}

	FORCEINLINE UEnergyAttributeSet* GetEnergyAttributeSet() const {return EnergyAttributeSet;}*/


private:

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
};

