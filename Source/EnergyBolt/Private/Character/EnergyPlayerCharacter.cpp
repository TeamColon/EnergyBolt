// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
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

// Called when the game starts or when spawned
void AEnergyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnergyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnergyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

