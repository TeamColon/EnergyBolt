// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyEnemyCharacter.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"


AEnergyEnemyCharacter::AEnergyEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void AEnergyEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
}

void AEnergyEnemyCharacter::InitAbilityActorInfo()
{
	EnergyAbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UEnergyAbilitySystemComponent>(EnergyAbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}
