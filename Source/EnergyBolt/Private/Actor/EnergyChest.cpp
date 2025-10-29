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
	if (SpawnItems.Num() == 0) return;

	const float Roll = FMath::FRand();
	if (Roll > DropChance)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("No drop this time (%.2f > %.2f)"), Roll, DropChance);*/
		return;
	}
	
	int32 RandIndex = FMath::RandRange(0, SpawnItems.Num() - 1);
	TSubclassOf<AEnergySpawnActor> SelectedItemClass = SpawnItems[RandIndex];

	if (SelectedItemClass == nullptr) return;

	SpawnLoot(1, SelectedItemClass);
	
	// 골드 ??% / 체력 포션 ??% / 아이템 ??%
	// 골드 10~300 / 체력 포션 1~2개 / 아이템 1개 나온다 만다

	/*FVector SpawnLocation = GetActorLocation() + FVector(500.f, 500.f, 120.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;*/


	/*FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;*/

	/*AEnergyEffectActor* SpawnedItem = GetWorld()->SpawnActor<AEnergyEffectActor>(
		SelectedItemClass, SpawnLocation, SpawnRotation);*/

	/*if (SpawnedItem)
	{
		UE_LOG(LogTemp, Log, TEXT("Spawned item: %s"), *SpawnedItem->GetName());
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 2.0f, FColor::Green,
				FString::Printf(TEXT("[Chest] Spawned item: %s"), *SpawnedItem->GetName())
			);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnActor FAILED for index %d"), RandIndex);
	}*/
}

void AEnergyChest::SpawnLoot(int32 Count, TSubclassOf<AEnergySpawnActor> TargetActor)
{
	for (int32 i = 0; i < Count; ++i)
	{
		FVector SpawnLoc = GetActorLocation() + FVector(0, 0, 100.f);

		// 위를 기준으로 살짝 대각선으로 튕겨 나가게 랜덤 회전
		FRotator RandomRot = FRotator(
			FMath::RandRange(60.f, 100.f), // 위로 발사 각도
			FMath::RandRange(-90.f, 90.f), // 좌우 퍼짐
			0.f
		);

		FVector LaunchDir = RandomRot.Vector();
		float Speed = FMath::RandRange(500.f, 700.f);
		
		AEnergySpawnActor* Item = GetWorld()->SpawnActor<AEnergySpawnActor>(
			TargetActor,
			SpawnLoc,
			RandomRot
		);

		if (Item)
		{
			Item->Launch(LaunchDir, Speed);
			/*UE_LOG(LogTemp, Warning, TEXT("EnergyChest Item->Launch"));*/
		}
	}
}

