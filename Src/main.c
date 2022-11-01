#include "cprocessing.h"
#include "FileIO/fileIO.h"
#include "FileIO/serialization.h"
#include "FileIO/encode.h"
#include "Character/gameMap.h"
#include "Character/gameChar.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"   
#include "utils.h"
#include "Level Stuff/lvl_editor.h"

CP_Image logo;


#define WINDOW_HEIGHT 1080
#define LEVEL_EDITOR

//CP_Image logo;


void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);


	

	init_dice();
	init_char(Warrior);
	//CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));


}

void game_update(void)
{
	// INPUT
	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
	// UPDATE


	// RENDER 
	

	//hardware_handler();
}

void game_exit(void)
{
	CP_Image_Free(&logo);
	
	//free_char();
	
}




int main(void)
{


	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(editor_init, editor_update, editor_exit);
	CP_Engine_Run();

 	return 0;
}
