#include "AI/DSAIController.h"
#include "AI/DSAICharacter.h"
#include "Components/DSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

//-------------------------------------------------------------------------------------------------------------
ADSAIController::ADSAIController()
{
	Component_Perception = CreateDefaultSubobject<UDSAIPerceptionComponent>("Component_Perception");
	SetPerceptionComponent(*Component_Perception);
}
//-------------------------------------------------------------------------------------------------------------
void ADSAIController::Tick(float delta_time)
{
	Super::Tick(delta_time);

	const auto aim_actor = GetFocusOnActor();
	SetFocus(aim_actor);
}
//-------------------------------------------------------------------------------------------------------------
void ADSAIController::OnPossess(APawn *in_pawn)
{
	Super::OnPossess(in_pawn);

	const auto character = Cast<ADSAICharacter>(in_pawn);

	if (character)
	{
		RunBehaviorTree(character->Tree);
	}
}
//-------------------------------------------------------------------------------------------------------------
AActor *ADSAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent())
	{
		return nullptr;
	}

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(Focus_On_Key_Name));
}
//-------------------------------------------------------------------------------------------------------------
