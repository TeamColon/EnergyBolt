// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyChest.h"

#include "Actor/Item/EnergySpawnActor.h"


// Sets default values
AEnergyChest::AEnergyChest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnergyChest::OpenTreasureChest()
{
	TArray<TPair<TSubclassOf<AEnergySpawnActor>, float>> LootList;
	LootList.Add({ SpawnHealPotion, HealDropChance });
	LootList.Add({ GetRandomItemFromList(), ItemDropChance });
	LootList.Add({ GetRandomItemFromList(), ItemDropChance });
	
	for (int32 i = 0; i < LootList.Num(); i++)
	{
		CheckAndSpawnLoot(LootList[i].Key, LootList[i].Value);
	}
}

// 각 아이템 스폰 확률 검사 함수
void AEnergyChest::CheckAndSpawnLoot(const TSubclassOf<AEnergySpawnActor>& TargetActor, const float Probability)
{
	if (TargetActor == nullptr) return;

	// 0.0 ~ 1.0 사이의 난수
	const float Roll = FMath::FRand();

	// 예: 확률이 0.7f면, 70% 확률로 스폰
	if (Roll <= Probability)
	{
		SpawnLoot(true, TargetActor);
	}
}

// 아이템 스폰 시키는 함수
void AEnergyChest::SpawnLoot(bool bIsSpawn, const TSubclassOf<AEnergySpawnActor>& TargetActor)
{
	UWorld* World = GetWorld();
	if (!World || World->bIsTearingDown)
	{
		return; // 현재 World가 아닐때 실행 취소
	}
	
	if (!bIsSpawn || !TargetActor)
	{
		return;
	}

	// 상자 기준 위치, z축 +100 에서 스폰
	const FVector ChestLoc = GetActorLocation();
	FVector SpawnLoc = ChestLoc + FVector(0.f, 0.f, 150.f);

	// 랜덤 방향 (위쪽 대각선으로)
	const FRotator ChestRot = GetActorRotation();
	float Pitch = FMath::RandRange(70.f, 80.f);
	float YawOffset;

	switch (SpawnItemCount)
	{
	case 0:
		YawOffset = 0.f;    // 정면
		break;
	case 1:
		YawOffset = -45.f;  // 왼쪽
		break;
	case 2:
		YawOffset = 45.f;   // 오른쪽
		break;
	default:
		YawOffset = 0.f;
		break;
	}

	FRotator FireRot = ChestRot + FRotator(Pitch, YawOffset, 0.f);
	const FVector LaunchDir = FireRot.Vector();
	float Speed = FMath::RandRange(500.f, 500.f);

	// 실제 아이템 생성
	AEnergySpawnActor* Item = GetWorld()->SpawnActor<AEnergySpawnActor>(
		TargetActor,
		SpawnLoc,
		FRotator::ZeroRotator
	);

	if (Item)
	{
		Item->Launch(LaunchDir, Speed);
		SpawnItemCount++;
	}
}

// 랜덤 아이템 선택
TSubclassOf<AEnergySpawnActor> AEnergyChest::GetRandomItemFromList()
{
	if (SpawnItems.Num() == 0)
	{
		return nullptr; // 아이템 리스트가 비어 있으면 nullptr 반환
	}

	int32 RandIndex = FMath::RandRange(0, SpawnItems.Num() - 1);
	return SpawnItems[RandIndex];
}


void AEnergyChest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 해당 액터와 관련된 타이머 삭제
	GetWorldTimerManager().ClearAllTimersForObject(this);
}

