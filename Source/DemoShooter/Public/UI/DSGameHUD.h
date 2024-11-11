#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DSGameHUD.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class DEMOSHOOTER_API ADSGameHUD : public AHUD
{
	GENERATED_BODY()
	
	virtual void DrawHUD() override;

	void Draw_CrossHair();
};
//-------------------------------------------------------------------------------------------------------------
