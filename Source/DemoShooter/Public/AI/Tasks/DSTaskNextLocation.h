#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DSTaskNextLocation.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API UDSTaskNextLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UDSTaskNextLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &owner_component, uint8 *node_memory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") bool Self_Center = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") float Radius = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FBlackboardKeySelector Key_Aim_Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!Self_Center")) FBlackboardKeySelector Key_Center_Actor;
};
//-------------------------------------------------------------------------------------------------------------
