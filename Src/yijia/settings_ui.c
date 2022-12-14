/*---------------------------------------------------------------
  File: settings_ui.c
  Project: DICE REBELS
  Author: Yeo Yi Jia, y.yijia@digipen.edu
  Co-Author: Liew Yeni, yeni.l@digipen.edu
  Co-Author: Muhammad Hazim Bin Gazali, m.bingazali@digipen.edu
  Copyright: 2022, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#include "cprocessing.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "settings_ui.h"
#include "GameStateManager.h"

asset exitsetting_icon; 
asset settingsbg;
asset brightness_icon;
asset brightnesslow_icon;
asset brightnesshigh_icon;
asset SoundOn_icon;
asset brightnesshover_icon;
asset soundhover;
asset brightnessSlider;
asset brightnessSlidercircle;
asset brightnesstxt;
asset soundtxt;
asset yes;
asset no; 
asset progresstxt;
asset soundoffscaled;
asset soundscaled;
asset matte; //for brightness
int brightposx = 255;
int alpha;
int bright_clicked = false;
extern bool sub;

void settings_init(void){

	get_image_size_set("Assets/settingsbg.png", &settingsbg);
	get_image_size_set("Assets/exitsetting_icon.png", &exitsetting_icon);
	get_image_size_set("Assets/brightness_icon.png", &brightness_icon);
	get_image_size_set("Assets/SoundOn_icon.png", &SoundOn_icon);
	get_image_size_set("Assets/brightnessSlidercircle.png", &brightnessSlidercircle);
	get_image_size_set("Assets/brightnessSlider.png", &brightnessSlider);
	get_image_size_set("Assets/brightnesshover_icon.png", &brightnesshover_icon);
	get_image_size_set("Assets/soundhover.png", &soundhover);
	get_image_size_set("Assets/brightnesstxt.png", &brightnesstxt);
	get_image_size_set("Assets/soundtxt.png", &soundtxt);
	get_image_size_set("Assets/yes.png", &yes);
	get_image_size_set("Assets/no.png", &no);
	get_image_size_set("Assets/progresstxt.png", &progresstxt);
	get_image_size_set("Assets/soundoffscaled.png", &soundoffscaled);
	get_image_size_set("Assets/soundscaled.png", &soundscaled);
	get_image_size_set("Assets/matte.png", &matte);
	get_image_size_set("Assets/brightnesslow_icon.png", &brightnesslow_icon);
	get_image_size_set("Assets/brightnesshigh_icon.png", &brightnesshigh_icon);

	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	
	//POSITIONS
	exitsetting_icon.position.x = (float)(CP_System_GetWindowWidth() - 440);
	exitsetting_icon.position.y = 170;

	settingsbg.position.x = (float)(CP_System_GetWindowWidth() - 640);
	settingsbg.position.y = 360;

	brightness_icon.position.x = (float)(CP_System_GetWindowWidth() - 765);
	brightness_icon.position.y = 565;


	SoundOn_icon.position.x = (float)(CP_System_GetWindowWidth() - 505);
	SoundOn_icon.position.y = 565;

	//hover

	brightnesshover_icon.position.x = brightness_icon.position.x;
	brightnesshover_icon.position.y = brightness_icon.position.y;

	soundhover.position.x = SoundOn_icon.position.x;
	soundhover.position.y = SoundOn_icon.position.y;

	//brightnessslider
	brightnessSlidercircle.position.x = (float)(CP_System_GetWindowWidth() - 525);
	brightnessSlidercircle.position.y = 360;

	brightnessSlider.position.x = (float)(CP_System_GetWindowWidth() - 635);
	brightnessSlider.position.y = 360;

	brightnesslow_icon.position.x = (float)(CP_System_GetWindowWidth() - 800);
	brightnesslow_icon.position.y = 360; 

	brightnesshigh_icon.position.x = (float)(CP_System_GetWindowWidth() - 470);
	brightnesshigh_icon.position.y = 360;

	matte.position.x = (float)(CP_System_GetWindowWidth() - 640);
	matte.position.y = 360;

	//txt 
	brightnesstxt.position.x = (float)(CP_System_GetWindowWidth() - 635);
	brightnesstxt.position.y = 260; 

	soundtxt.position.x = (float)(CP_System_GetWindowWidth() - 635);
	soundtxt.position.y = 260;
	
	//positions of variables inside the sound tab
	soundoffscaled.position.x = (float)(CP_System_GetWindowWidth() - 635);
	soundoffscaled.position.y = 360;

	soundscaled.position.x = (float)(CP_System_GetWindowWidth() - 635);
	soundscaled.position.y = 360;

	//	starts the game with the sound on
	soundscaled.clicked = 1;


}

void settings_update(void) 
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	//Exit Settings icon
	RenderAsset(settingsbg, 255);
	RenderAsset(exitsetting_icon, 255);
	if (mouse_in_rect(exitsetting_icon.position.x, exitsetting_icon.position.y, exitsetting_icon.size.x, exitsetting_icon.size.y))	// Settings hover
	{
		if (CP_Input_MouseClicked() && MAINMENU_SCENE)
		{
			GameStateSetNextSubScene(MAX_SCENE,true);
			sub = false;
		}
	}

	//BRIGHTNESS ICON
	RenderAsset(brightness_icon, 255);
	if (mouse_in_rect(brightness_icon.position.x, brightness_icon.position.y, brightness_icon.size.x, brightness_icon.size.y) == 1)	// brightness hover
	{
		RenderAsset(brightnesshover_icon, 255);
		if (CP_Input_MouseClicked())
		{
			brightness_icon.clicked = !brightness_icon.clicked;
			SoundOn_icon.clicked = 0;
		}
	}
	if (brightness_icon.clicked)
	{
		RenderAsset(brightnesstxt, 255);
		RenderAsset(brightnesslow_icon, 255);
		RenderAsset(brightnesshigh_icon, 255);
		RenderAsset(brightnesshover_icon, 255);
		RenderAsset(brightnessSlider, 255);
		RenderAsset(brightnessSlidercircle, 255);
	}
	if (mouse_in_rect(brightnessSlidercircle.position.x, brightnessSlidercircle.position.y, brightnessSlidercircle.size.x, brightnessSlidercircle.size.y) == 1)
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_1) && !bright_clicked)
		{
			bright_clicked = 1;
		}
		else if (CP_Input_MouseReleased(MOUSE_BUTTON_1) && bright_clicked)
		{
			bright_clicked = 0;
		}
		
	}
	if (CP_Input_MouseDown(MOUSE_BUTTON_1) && bright_clicked)
	{
		brightposx += (int)CP_Input_GetMouseDeltaX();
		brightposx = CP_Math_ClampInt(brightposx, 35, 255);
		brightnessSlidercircle.position.x += CP_Input_GetMouseDeltaX();
		brightnessSlidercircle.position.x = (float)CP_Math_ClampInt((int)brightnessSlidercircle.position.x, (int)brightnessSlider.position.x -110, (int)brightnessSlider.position.x + 110 );
	}

		

	//SOUND ICON 
	RenderAsset(SoundOn_icon, 255); // renders the soundicon in the selection tab
	if (mouse_in_rect(SoundOn_icon.position.x, SoundOn_icon.position.y, SoundOn_icon.size.x, SoundOn_icon.size.y) == 1)	// soundon hover
	{
		RenderAsset(soundhover, 255);
		if (CP_Input_MouseClicked())
		{
			SoundOn_icon.clicked = !SoundOn_icon.clicked;
			brightness_icon.clicked = 0;
		}
	}
	if (SoundOn_icon.clicked)	//	renders the sound window if the sound icon in the tab is selected
	{
		RenderAsset(soundtxt, 255);
		RenderAsset(soundhover, 255);
		if (soundscaled.clicked == 1)	// renders large soundon icon
		{
			RenderAsset(soundscaled, 255);
			
			if (mouse_in_rect(soundscaled.position.x, soundscaled.position.y, soundscaled.size.x, soundscaled.size.y) == 1 && CP_Input_MouseClicked())	// if player clicks icon to mute sound
			{
				CP_Sound_PauseAll();
				soundscaled.clicked = !soundscaled.clicked;
			}
		}
		else	// renders large soundoff icon
		{
			RenderAsset(soundoffscaled, 255);
	
			if (mouse_in_rect(soundscaled.position.x, soundscaled.position.y, soundscaled.size.x, soundscaled.size.y) == 1 && CP_Input_MouseClicked())	// if player clicked icon to turn on sound
			{	
				CP_Sound_ResumeAll();
				soundscaled.clicked = !soundscaled.clicked;
			}
		}
	}

	RenderAsset(matte, 255 - brightposx);

}


void settings_shutdown(void){

}



