#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DSCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADSCharacter();

	virtual void Tick(float delta_time) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *player_input_component) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera) UCameraComponent *Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera) USpringArmComponent *Spring_Arm;

protected:
	virtual void BeginPlay() override;

private:
	void Move_Forward(float value);
	void Move_Right(float value);
};
//-------------------------------------------------------------------------------------------------------------
