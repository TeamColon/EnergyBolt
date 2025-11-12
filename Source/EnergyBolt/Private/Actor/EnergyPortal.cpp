// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyPortal.h"

#include "NiagaraComponent.h"
#include "Character/EnergyPlayerCharacter.h"


AEnergyPortal::AEnergyPortal()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMesh);
	//StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Vortex = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Vortex"));
	Vortex->SetupAttachment(RootComponent);
	Vortex->bAutoActivate = false;
	
	Sparks1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sparks1"));
	Sparks1->SetupAttachment(Vortex);
	Sparks1->bAutoActivate = false;
	
	Sparks2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sparks2"));
	Sparks2->SetupAttachment(Vortex);
	Sparks2->bAutoActivate = false;
	
	Sparks3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sparks3"));
	Sparks3->SetupAttachment(Vortex);
	Sparks3->bAutoActivate = false;
	
}

void AEnergyPortal::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnStaticMeshOverlap);
	//StaticMesh->SetHiddenInGame(true);

	if (Vortex && Sparks1 && Sparks2 && Sparks3)
	{
		Vortex->Activate();
		Sparks1->Activate();
		Sparks2->Activate();
		Sparks3->Activate();
	}
	
}

void AEnergyPortal::OnStaticMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEnergyPlayerCharacter>(OtherActor))
	{
		OnPortalOverlap.Broadcast();
	}
	
}



