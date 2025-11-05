// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyChest.h"

#include "Actor/Item/EnergyEffectActor.h"
#include "Actor/Item/EnergySpawnActor.h"
#include "Data/ItemDataStruct.h"


// Sets default values
AEnergyChest::AEnergyChest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnergyChest::OpenTreasureChest()
{
	CheckAndSpawnLoot(SpawnGold, GoldDropChance); // 골드 70%
	CheckAndSpawnLoot(SpawnHealPotion, HealDropChance); // 회복포션 50%
	CheckAndSpawnLoot(GetRandomItemFromList(), ItemDropChance); // 아이템 10%
}

// 각 아이템 스폰 확률 검사 함수
void AEnergyChest::CheckAndSpawnLoot(TSubclassOf<AEnergySpawnActor> TargetActor, float Probability)
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
void AEnergyChest::SpawnLoot(bool bIsSpawn, TSubclassOf<AEnergySpawnActor> TargetActor)
{
	if (!bIsSpawn || !TargetActor) return;

	// 상자 기준 위치
	const FVector ChestLoc = GetActorLocation();
	FVector SpawnLoc = ChestLoc + FVector(0.f, 0.f, 100.f);

	// 이미 스폰된 아이템들의 위치 저장 (겹침 방지용)
	static TArray<FVector> PrevSpawnLocations;
	PrevSpawnLocations.RemoveAll([](const FVector& Loc) { return false; });

	const float MinDistance = 70.f;  // 아이템 간 최소 거리
	const int32 MaxRetry = 10;       // 위치 재시도 횟수 제한

	int32 RetryCount = 0;
	bool bFoundValidSpot = false;

	while (!bFoundValidSpot && RetryCount < MaxRetry)
	{
		// 랜덤 오프셋 생성
		FVector RandomOffset(
			FMath::RandRange(-100.f, 100.f),
			FMath::RandRange(-100.f, 100.f),
			FMath::RandRange(0.f, 30.f)
		);

		FVector TestLoc = ChestLoc + RandomOffset + FVector(0, 0, 100.f);

		// 기존 위치들과 최소 거리 확인
		bool bTooClose = false;
		for (const FVector& PrevLoc : PrevSpawnLocations)
		{
			if (FVector::Dist(PrevLoc, TestLoc) < MinDistance)
			{
				bTooClose = true;
				break;
			}
		}

		if (!bTooClose)
		{
			SpawnLoc = TestLoc;
			PrevSpawnLocations.Add(SpawnLoc);
			bFoundValidSpot = true;
			break;
		}

		RetryCount++;
	}

	// 랜덤 방향 (위쪽 대각선으로)
	FRotator RandomRot = FRotator(
		FMath::RandRange(50.f, 80.f),   // Pitch: 위로 쏘기
		FMath::RandRange(-90.f, 90.f),  // Yaw: 좌우 랜덤
		0.f
	);

	FVector LaunchDir = RandomRot.Vector();
	float Speed = FMath::RandRange(500.f, 700.f);

	// 실제 아이템 생성
	AEnergySpawnActor* Item = GetWorld()->SpawnActor<AEnergySpawnActor>(
		TargetActor,
		SpawnLoc,
		RandomRot
	);

	if (Item)
	{
		Item->Launch(LaunchDir, Speed);
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


