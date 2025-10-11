// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnergyBlueprintFunctionLibrary.generated.h"

class UAbilitySystemComponent;
enum class ECharacterClass : uint8;
/**
 * 어느 클래스에서든지 사용할 수 있는 전역 함수들을 모아둔 클래스
 */
UCLASS()
class ENERGYBOLT_API UEnergyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="EnergyFunctionLibrary")
	static void InitializeDefaultAttribute(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="EnergyFunctionLibrary")	
	static void GiveStartupAbilities(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="EnergyFunctionLibrary")
	static void GetLivePlayersWithRadius(const UObject* WorldContextObject,
		TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

};
