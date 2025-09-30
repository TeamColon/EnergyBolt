// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"


AEnergyBaseCharacter::AEnergyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Energy ASC, Set
	/*EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("EnergyAbilitySystemComponent"));
	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("EnergyAttributeSet"));*/

	// 캐스팅만 Energy로 <U"Energy"AbilitySystemComponent>
	EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("AttributeSet"));
}

void AEnergyBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (EnergyAbilitySystemComponent)
	{ 
		EnergyAbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}

UAbilitySystemComponent* AEnergyBaseCharacter::GetAbilitySystemComponent() const
{
	return EnergyAbilitySystemComponent;
}

FVector AEnergyBaseCharacter::GetCombatSocketLocation()
{
	check(GetMesh())
	
	return GetMesh()->GetSocketLocation(WeaponTipSocketName);
}

void AEnergyBaseCharacter::AddCharacterAbilities()
{
	// PlayerCharacter PossessedBy에서 호출됨.
	UEnergyAbilitySystemComponent* EnergyASC = CastChecked<UEnergyAbilitySystemComponent>(EnergyAbilitySystemComponent);

	EnergyASC->AddCharacterAbilities(StartupAbilities);
}
