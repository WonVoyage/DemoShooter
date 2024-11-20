#include "Components/DSHealthComponent.h"

//-------------------------------------------------------------------------------------------------------------
UDSHealthComponent::UDSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------------
void UDSHealthComponent::Set_Health(float health)
{
	Health = FMath::Clamp(health, 0.0f, Max_Health);
}
//-------------------------------------------------------------------------------------------------------------
bool UDSHealthComponent::Try_To_Add_Health(int32 amount_health)
{
	if (Is_Dead() || Is_Health_Full())
	{
		return false;
	}

	Set_Health(Health + amount_health);

	return true;
}
//-------------------------------------------------------------------------------------------------------------
bool UDSHealthComponent::Is_Health_Full() const
{
	return FMath::IsNearlyEqual(Health, Max_Health);
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
