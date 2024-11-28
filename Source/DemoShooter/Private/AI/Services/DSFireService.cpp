#include "AI/Services/DSFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/DSWeaponComponent.h"
#include "DSUtils.h"

//-------------------------------------------------------------------------------------------------------------
UDSFireService::UDSFireService()
{
	NodeName = "Fire";
}
//-------------------------------------------------------------------------------------------------------------
void UDSFireService::TickNode(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float delta_seconds)
{
	const AAIController *controller = owner_comp.GetAIOwner();
	const UBlackboardComponent *blackboard = owner_comp.GetBlackboardComponent();
	const bool has_aim = blackboard && blackboard->GetValueAsObject(Key_Enemy_Actor.SelectedKeyName);

	if (controller)
	{
		const auto component_weapon = DSUtils::Get_Component_PlayerPawn<UDSWeaponComponent>(controller->GetPawn());
		
		if (component_weapon)
		{
			has_aim ? component_weapon->Start_Fire() : component_weapon->Stop_Fire();
		}
	}

	Super::TickNode(owner_comp, node_memory, delta_seconds);
}
//-------------------------------------------------------------------------------------------------------------
