// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Data/EnergyCharacterClassInfo.h"
#include "Game/EnergyGameModeBase.h"
#include "Interface/CombatInterface.h"
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
	// TODO: GameMode를 통해 CharacterClassInfo 가져오는 함수 만들기(현재 중복되는 라인이 많기 때문)
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

	// 게임 내 클래스에 따라 기본적으로 가지는 StartupAbility 부여
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		ASC->GiveAbility(AbilitySpec);
	}
}

void UEnergyBlueprintFunctionLibrary::GetLivePlayersWithRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
	const FVector& SphereOrigin)
{
	/**
	 * Origin을 중심으로 구를 생성하여 구 안의 원하는 Actor를 찾는 함수
	 * GameplayStatics::ApplyRadialDamageWithFalloff 내부의 초반 부분이 원하는 기능과 유사하게 동작하여 참고하여 작성함
	 * FCollisionQueryParams 참고
	 */

	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity,
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);

		for (FOverlapResult& Overlap : Overlaps)
		{
			// Implements<>() Returns true if this object implements the interface T, false otherwise
			if (const bool ImplementCombatInterface = Overlap.GetActor()->Implements<UCombatInterface>())
			{
				if (const bool IsAlive = !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
				{
					OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
				}
			}
			
		}
	}
}
