/*---------------------------------------------------------------
  File: pause_ui.c
  Project: DICE REBELS
  Author: Yeo Yi Jia, y.yijia@digipen.edu
  Co-Author: Liew Yeni, yeni.l@digipen.edu 
  Co-Author: Muhammad Hazim Bin Gazali, m.bingazali@digipen.edu    
  Copyright: 2022, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/

#include "cprocessing.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "../UI/UtilsUI/ui_utils.h"
//#include"../yijia/pause_ui.h"
#include "GameStateManager.h"

asset pausedpopup;
asset arrowicon;
asset exit_icon;
asset gamepaused; 
asset resume;
asset restart;
asset exittxt;
int alpha;
extern bool sub;

void gamepaused_init(void) 
{
	//get_image_size_set("Assets/settings_icon.png", &settings_icon);
	get_image_size_set("Assets/pausedpopup.png", &pausedpopup);
	get_image_size_set("Assets/exit_icon.png", &exit_icon);
	get_image_size_set("Assets/gamepaused.png", &gamepaused);
	get_image_size_set("Assets/arrowicon.png", &arrowicon);
	get_image_size_set("Assets/resume.png", &resume);
	get_image_size_set("Assets/restart.png", &restart);
	get_image_size_set("Assets/exittxt.png", &exittxt);

	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	//POSITIONS

	pausedpopup.position.x = CP_System_GetWindowWidth() - 640;
	pausedpopup.position.y = 360;

	exit_icon.position.x = CP_System_GetWindowWidth() - 330;
	exit_icon.position.y = 220;

	gamepaused.position.x = CP_System_GetWindowWidth() - 640;
	gamepaused.position.y = 280;
	
	restart.position.x = CP_System_GetWindowWidth() - 640;
	restart.position.y = 350;

	resume.position.x = CP_System_GetWindowWidth() - 640;
	resume.position.y = 410;

	exittxt.position.x = CP_System_GetWindowWidth() - 640;
	exittxt.position.y = 470;
}


void gamepaused_update(void) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	RenderAsset(pausedpopup, 255);
	RenderAsset(gamepaused, 255);

	RenderAsset(resume, 200);
	if (mouse_in_rect(resume.position.x, resume.position.y, resume.size.x, resume.size.y) == 1) {
		arrowicon.position.x = resume.position.x -190;
		arrowicon.position.y = resume.position.y;
		RenderAsset(resume, 255);
		RenderAsset(arrowicon, 255);
		if (CP_Input_MouseClicked())
		{
			sub = false;
			GameStateSetNextSubScene(MAX_SCENE,true);	
		}
	}

	RenderAsset(restart, 200);
	if (mouse_in_rect(restart.position.x, restart.position.y, restart.size.x, restart.size.y) == 1) {
		arrowicon.position.x = restart.position.x - 130;
		arrowicon.position.y = restart.position.y;
		RenderAsset(restart, 255);
		RenderAsset(arrowicon, 255);
		if (CP_Input_MouseClicked())
		{
			combatants_present = false;
			if (the_enemy)
				the_enemy->b_combat = false;
			setNextLvl(currLvl);
			GameStateSetNextScene(GAME_SCENE);
			sub = false;
			GameStateSetNextSubScene(MAX_SCENE, true);
		}
	}
	
	RenderAsset(exittxt, 200);
	if (mouse_in_rect(exittxt.position.x, exittxt.position.y, exittxt.size.x, exittxt.size.y) == 1) {
		arrowicon.position.x = exittxt.position.x - 100;
		arrowicon.position.y = exittxt.position.y;
		RenderAsset(exittxt, 255);
		RenderAsset(arrowicon, 255);
		if (CP_Input_MouseClicked())
		{
			setInitScene(false);
			GameStateSetNextScene(MAINMENU_SCENE);
			sub = false;
			GameStateSetNextSubScene(MAX_SCENE, true);
		}
	}

	RenderAsset(exit_icon, 255);
	if (mouse_in_rect(exit_icon.position.x, exit_icon.position.y, exit_icon.size.x, exit_icon.size.y))
	{
		if (CP_Input_MouseClicked()) {
			sub = false;
			GameStateSetNextSubScene(MAX_SCENE, true);
		}
	}
}


void gamepaused_shutdown(void) {


}


