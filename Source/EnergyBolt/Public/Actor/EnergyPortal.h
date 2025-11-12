// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyPortal.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPortalOverlap);

UCLASS()
class ENERGYBOLT_API AEnergyPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnergyPortal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	FOnPortalOverlap OnPortalOverlap;

	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStaticMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
#pragma region NiagaraComponent
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Vortex;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Sparks1;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Sparks2;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> Sparks3;
#pragma endregion
};
