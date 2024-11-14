#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ADSProjectile();

	void Set_Shot_Direction(const FVector &direction);

protected:
	virtual void BeginPlay() override;

	UFUNCTION() void On_Projectile_Hit(UPrimitiveComponent *hit_component, AActor *other_actor, UPrimitiveComponent *other_comp, FVector normal_impulse, const FHitResult &hit);
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon") bool Full_Damage = true;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon") float Life_Seconds = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon") float Damage_Radius = 200.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon") float Damage_Amount = 50.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon") USphereComponent *Component_Collision;
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon") UProjectileMovementComponent *Component_Movement;

private:
	FVector Shot_Direction;
	AController *Get_Controller() const;
};
//-------------------------------------------------------------------------------------------------------------
