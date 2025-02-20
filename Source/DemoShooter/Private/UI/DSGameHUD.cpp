#include "UI/DSGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

//-------------------------------------------------------------------------------------------------------------
void ADSGameHUD::DrawHUD()
{
	Super::DrawHUD();

	//Draw_CrossHair();
}
//-------------------------------------------------------------------------------------------------------------
void ADSGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (auto player_hud_widget = CreateWidget<UUserWidget>(GetWorld(), Player_HUD_Widget_Class))
	{
		player_hud_widget->AddToViewport();
	}
}
//-------------------------------------------------------------------------------------------------------------
void ADSGameHUD::Draw_CrossHair()
{
	const TInterval<float> center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	const float half_line_size = 10.0f;
	const float line_thickness = 2.0f;
	const FLinearColor line_color = FLinearColor::Green;
	
	DrawLine(center.Min - half_line_size, center.Max, center.Min + half_line_size, center.Max, line_color, line_thickness);
	DrawLine(center.Min, center.Max - half_line_size, center.Min, center.Max + half_line_size, line_color, line_thickness);
}
//-------------------------------------------------------------------------------------------------------------
