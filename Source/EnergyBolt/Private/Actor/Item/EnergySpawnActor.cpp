// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/EnergySpawnActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AEnergySpawnActor::AEnergySpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(StaticMesh);
	
	/*NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(RootComponent);*/
	// 자동 활성화 비활성화 (원할 때 에디터나 코드에서 수동 활성)
	/*NiagaraComp->bAutoActivate = false;*/
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 1.0f; // 중력 적용
	ProjectileMovement->InitialSpeed = 800.f;
	ProjectileMovement->MaxSpeed = 800.f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bAutoActivate = false; // Launch() 호출 전까지 비활성화
}

void AEnergySpawnActor::BeginPlay()
{
	Super::BeginPlay();

	if (!bSpawnActor)
	{
		// 일반 아이템이라면 충돌 켜기
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AEnergySpawnActor::Land()
{
	// 투사체 이동 멈춤
	if (ProjectileMovement)
	{
		ProjectileMovement->StopMovementImmediately();
		ProjectileMovement->Deactivate();
	}

	// 착지 후 Sphere 오버랩 활성화
	if (Sphere)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	// 약간 위로 고정해서 바닥 관통 방지
	FVector FixedLoc = GetActorLocation();
	FixedLoc.Z += 2.f;
	SetActorLocation(FixedLoc);
}

void AEnergySpawnActor::Launch(FVector Dir, float Speed)
{
	if (ProjectileMovement && bSpawnActor)
	{
		ProjectileMovement->Velocity = Dir * Speed;
		ProjectileMovement->Activate(); // ProjectileMovement 작동 시작

		// 일정 시간 후 착지 처리 타이머 시작
		GetWorldTimerManager().SetTimer(LandTimer, this, &AEnergySpawnActor::Land, 2.f, false);
	}
}
