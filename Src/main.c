//#include "SpriteAnimation/spriteAnimation.h"
//#include "Character/diceHandler.h"
//#include "Character/charMovement.h"   
//#include "utils.h"
//#include "Level Stuff/lvl_editor.h"
//#include "GameObject/gameObject.h"
//#include "../Extern/CProcessing/inc/cprocessing.h"
//#include "yijia/settings_ui.h"
//#include "../Src/yijia/overworld_ui.h"
//#include "../Src/yijia/pause_ui .h"
//#define WINDOW_HEIGHT 1080
//#define LEVEL_EDITOR
//
////CP_Image logo;
//
//
//
//#include "Character/gameChar.h"
//
//GameObject logo;
//Sprite* ash;
//
//void game_init(void)
//{
//	logo.image = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
//	
//	//ash = CreateSprite("Assets/poke.png",4,4,true,true);
//
//	CP_Settings_ImageMode(CP_POSITION_CORNER);
//	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
//
//	
//	CP_System_SetWindowSize(CP_Image_GetWidth(logo.image), CP_Image_GetHeight(logo.image) * 3);
//
//	init_dice();
//	init_char(Warrior);
//}
//
//void game_update(void)
//{
//	// INPUT
//	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
//	if (CP_Input_KeyDown(KEY_ESCAPE))
//	{
//		CP_Engine_Terminate();
//	}
//	// UPDATE
//
//
//	// RENDER 
//	
//
//	//hardware_handler();
//	hardware_handler();
//	UpdateSprite(get_character()->sp, CP_System_GetDt());
//	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));
//
//	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
//	RenderSprite(get_character()->sp);
//}
//
//void game_exit(void)
//{
//	CP_Image_Free(&logo);
//
//
//	free_char();
//}
//
//
//
//
//void main(void)
//{
//	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
//	CP_Engine_SetNextGameState(settings_init, settings_update, settings_shutdown);
//	CP_Engine_Run();
//
// 	return 0;
//}
#include "GameStateManager.h"

void main(void)
{
	GameStateRun();
}
