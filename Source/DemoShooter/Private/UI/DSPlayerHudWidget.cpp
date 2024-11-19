#include "UI/DSPlayerHudWidget.h"
#include "Components/DSHealthComponent.h"

//-------------------------------------------------------------------------------------------------------------
float UDSPlayerHudWidget::Get_Health_Percent() const
{
	const auto player = GetOwningPlayerPawn();
	const auto component = player->GetComponentByClass(UDSHealthComponent::StaticClass());
	const auto health_component = Cast<UDSHealthComponent>(component);

	return health_component->Get_Health_Percent();
}
//-------------------------------------------------------------------------------------------------------------