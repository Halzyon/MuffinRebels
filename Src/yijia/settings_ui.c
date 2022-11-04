#include "cpprocessing.h"
#include <stdbool.h>
#include "ui_utils.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "brightness_Settings_ui.h"

GameObject settings_icon;
GameObject exit_icon;
GameObject soundOn_icon;
GameObject sounfOff_icon;
GameObject save_icon;
GameObject brightness_icon; 
CP_Font myFont;
int alpha 

void settings_init (void) {
	myFont= CP_Font_Load("Assets/Kenney Pixel.ttf")
}

void settings_update(void) { 
	CP_Graphics_ClearBackground(CP_Color_Create(0, 255, 0, 255));

	//once clicked on settings icon
	if (CP_Input_Mouselicked())
	{
		if (
			IsAreaClicked(250.0f,250.0f,50.0f, 50.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()); //opens settings
			)
		}
		if (
			IsAreaClicked(250.0f, 250.0f, 50.0f, 50.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()); //exits --to change the position
			)
		{
			CP_Engine_Terminate(); 
		}
	}

	//render settings icons
	icon = CP_Image_Load("./Assets/settings_icon.png");
	alpha = 0;
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(settings_icon, 35.0f, 26.0f, CP_Image_GetWidth(settings_icon), CP_Image_GetHeight(settings_icon), alpha);

	//render exit icon
	icon = CP_Image_Load("./Assets/exit_icon.png");
	alpha = 0;
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(exit_icon, 1037.0f, 197.0f, CP_Image_GetWidth(exit_icon), CP_Image_GetHeight(exit_icon), alpha); 

	//render sound icon
	icon = CP_Image_Load("./Assets/soundOn_icon.png");
	alpha = 0;
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	int soundOn_icon = CP_Image_Draw(soundOn_icon, 1037.0f, 197.0f, CP_Image_GetWidth(soundOn_icon), CP_Image_GetHeight(soundOn_icon), alpha);

	//render save icon
	icon = CP_Image_Load("./Assets/save_icon.png");
	alpha = 0;
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	int save_icon = CP_Image_Draw(save_icon, 1037.0f, 197.0f, CP_Image_GetWidth(save_icon), CP_Image_GetHeight(save_icon), alpha);

	//render brightness icon
	icon = CP_Image_Load("./Assets/brightness_iocn.png");
	alpha = 0;
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	int brightness_iocn = CP_Image_Draw(brightness_iocn, 1037.0f, 197.0f, CP_Image_GetWidth(brightness_iocn), CP_Image_GetHeight(brightness_iocn), alpha);

	//render settings text
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(0, 255, 163, 255)); //original text color
	CP_Settings_TextSize(10.0f); //change the text size
	CP_Font_DrawText("-SETTINGS-", ); //Settings text 

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255)); //original text color
	CP_Settings_TextSize(10.0f); //change the text size
	CP_Font_DrawText("Brightness", 720, 650);
	CP_Font_DrawText("Sound", 720, 650);
	CP_Font_DrawText("Save", 750, 680); 

	//renders settings bg
	void CP_Graphics_DrawRectAdvanced(1126.0f, 646.0f, 951.0f, 473.0f, 0.0, 4.0f); 
	CP_Settings_Fill(CP_Color_Create(128, 128, 128, 128)); //color 

	//text hover animation
	if (CP_Input_MouseMoved())
	{
		if (IsAreaClicked(CP_Font_DrawText("Brightness", 720, 650); {  //mouse hovers over brightness text
		CP_Settings_Fill(CP_Color_Create(250, 255, 0, 255)); //text hover color 
		}
		
		if (IsAreaClicked(CP_Font_DrawText("Sound", 720, 650);//mouse hovers over sound text
		{
		CP_Settings_Fill(CP_Color_Create(250, 255, 0, 255)); //text hover color 
		}

		if (IsAreaClicked(CP_Font_DrawText("Save", 750, 680);//mouse hovers over save text
		{
		CP_Settings_Fill(CP_Color_Create(250, 255, 0, 255)); //text hover color 
		}
	}

	//brightness--> brightness_Settings_ui
	if (IsAreaClicked(CP_Font_DrawText("Brightness", 720, 650)))
	{

	}

	//sound - mouse clicked no sound
	if (IsAreaClicked(soundOn_icon)) 
	{

	}

	//save 
	if (IsAreaClicked(save_icon))
	{

	}


}


void settings_shutdown(void) {

}