// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "EnergyPlayerController.generated.h"

class UEnergyAbilitySystemComponent;
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
	TObjectPtr<UInputAction> AttackAction_Up;
	
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> AttackAction_Down;
	
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> AttackAction_Left;
	
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> AttackAction_Right;

	
	void Move(const FInputActionValue& InputActionValue);
	void Attack(const FInputActionInstance& Instance);

private:
	UPROPERTY()
	TObjectPtr<UEnergyAbilitySystemComponent> EnergyAbilitySystemComponent;
	
	UEnergyAbilitySystemComponent* GetASC();
};
