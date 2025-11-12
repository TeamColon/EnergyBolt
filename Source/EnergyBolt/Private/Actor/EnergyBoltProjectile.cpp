// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnergyBoltProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnergyBlueprintFunctionLibrary.h"
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
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
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
	LifeSpan = InRange * 0.7;
	/*Range = InRange;*/
}

void AEnergyBoltProjectile::EnableGravity()
{
	// 중력 활성화해서 바닥으로 떨어지도록 하기
	/*if (ProjectileMovement)
	{
		ProjectileMovement->ProjectileGravityScale = 1.0f; // 기본 중력 적용
	}*/
}

void AEnergyBoltProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	
	// 스폰 시점에 발사자(Instigator)를 Ignore
	AActor* MyInstigator = GetInstigator();
	if (MyInstigator)
	{
		Sphere->IgnoreActorWhenMoving(MyInstigator, true);
	}

	if (Sphere)
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEnergyBoltProjectile::OnSphereOverlap);
	}

	// projectile이 날아가는 동안 들릴 사운드 부착하기
	/*LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());*/
	/*GetWorldTimerManager().SetTimer(GravityTimerHandle, this, &AEnergyBoltProjectile::EnableGravity, Range, false);*/
}

void AEnergyBoltProjectile::Destroyed()
{
	// 충돌 처리 안됐으면 실행됨
	if (!bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		/*LoopingSoundComponent->Stop();*/
	}
	Super::Destroyed();
}

void AEnergyBoltProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌 즉시 이펙트 재생
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());

	
	if (OtherActor == GetInstigator()) return;
	
	if (!UEnergyBlueprintFunctionLibrary::IsNotFriend(GetOwner(),OtherActor)) return;
	
	// 데미지 적용
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
	}

	if (bHit) return;
	bHit = true;
	
	Destroy();
}
