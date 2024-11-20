#include "Pickups/DSAmmoPickup.h"
#include "Components/DSWeaponComponent.h"
#include "Components/DSHealthComponent.h"
#include "DSUtils.h"

//-------------------------------------------------------------------------------------------------------------
bool ADSAmmoPickup::Give_Pickup_To(APawn *pawn)
{
	const auto component_health = DSUtils::Get_Component_PlayerPawn<UDSHealthComponent>(pawn);

	if (component_health->Is_Dead())
	{
		return false;
	}

	if (const auto component_weapon = DSUtils::Get_Component_PlayerPawn<UDSWeaponComponent>(pawn))
	{
		return component_weapon->Try_To_Add_Ammo(Type_Weapon, Amount_Clips);
	}
	else
	{
		return false;
	}
}
//-------------------------------------------------------------------------------------------------------------
