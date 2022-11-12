#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"
#include "Character/gameEnemy.h"
#include "GameStateManager.h"
#include "../Combat/combatHandler.h"
#include "../Character/gameMap.h"
#include "../FileIO/fileIO.h"

Sprite* ash;
game_map* Level;
Enemy* enemy;
bool b_paused = false;
void game_init(void)
{
	// set draw settings
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	// create and initialise cplayer
	init_dice();
	init_char(Warrior);
	get_character()->sp->go.position.x = 4;
	//creating map data
	Level = malloc(sizeof(game_map));
	init_map_obj(Level, 10, 10, CP_System_GetWindowHeight(), CP_System_GetWindowHeight());
	Buffer* b = newBuffer();
	b->data = readFile("map.dat");
	size_t len = 0;
	//b->data = b64_decode(b->data, strlen(b->data), &len);
	load_map_file(Level, b->data);
	clearBuffer(b);
	fclose(getFile("map.dat"));

	//creating and initialise 1 enemy
	enemy = CreateEnemy();
	enemy->sp->go.position.x = 12;
	enemy->sp->go.position.y = 5;
	enemy->sp->go.scale.x = 0.5;
	enemy->sp->go.scale.y = 0.5;

	enemy->steps = 1;
	loadSprites();
	//set sub scenes to run 
	GameStateSetNextSubScene(COMBAT_OVERLAY_SCENE, false);
	//GameStateSetNextSubScene(MAX_SCENE, false); // to stop sub scene from running*/
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

	//GameStateSetNextSubScene(COMBAT_OVERLAY_SCENE, true);


	//get player input
	hardware_handler();
	//update player pos
	UpdateSprite(get_character()->sp, dt);

	//set logic for enemy temporary
	if(get_character()->sp->moved)
		UpdateEnemy(enemy, dt, true);
	else
		UpdateEnemy(enemy, dt, false);
	UpdateCombat(enemy, dt);


	/*if (enemy->enemyState == ATTACK_STATE)
	{
		declare_combatants(enemy, enemy->enemyState);
		for (; get_character()->energy >= 0; --get_character()->energy)
		{
			combat_phase();
			if (get_character()->hp == 0 || enemy->hp == 0)
				break;
		}
	}

	*/
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