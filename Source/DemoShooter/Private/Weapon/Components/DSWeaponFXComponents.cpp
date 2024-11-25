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
	UNiagaraSystem *effect = Default_Effect;

	if (hit.PhysMaterial.IsValid())
	{
		const auto material = hit.PhysMaterial.Get();

		if (Map_Effects.Contains(material))
		{
			effect = Map_Effects[material];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effect, hit.ImpactPoint, hit.ImpactNormal.Rotation());
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponFXComponents::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
