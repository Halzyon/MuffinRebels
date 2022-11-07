#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"

Sprite* ash;
game_map* Level;
void game_init(void)
{
	//ash = CreateSprite("Assets/poke.png",4,4,true,true);

	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	Level = malloc(sizeof(game_map));
	init_dice();
	init_char(Warrior);
	init_map_obj(Level, get_character()->sp->go.size.x, get_character()->sp->go.size.y, 1280, 720);
}

void game_update(void)
{
	hardware_handler();
	UpdateSprite(get_character()->sp, CP_System_GetDt());
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	RenderSpriteOnMap(get_character()->sp, Level);

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}

}

void game_exit(void)
{
	free(Level);
	free_char();
}