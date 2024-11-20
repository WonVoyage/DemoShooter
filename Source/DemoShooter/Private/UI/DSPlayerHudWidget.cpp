#include "UI/DSPlayerHudWidget.h"
#include "Components/DSHealthComponent.h"
#include "Components/DSWeaponComponent.h"
#include "DSUtils.h"

//-------------------------------------------------------------------------------------------------------------
float UDSPlayerHudWidget::Get_Health_Percent() const
{
	const auto health_component = DSUtils::Get_Component_PlayerPawn<UDSHealthComponent>(GetOwningPlayerPawn());
	return health_component->Get_Health_Percent();
}
//-------------------------------------------------------------------------------------------------------------
bool UDSPlayerHudWidget::Get_Weapon_UI_Data(FWeaponUIData &data) const
{
	if (const auto weapon_component = DSUtils::Get_Component_PlayerPawn<UDSWeaponComponent>(GetOwningPlayerPawn()))
	{
		return weapon_component->Get_Weapon_UI_Data(data);
	}
	else
	{
		return false;
	}
}
//-------------------------------------------------------------------------------------------------------------
bool UDSPlayerHudWidget::Get_Weapon_Ammo_Data(FAmmoData &data) const
{
	if (const auto weapon_component = DSUtils::Get_Component_PlayerPawn<UDSWeaponComponent>(GetOwningPlayerPawn()))
	{
		return weapon_component->Get_Weapon_Ammo_Data(data);
	}
	else
	{
		return false;
	}
}
//-------------------------------------------------------------------------------------------------------------
