// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyPortal.h"

#include "NiagaraComponent.h"
#include "Character/EnergyPlayerCharacter.h"
#include "Components/SpotLightComponent.h"


AEnergyPortal::AEnergyPortal()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMesh);
	//StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->Intensity = 500000.f;
	SpotLightComponent->IntensityUnits = ELightUnits::Unitless;
	SpotLightComponent->LightColor =FColor(255,48, 0);
	SpotLightComponent->AttenuationRadius = 2000.f;
	SpotLightComponent->InnerConeAngle = 25.f;
	SpotLightComponent->OuterConeAngle = 80.f;
	SpotLightComponent->SourceRadius = 2000.f;
	SpotLightComponent->SoftSourceRadius = 2000.f;
	SpotLightComponent->SourceLength = 0.f;
	SpotLightComponent->CastShadows = true;
	SpotLightComponent->VolumetricScatteringIntensity = 0.f;
	
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLightComponent->SetupAttachment(RootComponent);

	PointLightComponent->Intensity = 75.f;
	PointLightComponent->IntensityUnits = ELightUnits::Candelas;
	PointLightComponent->LightColor = FColor(255,48,0);
	PointLightComponent->AttenuationRadius = 2000.f;
	PointLightComponent->SourceRadius = 2000.f;
	PointLightComponent->SoftSourceRadius = 2000.f;
	PointLightComponent->SourceLength = 0.f;
	PointLightComponent->CastShadows = false;
	PointLightComponent->VolumetricScatteringIntensity = 0.f;

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

	Sparks4 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sparks4"));
	Sparks4->SetupAttachment(Vortex);
	Sparks4->bAutoActivate = false;
}

void AEnergyPortal::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
	
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnStaticMeshOverlap);
	
	if (Vortex && Sparks1 && Sparks2 && Sparks3)
	{
		Vortex->Activate();
		Sparks1->Activate();
		Sparks2->Activate();
		Sparks3->Activate();
		Sparks4->Activate();
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



