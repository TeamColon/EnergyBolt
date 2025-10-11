
#pragma once

#include "CoreMinimal.h"
#include "EnergyBaseCharacter.h"
#include "Data/EnergyCharacterClassInfo.h"
#include "EnergyEnemyCharacter.generated.h"

struct FGameplayTag;
enum class ECharacterClass : uint8;
class UGameplayEffect;
class AEnergyAIController;
class UBehaviorTree;

UCLASS()
class ENERGYBOLT_API AEnergyEnemyCharacter : public AEnergyBaseCharacter
{
	GENERATED_BODY()

public:
	
	AEnergyEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AEnergyAIController> EnergyAIController;

public:
	virtual void PossessedBy(AController* NewController) override;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 300.f;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;
	
	//~Begin ICombatInterface
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	virtual void Die() override;
	//~End ICombatInterface

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeSpan = 5.f;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttribute;
	
	//void InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterClass CharacterClass = ECharacterClass::Melee;
};
