#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"
#include "Character/gameEnemy.h"
#include "GameStateManager.h"
Sprite* ash;
game_map* Level;
Enemy* enemy;
float time = 0;
bool b_paused = false;
void game_init(void)
{
	//ash = CreateSprite("Assets/poke.png",4,4,true,true);

	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	Level = malloc(sizeof(game_map));
	init_dice();
	init_char(Warrior);
	init_map_obj(Level, 1280/get_character()->sp->go.size.x, 720/get_character()->sp->go.size.y, 1280, 720);
	enemy = CreateEnemy();
	enemy->sp->go.position.x = 7;
	enemy->sp->go.position.y = 5;
	enemy->sp->go.scale.x = 0.5;
	enemy->sp->go.scale.y = 0.5;
	enemy->steps = 1;
	GameStateSetNextSubScene(SPRITEANIMATION_SCENE, false);
	GameStateSetNextSubScene(MAX_SCENE, false);

}

void game_update(void)
{
	hardware_handler();
	float dt = CP_System_GetDt();
	time += dt;
	if (time > 1)
	{
		UpdateEnemy(enemy, dt, true);
		time -= 1;
	}
	else
		UpdateEnemy(enemy, dt, false);


	UpdateSprite(get_character()->sp, dt);


	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	RenderSpriteOnMap(get_character()->sp, Level);
	RenderSpriteOnMap(enemy->sp, Level);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	if (CP_Input_KeyTriggered(KEY_P))
	{
		if(!b_paused)
			GameStateSetNextSubScene(SPRITEANIMATION_SCENE, true);
		else
			GameStateSetNextSubScene(MAX_SCENE, true);
		b_paused = !b_paused;

	}

}

void game_exit(void)
{
	free(Level);
	free_char();
	FreeEnemy(enemy);
}