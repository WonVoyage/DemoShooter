#include "Components/DSWeaponComponent.h"
#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/DSEquipFinishedAnimNotify.h"

//-------------------------------------------------------------------------------------------------------------
UDSWeaponComponent::UDSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Start_Fire()
{
	if (Can_Fire())
	{
		Current_Weapon->Start_Fire();
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Stop_Fire()
{
	Current_Weapon->Stop_Fire();
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Next_Weapon()
{
	if (!Can_Equip())
	{
		return;
	}

	Current_Weapon->Stop_Fire();
	Current_Weapon_Index = (Current_Weapon_Index + 1) % Weapons.Num();

	Equip_Weapon(Current_Weapon_Index);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Reload()
{
	Play_AnimMontage(AnimMontage_Current_Reload);
}
//-------------------------------------------------------------------------------------------------------------
ADSBaseWeapon* UDSWeaponComponent::Get_Current_Weapon()
{
	return Current_Weapon;
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Init_Animations();
	Spawn_Weapons();
	Equip_Weapon(Current_Weapon_Index);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Spawn_Weapons()
{
	ACharacter *character = Cast<ACharacter>(GetOwner());
	
	if (!character)
	{
		throw 23;
	}

	for (auto &weapon_data : Weapon_Data)
	{
		ADSBaseWeapon *weapon = GetWorld()->SpawnActor<ADSBaseWeapon>(weapon_data.Weapon_Class);

		weapon->SetOwner(GetOwner());
		Weapons.Add(weapon);
		Attach_Weapon_To_Socket(weapon, character->GetMesh(), Name_Weapon_Armory_Socket);
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Attach_Weapon_To_Socket(ADSBaseWeapon *weapon, USceneComponent *scene_component, FName socket_name)
{
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, false);
	weapon->AttachToComponent(scene_component, attachment_rules, socket_name);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Equip_Weapon(int32 weapon_index)
{
	ACharacter *character = Cast<ACharacter>(GetOwner());
	
	if (!character)
	{
		return;
	}

	if (Current_Weapon)
	{
		Attach_Weapon_To_Socket(Current_Weapon, character->GetMesh(), Name_Weapon_Armory_Socket);
	}

	//AnimMontage_Current_Reload = Weapon_Data[weapon_index].AnimMontage_Reload;
	Current_Weapon = Weapons[weapon_index];
	Equip_Anim_In_Progress = true;

	Attach_Weapon_To_Socket(Current_Weapon, character->GetMesh(), Name_Weapon_Equip_Socket);
	Play_AnimMontage(AnimMontage_Equip);

	const auto current_data = Weapon_Data.FindByPredicate([&](const FWeaponData& data) {return data.Weapon_Class == Current_Weapon->GetClass(); });
	AnimMontage_Current_Reload = current_data->AnimMontage_Reload;

}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Play_AnimMontage(UAnimMontage *animation)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	character->PlayAnimMontage(animation);
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::Init_Animations()
{
	if (!AnimMontage_Equip)
	{
		return;
	}

	const auto notify_events = AnimMontage_Equip->Notifies;

	for (auto notify_event : notify_events)
	{
		auto notify_equip_finished = Cast<UDSEquipFinishedAnimNotify>(notify_event.Notify);

		if (notify_equip_finished)
		{
			notify_equip_finished->OnNotified.AddUObject(this, &UDSWeaponComponent::On_Equip_Finished);
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponComponent::On_Equip_Finished(USkeletalMeshComponent* mesh_component)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

 	if (character->GetMesh() == mesh_component)
	{
		Equip_Anim_In_Progress = false;
		UE_LOG(LogTemp, Error, TEXT("Equip Finished"));
	}
}
//-------------------------------------------------------------------------------------------------------------
bool UDSWeaponComponent::Can_Fire() const
{
	return !Equip_Anim_In_Progress;
}
//-------------------------------------------------------------------------------------------------------------
bool UDSWeaponComponent::Can_Equip() const
{
	return !Equip_Anim_In_Progress;
}
//-------------------------------------------------------------------------------------------------------------
