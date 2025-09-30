// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyBaseCharacter.h"

#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"


AEnergyBaseCharacter::AEnergyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	
	EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("EnergyAbilitySystemComponent"));

	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("EnergyAttributeSet"));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
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

UAnimMontage* AEnergyBaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

