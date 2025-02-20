#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSCoreTypes.h"
#include "DSHealthComponent.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOSHOOTER_API UDSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDSHealthComponent();

	void Set_Health(float health);
	bool Try_To_Add_Health(int32 amount_health);
	bool Is_Health_Full() const;
	float Get_Health() const;

	UFUNCTION(BlueprintCallable) bool Is_Dead() const;
	UFUNCTION(BlueprintCallable) float Get_Health_Percent() const;
	UFUNCTION() void OnTakeAnyDamage(AActor *damage_actor, float damage, const class UDamageType *damage_type, class AController *instigated_by, AActor *damage_causer);

	float Health = 100.0f;
	FOnDeath OnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "1.0", ClampMax = "100.0")) float Max_Health = 100.0f;

protected:
	virtual void BeginPlay() override;
};
//-------------------------------------------------------------------------------------------------------------
