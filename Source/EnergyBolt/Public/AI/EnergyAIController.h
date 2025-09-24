
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnergyAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class ENERGYBOLT_API AEnergyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnergyAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
