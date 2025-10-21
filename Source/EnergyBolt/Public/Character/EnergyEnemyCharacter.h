// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnergyBaseCharacter.h"
#include "EnergyEnemyCharacter.generated.h"

UCLASS()
class ENERGYBOLT_API AEnergyEnemyCharacter : public AEnergyBaseCharacter
{
	GENERATED_BODY()

public:
	AEnergyEnemyCharacter();

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
};
