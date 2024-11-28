#include "AI/Services/DSFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/DSAIPerceptionComponent.h"
#include "AIController.h"
#include "DSUtils.h"

//-------------------------------------------------------------------------------------------------------------
UDSFindEnemyService::UDSFindEnemyService()
{
	NodeName = "Find Enemy";
}
//-------------------------------------------------------------------------------------------------------------
void UDSFindEnemyService::TickNode(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float delta_seconds)
{
	const auto blackboard = owner_comp.GetBlackboardComponent();
	if (blackboard)
	{
		const auto controller = owner_comp.GetOwner();
		const auto component_perception = DSUtils::Get_Component_PlayerPawn<UDSAIPerceptionComponent>(controller);

		if (component_perception)
		{
			blackboard->SetValueAsObject(Key_Enemy_Actor.SelectedKeyName, component_perception->Get_Closes_Enemy());
		}
	}

	Super::TickNode(owner_comp, node_memory, delta_seconds);
}
//-------------------------------------------------------------------------------------------------------------
