
#pragma once

#include "CoreMinimal.h"
#include "EnergyBaseCharacter.h"
#include "EnergyEnemyCharacter.generated.h"

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

	
};
