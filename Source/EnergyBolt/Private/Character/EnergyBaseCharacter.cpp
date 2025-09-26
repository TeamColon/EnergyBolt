// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyBaseCharacter.h"

#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"


AEnergyBaseCharacter::AEnergyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Energy ASC, Set
	/*EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("EnergyAbilitySystemComponent"));
	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("EnergyAttributeSet"));*/

	// 캐스팅만 Energy로 <U"Energy"AbilitySystemComponent>
	AbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("AttributeSet"));
}

void AEnergyBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{ 
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}

UAbilitySystemComponent* AEnergyBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

