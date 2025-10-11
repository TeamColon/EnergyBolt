// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UAnimMontage;
/**
 * 
 */
class ENERGYBOLT_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation();

	// MotionWarping Update
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	// MotionWarping에 필요한 Target Setter, Getter
	// PlayMontage에 사용될 Montage를 가져오는 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetCombatTarget() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();
};
