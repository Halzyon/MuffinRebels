#include "cprocessing.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "settings_ui.h"

/*
Sprite* exitsetting_icon;
Sprite* settingsbg;
Sprite* brightness_icon;
Sprite* save_icon;
Sprite* SoundOn_icon;
Sprite* savehover_icon;
Sprite* brightnesshover_icon;
Sprite* soundhover_icon;
*/

asset exitsetting_icon; 
asset settingsbg;
asset brightness_icon;
asset save_icon;
asset SoundOn_icon;
asset savehover;
asset brightnesshover_icon;
asset soundhover;
asset brightnessSlider;
asset brightnessSlidercircle;
asset brightnesstxt;
asset soundtxt;
asset savetxt;
CP_Font myFont;
int alpha;




void settings_init(void){
	//OPENFILE
	myFont = CP_Font_Load("Assets/Kenney Pixel.ttf");
	/*settingsbg = get_image_size("Assets/settingsbg.png", &settingsbg);
	exitsetting_icon = CreateSprite("Assets/exitsetting_icon.png", 1, 1, false, false);
	brightness_icon = CreateSprite("Assets/brightness_icon.png", 1, 1, false, false);
	save_icon = CreateSprite("Assets/save_icon.png", 1, 1, false, false);
	SoundOn_icon = CreateSprite("Assets/SoundOn_icon.png", 1, 1, false, false);
	
	savehover_icon = CreateSprite("Assets/savehover_icon.png", 1, 1, false, false);
	brightnesshover_icon = CreateSprite("Assets/brightnesshover_icon.png", 1, 1, false, false);
	soundhover_icon = CreateSprite("Assets/soundhover_icon.png", 1, 1, false, false);*/

	get_image_size_set("Assets/settingsbg.png", &settingsbg);
	get_image_size_set("Assets/exitsetting_icon.png", &exitsetting_icon);
	get_image_size_set("Assets/brightness_icon.png", &brightness_icon);
	get_image_size_set("Assets/save_icon.png", &save_icon);
	get_image_size_set("Assets/SoundOn_icon.png", &SoundOn_icon);
	get_image_size_set("Assets/savehover.png", &savehover);
	get_image_size_set("Assets/brightnessSlidercircle.png", &brightnessSlidercircle);
	get_image_size_set("Assets/brightnessSlider.png", &brightnessSlider);
	get_image_size_set("Assets/brightnesshover_icon.png", &brightnesshover_icon);
	get_image_size_set("Assets/soundhover.png", &soundhover);
	get_image_size_set("Assets/brightnesstxt.png", &brightnesstxt);
	get_image_size_set("Assets/soundtxt.png", &soundtxt);
	get_image_size_set("Assets/savetxt.png", &savetxt);



	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	
	//POSITIONS
	exitsetting_icon.position.x = CP_System_GetWindowWidth() - 440;
	exitsetting_icon.position.y = 170;

	settingsbg.position.x = CP_System_GetWindowWidth() - 640;
	settingsbg.position.y = 360;

	brightness_icon.position.x = CP_System_GetWindowWidth() - 810;
	brightness_icon.position.y = 565;

	save_icon.position.x = CP_System_GetWindowWidth() - 460;
	save_icon.position.y = 565;

	SoundOn_icon.position.x = CP_System_GetWindowWidth() - 635;
	SoundOn_icon.position.y = 565;

	//hover
	savehover.position.x = CP_System_GetWindowWidth() - 460;
	savehover.position.y = 565;

	brightnesshover_icon.position.x = CP_System_GetWindowWidth() - 810;
	brightnesshover_icon.position.y = 565;

	soundhover.position.x = CP_System_GetWindowWidth() - 635;
	soundhover.position.y = 565;

	//slider
	brightnessSlidercircle.position.x = CP_System_GetWindowWidth() - 635;
	brightnessSlidercircle.position.y = 360;

	brightnessSlider.position.x = CP_System_GetWindowWidth() - 635;
	brightnessSlider.position.y = 360;

	//txt 
	brightnesstxt.position.x = CP_System_GetWindowWidth() - 635;
	brightnesstxt.position.y = 260; 

	soundtxt.position.x = CP_System_GetWindowWidth() - 635;
	soundtxt.position.y = 260;

	savetxt.position.x = CP_System_GetWindowWidth() - 635;
	savetxt.position.y = 260;
	
} 

void settings_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//RENDER ICONS
	/*(settingsbg);
	RenderSprite(exitsetting_icon);
	RenderSprite(brightness_icon);
	RenderSprite(save_icon);
	RenderSprite(SoundOn_icon);*/
	RenderAsset(settingsbg, 255);
	RenderAsset(exitsetting_icon, 255);
	
	//BRIGHTNESS ICON
	RenderAsset(brightness_icon, 255);
	if (mouse_in_rect(brightness_icon.position.x, brightness_icon.position.y, brightness_icon.size.x, brightness_icon.size.y) == 1)	// brightness hover
    {
		RenderAsset(brightnesshover_icon, 255);
		if (CP_Input_MouseClicked())
		{
			brightnessSlider.clicked = !brightnessSlider.clicked;
			save_icon.clicked = SoundOn_icon.clicked = 0;
		}
    }
	if (brightnessSlider.clicked)
	{
		RenderAsset(brightnesstxt, 255);
		RenderAsset(brightnessSlider, 255);
		RenderAsset(brightnessSlidercircle, 255);
		RenderAsset(brightnesshover_icon, 255);  
		
	}

	//SAVE ICON
	RenderAsset(save_icon, 255);
	if (mouse_in_rect(save_icon.position.x, save_icon.position.y, save_icon.size.x, save_icon.size.y) == 1)	// save hover 
	{
		RenderAsset(savehover, 255);
		if (CP_Input_MouseClicked())
		{
			save_icon.clicked = !save_icon.clicked;
			brightness_icon.clicked = SoundOn_icon.clicked = 0;
		}
	}
	if (save_icon.clicked)
	{
		RenderAsset(savetxt, 255);
		RenderAsset(savehover, 255);

	}


	//SOUND ICON 
	RenderAsset(SoundOn_icon, 255);
	if (mouse_in_rect(SoundOn_icon.position.x, SoundOn_icon.position.y, SoundOn_icon.size.x, SoundOn_icon.size.y) == 1)	// soundon hover
	{
		RenderAsset(soundhover, 255);
		if (CP_Input_MouseClicked())
		{
			SoundOn_icon.clicked = !SoundOn_icon.clicked;
			brightness_icon.clicked = save_icon.clicked = 0;
		}
	}
	if (SoundOn_icon.clicked)
	{
		RenderAsset(soundtxt, 255);
		RenderAsset(soundhover, 255);

	}
	
}


void settings_shutdown(void) {

}

void RenderAsset(asset render, int opacity)
{
	CP_Image_Draw(render.image, render.position.x, render.position.y, render.size.x, render.size.y, opacity);
}

