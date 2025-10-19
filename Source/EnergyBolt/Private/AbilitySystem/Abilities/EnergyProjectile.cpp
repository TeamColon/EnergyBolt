// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EnergyProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnergyGameplayTags.h"
#include "Actor/EnergyBoltProjectile.h"
#include "Interfaces/CombatInterface.h"

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
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		// Rotation 관련
		// FRotator Rotation = GetAvatarActorFromActorInfo()->GetActorRotation(); // 캐릭터 기준 방향
		FRotator Rotation = FRotator::ZeroRotator; // world 상 방향
		
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
		
		FTransform SpawnTransform;
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
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

