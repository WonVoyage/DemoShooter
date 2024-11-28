#include "Components/DSAIPerceptionComponent.h"
#include "AIController.h"
#include "DSUtils.h"
#include "Components/DSHealthComponent.h"
#include "Perception/AISense_Sight.h"

//-------------------------------------------------------------------------------------------------------------
AActor *UDSAIPerceptionComponent::Get_Closes_Enemy() const
{
	TArray<AActor*> actors_percieve;

	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), actors_percieve);

	if (actors_percieve.Num() == 0)
	{
		return nullptr;
	}

	const auto controller = Cast<AAIController>(GetOwner());

	if (!controller)
	{
		return nullptr;
	}

	const auto pawn = controller->GetPawn();

	if (!pawn)
	{
		return nullptr;
	}

	float best_distance = MAX_FLT;
	AActor *best_pawn = nullptr;

	for (const auto actor : actors_percieve)
	{
		const auto component_health = DSUtils::Get_Component_PlayerPawn<UDSHealthComponent>(actor);

		if (component_health && !component_health->Is_Dead())
		{
			const auto current_distance = (actor->GetActorLocation() - pawn->GetActorLocation()).Size();
			
			if (current_distance < best_distance)
			{
				best_distance = current_distance;
				best_pawn = actor;
			}
		}
	}

	return best_pawn;
}
//-------------------------------------------------------------------------------------------------------------
