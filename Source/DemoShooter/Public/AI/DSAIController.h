#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DSAIController.generated.h"

class UDSAIPerceptionComponent;

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADSAIController();

protected:
	virtual void Tick(float delta_time) override;
	virtual void OnPossess(APawn *in_pawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") UDSAIPerceptionComponent *Component_Perception;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FName Focus_On_Key_Name = "Enemy_Actor";

private:
	AActor *GetFocusOnActor() const;
};
//-------------------------------------------------------------------------------------------------------------
