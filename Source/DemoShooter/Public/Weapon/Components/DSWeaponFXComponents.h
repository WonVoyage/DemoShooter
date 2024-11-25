#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem *Default_Effect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") TMap<UPhysicalMaterial*, UNiagaraSystem*> Map_Effects;

protected:
	virtual void BeginPlay() override;
};
//-------------------------------------------------------------------------------------------------------------
