// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "EnergyBaseCharacter.generated.h"

class UEnergyAttributeSet;
class UEnergyAbilitySystemComponent;

UCLASS()
class ENERGYBOLT_API AEnergyBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEnergyBaseCharacter();
	

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAbilitySystemComponent* EnergyAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAttributeSet* EnergyAttributeSet;
	
public:
	
	FORCEINLINE UEnergyAbilitySystemComponent* GetEnergyAbilitySystemComponent() const {return EnergyAbilitySystemComponent;}

	FORCEINLINE UEnergyAttributeSet* GetEnergyAttributeSet() const {return EnergyAttributeSet;}
	
};
