// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EnergyPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnergyGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/EnergyProjectile.h"
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
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


/*void AEnergyPlayerController::Attack(o)
{
	// Projectile 발사 코드 추가
	FVector Direction = FVector::ZeroVector;

	for (const FGameplayAbilitySpec& Spec : GetASC()->GetActivatableAbilities())
	{
		if (Spec.Ability && Spec.Ability->GetClass()->IsChildOf(UEnergyProjectile::StaticClass()))
		{
			GetASC()->TryActivateAbility(Spec.Handle);
			break;
		}
	}
}*/

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


