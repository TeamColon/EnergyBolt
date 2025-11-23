// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Data/EnergySaveGame.h"
#include "Game/EnergyGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EnergyPlayerController.h"
#include "Player/EnergyPlayerState.h"
#include "UI/HUD/EnergyHUD.h"


AEnergyPlayerCharacter::AEnergyPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CharacterClass = ECharacterClass::Player;
}

void AEnergyPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 초기 액터 정보 부여
	InitAbilityActorInfo();				// ability overlay 부여
	AddCharacterAbilities();			// ability 부여

	// Character Stats의 변화 감지 함수 바인딩 (배율만)
	// ※추후 바인딩 해제도 고려해야됨. (맵 이동)
	if (GetAttributeSet() && GetAbilitySystemComponent())
	{
		EnergyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			GetAttributeSet()->GetSpeedMultiplierAttribute()).AddUObject(this, &AEnergyPlayerCharacter::OnSpeedMultiplierChanged);

		UpdateMovementSpeed();
	}

	bool bSavedGameExist = UGameplayStatics::DoesSaveGameExist("Slot1", 0);
	//UEnergySaveGame* SaveGameInstance = Cast<UEnergySaveGame>(UGameplayStatics::CreateSaveGameObject(UEnergySaveGame::StaticClass()));
	if (bSavedGameExist)
	{
		UGameplayStatics::AsyncLoadGameFromSlot(TEXT("Slot1"), 0,
			FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &ThisClass::OnGameLoaded));
	}
	else
	{
		if (AEnergyGameModeBase* GameMode = Cast<AEnergyGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			GameMode->LevelIndex = 0;
			GameMode->NextLevelIndex = 1;
		}
	}
}

void AEnergyPlayerCharacter::AddCharacterAbilities()
{
	// PlayerCharacter PossessedBy에서 호출됨.
	UEnergyAbilitySystemComponent* EnergyASC = CastChecked<UEnergyAbilitySystemComponent>(EnergyAbilitySystemComponent);

	EnergyASC->AddCharacterAbilities(StartupAbilities);
}

void AEnergyPlayerCharacter::InitAbilityActorInfo()
{
	AEnergyPlayerState* EnergyPlayerState = GetPlayerState<AEnergyPlayerState>();
	check(EnergyPlayerState);		// Player State를 EnergyPlayerState로 해줘야 크러쉬가 안남.
	
	Cast<UEnergyAbilitySystemComponent>(GetAbilitySystemComponent())->AbilityActorInfoSet();
	
	// HUD 시작하기
	if (AEnergyPlayerController* EnergyPlayerController = Cast<AEnergyPlayerController>(GetController()))
	{
		if (AEnergyHUD* EnergyHUD = Cast<AEnergyHUD>(EnergyPlayerController->GetHUD()))
		{
			EnergyHUD->InitOverlay(EnergyPlayerController, EnergyPlayerState, EnergyAbilitySystemComponent, EnergyAttributeSet);
		}
	}
	// InitializeDefaultAttributes(); // AttributeSet 값 설정 함수
}

void AEnergyPlayerCharacter::OnSpeedMultiplierChanged(const FOnAttributeChangeData& Data)
{
	UpdateMovementSpeed();
}

void AEnergyPlayerCharacter::UpdateMovementSpeed()
{
	if (EnergyAbilitySystemComponent && EnergyAttributeSet)
	{
		const float Base = EnergyAttributeSet->GetBaseSpeed();
		const float Multiplier = EnergyAttributeSet->GetSpeedMultiplier();
		const float FinalSpeed = Base * Multiplier;
		
		GetCharacterMovement()->MaxWalkSpeed = FinalSpeed;
		/*UE_LOG(LogTemp, Warning, TEXT("Speed Updated: Base=%.1f Mult=%.2f -> MaxWalkSpeed=%.1f"), 
			Base, Multiplier, FinalSpeed);*/
	}
}

void AEnergyPlayerCharacter::OnGameLoaded(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData) const
{
	const UEnergySaveGame* SaveGameData = Cast<UEnergySaveGame>(LoadedGameData);
	TMap<FString, float> AttributeDataMap =  SaveGameData->GASData.AttributeData;

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	UClass* ASClass = ASC->GetSet<UEnergyAttributeSet>()->GetClass();
	
	for (const TPair<FString, float>& Attr : AttributeDataMap)
	{
		const FString& AttrName = Attr.Key;
		const float Value = Attr.Value;
		
		FProperty* Prop = FindFProperty<FProperty>(ASClass, *AttrName);
		FGameplayAttribute GameplayAttribute(Prop);
		ASC->SetNumericAttributeBase(GameplayAttribute, Value);
	}
	
	if (AEnergyGameModeBase* GameMode = Cast<AEnergyGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->LevelIndex = SaveGameData->NextMapIndex;
		GameMode->NextLevelIndex = SaveGameData->NextMapIndex + 1;
	}
}
