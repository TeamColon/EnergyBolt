// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Data/EnergyCharacterClassInfo.h"
#include "Game/EnergyGameModeBase.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EnergyPlayerState.h"
#include "UI/HUD/EnergyHUD.h"
#include "UI/WidgetController/EnergyWidgetController.h"

void UEnergyBlueprintFunctionLibrary::InitializeDefaultAttribute(const UObject* WorldContextObject, ECharacterClass CharacterClass,
                                                                 UAbilitySystemComponent* ASC)
{
	const AEnergyGameModeBase* EnergyGameMode = Cast<AEnergyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (EnergyGameMode == nullptr) return;

	// GameMode에 저장된 DataAsset => 캐릭터 클래스에 맞는 FCharacterClassDefaultInfo(Attributes, Ability 포함된) 구조체 가져오기
	//FCharacterClassDefaultInfo ClassInfo = EnergyGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	UEnergyCharacterClassInfo* CharacterClassInfo = EnergyGameMode->CharacterClassInfo;
	if (CharacterClassInfo == nullptr) return;

	for (const TSubclassOf<UGameplayEffect> AttributeClass : CharacterClassInfo->DefaultAttributes)
	{
		const FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(AttributeClass, 1.f, ContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	for (const TSubclassOf<UGameplayEffect> AttributesClass : DefaultInfo.Attributes)
	{
		const FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(AttributesClass, 1.f, ContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	
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

bool UEnergyBlueprintFunctionLibrary::IsNotFriend(const AActor* FirstActor, const AActor* SecondActor)
{
	const bool bBothArePlayer = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemy = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));

	return !(bBothArePlayer || bBothAreEnemy);
}

TArray<FRotator> UEnergyBlueprintFunctionLibrary::EvenlySpreadRotators(const FVector& ForwardVector,
	const FVector& Axis, float Spread, int32 NumRotators)
{
	TArray<FRotator> Rotators;
	
	const FVector LeftSpread = ForwardVector.RotateAngleAxis(-Spread / 2.f, Axis);
	if (NumRotators > 1)
	{
		const float DeltaSpread = Spread / (NumRotators - 1);
		for (int32 i = 0; i < NumRotators; i++)
		{
			const FVector Direction = LeftSpread.RotateAngleAxis(DeltaSpread * i, Axis);
			Rotators.Add(Direction.Rotation());
		}
	}
	else
	{
		Rotators.Add(ForwardVector.Rotation());
	}
	
	return Rotators;
}

TArray<FVector> UEnergyBlueprintFunctionLibrary::EvenlyRotatedVectors(const FVector& ForwardVector, const FVector& Axis,
	float Spread, int32 NumVectors)
{
	TArray<FVector> Vectors;
	
	const FVector LeftSpread = ForwardVector.RotateAngleAxis(-Spread / 2.f, Axis);
	if (NumVectors > 1)
	{
		const float DeltaSpread = Spread / (NumVectors - 1);
		for (int32 i = 0; i < NumVectors; i++)
		{
			const FVector Direction = LeftSpread.RotateAngleAxis(DeltaSpread * i, Axis);
			Vectors.Add(Direction);
		}
	}
	else
	{
		Vectors.Add(ForwardVector);
	}
	
	return Vectors;
}

