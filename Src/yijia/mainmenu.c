#include "cprocessing.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"
#include "../yijia/mainmenu.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"
#include "GameStateManager.h"

asset button;
asset button1pressed;
asset button2;
asset button2pressed;
asset button3;
asset button3pressed;
asset settings;
asset creditstxt;
asset exittxtlarge;
asset startxt;
asset bg;
asset dicerebellogo;
CP_Sound click;
asset qnmark;
int alpha; 
extern asset matte;
extern int brightposx;
bool sub = false;
extern int currentScene;

void mainmenu_init() {
	
	//	loads images and finds their sizes
	//CP_Sound_PlayAdvanced(*bgm, 0.5f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);

	get_image_size_set("Assets/button.png", &button);
	get_image_size_set("Assets/button2.png", &button2);
	get_image_size_set("Assets/button3.png", &button3);
	get_image_size_set("Assets/button1pressed.png", &button1pressed);
	get_image_size_set("Assets/button2pressed.png", &button2pressed);
	get_image_size_set("Assets/button3pressed.png", &button3pressed);
	get_image_size_set("Assets/combat_overlay_ui/settings.png", &settings);
	get_image_size_set("Assets/creditstxt.png", &creditstxt);
	get_image_size_set("Assets/exittxtlarge.png", &exittxtlarge);
	get_image_size_set("Assets/startxt.png", &startxt);
	get_image_size_set("Assets/bg.png", &bg);
	get_image_size_set("Assets/dicerebellogo.png", &dicerebellogo);
	get_image_size_set("Assets/qnmark.png", &qnmark);
	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	second_sfx_init();
	//positions
	settings.position.x = CP_System_GetWindowWidth() - 50;
	settings.position.y = 50;

	button.position.x = CP_System_GetWindowWidth() - 640;
	button.position.y = 300;

	button2.position.x = CP_System_GetWindowWidth() - 640;
	button2.position.y = 450;

	button3.position.x = CP_System_GetWindowWidth() - 640;
	button3.position.y = 600;

	button1pressed.position.x = button.position.x;
	button1pressed.position.y = button.position.y;

	button2pressed.position.x = button2.position.x;
	button2pressed.position.y = button2.position.y;

	button3pressed.position.x = button3.position.x;
	button3pressed.position.y = button3.position.y;

	creditstxt.position.x = CP_System_GetWindowWidth() - 640;
	creditstxt.position.y = 445;

	startxt.position.x = CP_System_GetWindowWidth() - 640;
	startxt.position.y = 295;

	exittxtlarge.position.x = CP_System_GetWindowWidth() - 640;
	exittxtlarge.position.y = 595;

	bg.position.x = CP_System_GetWindowWidth() - 640;
	bg.position.y = 360;

	dicerebellogo.position.x= CP_System_GetWindowWidth() - 640;
	dicerebellogo.position.y = 150;

	qnmark.position.x = CP_System_GetWindowWidth() - 50;
	qnmark.position.y = 160;
	
	GameStateSetNextSubScene(SETTINGS_SCENE, false);
	GameStateSetNextSubScene(MAX_SCENE, false);
}


void mainmenu_update() {

	
	//SETTINGS ICON - open settings_ui

	if (!sub)
	{
		if (mouse_in_rect(settings.position.x, settings.position.y, settings.size.x, settings.size.y) == 1)
		{
			if (CP_Input_MouseClicked())
			{
				CP_Sound_Play(click);
				GameStateSetNextSubScene(SETTINGS_SCENE, true);
				sub = true;
			}
		}

		if (mouse_in_rect(button.position.x, button.position.y, button.size.x, button.size.y) == 1)	 //-100 to reduce the size of area of detection 
		{
			RenderAsset(button1pressed, 255);
			if (CP_Input_MouseClicked())
			{
				CP_Sound_Play(click);
				GameStateSetNextScene(OVERWORLD_UI_SCENE);
			}

		}

		//LVL 2 BUTTON 

		if (mouse_in_rect(button2.position.x, button2.position.y, button2.size.x, button2.size.y) == 1)	 //-100 to reduce the size of area of detection 
		{
			RenderAsset(button2pressed, 255);
			if (CP_Input_MouseClicked())
			{
				CP_Sound_Play(click);
				currentScene = 0;
				GameStateSetNextScene(CREDITS_SCENE);
			}
			//if (button2.clicked == 1 )
			//{
			//	//level 2
			//}
		}


		if (mouse_in_rect(button3.position.x, button3.position.y, button3.size.x, button3.size.y) == 1)	 //-100 to reduce the size of area of detection 
		{
			RenderAsset(button3pressed, 255);
			if (CP_Input_MouseClicked())
			{
				CP_Sound_Play(click);
				CP_Engine_Terminate();
			}
			//if (button3.clicked == 1 )
			//{
			//	//level 3
			//}

		}
		if (mouse_in_rect(qnmark.position.x, qnmark.position.y, qnmark.size.x , qnmark.size.y) == 1)	 //-100 to reduce the size of area of detection 
		{
			if (CP_Input_MouseClicked())
			{
				CP_Sound_Play(click);
				GameStateSetNextSubScene(TUTORIAL_SCENE, false);
				sub = true;
			}
		}
	}
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	RenderAsset(bg, 255);
	RenderAsset(dicerebellogo, 255);
	RenderAsset(qnmark, 255);

	//SETTINGS ICON - open settings_ui


	RenderAsset(settings, 255);
	RenderAsset(button, 255);
	RenderAsset(button2, 255);
	RenderAsset(button3, 255);
	RenderAsset(startxt, 255);
	RenderAsset(exittxtlarge, 255);
	RenderAsset(creditstxt, 255);

	if (!sub)
		RenderAsset(matte, 255 - brightposx);
}


void mainmenu_exit(){

}


void RenderAsset(asset render, int opacity)
{
	CP_Image_Draw(render.image, render.position.x, render.position.y, render.size.x, render.size.y, opacity);
}