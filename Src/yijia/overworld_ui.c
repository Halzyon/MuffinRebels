#include "cprocessing.h"
#include "GameStateManager.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "../yijia/overworld_ui.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"

asset bg;
asset button;
asset button2;
asset button3;
asset button1pressed;
asset button2pressed;
asset button3pressed;
asset settings;
asset lvl1icon;
asset lvl2icon;
asset lvl3icon; 
asset prev;
int alpha; 

void overworld_init(void) {
	
	CP_System_SetWindowSize(1280, 720); 
	CP_Settings_ImageMode(CP_POSITION_CENTER);  

	//get_image_size_set("Assets/exitsetting_icon.png", &exitsetting_icon);
	get_image_size_set("Assets/lvl1icon.png", &lvl1icon);
	get_image_size_set("Assets/lvl2icon.png", &lvl2icon);
	get_image_size_set("Assets/lvl3icon.png", &lvl3icon);
	get_image_size_set("Assets/button.png", &button);
	get_image_size_set("Assets/button2.png", &button2);
	get_image_size_set("Assets/button3.png", &button3);
	get_image_size_set("Assets/button1pressed.png", &button1pressed);
	get_image_size_set("Assets/button3pressed.png", &button3pressed);
	get_image_size_set("Assets/button2pressed.png", &button2pressed);
	get_image_size_set("Assets/combat_overlay_ui/settings.png", &settings);
	get_image_size_set("Assets/bg.png", &bg);
	get_image_size_set("Assets/prev.png", &prev);

	//positions

	settings.position.x = CP_System_GetWindowWidth() - 50;
	settings.position.y = 50;

	button.position.x = CP_System_GetWindowWidth() - 640;
	button.position.y = 220;

	button2.position.x = CP_System_GetWindowWidth() - 640;
	button2.position.y = 370;

	button3.position.x = CP_System_GetWindowWidth() - 640;
	button3.position.y = 520;

	button1pressed.position.x = CP_System_GetWindowWidth() - 640;
	button1pressed.position.y = 220;

	button2pressed.position.x = CP_System_GetWindowWidth() - 640;
	button2pressed.position.y = 370;

	button3pressed.position.x = CP_System_GetWindowWidth() - 640;
	button3pressed.position.y = 520;

	lvl1icon.position.x = CP_System_GetWindowWidth() - 640;
	lvl1icon.position.y = 220;

	lvl2icon.position.x = CP_System_GetWindowWidth() - 640; 
	lvl2icon.position.y = 370;

	lvl3icon.position.x = CP_System_GetWindowWidth() - 640;
	lvl3icon.position.y = 520;

	bg.position.x = CP_System_GetWindowWidth() - 640;
	bg.position.y = 360;

	prev.position.x = CP_System_GetWindowWidth() - 1230;
	prev.position.y = 670;

}


void overworld_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	RenderAsset(prev, 128);
	//if (mouse_in_rect(prev.position.x, prev.position.y, prev.size.x - 10, prev.size.y - 10) == 1)	 //-100 to reduce the size of area of detection 
	//{
	//	RenderAsset(prev, 255);
	//	if (CP_Input_MouseClicked())
	//	{
	//		//exit
	//		GameStateSetNextSubScene(MAX_SCENE, false);
	//	}
	
	RenderAsset(bg, 128); 

	//SETTINGS ICON - open settings_ui
	RenderAsset(settings, 255);
	//if (mouse_in_rect(settings_icon.position.x, settings_icon.position.y, settings_icon.size.x, settings_icon.size.y) == 1)
	//{
	//	//open settings pop up
	//}

	//LVL 1 BUTTON
	RenderAsset(button, 255);
	if (mouse_in_rect(button.position.x, button.position.y, button.size.x-100, button.size.y-100) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button1pressed, 255);
		if (CP_Input_MouseClicked())
		{
			button.clicked = !button.clicked;
		}
		//if (button.clicked == 1 )
		//{
		//	//level 1 
		//}
	}

	//LVL 2 BUTTON 
	RenderAsset(button2, 255);
	if (mouse_in_rect(button2.position.x, button2.position.y, button2.size.x - 100, button2.size.y - 100) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button2pressed, 255);
		if (CP_Input_MouseClicked())
		{
			button2.clicked = !button2.clicked;
		}
		//if (button2.clicked == 1 )
		//{
		//	//level 2
		//}
	}

	RenderAsset(button3, 255);
	if (mouse_in_rect(button3.position.x, button3.position.y, button3.size.x - 100, button3.size.y - 100) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button3pressed, 255);
		if (CP_Input_MouseClicked())
		{
			button3.clicked = !button3.clicked;
		}
		//if (button3.clicked == 1 )
		//{
		//	//level 3
		//}
	}
	RenderAsset(lvl1icon, 255);
	RenderAsset(lvl2icon, 255);
	RenderAsset(lvl3icon, 255);


}



void overworld_shutdown(void) {


}



