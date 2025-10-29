// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/EnergyEffectActor.h"
#include "EnergySpawnActor.generated.h"

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
	
	/*UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

protected:
	virtual void BeginPlay() override;

	/*virtual void OnHitStop(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);*/
	
};
