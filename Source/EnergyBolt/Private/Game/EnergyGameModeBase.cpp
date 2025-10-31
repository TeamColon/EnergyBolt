// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EnergyGameModeBase.h"

#include "EngineUtils.h"
#include "Actor/EnergyPortal.h"
#include "Actor/EnergySpawner.h"
#include "Character/EnergyEnemyCharacter.h"

void AEnergyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/**
	 * 
	 */
	for (TActorIterator<AEnergySpawner> It(GetWorld()); It; ++It)
	{
		AEnergySpawner* Spawner = *It;
		Spawner->OnEnemySpawned.AddDynamic(this, &ThisClass::RegisterEnemy);
	}
}


void AEnergyGameModeBase::RegisterEnemy(AEnergyEnemyCharacter* Enemy)
{
	check(IsValid(Enemy));
	
	EnemyList.Add(Enemy);
	Enemy->OnEnemyDied.AddDynamic(this, &ThisClass::RemoveEnemy);
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
			FString::Printf(TEXT("%s Added"), *Enemy->GetName()));
	}*/
}

void AEnergyGameModeBase::RemoveEnemy(AEnergyEnemyCharacter* Enemy)
{
	if (!Enemy) return;
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
			FString::Printf(TEXT("%s Removed"), *Enemy->GetName()));
	}*/
	
	EnemyList.Remove(Enemy);
	if (EnemyList.IsEmpty())
	{
		OnStageCleared.Broadcast(EnemyList.IsEmpty());
	}
}

