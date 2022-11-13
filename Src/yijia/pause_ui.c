#include "cprocessing.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "../UI/UtilsUI/ui_utils.h"
#include"../yijia/pause_ui .h"

asset pausedpopup;
asset arrowicon;
asset exit_icon;
asset settings_icon;
asset gamepaused; 
asset resume;
asset restart;
asset exittxt;
int alpha;

void gamepaused_init(void) {

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
	settings_icon.position.x = CP_System_GetWindowWidth() - 50;
	settings_icon.position.y = 50;

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
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	RenderAsset(settings_icon, 255);
	RenderAsset(pausedpopup, 255);
	RenderAsset(gamepaused, 255);

	RenderAsset(resume, 255);
	if (mouse_in_rect(resume.position.x, resume.position.y, resume.size.x -100, resume.size.y - 100 ) == 1) {
		arrowicon.position.x = resume.position.x -100;
		arrowicon.position.y = resume.position.y;
		RenderAsset(arrowicon, 255);
		/*if (CP_Input_MouseClicked())
		{
		resumes
		}*/
	}

	RenderAsset(restart, 255);
	if (mouse_in_rect(restart.position.x, restart.position.y, restart.size.x -100, restart.size.y -100) == 1) {
		arrowicon.position.x = restart.position.x - 100;
		arrowicon.position.y = restart.position.y;
		RenderAsset(arrowicon, 255);
		/*if (CP_Input_MouseClicked())
			{
			restarts
			}*/
	}
	
	RenderAsset(exittxt, 255);
	if (mouse_in_rect(exittxt.position.x, exittxt.position.y, exittxt.size.x -100, exittxt.size.y - 100) == 1) {
		arrowicon.position.x = exittxt.position.x - 60;
		arrowicon.position.y = exittxt.position.y;
		RenderAsset(arrowicon, 255);
		/*if (CP_Input_MouseClicked())
		{
			exits
		}*/
	}

	RenderAsset(exit_icon, 255); //not very necessary 
	/*if (CP_Input_MouseClicked()) {
	   close pop up = resume 
	}*/
}


void gamepaused_shutdown(void) {


}


