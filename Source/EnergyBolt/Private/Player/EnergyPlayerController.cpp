// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EnergyPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnergyGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/EnergyProjectile.h"

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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(AttackAction_Up, ETriggerEvent::Triggered, this, &ThisClass::Attack);
	EnhancedInputComponent->BindAction(AttackAction_Down, ETriggerEvent::Triggered, this, &ThisClass::Attack);
	EnhancedInputComponent->BindAction(AttackAction_Left, ETriggerEvent::Triggered, this, &ThisClass::Attack);
	EnhancedInputComponent->BindAction(AttackAction_Right, ETriggerEvent::Triggered, this, &ThisClass::Attack);
	
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


void AEnergyPlayerController::Attack(const FInputActionInstance& Instance)
{
	// Projectile 발사 코드 추가
	FVector Direction = FVector::ZeroVector;

	if (Instance.GetSourceAction() == AttackAction_Up)
		Direction = FVector(0, 1, 0);
	else if (Instance.GetSourceAction() == AttackAction_Down)
		Direction = FVector(0, -1, 0);
	else if (Instance.GetSourceAction() == AttackAction_Left)
		Direction = FVector(-1, 0, 0);
	else if (Instance.GetSourceAction() == AttackAction_Right)
		Direction = FVector(1, 0, 0);

	for (const FGameplayAbilitySpec& Spec : GetASC()->GetActivatableAbilities())
	{
		if (Spec.Ability && Spec.Ability->GetClass()->IsChildOf(UEnergyProjectile::StaticClass()))
		{
			GetASC()->TryActivateAbility(Spec.Handle);
			break;
		}
	}
}

UEnergyAbilitySystemComponent* AEnergyPlayerController::GetASC()
{
	if (EnergyAbilitySystemComponent == nullptr)
	{
		EnergyAbilitySystemComponent = Cast<UEnergyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	
	return EnergyAbilitySystemComponent;
}


