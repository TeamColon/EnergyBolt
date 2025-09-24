
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
	// BlackBoard는 AIController 내부에 있는 변수 사용.
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
