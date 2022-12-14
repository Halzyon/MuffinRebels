/*---------------------------------------------------------------
  File: gameOver.c
  Project: DICE REBELS
  Author: Muhammad Hazim Bin Gazali, m.bingazali@digipen.edu
  Co-Author: Yeo Yi Jia, y.yijia@digipen.edu 
  Copyright: 2022, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "cprocessing.h"
#include "../yijia/gameOver.h"
#include "../UI/UtilsUI/ui_utils.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "settings_ui.h"
#include "GameStateManager.h"

//Game Over and win page

asset win;
asset gameover;
static int alpha;
CP_Vector overPos;
float overdt;
extern bool sub;
void gameTransition_init(void) {
	get_image_size_set("Assets/win.png", &win);
	get_image_size_set("Assets/gameover.png", &gameover);

	//position
	/*win.position.x = CP_System_GetWindowWidth() - 640;
	win.position.y = 360;*/

	win.position.x = 0;
	win.position.y = 360;

	gameover.position.x = 0;
	gameover.position.y = 360;

	/*gameover.position.x = CP_System_GetWindowWidth() - 640;
	gameover.position.y = 360;*/
	overPos.x = CP_System_GetWindowWidth() / 2.0f;
	overPos.y = CP_System_GetWindowHeight() / 2.0f;
	overdt = 0;
	// TODO: pause the bgm here

}


void gameTransition_update(void) {
	//win
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	if (win.position.x > overPos.x - 1 && win.position.x < overPos.x + 1)
	{
		if (win.position.y > overPos.y - 1 && win.position.y < overPos.y + 1)
		{
			overdt += CP_System_GetDt();
			if (overdt >= 3)
			{
				setInitScene(false);
				GameStateSetNextScene(MAINMENU_SCENE);
				sub = false;
			}
		}
	}
	//gameover
	if (get_character()->hp > 0)
	{
		go_to_animation(overPos.x, overPos.y, &win.position);
		RenderAsset(win, 255);
	}
	else
	{
		go_to_animation(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, &gameover.position);
		RenderAsset(gameover, 255);
	}



}


void gameTransition_shutdown(void) {

}


