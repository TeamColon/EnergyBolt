// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CombatInterface.h"
#include "EnergySpawner.generated.h"

class UArrowComponent;

UCLASS()
class ENERGYBOLT_API AEnergySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnergySpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnSelectedActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ActorsArray;
	
};
