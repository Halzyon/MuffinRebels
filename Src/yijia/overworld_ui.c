/*---------------------------------------------------------------
  File: overworld.c
  Project: DICE REBELS
  Author: Yeo Yi Jia, y.yijia@digipen.edu
  Co-Author: Liew Yeni, yeni.l@digipen.edu
  Co-Author: Muhammad Hazim Bin Gazali, m.bingazali@digipen.edu
  Copyright: 2022, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#include "cprocessing.h"
#include "GameStateManager.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "../yijia/overworld_ui.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"
#include "GameStateManager.h"
#include "../Scenes/GameScene.h"
#include "../yijia/pause_ui.h"

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
extern asset matte;
extern int brightposx;
extern bool sub;
extern int enemykilled;
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
	get_image_size_set("Assets/bg.png", &bg);
	get_image_size_set("Assets/prevscaled.png", &prev);

	//positions


	button.position.x = (float)(CP_System_GetWindowWidth() - 640);
	button.position.y = 220;

	button2.position.x = (float)(CP_System_GetWindowWidth() - 640);
	button2.position.y = 370;

	button3.position.x = (float)(CP_System_GetWindowWidth() - 640);
	button3.position.y = 520;

	button1pressed.position.x = (float)(CP_System_GetWindowWidth() - 640);
	button1pressed.position.y = 220;

	button2pressed.position.x = (float)(CP_System_GetWindowWidth() - 640);
	button2pressed.position.y = 370;

	button3pressed.position.x = (float)(CP_System_GetWindowWidth() - 640);
	button3pressed.position.y = 520;

	lvl1icon.position.x = (float)(CP_System_GetWindowWidth() - 640);
	lvl1icon.position.y = 220;

	lvl2icon.position.x = (float)(CP_System_GetWindowWidth() - 640);
	lvl2icon.position.y = 370;

	lvl3icon.position.x = (float)(CP_System_GetWindowWidth() - 640);
	lvl3icon.position.y = 520;

	bg.position.x = (float)(CP_System_GetWindowWidth() - 640);
	bg.position.y = 360;

	prev.position.x = (float)(CP_System_GetWindowWidth() - 1230);
	prev.position.y = 670;

}


void overworld_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	RenderAsset(prev, 150);
	if (mouse_in_rect(prev.position.x, prev.position.y, prev.size.x - 10, prev.size.y - 10) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(prev, 255);
		if (CP_Input_MouseClicked())
		{
			//exit
			GameStateSetNextScene(MAINMENU_SCENE);
		}
	}
	RenderAsset(bg, 128); 


	//LVL 1 BUTTON
	RenderAsset(button, 255);
	if (mouse_in_rect_lvl(button.position.x, button.position.y, button.size.x, button.size.y) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button1pressed, 255);
		if (CP_Input_MouseClicked())
		{
		//	button.clicked = !button.clicked;
		//}
		//if (button.clicked == 1 )
		//{
			enemykilled = 0;
			GameStateSetNextScene(GAME_SCENE);
			button.clicked = 0;
			
			setNextLvl(0);
		}
	}

	//LVL 2 BUTTON 
	RenderAsset(button2, 255);
	if (mouse_in_rect_lvl(button2.position.x, button2.position.y, button2.size.x, button2.size.y) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button2pressed, 255);
		if (CP_Input_MouseClicked())
		{
		//	button2.clicked = !button2.clicked;
		//}
		//if (button2.clicked == 1 )
		//{
			// 2level
			enemykilled = 0;
			GameStateSetNextScene(GAME_SCENE);
			button2.clicked = 0;
			setNextLvl(1);
		}
	}

	RenderAsset(button3, 255);
	if (mouse_in_rect_lvl(button3.position.x, button3.position.y, button3.size.x, button3.size.y) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button3pressed, 255);
		if (CP_Input_MouseClicked())
		{
		//	button3.clicked = !button3.clicked;
		//}
		//if (button3.clicked == 1 )
		//{
			//level 3
			enemykilled = 0;
			GameStateSetNextScene(GAME_SCENE);
			button3.clicked = 0;
			setNextLvl(2);
		}
	}
	RenderAsset(lvl1icon, 255);
	RenderAsset(lvl2icon, 255);
	RenderAsset(lvl3icon, 255);
	
	if (!sub)
		RenderAsset(matte, 255 - brightposx);

}



void overworld_shutdown(void) {


}



