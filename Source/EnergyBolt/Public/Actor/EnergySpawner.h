// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CombatInterface.h"
#include "EnergySpawner.generated.h"

class AEnergyEnemyCharacter;
class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, AEnergyEnemyCharacter*, EnemyCharacter);

UCLASS()
class ENERGYBOLT_API AEnergySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnergySpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnSelectedActor();

	UPROPERTY()
	FOnEnemySpawned OnEnemySpawned;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ActorsArray;

	UPROPERTY(EditAnywhere, Category="Effects")
	TObjectPtr<USoundBase> SpawnSound;
};
