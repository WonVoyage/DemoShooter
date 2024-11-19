#include "Weapon/DSRifleWeapon.h"
//-------------------------------------------------------------------------------------------------------------
ADSRifleWeapon::ADSRifleWeapon()
{
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Start_Fire()
{
	UE_LOG(LogTemp, Error, TEXT("FIRE!!!!"));
	GetWorldTimerManager().SetTimer(Timer_Fire, this, &ADSRifleWeapon::Make_Shot, Time_Between_Shots, true);
	Make_Shot();
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Stop_Fire()
{
	GetWorldTimerManager().ClearTimer(Timer_Fire);
}
//-------------------------------------------------------------------------------------------------------------
void ADSRifleWeapon::Make_Shot()
{
	if (!GetWorld() || Is_Ammo_Empty())
	{
		return;
	}

	FVector trace_start, trace_end;
	FHitResult hit_result;
	
	if (!Get_Trace_Data(trace_start, trace_end))
	{
		return;
	}

	Make_Hit(hit_result, trace_start, trace_end);

	if (hit_result.bBlockingHit)
	{
		Make_Damage(hit_result);
		DrawDebugLine(GetWorld(), Get_Muzzle_World_Location(), hit_result.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

	}
	else
	{
		DrawDebugLine(GetWorld(), Get_Muzzle_World_Location(), trace_end, FColor::Red, false, 3.0f, 0, 3.0f);
	}

	Decrease_Ammo();
}
//-------------------------------------------------------------------------------------------------------------
bool ADSRifleWeapon::Get_Trace_Data(FVector &trace_start, FVector &trace_end) const
{
	const auto half_rad = FMath::DegreesToRadians(Bullet_Spread);
	FVector view_location;
	FRotator view_rotaion;

	if (!Get_PlayerViewPoint(view_location, view_rotaion))
	{
		return false;
	}

	const FVector shoot_direction = FMath::VRandCone(view_rotaion.Vector(), half_rad);
	trace_start = view_location;
	trace_end = trace_start + shoot_direction * Trace_Max_Distance;


	return true;
}
//-------------------------------------------------------------------------------------------------------------
