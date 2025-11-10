// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "EnergyBoltProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class ENERGYBOLT_API AEnergyBoltProjectile : public AActor
{
	GENERATED_BODY()

public:
	AEnergyBoltProjectile();

	void InitializeProjectile(float InDamage, float InSpeed, float InRange);

	void EnableGravity();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))		// Spawn 시점에 값을 설정 가능
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

#pragma region AttackStats
	
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed = 0.f;	// 기본 1000 u/s * ProjectileSpeed

	UPROPERTY(EditDefaultsOnly)
	float Range = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float ShotCount = 1.f;

	/*UPROPERTY(VisibleDefaultsOnly)
	bool bIsBurning = false;

	속성을 부여하는 것으로 bIsBurning 같은걸 생각했는데 사실
	gameplayTag로 관리하는게 더 나은 방법이 된다.
	*/
	
#pragma endregion

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep, const
		FHitResult& SweepResult
		);

	/*UFUNCTION()
	void OnSphereHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
		);*/
	
private:
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 1.f;

	bool bHit = false;

	FTimerHandle GravityTimerHandle;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	// 추후 추가 (사운드, 임펙트 등등)
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
	
};
