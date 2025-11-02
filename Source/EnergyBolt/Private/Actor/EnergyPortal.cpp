// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyPortal.h"

#include "Character/EnergyPlayerCharacter.h"


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
	
}

void AEnergyPortal::OnStaticMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEnergyPlayerCharacter>(OtherActor))
	{
		OnPortalOverlap.Broadcast();
	}
	
}



