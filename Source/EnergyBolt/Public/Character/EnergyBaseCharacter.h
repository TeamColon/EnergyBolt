// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Data/EnergyCharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "EnergyBaseCharacter.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UAttributeSet;
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
	virtual FVector GetCombatSocketLocation_Implementation() override;
	virtual void Die() override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	//~ End ICombatInterface

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<FTaggedMontage> AttackMontages;
	

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

	//~ Begin IAbilitySystemInterface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface.

	UEnergyAttributeSet* GetAttributeSet() const {return EnergyAttributeSet;};
	virtual void InitAbilityActorInfo();		// Player branch
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAbilitySystemComponent*  EnergyAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnergyAttributeSet* EnergyAttributeSet;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	bool bDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterClass CharacterClass = ECharacterClass::Melee;

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
};

