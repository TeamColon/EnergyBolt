// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/EnergySpawnActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AEnergySpawnActor::AEnergySpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
	
	
	/*ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 1.0f;   // 중력 적용
	ProjectileMovement->bShouldBounce = true;            // 튀기는 효과
	ProjectileMovement->Bounciness = 0.3f;
	ProjectileMovement->Friction = 0.5f;
	
	// 핵심: ProjectileMovement가 SceneRoot를 실제로 움직이게 지정
	/*ProjectileMovement->UpdatedComponent = StaticMesh;*/
}

void AEnergySpawnActor::BeginPlay()
{
	Super::BeginPlay();

	if (StaticMesh)
	{
		/*StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		StaticMesh->SetSimulatePhysics(true);
		StaticMesh->SetEnableGravity(true);*/
		
		StaticMesh->SetSimulatePhysics(true);
		StaticMesh->SetEnableGravity(true);
		StaticMesh->SetCollisionProfileName(TEXT("PhysicsActor")); 
	}

	if (Sphere)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		Sphere->SetupAttachment(StaticMesh);
	}
}

void AEnergySpawnActor::Launch(FVector Dir, float Speed)
{
	/*if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = Dir * Speed;
		UE_LOG(LogTemp, Display, TEXT("Launching ProjectileMovement"));
	}*/
	if (StaticMesh && StaticMesh->IsSimulatingPhysics())
	{
		StaticMesh->AddImpulse(Dir * Speed, NAME_None, true);
		UE_LOG(LogTemp, Warning, TEXT("Launch AddImpulse"));
	}
}

/*void AEnergySpawnActor::OnHitStop(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// 바닥이나 월드 스태틱에 닿았을 때만 멈추게
	if (OtherActor && OtherActor != this && OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		if (ProjectileMovement)
		{
			ProjectileMovement->StopMovementImmediately(); // 즉시 정지
			ProjectileMovement->Deactivate();              // 더 이상 업데이트 X
		}

		// 충돌 후 위치 정확히 바닥에 고정
		FVector NewLocation = GetActorLocation();
		NewLocation.Z += 2.f; // 살짝 띄워서 바닥 관통 방지
		SetActorLocation(NewLocation);
	}
}*/
