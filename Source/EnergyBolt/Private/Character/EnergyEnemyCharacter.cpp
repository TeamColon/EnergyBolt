// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyEnemyCharacter.h"

#include "InterchangeResult.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"


AEnergyEnemyCharacter::AEnergyEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnergyEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AEnergyEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(!EnergyAbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy ASC is NULL!"));
	}
	if(!EnergyAttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy AS is NULL!"));
	}
	
	InitAbilityActorInfo();
}

void AEnergyEnemyCharacter::InitAbilityActorInfo()
{
	EnergyAbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UEnergyAbilitySystemComponent>(EnergyAbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}
