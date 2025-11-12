// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnergyBaseCharacter.h"

#include "EnergyBlueprintFunctionLibrary.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "EnergyBolt/EnergyBolt.h"


AEnergyBaseCharacter::AEnergyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 캐스팅만 Energy로 <U"Energy"AbilitySystemComponent>
	EnergyAbilitySystemComponent = CreateDefaultSubobject<UEnergyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	EnergyAttributeSet = CreateDefaultSubobject<UEnergyAttributeSet>(TEXT("AttributeSet"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);							// overlap event cpp, bp 둘다 끄거나 켜줘야됨.
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

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

		// 추후 지우고 enemycharacter possessedby로 옮기기, classinfo data blueprint 에서 player 없애기
		// InitializeDefaultAttributes
		UEnergyBlueprintFunctionLibrary::InitializeDefaultAttribute(this, CharacterClass, EnergyAbilitySystemComponent);

		
	}
}

UAbilitySystemComponent* AEnergyBaseCharacter::GetAbilitySystemComponent() const
{
	return EnergyAbilitySystemComponent;
}

void AEnergyBaseCharacter::InitAbilityActorInfo()
{
}

FVector AEnergyBaseCharacter::GetCombatSocketLocation_Implementation()
{
	return IsValid(Weapon) ? Weapon->GetSocketLocation(WeaponTipSocketName) : GetMesh()->GetSocketLocation(FName("WeaponHandSocket"));
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

TArray<FTaggedMontage> AEnergyBaseCharacter::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UAnimMontage* AEnergyBaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

// Player branch
void AEnergyBaseCharacter::AddCharacterAbilities()
{
	// PlayerCharacter PossessedBy에서 호출됨.
	UEnergyAbilitySystemComponent* EnergyASC = CastChecked<UEnergyAbilitySystemComponent>(EnergyAbilitySystemComponent);

	EnergyASC->AddCharacterAbilities(StartupAbilities);
}
// 머지하고 코드 옮기기


/*
 * 이 부분이 Attribute 부여 부분이기 때문에
 * Character class info에 넣는 방식으로 구현
 */
/*void AEnergyBaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
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
}*/
// Player branch
