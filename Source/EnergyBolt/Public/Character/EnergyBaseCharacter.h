// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "EnergyBaseCharacter.generated.h"

class UEnergyAttributeSet;
class UEnergyAbilitySystemComponent;
class UAnimMontage;

UCLASS()
class ENERGYBOLT_API AEnergyBaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AEnergyBaseCharacter();

	//~ Begin ICombatInterface
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	//~ End ICombatInterface

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

	//~ Begin IAbilitySystemInterface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface.
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAbilitySystemComponent* EnergyAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAttributeSet* EnergyAttributeSet;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon; 

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
public:
	
	/*FORCEINLINE UEnergyAbilitySystemComponent* GetEnergyAbilitySystemComponent() const {return EnergyAbilitySystemComponent;}

	FORCEINLINE UEnergyAttributeSet* GetEnergyAttributeSet() const {return EnergyAttributeSet;}*/
	
};
