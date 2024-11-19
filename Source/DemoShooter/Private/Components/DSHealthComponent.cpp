#include "Components/DSHealthComponent.h"

//-------------------------------------------------------------------------------------------------------------
UDSHealthComponent::UDSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------------
float UDSHealthComponent::Get_Health() const
{
	return Health;
}
//-------------------------------------------------------------------------------------------------------------
bool UDSHealthComponent::Is_Dead() const
{
	return Health <= 0.0f;
}
//-------------------------------------------------------------------------------------------------------------
float UDSHealthComponent::Get_Health_Percent() const
{
	return Health / Max_Health;
}
//-------------------------------------------------------------------------------------------------------------
void UDSHealthComponent::OnTakeAnyDamage(AActor *damage_actor, float damage, const class UDamageType *damage_type, class AController *instigated_by, AActor *damage_causer)
{
	if (damage <= 0.0f || Is_Dead())
	{
		return;
	}

	Health = FMath::Clamp(Health - damage, 0.0f, Max_Health);

	if (Is_Dead())
	{
		OnDeath.Broadcast();
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor *owner = GetOwner();

	if (owner)
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UDSHealthComponent::OnTakeAnyDamage);
	}
}
//-------------------------------------------------------------------------------------------------------------
