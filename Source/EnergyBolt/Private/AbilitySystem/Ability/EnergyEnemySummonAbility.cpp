// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnergyEnemySummonAbility.h"

#include "EnergyBlueprintFunctionLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"

TArray<FVector> UEnergyEnemySummonAbility::GetSummonLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();

	TArray<FVector> Directions = UEnergyBlueprintFunctionLibrary::EvenlyRotatedVectors(
		Forward,
		FVector::UpVector,
		SummonSpread,
		NumMinions
	);

	TArray<FVector> SummonLocations;
	for (FVector Direction : Directions)
	{
		const float Distance = FMath::RandRange(MinSummonDistance, MaxSummonDistance);
		FVector SummonLocation = Location + Direction * Distance;
		
		/*DrawDebugSphere(GetWorld(), SummonLocation, 30.f, 12, FColor::Cyan, false, 5.f);*/

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit,
			SummonLocation + FVector(0.f, 0.f, 500.f),
			SummonLocation - FVector(0.f, 0.f, 500.f),
			ECC_Visibility
		);

		if (Hit.bBlockingHit)
		{
			SummonLocation = Hit.ImpactPoint;
		}
		
		SummonLocations.Add(SummonLocation);
	}
	
	
	return SummonLocations;
}

TSubclassOf<APawn> UEnergyEnemySummonAbility::GetRandomClass()
{
	const int32 Index = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Index];
}

void UEnergyEnemySummonAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (MinionClasses.IsEmpty())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	TArray<FVector> SummonLocations = GetSummonLocations();
	Test::Shuffle(SummonLocations);
	
	TArray<FTimerHandle> ActiveSpawnTimers;
	for (int32 i = 0; i < SummonLocations.Num(); i++)
	{
		FVector Location = SummonLocations[i] + FVector(0.f, 0.f, 65.f);
		FRotator Rotation = GetAvatarActorFromActorInfo()->GetActorRotation();
		FTimerHandle TimerHandle;
		ActiveSpawnTimers.Add(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			[this, Location, Rotation]()
			{
				APawn* SpawnedMinion = GetWorld()->SpawnActor<APawn>(GetRandomClass(), Location, Rotation);
				if (SpawnedMinion) SpawnedMinion->SpawnDefaultController();
			},
			i * SpawnDelay,
			false
		);
		if (i == SummonLocations.Num() - 1) return;
	}
	
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
