

#include "Character/EnergyEnemyCharacter.h"

#include "EnergyBlueprintFunctionLibrary.h"
#include "EnergyGameplayTags.h"
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

	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	// GameplayTag가 추가되거나 제거될 때 이벤트 등록
	// HitReactTag가 추가 혹은 제거될 때 마다 HitReactTagChanged 함수 호출
	EnergyAbilitySystemComponent->RegisterGameplayTagEvent(
		EnergyGameplayTags::HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this, &ThisClass::HitReactTagChanged
		);
}

void AEnergyEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	// TODO: HitReact Ability 만들고 Activate 하기
	bHitReacting = NewCount > 0.f;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AEnergyEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// InitializeDefaultAttributes
	UEnergyBlueprintFunctionLibrary::InitializeDefaultAttribute(this, CharacterClass, EnergyAbilitySystemComponent);

	// InitializeDefaultAbilities
	UEnergyBlueprintFunctionLibrary::GiveStartupAbilities(this, CharacterClass, EnergyAbilitySystemComponent);
	
	// Initialize BehaviorTree, BlackBoard
	EnergyAIController = Cast<AEnergyAIController>(NewController);
	EnergyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	EnergyAIController->RunBehaviorTree(BehaviorTree);

	// BlackBoard의 변수 초기화
	EnergyAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsRanged"), CharacterClass != ECharacterClass::Melee);
	
}

void AEnergyEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AEnergyEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void AEnergyEnemyCharacter::Die()
{
	// LifeSpan을 정하여 N초 이후에 Destroy하게 할 수 있다.
	SetLifeSpan(LifeSpan);
	Super::Die();
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







