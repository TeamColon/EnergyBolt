// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Data/EnergyCharacterClassInfo.h"
#include "Game/EnergyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UEnergyBlueprintFunctionLibrary::InitializeDefaultAttribute(const UObject* WorldContextObject, ECharacterClass CharacterClass,
	UAbilitySystemComponent* ASC)
{
	const AEnergyGameModeBase* EnergyGameMode = Cast<AEnergyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (EnergyGameMode == nullptr) return;

	// GameMode에 저장된 DataAsset => 캐릭터 클래스에 맞는 FCharacterClassDefaultInfo(Attributes, Ability 포함된) 구조체 가져오기
	FCharacterClassDefaultInfo ClassInfo = EnergyGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	const FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ClassInfo.Attributes, 1.f, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UEnergyBlueprintFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, ECharacterClass CharacterClass,
	UAbilitySystemComponent* ASC)
{
	// TODO: GameMode를 통해 CharacterClassInfo 가져오는 함수 만들기
	const AEnergyGameModeBase* EnergyGameMode = Cast<AEnergyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (EnergyGameMode == nullptr) return;
	UEnergyCharacterClassInfo* CharacterClassInfo = EnergyGameMode->CharacterClassInfo;
	if (CharacterClassInfo == nullptr) return;

	// 모든 클래스들이 가지는 Default Ability 부여
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->DefaultAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		ASC->GiveAbility(AbilitySpec);
	}

	// 게임 내 클래스에 따라 기본적으로 가지는 StartupAbility 부터여
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		ASC->GiveAbility(AbilitySpec);
	}
}
