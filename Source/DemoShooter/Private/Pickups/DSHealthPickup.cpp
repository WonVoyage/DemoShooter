#include "Pickups/DSHealthPickup.h"
#include "Components/DSHealthComponent.h"
#include "DSUtils.h"

//-------------------------------------------------------------------------------------------------------------
bool ADSHealthPickup::Give_Pickup_To(APawn* pawn)
{
	if (const auto component_health = DSUtils::Get_Component_PlayerPawn<UDSHealthComponent>(pawn))
	{
		return component_health->Try_To_Add_Health(Amount_Health);
	}
	else
	{
		return false;
	}
}
//-------------------------------------------------------------------------------------------------------------
