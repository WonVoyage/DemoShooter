#include "UI/DSPlayerHudWidget.h"
#include "Components/DSHealthComponent.h"
#include "Components/DSWeaponComponent.h"

//-------------------------------------------------------------------------------------------------------------
float UDSPlayerHudWidget::Get_Health_Percent() const
{
	const auto player = GetOwningPlayerPawn();
	const auto component = player->GetComponentByClass(UDSHealthComponent::StaticClass());
	const auto health_component = Cast<UDSHealthComponent>(component);

	return health_component->Get_Health_Percent();
}
//-------------------------------------------------------------------------------------------------------------
bool UDSPlayerHudWidget::Get_Weapon_UI_Data(FWeaponUIData &data) const
{
	if (const auto weapon_component = Get_Weapon_Component())
	{
		return weapon_component->Get_Weapon_UI_Data(data);
	}

	return false;
}
//-------------------------------------------------------------------------------------------------------------
bool UDSPlayerHudWidget::Get_Weapon_Ammo_Data(FAmmoData &data) const
{
	if (const auto weapon_component = Get_Weapon_Component())
	{
		return weapon_component->Get_Weapon_Ammo_Data(data);
	}

	return false;
}
//-------------------------------------------------------------------------------------------------------------
UDSWeaponComponent *UDSPlayerHudWidget::Get_Weapon_Component() const
{
	if (const auto player = GetOwningPlayerPawn())
	{
		const auto component = player->GetComponentByClass(UDSWeaponComponent::StaticClass());
		const auto weapon_component = Cast<UDSWeaponComponent>(component);
		
		return weapon_component;
	}
	else
	{
		return nullptr;
	}
}
//-------------------------------------------------------------------------------------------------------------