// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnergyCharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

/**
 * 게임내에서 캐릭터의 클래스 지정,
 * 클래스를 지정하여 근접인지, 원거리인지 등등을 확인하기 위함
 * 현재는 Enemy를 위한 클래스만 생성, 추후 추가 가능
 */
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Melee,
	Ranged
};

// Data 구조체
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "CharacterClass")
	TSubclassOf<UGameplayEffect> Attributes;

	// 클래스 특징에 따라 기본적으로 있어야 하는 Ability MeleeAttack, RangedAttack 등등
	UPROPERTY(EditDefaultsOnly, Category="CharacterClass")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};


/**
 * 캐릭터의 클래스를 지정하고 GameplayEffect를 활용하여 DefaultAttribute를 초기화 하기 위한 데이터 클래스
 */
UCLASS()
class ENERGYBOLT_API UEnergyCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="CharacterClass")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInfo;

	// 모든 캐릭터들이 가지는 기본 Ability HitReact, Death 등등
	UPROPERTY(EditDefaultsOnly, Category="Character Default Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	
	// CharacterClassInfo[CharacterClass]를 통해 CharacterClass에 맞는 DefaultInfo 가져오기
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
};
