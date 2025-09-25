// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnergyGameModeBase.generated.h"

class UEnergyCharacterClassInfo;
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API AEnergyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="CharacterClassDefault")
	TObjectPtr<UEnergyCharacterClassInfo> CharacterClassInfo;
	
};
