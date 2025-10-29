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

	// 상하 / 좌우 각각 랜덤 범위 내에서 더하고 빼게 되는데
	// 그냥 0~1 랜덤 돌려서 상 or 하 / 좌 or 우 만 설정하고 수치는 그대로 두는 것도 나쁘지 않을듯
	if (IsValid(HomingTarget) && bIsHoming)
	{
		/*const float YawOffset = FMath::RandRange(MinYawOffest, MaxYawOffset); // 상하
		const float PitchOffset = FMath::RandRange(MinPitchOffset, MaxPitchOffset); // 좌우*/

		int32 UpAndDown = FMath::RandRange(0, 1);
		int32 LeftAndRight = FMath::RandRange(0, 1);
		const float YawOffset = UpAndDown & 1 ? MinYawOffset : MaxYawOffset;
		const float PitchOffset = LeftAndRight & 1 ? MinPitchOffset : MaxYawOffset;
		
		Rotation.Yaw += YawOffset;
		Rotation.Pitch += PitchOffset;
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				FString::Printf(TEXT("Yaw: %f, Pitch: %f"), YawOffset, PitchOffset));
		}*/
	}
	
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

	Projectile->FinishSpawning(SpawnTransform);
	
	Projectile->ProjectileMovement->bIsHomingProjectile = false;
	Projectile->ProjectileMovement->ProjectileGravityScale = 0.f;
	Projectile->ProjectileMovement->Velocity = Rotation.Vector() * Projectile->ProjectileMovement->InitialSpeed;

	if (IsValid(HomingTarget)&& bIsHoming)
	{
		FTimerHandle HomingDelayTimer;
		const float HomingDelay = 0.3f;

		GetWorld()->GetTimerManager().SetTimer(HomingDelayTimer,
			[this, Projectile, HomingTarget](){
			if (IsValid(Projectile) && IsValid(HomingTarget))
			{
				Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
				Projectile->ProjectileMovement->bIsHomingProjectile = true;
				Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::RandRange(MinHomingAcceleration, MaxHomingAcceleration);
			}
		}, HomingDelay, false);
	}
	
}

void UEnergyEnemyRangedAttack::SpawnProjectileMultiTimes(const FVector& TargetLocation, AActor* HomingTarget)
{
	for (int32 i = 0; i < Times; i++)
	{
		SpawnProjectile(TargetLocation, HomingTarget);
	}
}
