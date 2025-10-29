// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyEffectActor.generated.h"

class UProjectileMovementComponent;
class UGameplayEffect;

UCLASS(Blueprintable)
class ENERGYBOLT_API AEnergyEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AEnergyEffectActor();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
};
