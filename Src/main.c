//#include "cprocessing.h"
#include "FileIO/fileIO.h"
#include "FileIO/serialization.h"
#include "FileIO/encode.h"
#include "Character/gameMap.h"
#include "Character/gameChar.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"   
#include "UI/CombatOverlayUI/combat_overlay.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"

CP_Image logo;
Sprite* ash;
void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	
	//ash = CreateSprite("Assets/poke.png",4,4,true,true);

	//CP_System_Fullscreen();
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(1280,720);
	combat_init();
	init_dice();
	init_char(Warrior);
	//init_map_obj(10, 10, &map1);
	
	//CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo) * 3);
}

void game_update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	combat_buttons(5);
	health_bar(4);
	settings_button();

	hardware_handler();
	UpdateSprite(get_character()->sp, CP_System_GetDt());
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));

	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	RenderSprite(get_character()->sp);

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	
}

void game_exit(void)
{
	CP_Image_Free(&logo);
	//free_map_obj(&map1);
	free_char();
	combat_ui_shutdown();
	CP_Image_Free(&ash->go.image);
	free(ash);
}




void main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}