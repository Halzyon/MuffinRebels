#include "SpriteAnimation/spriteAnimation.h"
#include "../Character/diceHandler.h"
#include "../Character/charMovement.h"   
#include "../utils.h"
#include "../Level Stuff/lvl_editor.h"


#define WINDOW_HEIGHT 1080
#define LEVEL_EDITOR

//CP_Image logo;



#include "../Character/gameChar.h"

Sprite* ash;

void game_init(void)
{

	ash = CreateSprite("Assets/poke.png",4,4,true,true);

	init_dice();
	init_char(Warrior);
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
	hardware_handler();
	UpdateSprite(get_character()->sp, CP_System_GetDt());
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	RenderSprite(get_character()->sp);
}

void game_exit(void)
{
	

	free(ash);
	free_char();
}
