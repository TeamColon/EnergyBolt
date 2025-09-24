

#include "Character/EnergyEnemyCharacter.h"

#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AI/EnergyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AEnergyEnemyCharacter::AEnergyEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
}


void AEnergyEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(EnergyAbilitySystemComponent);
	EnergyAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AEnergyEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	EnergyAIController = Cast<AEnergyAIController>(NewController);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("AIControllerSet"));
	}
	EnergyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	EnergyAIController->RunBehaviorTree(BehaviorTree);
}



