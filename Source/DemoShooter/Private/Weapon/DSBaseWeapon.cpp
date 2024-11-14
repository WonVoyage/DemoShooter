#include "Weapon/DSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/DamageEvents.h"

//-------------------------------------------------------------------------------------------------------------
ADSBaseWeapon::ADSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));

	SetRootComponent(SkeletalMesh_Weapon);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Start_Fire()
{

}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Stop_Fire()
{

}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Make_Shot()
{
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Get_Trace_Data(FVector &trace_start, FVector &trace_end) const
{
	FVector view_location;
	FRotator view_rotaion;
	FVector shoot_direction;

	if (!Get_PlayerViewPoint(view_location, view_rotaion))
	{
		return false;
	}

	shoot_direction = view_rotaion.Vector();
	trace_start = view_location;
	trace_end = trace_start + shoot_direction * Trace_Max_Distance;

	return true;
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Make_Hit(FHitResult &hit_result, const FVector &trace_start, const FVector &trace_end)
{
	if (!GetWorld())
	{
		return;
	}

	FCollisionQueryParams collision_params;
	collision_params.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(hit_result, trace_start, trace_end, ECollisionChannel::ECC_Visibility, collision_params);
}
//-------------------------------------------------------------------------------------------------------------
void ADSBaseWeapon::Make_Damage(const FHitResult &hit_result)
{
	const auto damage_actor = hit_result.GetActor();

	if (!damage_actor)
	{
		return;
	}

	damage_actor->TakeDamage(10.0f, FDamageEvent(), UGameplayStatics::GetPlayerController(this, 0), this);
}
//-------------------------------------------------------------------------------------------------------------
bool ADSBaseWeapon::Get_PlayerViewPoint(FVector &view_location, FRotator &view_rotation) const
{
	const auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!controller)
	{
		return false;
	}

	controller->GetPlayerViewPoint(view_location, view_rotation);

	return true;
}
//-------------------------------------------------------------------------------------------------------------
APlayerController *ADSBaseWeapon::Get_PlayerController() const
{
	const auto player = Cast<ACharacter>(GetOwner());

	if (!player)
	{
		return nullptr;
	}
	
	return player->GetController<APlayerController>();
}
//-------------------------------------------------------------------------------------------------------------
FVector ADSBaseWeapon::Get_Muzzle_World_Location() const
{
	return SkeletalMesh_Weapon->GetSocketLocation(Name_MuzzleSocket);
}
//-------------------------------------------------------------------------------------------------------------
