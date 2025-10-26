// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnergyEnemyRangedAttack.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnergyGameplayTags.h"
#include "Actor/EnergyEnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/CombatInterface.h"

void UEnergyEnemyRangedAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UEnergyEnemyRangedAttack::SpawnProjectile(const FVector& TargetLocation, AActor* HomingTarget)
{
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());

	FRotator Rotation = (TargetLocation - SocketLocation).Rotation();
	// 아래에서 위로 발사하면 계속해서 대각선 위로 올라가게 되는 것을 방지
	Rotation.Pitch = 0.f;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	

	AEnergyEnemyProjectile* Projectile = GetWorld()->SpawnActorDeferred<AEnergyEnemyProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.f, SourceASC->MakeEffectContext());

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, EnergyGameplayTags::Damage, Damage);
	Projectile->DamageEffectSpecHandle = SpecHandle;

	if (IsValid(HomingTarget))
	{
		Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::RandRange(MinHomingAcceleration, MaxHomingAcceleration);
	}
	Projectile->ProjectileMovement->bIsHomingProjectile = bIsHoming;
	
	Projectile->FinishSpawning(SpawnTransform);
}
