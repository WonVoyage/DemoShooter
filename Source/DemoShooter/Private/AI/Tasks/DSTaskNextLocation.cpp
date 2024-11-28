#include "AI/Tasks/DSTaskNextLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

//-------------------------------------------------------------------------------------------------------------
UDSTaskNextLocation::UDSTaskNextLocation()
{
	NodeName = "Next Location";
}
//-------------------------------------------------------------------------------------------------------------
EBTNodeResult::Type UDSTaskNextLocation::ExecuteTask(UBehaviorTreeComponent &owner_component, uint8 *node_memory)
{
	const auto controller = owner_component.GetAIOwner();
	const auto blackboard = owner_component.GetBlackboardComponent();

	if (!controller || !blackboard)
	{
		return EBTNodeResult::Failed;
	}

	const auto pawn = controller->GetPawn();

	if (!pawn)
	{
		return EBTNodeResult::Failed;
	}

	const auto nav_system = UNavigationSystemV1::GetCurrent(pawn);

	if (!nav_system)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation nav_location;
	auto location = pawn->GetActorLocation();

	if (!Self_Center)
	{
		auto center_actor = Cast<AActor>(blackboard->GetValueAsObject(Key_Center_Actor.SelectedKeyName));

		if (!center_actor)
		{
			return EBTNodeResult::Failed;
			location = pawn->GetActorLocation();
		}
	}

	if (const auto found = nav_system->GetRandomReachablePointInRadius(pawn->GetActorLocation(), Radius, nav_location))
	{
		blackboard->SetValueAsVector(Key_Aim_Location.SelectedKeyName, nav_location.Location);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
//-------------------------------------------------------------------------------------------------------------
