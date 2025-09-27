// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
}

void AEnergyPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 초기 액터 정보 부여
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AEnergyPlayerCharacter::InitAbilityActorInfo() const
{
	AEnergyPlayerState* EnergyPlayerState = GetPlayerState<AEnergyPlayerState>();
	check(EnergyPlayerState);		// Player State를 EnergyPlayerState로 해줘야 크러쉬가 안남.
	
	// HUD 시작하기
	if (AEnergyPlayerController* EnergyPlayerController = Cast<AEnergyPlayerController>(GetController()))
	{
		if (AEnergyHUD* EnergyHUD = Cast<AEnergyHUD>(EnergyPlayerController->GetHUD()))
		{
			EnergyHUD->InitOverlay(EnergyPlayerController, EnergyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

