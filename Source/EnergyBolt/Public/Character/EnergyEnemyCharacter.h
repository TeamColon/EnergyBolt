
#pragma once

#include "CoreMinimal.h"
#include "EnergyBaseCharacter.h"
#include "Data/EnergyCharacterClassInfo.h"
#include "EnergyEnemyCharacter.generated.h"

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attrbutes")
	TSubclassOf<UGameplayEffect> DefaultAttribute;
	
	//void InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterClass CharacterClass = ECharacterClass::Melee;
};
