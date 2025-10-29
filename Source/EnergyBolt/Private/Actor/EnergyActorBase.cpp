// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyActorBase.h"


AEnergyActorBase::AEnergyActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnergyActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}