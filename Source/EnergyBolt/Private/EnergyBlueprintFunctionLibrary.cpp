// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Data/EnergyCharacterClassInfo.h"
#include "Game/EnergyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UEnergyBlueprintFunctionLibrary::InitializeDefaultAttribute(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* ASC)
{
	AEnergyGameModeBase* EnergyGameMode = Cast<AEnergyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (EnergyGameMode == nullptr) return;
	
	FCharacterClassDefaultInfo ClassInfo = EnergyGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	const FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ClassInfo.Attributes, 1.f, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
