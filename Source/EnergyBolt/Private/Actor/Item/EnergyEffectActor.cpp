// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/EnergyEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "BlueprintGameplayTagLibrary.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AEnergyEffectActor::AEnergyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetEnableGravity(false);

	// Sphere (플레이어 감지용)
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEnergyEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

// GAS Effect 적용 함수
void AEnergyEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	/*
	 * 적용 방법 1 (정석)
	 * 인터페이스 에서 가져오기
	 */
	
	/*IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target);
	if (ASCInterface)
	{
		ASCInterface->GetAbilitySystemComponent();
	}*/
	

	/*
	 * 적용 방법 2 (라이브러리 사용)
	 * gameplayStatic, kismetMath, StaticFunction 등등 해당 라이브러리에 익숙해지면 편하다.
	 */
	
	// UAbilitySystemBlueprintLibrary를 사용해 적용 대상 ASC 들고오기
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	
	check(GameplayEffectClass);

	// 적용 대상 EffectContext 들고오기
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	
	// 현재 액터를 효과의 'Sourceobject'로 등록하기
	EffectContextHandle.AddSourceObject(this);
	
	// 전달 받은 effect 클래스를 기반으로 EffectSpec 생성
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	// Target에게 Effect 적용
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}