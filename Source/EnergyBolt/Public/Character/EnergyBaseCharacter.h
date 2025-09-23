// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnergyBaseCharacter.generated.h"

class UEnergyAttributeSet;
class UEnergyAbilitySystemComponent;

UCLASS()
class ENERGYBOLT_API AEnergyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnergyBaseCharacter();
	

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAbilitySystemComponent* EnergyAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAttributeSet* EnergyAttributeSet;

public:
	
	FORCEINLINE UEnergyAbilitySystemComponent* GetWarriorAbilitySystemComponent() const {return EnergyAbilitySystemComponent;}

	FORCEINLINE UEnergyAttributeSet* GetWarriorAttributeSet() const {return EnergyAttributeSet;}
	
};
