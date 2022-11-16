#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"
#include "Character/gameEnemy.h"
#include "GameStateManager.h"
#include "../Combat/combatHandler.h"
#include "../Character/gameMap.h"
#include "../FileIO/fileIO.h"

#define ENEMYSIZE 1

Sprite* ash;
game_map* Level;
Enemy* enemy[ENEMYSIZE];
bool b_paused = false;


extern asset matte;
extern int brightposx;
extern bool sub;
CP_BOOL combatStart = false;
CP_BOOL combatOver = false;
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
	for (int i = 0; i < ENEMYSIZE; ++i)
	{
		enemy[i] = CreateEnemy();
		enemy[i]->sp->go.position.x = 12;
		enemy[i]->sp->go.position.y = 5;
		enemy[i]->sp->go.scale.x = 0.5;
		enemy[i]->sp->go.scale.y = 0.5;

		enemy[i]->steps = 1;
	}
	loadSprites();

	//set sub scenes to run 
	GameStateSetNextSubScene(PAUSE_SCENE, false);
	GameStateSetNextSubScene(COMBAT_OVERLAY_SCENE, false);
	GameStateSetNextSubScene(OVERWORLD_UI_SCENE, false);
	GameStateSetNextSubScene(BATTLE_SCENE, false);
	GameStateSetNextSubScene(BATTLE_SCENE_UI, false);
	GameStateSetNextSubScene(MAX_SCENE, true);
}

void game_update(void)
{
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	//UPDATE
	float dt = CP_System_GetDt();

	//Scene inputs
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	if (CP_Input_KeyDown(KEY_P))
	{
		GameStateSetNextSubScene(PAUSE_SCENE, true);
	}



	//get player input
	hardware_handler();

	if (combatStart && !combatOver)
	{
		ManualUpdate(BATTLE_SCENE);
		ManualUpdate(BATTLE_SCENE_UI);
		// if enemy dead/player dead do smth
		if (CP_Input_KeyDown(KEY_2))
		{
			battleEnd();
		}
		if (getCombatState())
		{
			combatStart = false;
			combatOver = true;
		}
	}
	else
	{
		//update player pos
		UpdateSprite(get_character()->sp, dt);

		for (int i = 0; i < ENEMYSIZE; ++i)
		{
			//set logic for enemy temporary
			if (get_character()->sp->moved)
				UpdateEnemy(enemy[i], dt, true);
			else
				UpdateEnemy(enemy[i], dt, false);
			UpdateCombat(enemy[i], dt);
		}

		combat_phase();


		if ((enemy[0]->b_combat && !combatStart) || CP_Input_KeyDown(KEY_1))
		{
			second_init();
			combat_scene_init();
			combatStart = true;
			combatOver = false;
		}



		//RENDER
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Vector vec = { CP_System_GetWindowWidth() / 4.5,0 };
		render_map(Level, vec);

		//render player
		RenderSpriteOnMap(get_character()->sp, Level);

		//render enemy
		for (int i = 0; i < ENEMYSIZE; ++i)
			RenderSpriteOnMap(enemy[i]->sp, Level);

		ManualUpdate(COMBAT_OVERLAY_SCENE);
		if (!sub)
			RenderAsset(matte, 255 - brightposx);
	}
	
}

void game_exit(void)
{
	free(Level);
	free_char();
	for(int i = 0; i < ENEMYSIZE; ++i)
		FreeEnemy(enemy[i]);
}


unsigned char getEnemyState()
{
	return enemy[0]->enemyState;
}
