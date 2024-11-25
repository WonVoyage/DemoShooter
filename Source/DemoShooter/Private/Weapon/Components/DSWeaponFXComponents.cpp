#include "Weapon/Components/DSWeaponFXComponents.h"
#include "NiagaraFunctionLibrary.h"

//-------------------------------------------------------------------------------------------------------------
UDSWeaponFXComponents::UDSWeaponFXComponents()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponFXComponents::Play_Impact_FX(const FHitResult &hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, hit.ImpactPoint, hit.ImpactNormal.Rotation());
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponFXComponents::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
