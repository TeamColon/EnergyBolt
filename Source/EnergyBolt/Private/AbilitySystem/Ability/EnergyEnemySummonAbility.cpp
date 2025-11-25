// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnergyEnemySummonAbility.h"

#include "EnergyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"

/**
 * ActivateAbility는 블루프린트로 구현
 */
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


