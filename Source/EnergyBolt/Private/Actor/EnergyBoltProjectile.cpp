// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyBoltProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnergyBolt/EnergyBolt.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AEnergyBoltProjectile::AEnergyBoltProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 2000.f;							// 최대 ProjectileSpeed = 2로 고정
	ProjectileMovement->ProjectileGravityScale = 0.f;				// 중력 부여 X
}

// Damage, Shot speed, Range 설정 함수
void AEnergyBoltProjectile::InitializeProjectile(float InDamage, float InSpeed, float InRange)
{
	DamageAmount = InDamage;
	ProjectileMovement->InitialSpeed = 1000.f * InSpeed;			// 1000 유닛/초 , ue5 -> 1 Unit = 1 cm
	Range = InRange;
}

void AEnergyBoltProjectile::EnableGravity()
{
	if (ProjectileMovement)
	{
		ProjectileMovement->ProjectileGravityScale = 1.0f; // 기본 중력 적용
	}
}

void AEnergyBoltProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 스폰 시점에 발사자(Instigator)를 Ignore
	/*AActor* MyInstigator = GetInstigator();
	if (MyInstigator)
	{
		Sphere->IgnoreActorWhenMoving(MyInstigator, true);
	}*/
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEnergyBoltProjectile::OnSphereOverlap);
	/*LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());*/
	GetWorldTimerManager().SetTimer(GravityTimerHandle, this, &AEnergyBoltProjectile::EnableGravity, Range, false);
}

void AEnergyBoltProjectile::Destroyed()
{
	/*if (!bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		LoopingSoundComponent->Stop();
	}*/
	Super::Destroyed();
}

void AEnergyBoltProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	LoopingSoundComponent->Stop();*/

	if (OtherActor == GetInstigator()) return;

	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());

		UE_LOG(LogTemp, Warning, TEXT("Attacking!!"));
	}
	
	Destroy();
}

