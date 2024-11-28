#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DSFireService.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSFireService : public UBTService
{
	GENERATED_BODY()	

public:
	UDSFireService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float delta_seconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FBlackboardKeySelector Key_Enemy_Actor;
};
//-------------------------------------------------------------------------------------------------------------
