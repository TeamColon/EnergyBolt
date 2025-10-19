// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyBaseCharacter.h"

#include "EnergyBolt/EnergyBolt.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Components/CapsuleComponent.h"


AEnergyBaseCharacter::AEnergyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Energy ASC, Set
	/*EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("EnergyAbilitySystemComponent"));
	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("EnergyAttributeSet"));*/

	// 캐스팅만 Energy로 <U"Energy"AbilitySystemComponent>
	EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("AttributeSet"));

	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void AEnergyBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (EnergyAbilitySystemComponent)
	{ 
		EnergyAbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}

void AEnergyBaseCharacter::InitAbilityActorInfo()
{
}

UAbilitySystemComponent* AEnergyBaseCharacter::GetAbilitySystemComponent() const
{
	return EnergyAbilitySystemComponent;
}

FVector AEnergyBaseCharacter::GetCombatSocketLocation()
{
	check(GetMesh())
	
	return GetMesh()->GetSocketLocation(WeaponTipSocketName);
}

void AEnergyBaseCharacter::AddCharacterAbilities()
{
	// PlayerCharacter PossessedBy에서 호출됨.
	UEnergyAbilitySystemComponent* EnergyASC = CastChecked<UEnergyAbilitySystemComponent>(EnergyAbilitySystemComponent);

	EnergyASC->AddCharacterAbilities(StartupAbilities);
}

void AEnergyBaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AEnergyBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultCharacterAttributes, 1.f);
	ApplyEffectToSelf(DefaultAttackAttributes, 1.f);
}
