// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EnergyGameModeBase.h"

#include "Character/EnergyEnemyCharacter.h"

void AEnergyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	OnEnemySpawned.AddDynamic(this, &ThisClass::RegisterEnemy);
}


void AEnergyGameModeBase::RegisterEnemy(AEnergyEnemyCharacter* Enemy)
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("%s Added"), *Enemy->GetName()));
	}*/
	EnemyList.Add(Enemy);
}

void AEnergyGameModeBase::DeleteEnemy(AEnergyEnemyCharacter* Enemy)
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("%s Deleted"), *Enemy->GetName()));
	}*/
	EnemyList.Remove(Enemy);
	if (EnemyList.IsEmpty())
	{
		// Portal 보이게 하기(스테이지 클리어 bool 변수 넘기기), chest 소환 
	}
}

