// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnergyEnemyMultiRangedAttack.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnergyBlueprintFunctionLibrary.h"
#include "EnergyGameplayTags.h"
#include "Actor/EnergyEnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UEnergyEnemyMultiRangedAttack::SpawnProjectiles(const FVector& TargetLocation)
{
	// StartLocation = ActorLocation에서 위로 10.f 만큼 이동한 곳.
	const FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + FVector(0.f, 0.f, 0.f);
	FRotator Rotation = (TargetLocation - StartLocation).Rotation();
	Rotation.Pitch = 0.f;

	const FVector Forward = Rotation.Vector();
	
	TArray<FRotator> Rotations = UEnergyBlueprintFunctionLibrary::EvenlySpreadRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator& Rotator : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(StartLocation);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		AEnergyEnemyProjectile* Projectile = GetWorld()->SpawnActorDeferred<AEnergyEnemyProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
		
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.f, SourceASC->MakeEffectContext());

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, EnergyGameplayTags::Damage, Damage);
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
	
	// Debugging Projectiles Vectors
	/*for (FRotator& Rotator : Rotators)
	{
		UKismetSystemLibrary::DrawDebugArrow(
			GetAvatarActorFromActorInfo(),
			StartLocation,
			StartLocation + Rotator.Vector() * 100.f,
			1.f,
			FLinearColor::Blue,
			10,
			1.f
		);
	}*/
}
