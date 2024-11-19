#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DSGameHUD.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSGameHUD : public AHUD
{
	GENERATED_BODY()

public:	
	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> Player_HUD_Widget_Class;

private:
	void Draw_CrossHair();
};
//-------------------------------------------------------------------------------------------------------------
