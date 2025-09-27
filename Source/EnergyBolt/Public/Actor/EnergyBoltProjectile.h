// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyBoltProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class ENERGYBOLT_API AEnergyBoltProjectile : public AActor
{
	GENERATED_BODY()

public:
	AEnergyBoltProjectile();

	void InitProjectile();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UProjectileMovementComponent* MovementComp;
};
