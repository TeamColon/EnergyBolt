// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/EnergyEffectActor.h"
#include "EnergySpawnActor.generated.h"

class UShopItemComponent;
class UNiagaraComponent;
class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ENERGYBOLT_API AEnergySpawnActor : public AEnergyEffectActor
{
	GENERATED_BODY()

public:
	AEnergySpawnActor();
	
	void Launch(FVector Dir, float Speed);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> NiagaraComp;*/

	UPROPERTY(VisibleAnywhere, Category = "SpawnActor")
	bool bSpawnActor = false;

protected:
	virtual void BeginPlay() override;

	void Land();

	FTimerHandle LandTimer;
};
