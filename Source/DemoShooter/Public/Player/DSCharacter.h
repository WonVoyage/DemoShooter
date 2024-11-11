#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DSCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDSHealthComponent;
class UTextRenderComponent;
class ADSBaseWeapon;
class UDSWeaponComponent;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADSCharacter(const FObjectInitializer &object_init);

	virtual void Tick(float delta_time) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *player_input_component) override;


	UFUNCTION(BlueprintCallable, Category = "Movement") bool Is_Running() const;
	UFUNCTION() void On_Death();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component") USpringArmComponent *Component_SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component") UCameraComponent *Component_Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component") UDSHealthComponent *Component_Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component") UTextRenderComponent *Component_Health_Text;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component") UDSWeaponComponent *Component_Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation") UAnimMontage *AnimMontage_Death = 0;

protected:
	virtual void BeginPlay() override;

private:
	void Move_Forward(float value);
	void Move_Right(float value);
	void On_Run_Start();
	void On_Run_End();

	bool Is_Moving_Forward = false;
	bool Wants_To_Run = false;
};
//-------------------------------------------------------------------------------------------------------------
