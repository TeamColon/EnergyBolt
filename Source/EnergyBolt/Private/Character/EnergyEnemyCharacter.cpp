

#include "Character/EnergyEnemyCharacter.h"

#include "EnergyBlueprintFunctionLibrary.h"
#include "AbilitySystem/EnergyAbilitySystemComponent.h"
#include "AI/EnergyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnergyEnemyCharacter::AEnergyEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
}


void AEnergyEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnergyEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Initialize BehaviorTree, BlackBoard
	EnergyAIController = Cast<AEnergyAIController>(NewController);
	EnergyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	EnergyAIController->RunBehaviorTree(BehaviorTree);

	//InitializeDefaultAttributes();
	UEnergyBlueprintFunctionLibrary::InitializeDefaultAttribute(this, CharacterClass, EnergyAbilitySystemComponent);
}

/*
DataAsset을 통해 Class 지정, 속성 초기화 하면서 필요 없어진 함수
추후 삭제 고려
void AEnergyEnemyCharacter::InitializeDefaultAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultAttribute);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttribute, 1, ContextHandle);
	
	if (SpecHandle.IsValid())
	{
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
*/







