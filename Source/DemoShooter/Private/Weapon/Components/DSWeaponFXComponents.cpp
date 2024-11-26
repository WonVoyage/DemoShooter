#include "Weapon/Components/DSWeaponFXComponents.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

//-------------------------------------------------------------------------------------------------------------
UDSWeaponFXComponents::UDSWeaponFXComponents()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------------
void UDSWeaponFXComponents::Play_Impact_FX(const FHitResult &hit)
{
	auto data_impact = Data_Impact;

	if (hit.PhysMaterial.IsValid())
	{
		const auto material = hit.PhysMaterial.Get();

		if (Map_Data_Impacts.Contains(material))
		{
			data_impact = Map_Data_Impacts[material];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), data_impact.Effect_Niagara, hit.ImpactPoint, hit.ImpactNormal.Rotation());

	if (auto decal_component = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), data_impact.Data_Decal.Material, data_impact.Data_Decal.Size, hit.ImpactPoint, hit.ImpactNormal.Rotation()))
	{
		decal_component->SetFadeOut(data_impact.Data_Decal.Time_Life, data_impact.Data_Decal.Time_Fade_Out);
	}
}
//-------------------------------------------------------------------------------------------------------------
