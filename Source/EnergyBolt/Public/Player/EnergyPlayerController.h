// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "EnergyPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API AEnergyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEnergyPlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> AttackAction;

	void Move(const FInputActionValue& InputActionValue);
	void Attack(const FInputActionValue& InputActionValue);
};
