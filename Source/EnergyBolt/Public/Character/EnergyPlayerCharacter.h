// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnergyBaseCharacter.h"
#include "EnergyPlayerCharacter.generated.h"

UCLASS()
class ENERGYBOLT_API AEnergyPlayerCharacter : public AEnergyBaseCharacter
{
	GENERATED_BODY()

public:
	AEnergyPlayerCharacter();

	
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

private:
	void InitAbilityActorInfo() const;


};
