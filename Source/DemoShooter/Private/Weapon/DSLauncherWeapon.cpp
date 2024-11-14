#include "Weapon/DSLauncherWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/DSProjectile.h"

//-------------------------------------------------------------------------------------------------------------
ADSLauncherWeapon::ADSLauncherWeapon()
{
}
//-------------------------------------------------------------------------------------------------------------
void ADSLauncherWeapon::Start_Fire()
{
	Make_Shot();
}
//-------------------------------------------------------------------------------------------------------------
void ADSLauncherWeapon::Stop_Fire()
{

}
//-------------------------------------------------------------------------------------------------------------
void ADSLauncherWeapon::Make_Shot()
{
	const FTransform spawn_transform(FRotator::ZeroRotator, Get_Muzzle_World_Location());
	auto projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), Class_Projectile, spawn_transform);

	UGameplayStatics::FinishSpawningActor(projectile, spawn_transform);
}
//-------------------------------------------------------------------------------------------------------------
