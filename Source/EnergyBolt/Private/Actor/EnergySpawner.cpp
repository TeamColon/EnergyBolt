// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergySpawner.h"

#include "Character/EnergyEnemyCharacter.h"
#include "Components/ArrowComponent.h"

AEnergySpawner::AEnergySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	ArrowComponent->SetHiddenInGame(true);
}

void AEnergySpawner::SpawnSelectedActor()
{
	if (ActorsArray.IsEmpty()) return;
	
	for (int32 i = 0; i < ActorsArray.Num(); i++)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator::ZeroRotator;
		if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorsArray[i], Location, Rotation))
		{
			if (AEnergyEnemyCharacter* Character = Cast<AEnergyEnemyCharacter>(SpawnedActor))
			{
				Character->SpawnDefaultController();
				OnEnemySpawned.Broadcast(Character);
			}
		}
	}
	
}

void AEnergySpawner::BeginPlay()
{
	Super::BeginPlay();
}


/**
		 * 몬스터 소환 시 바라보는 방향을 Spawner의 Rotation이 아닌 Target에 대해 바라보게 하려고 했으나
		 * SetCombatTarget이 BehaviorTree(PossessedBy) 이후 실행되기 때문에 GetCombatTarget이 nullptr 반환되는 것 같다.
		 */
/*FTransform SpawnTransform;
SpawnTransform.SetLocation(GetActorLocation());
SpawnTransform.SetRotation(FRotator::ZeroRotator.Quaternion());

AActor* SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(
	ActorsArray[i],
	SpawnTransform,
	nullptr,
	nullptr,
	ESpawnActorCollisionHandlingMethod::AlwaysSpawn
);

if (!SpawnedActor) return;
if (AEnergyBaseCharacter* Character = Cast<AEnergyBaseCharacter>(SpawnedActor))
{
	Character->SpawnDefaultController();

	if (AActor* Target = Character->Execute_GetCombatTarget(Character))
	{
		const FRotator CharacterRotation = (GetActorLocation() - Target->GetActorLocation()).Rotation();
		Character->SetActorRotation(CharacterRotation);
	}
	Character->FinishSpawning(SpawnTransform);
}
else
{
	SpawnedActor->FinishSpawning(SpawnTransform);
}*/

