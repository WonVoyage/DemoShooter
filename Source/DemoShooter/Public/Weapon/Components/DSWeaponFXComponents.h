#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <DSCoreTypes.h>
#include "DSWeaponFXComponents.generated.h"

class UNiagaraSystem;

//-------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOSHOOTER_API UDSWeaponFXComponents : public UActorComponent
{
	GENERATED_BODY()

public:
	UDSWeaponFXComponents();

	void Play_Impact_FX(const FHitResult &hit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") FImpactData Data_Impact;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") TMap<UPhysicalMaterial*, FImpactData> Map_Data_Impacts;
};
//-------------------------------------------------------------------------------------------------------------
