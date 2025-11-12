// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnergyProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnergyBlueprintFunctionLibrary.h"
#include "EnergyGameplayTags.h"
#include "AbilitySystem/EnergyAttributeSet.h"
#include "Actor/EnergyBoltProjectile.h"
#include "Interface/CombatInterface.h"

UEnergyProjectile::UEnergyProjectile()
{
	// 인스턴스 1개 쭉 유지
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UEnergyProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 일단 유지
}

void UEnergyProjectile::SpawnProjectile(const FGameplayTag &InputTag)
{
	// Socket 얻기 위해서 사용
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface) return;
	{
		const FVector SocketLocation = CombatInterface->Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());

		// Rotation 관련
		// FRotator Rotation = GetAvatarActorFromActorInfo()->GetActorRotation(); // 캐릭터 기준 방향
		FRotator BaseRotation = FRotator::ZeroRotator; // world 상 방향으로 초기화 시켜두기
		ProjectileCalcRotation(InputTag, BaseRotation);

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		if (!SourceASC) return;

		const float ShotCountValue = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetShotCountAttribute());
		const int32 ShotCount = FMath::Max(1, FMath::RoundToInt(ShotCountValue));

		if (ShotCount > 1)
		{
			SpawnMultipleProjectiles(SocketLocation, BaseRotation, ShotCount, SourceASC);
		}
		else
		{
			SpawnSingleProjectile(SocketLocation, BaseRotation, SourceASC);
		}
		
		/*FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		AEnergyBoltProjectile* Projectile = GetWorld()->SpawnActorDeferred<AEnergyBoltProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		Projectile->DamageEffectSpecHandle = SpecHandle;

		const float Damage = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetAttackPowerAttribute());
		const float Speed = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetProjectileSpeedAttribute());
		const float Range = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetRangeAttribute());
		const float DamageMultipler = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetDamageMultiplierAttribute());
		const float ShotCountValue = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetShotCountAttribute());
		const int32 NumProjectiles = FMath::Max(1, FMath::RoundToInt(ShotCountValue));
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, EnergyGameplayTags::Player_Attack_Power, Damage * DamageMultipler);

		// Projectile에 세팅
		Projectile->InitializeProjectile(Damage, Speed, Range);
		
		Projectile->FinishSpawning(SpawnTransform);*/
	}
}

void UEnergyProjectile::SpawnSingleProjectile(const FVector& SocketLocation, const FRotator& Rotation,
	const UAbilitySystemComponent* SourceASC)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	AEnergyBoltProjectile* Projectile = GetWorld()->SpawnActorDeferred<AEnergyBoltProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	const float Damage = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetAttackPowerAttribute());
	const float Multiplier = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetDamageMultiplierAttribute());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, EnergyGameplayTags::Player_Attack_Power, Damage * Multiplier);

	const float Speed = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetShotSpeedAttribute());
	const float Range = SourceASC->GetNumericAttribute(UEnergyAttributeSet::GetRangeAttribute());

	Projectile->DamageEffectSpecHandle = SpecHandle;
	Projectile->InitializeProjectile(Damage, Speed, Range);
	Projectile->FinishSpawning(SpawnTransform);
}

void UEnergyProjectile::SpawnMultipleProjectiles(const FVector& SocketLocation, const FRotator& BaseRotation,
	int32 ShotCount, const UAbilitySystemComponent* SourceASC)
{
	const float Spread = 10.f + (ShotCount - 1) * 1.5f; // 샷수가 많을수록 살짝 더 퍼지게
	const FVector Forward = BaseRotation.Vector();

	TArray<FRotator> Rotations = UEnergyBlueprintFunctionLibrary::EvenlySpreadRotators(
		Forward,
		FVector::UpVector,
		Spread,
		ShotCount
	);

	for (const FRotator& Rot : Rotations)
	{
		SpawnSingleProjectile(SocketLocation, Rot, SourceASC);
	}
}

// 방향키에 따라 그쪽 방향으로 쏘도록
void UEnergyProjectile::ProjectileCalcRotation(const FGameplayTag& InputTag, FRotator& Rotation) const
{
	// InputTag에 따라 회전 변경
	if (InputTag == EnergyGameplayTags::Player_Attack_Up)
	{
		Rotation.Yaw += 0.f;
	}
	else if (InputTag == EnergyGameplayTags::Player_Attack_Down)
	{
		Rotation.Yaw += 180.f;
	}
	else if (InputTag == EnergyGameplayTags::Player_Attack_Left)
	{
		Rotation.Yaw += -90.f;
	}
	else if (InputTag == EnergyGameplayTags::Player_Attack_Right)
	{
		Rotation.Yaw += 90.f;
	}

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	const FVector Velocity = AvatarActor->GetVelocity();
	if (!Velocity.IsNearlyZero())
	{
		const FVector MoveDir = Velocity.GetSafeNormal2D();
		const FVector AttackDir = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		// 내적(dot): 1이면 같은 방향, -1이면 반대 방향
		const float DirectionDot = FVector::DotProduct(MoveDir, AttackDir);

		// 같은 방향일 때만 보정 (0.3 이상일 때)
		if (DirectionDot > 0.3f)
		{
			const float MoveYaw = Velocity.Rotation().Yaw;
			const float Influence = 0.3f; // 보정 강도
			Rotation.Yaw = FMath::Lerp(Rotation.Yaw, MoveYaw, Influence);
		}
	}
}
