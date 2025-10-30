// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyPortal.h"


AEnergyPortal::AEnergyPortal()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

}


void AEnergyPortal::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnStaticMeshOverlap);
	
}

void AEnergyPortal::OnStaticMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// OtherActor

	
}

