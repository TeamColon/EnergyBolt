// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyActorBase.generated.h"

UCLASS()
class ENERGYBOLT_API AEnergyActorBase : public AActor
{
	GENERATED_BODY()

public:
	AEnergyActorBase();

protected:
	virtual void BeginPlay() override;

	void Launch(FVector Dir, float Speed);
};
