/*---------------------------------------------------------------
  File: credits.c
  Project: DICE REBELS
  Author: Yeo Yi Jia, y.yijia@digipen.edu
  Co-Author: Liew Yeni, yeni.l@digipen.edu
  Co-Author: Muhammad Hazim Bin Gazali, m.bingazali@digipen.edu
  Copyright: 2022, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#include "cprocessing.h"
#include <stdbool.h>
#include "../yijia/credits.h"
#include "../UI/UtilsUI/ui_utils.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"
#include "GameStateManager.h"
#include "../yijia/pause_ui.h"

asset credit[5]; 
int currentScene = 0;
static int alpha = 255;


void credits_init() {
get_image_size_set("Assets/credit1.png", &credit[0]);
get_image_size_set("Assets/credit2.png", &credit[1]);
get_image_size_set("Assets/credit3.png", &credit[2]);
get_image_size_set("Assets/credit4.png", &credit[3]);
get_image_size_set("Assets/credit5.png", &credit[4]);
CP_System_SetWindowSize(1280, 720);
CP_Settings_ImageMode(CP_POSITION_CENTER);

credit[0].position.x = (float)(CP_System_GetWindowWidth() - 640);
credit[0].position.y = 360;

credit[1].position.x = credit[0].position.x;
credit[1].position.y = credit[0].position.y;

credit[2].position.x = credit[0].position.x;
credit[2].position.y = credit[0].position.y;

credit[3].position.x = credit[0].position.x;
credit[3].position.y = credit[0].position.y;

credit[4].position.x = credit[0].position.x;
credit[4].position.y = credit[0].position.y;
 alpha = 255;
}


void credits_update() {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	float Speed = 90; //speed of alpha 
	Speed *= CP_System_GetDt(); //time difference between frames 
	alpha = alpha  - (int)Speed; //fading of bg
	if (alpha < 2)
	{
		alpha = 255;
		++currentScene; 
		if (currentScene > 4)
		{
			GameStateSetNextScene(MAINMENU_SCENE);
			return;
		}
	}

	RenderAsset(credit[currentScene], alpha);
	
}

void credits_exit() {

}

