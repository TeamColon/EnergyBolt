// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EnergyPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnergyGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/Ability/EnergyProjectile.h"
#include "Player/Input/EnergyInputComponent.h"

AEnergyPlayerController::AEnergyPlayerController()
{
}

void AEnergyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add Mapping Context to Subsystem
	check(MappingContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext, 0);
	
}

void AEnergyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// custom input comp
	// 엔진 에디터 -> Project Setting -> Input -> EnergyInputComponent로 변경.
	UEnergyInputComponent* EnergyInputComponent = CastChecked<UEnergyInputComponent>(InputComponent);
	
	EnergyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnergyInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AEnergyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	/*const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}*/
	
	// 카메라의 Rotation 가져오기
	FRotator CamRot = PlayerCameraManager->GetCameraRotation();

	// Pitch와 Roll은 필요 없음
	CamRot.Pitch = 0.f;
	CamRot.Roll  = 0.f;

	// 카메라 기준 Forward / Right 벡터 생성
	const FVector ForwardDirection = FRotationMatrix(CamRot).GetUnitAxis(EAxis::X);
	const FVector RightDirection   = FRotationMatrix(CamRot).GetUnitAxis(EAxis::Y);

	// 적용
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);	// 위, 아래
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);	// 왼, 오
	}
}

void AEnergyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AEnergyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AEnergyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UEnergyAbilitySystemComponent* AEnergyPlayerController::GetASC()
{
	if (EnergyAbilitySystemComponent == nullptr)
	{
		EnergyAbilitySystemComponent = Cast<UEnergyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	
	return EnergyAbilitySystemComponent;
}


