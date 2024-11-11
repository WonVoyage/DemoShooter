#include "Components/DSWeaponComponent.h"
#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"

//-------------------------------------------------------------------------------------------------------------
UDSWeaponComponent::UDSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Spawn_Weapon();
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Spawn_Weapon()
{
	if (!Weapon_Class)
	{
		return;
	}

	ACharacter *character = Cast<ACharacter>(GetOwner());
	
	if (!character)
	{
		throw 23;
	}

	Current_Weapon = GetWorld()->SpawnActor<ADSBaseWeapon>(Weapon_Class);

	if (!Current_Weapon)
	{
		throw 23;
	}

	Current_Weapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon_Socket"));
	Current_Weapon->SetOwner(GetOwner());
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Fire()
{
	if (!Weapon_Class)
	{
		throw 23;
	}

	Current_Weapon->Fire();
}
//-------------------------------------------------------------------------------------------------------------
