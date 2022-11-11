#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"
#include "Character/gameEnemy.h"
#include "GameStateManager.h"
#include "../Character/gameMap.h"
#include "../FileIO/fileIO.h"

Sprite* ash;
game_map* Level;
Enemy* enemy;
bool b_paused = false;
void game_init(void)
{
	CP_System_SetWindowSize(1280,720);
	// set draw settings
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	// create and initialise cplayer
	init_dice();
	init_char(Warrior);

	//creating map data
	Level = malloc(sizeof(game_map));
	init_map_obj(Level, 15, 15, CP_System_GetWindowHeight(), CP_System_GetWindowHeight());
	Buffer* b = newBuffer();
	b->data = readFile("map.dat");
	size_t len = 0;
	//b->data = b64_decode(b->data, strlen(b->data), &len);
	load_map_file(Level, b->data);
	clearBuffer(b);
	fclose(getFile("map.dat"));

	//creating and initialise 1 enemy
	enemy = CreateEnemy();
	enemy->sp->go.position.x = 7;
	enemy->sp->go.position.y = 5;
	enemy->sp->go.scale.x = 0.5;
	enemy->sp->go.scale.y = 0.5;

	enemy->steps = 1;
	loadSprites();
	//set sub scenes to run 
	GameStateSetNextSubScene(SPRITEANIMATION_SCENE, false);
	GameStateSetNextSubScene(MAX_SCENE, false); // to stop sub scene from running*/
}

void game_update(void)
{
	//UPDATE
	float dt = CP_System_GetDt();

	//Scene inputs
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	//Trigger for sub scene
	if (CP_Input_KeyTriggered(KEY_P))
	{
		if (!b_paused)
			GameStateSetNextSubScene(SPRITEANIMATION_SCENE, true);
		else
			GameStateSetNextSubScene(MAX_SCENE, true);
		b_paused = !b_paused;
	}

	//get player input
	hardware_handler();
	//update player pos
	UpdateSprite(get_character()->sp, dt);

	//set logic for enemy temporary
	if(get_character()->sp->moved)
		UpdateEnemy(enemy, dt, true);
	else
		UpdateEnemy(enemy, dt, false);


	//RENDER
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Vector vec = {CP_System_GetWindowWidth() / 4.5,0};
	render_map(Level,vec);

	//render player
	RenderSpriteOnMap(get_character()->sp, Level);

	//render enemy
	RenderSpriteOnMap(enemy->sp, Level);
}

void game_exit(void)
{
	free(Level);
	free_char();
	FreeEnemy(enemy);
}