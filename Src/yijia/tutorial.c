/*---------------------------------------------------------------
  File: tutorial.c
  Project: DICE REBELS
  Author: Yeo Yi Jia, y.yijia@digipen.edu
  Co-Author: Liew Yeni, yeni.l@digipen.edu
  Co-Author: Muhammad Hazim Bin Gazali, m.bingazali@digipen.edu
  Copyright: 2022, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#include "cprocessing.h"
#include <stdbool.h>
#include "../yijia/tutorial.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"
#include "GameStateManager.h"
#include "../UI/UtilsUI/ui_utils.h"
#include "../yijia/pause_ui.h"

asset howtoplay1;
asset howtoplay2;
asset next;
asset prev; 
asset exit_icon;
int alpha;
extern bool sub;
void tutorial_init() {

	get_image_size_set("Assets/howtoplay1.png", &howtoplay1);
	get_image_size_set("Assets/howtoplay2.png", &howtoplay2);
	get_image_size_set("Assets/next.png", &next);
	get_image_size_set("Assets/prev.png", &prev);
	get_image_size_set("Assets/exit_icon.png", &exit_icon);
	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER); 

	//positions
	howtoplay1.position.x = (float)(CP_System_GetWindowWidth() - 640);
	howtoplay1.position.y = 360;

	howtoplay2.position.x = (float)(CP_System_GetWindowWidth() - 640);
	howtoplay2.position.y = 360;

	next.position.x = (float)(CP_System_GetWindowWidth() - 325);
	next.position.y = 380;

	prev.position.x = (float)(CP_System_GetWindowWidth() - 950);
	prev.position.y = 380;

	exit_icon.position.x = (float)(CP_System_GetWindowWidth() - 330);
	exit_icon.position.y = 220;

}

void tutorial_update() {

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	



	//Hover over exit
	if (mouse_in_rect(exit_icon.position.x, exit_icon.position.y, exit_icon.size.x - 10, exit_icon.size.y - 10) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(exit_icon, 255);
		if (CP_Input_MouseClicked())
		{
			sub = false;
			//exit
			GameStateSetNextSubScene(MAX_SCENE,false);
		}
	}
	
	if (!next.clicked)
	{
		if (mouse_in_rect(next.position.x, next.position.y, next.size.x - 10, next.size.y - 10) == 1)	 //-100 to reduce the size of area of detection 
		{

			if (CP_Input_MouseClicked())
			{

				next.clicked = !next.clicked;
			}
		}
		RenderAsset(howtoplay1, 255);
		RenderAsset(next, 255);

	}
	if (next.clicked == 1)
	{
		if (mouse_in_rect(prev.position.x, prev.position.y, prev.size.x - 10, prev.size.y - 10) == 1)	 //-100 to reduce the size of area of detection 
		{

			if (CP_Input_MouseClicked())
			{

				next.clicked = !next.clicked;
			}
		}
		RenderAsset(howtoplay2,255);
		RenderAsset(prev, 255);
	}
	RenderAsset(exit_icon, 200);

}

void tutorial_exit() {

}

