#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"

CP_Image logo;
Sprite* ash;
game_map* Level;
void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	
	//ash = CreateSprite("Assets/poke.png",4,4,true,true);

	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo) * 3);

	Level = malloc(sizeof(game_map));
	init_dice();
	init_char(Warrior);
	init_map_obj(CP_Image_GetWidth(logo) / get_character()->sp->go.size.x, CP_Image_GetHeight(logo) / get_character()->sp->go.size.y, Level, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
}

void game_update(void)
{
	hardware_handler();
	UpdateSprite(get_character()->sp, CP_System_GetDt());
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));

	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	RenderSprite(get_character()->sp,Level);

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	
}

void game_exit(void)
{
	CP_Image_Free(&logo);
	free(Level);
	free_char();
}




void main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}