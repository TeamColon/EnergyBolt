// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyPortal.h"

#include "Character/EnergyPlayerCharacter.h"
#include "Game/EnergyGameModeBase.h"
#include "Kismet/GameplayStatics.h"


AEnergyPortal::AEnergyPortal()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEnergyPortal::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnStaticMeshOverlap);
	//StaticMesh->SetHiddenInGame(true);

	if (AEnergyGameModeBase* GameMode = Cast<AEnergyGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnStageCleared.AddDynamic(this, &ThisClass::SetIsStageCleared);
	}
	
}

void AEnergyPortal::SetIsStageCleared(const bool bIsCleared)
{
	bIsStageCleared = bIsCleared;
	if (bIsStageCleared)
	{
		//StaticMesh->SetHiddenInGame(false);
		// true이면 상자 소환?
	}
}


void AEnergyPortal::OnStaticMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// OtherActor
	if (bIsStageCleared)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap"));
		}
		// 포탈과 overlap되었을 때, 스테이지 클리어이면 다음 스테이지로 이동.
		if (Cast<AEnergyPlayerCharacter>(OtherActor))
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("OpenLevel"));
			}
			UGameplayStatics::OpenLevel(this, FName("TestMap1"));
			
		}
	}
	
}



