// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyBaseCharacter.h"

#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Components/CapsuleComponent.h"


AEnergyBaseCharacter::AEnergyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	
	EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("EnergyAbilitySystemComponent"));

	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("EnergyAttributeSet"));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AEnergyBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (EnergyAbilitySystemComponent)
	{ 
		EnergyAbilitySystemComponent->InitAbilityActorInfo(this,this);
		
	}
}

UAbilitySystemComponent* AEnergyBaseCharacter::GetAbilitySystemComponent() const
{
	return EnergyAbilitySystemComponent;
}

FVector AEnergyBaseCharacter::GetCombatSocketLocation_Implementation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AEnergyBaseCharacter::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bDead = true;
}

bool AEnergyBaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

AActor* AEnergyBaseCharacter::GetAvatar_Implementation()
{
	return this;
}

UAnimMontage* AEnergyBaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

