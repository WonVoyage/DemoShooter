#include "Components/DSAIWeaponComponent.h"
#include "Weapon/DSBaseWeapon.h"

//-------------------------------------------------------------------------------------------------------------
void UDSAIWeaponComponent::Start_Fire()
{
	if (!Can_Fire())
	{
		return;
	}

	if (Current_Weapon->Is_Ammo_Empty())
	{
		Next_Weapon();
	}
	else
	{
		Current_Weapon->Start_Fire();
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSAIWeaponComponent::Next_Weapon()
{
	int32 next_index;

	next_index = (Index_Current_Weapon + 1) % Weapons.Num();

	while (next_index != Index_Current_Weapon)
	{
		if (!Weapons[next_index]->Is_Ammo_Empty())
		{
			break;
		}

		next_index = (next_index + 1) % Weapons.Num();
	}

	if (next_index != Index_Current_Weapon)
	{
		Index_Current_Weapon = next_index;
		Equip_Weapon(Index_Current_Weapon);
	}
}
//-------------------------------------------------------------------------------------------------------------
