// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"
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

	// Character Stats의 변화 감지 함수 바인딩 (배율만)
	if (GetAttributeSet() && GetAbilitySystemComponent())
	{
		EnergyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			GetAttributeSet()->GetSpeedMultiplierAttribute()).AddUObject(this, &AEnergyPlayerCharacter::OnSpeedMultiplierChanged);

		UpdateMovementSpeed();
	}
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
	InitializeDefaultAttributes(); // AttributeSet 값 설정 함수
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

