// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyPortal.generated.h"

UCLASS()
class ENERGYBOLT_API AEnergyPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnergyPortal();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UFUNCTION()
	void SetIsStageCleared(bool bIsCleared);

	FORCEINLINE bool GetIsStageCleared() const {return bIsStageCleared;}
	
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStaticMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	bool bIsStageCleared = true;
};
