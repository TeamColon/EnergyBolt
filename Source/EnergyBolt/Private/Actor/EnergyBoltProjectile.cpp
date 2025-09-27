// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyBoltProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"


AEnergyBoltProjectile::AEnergyBoltProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->MaxSpeed = 1000.f;
	MovementComp->ProjectileGravityScale = 0.f;
}

void AEnergyBoltProjectile::InitProjectile()
{
	
}

