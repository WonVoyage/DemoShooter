#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DSFindEnemyService.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UDSFindEnemyService();

protected:
	virtual void TickNode(UBehaviorTreeComponent &owner_comp, uint8 *node_memory, float delta_seconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FBlackboardKeySelector Key_Enemy_Actor;
};
//-------------------------------------------------------------------------------------------------------------
