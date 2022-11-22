#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"
#include "Character/gameEnemy.h"
#include "GameStateManager.h"
#include "../Combat/combatHandler.h"
#include "../Character/gameMap.h"
#include "../FileIO/fileIO.h"

#define ENEMYSIZE 2
#define FILEPATH "Assets/"


Sprite* ash;
game_map* Level;
Enemy* enemy[ENEMYSIZE];
bool b_paused = false;

bool goNextLvl = false;
bool transitionOver = false;

CP_Image transition_img;
CP_Vector transitionPos;
CP_Vector transitionSize;

extern asset matte;
extern int brightposx;
extern bool sub;
CP_BOOL combatStart = false;
CP_BOOL combatOver = false;

void resetTransition();

void game_init(void)
{
	currLvl = 0;
	transition_img = CP_Image_Load(FILEPATH "transition.png");
	transitionSize = CP_Vector_Set(CP_Image_GetWidth(transition_img), CP_Image_GetHeight(transition_img));
	transitionPos = CP_Vector_Set(transitionSize.x, transitionSize.y);

	// set draw settings
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	// create and initialise cplayer
	init_dice();
	init_char(Warrior);
	
	//creating map data
	int width = MAP1_SIZE;

	Level = malloc(sizeof(game_map) * 3);
	if (Level)
	{
		Buffer* b = newBuffer();
		b->data = readFile("map1.dat");
		//size_t len = strlen(b->data);
		//b->data = b64_decode(b->data, strlen(b->data), &len);
		init_map_obj(Level, MAP1_SIZE, MAP1_SIZE, CP_System_GetWindowHeight(), CP_System_GetWindowHeight());
		load_map_file(Level, b->data);
		clearBuffer(b);
		fclose(getFile("map1.dat"));
		int numtileswidth = (int)(CP_System_GetWindowWidth() / (int)(CP_System_GetWindowHeight() / Level[0].height));
		mapOffset[0] = (numtileswidth - Level[0].height) / 2 + 1;


		
		b = newBuffer();
		b->data = readFile("map2.dat");
		//size_t len = strlen(b->data);
		//b->data = b64_decode(b->data, strlen(b->data), &len);
		init_map_obj(Level + 1, MAP2_SIZE, MAP2_SIZE, CP_System_GetWindowHeight(), CP_System_GetWindowHeight());
		load_map_file(Level + 1, b->data);
		clearBuffer(b);
		fclose(getFile("map2.dat"));
		numtileswidth = (int)(CP_System_GetWindowWidth() / (int)(CP_System_GetWindowHeight() / Level[1].height));
		mapOffset[1] = (numtileswidth - Level[1].height) / 2 + 1;

		
		b = newBuffer();
		b->data = readFile("map3.dat");
		//size_t len = strlen(b->data);
		//b->data = b64_decode(b->data, strlen(b->data), &len);
		init_map_obj(Level + 2, MAP3_SIZE, MAP3_SIZE, CP_System_GetWindowHeight(), CP_System_GetWindowHeight());
		load_map_file(Level + 2, b->data);
		clearBuffer(b);
		fclose(getFile("map3.dat"));
		numtileswidth = (int)(CP_System_GetWindowWidth() / (int)(CP_System_GetWindowHeight() / Level[2].height));
		mapOffset[2] = (numtileswidth - Level[2].height) / 2 + 1;
	}

	


	//load_map_file(Level, b->data);

	
	

	//creating and initialise 1 enemy
	for (int i = 0; i < ENEMYSIZE; ++i)
	{
		enemy[i] = CreateEnemy();
		enemy[i]->sp->go.position.x = i * (9) + mapOffset[currLvl];
		enemy[i]->sp->go.position.y = 4;
		enemy[i]->sp->go.scale.x = 0.5;
		enemy[i]->sp->go.scale.y = 0.5;
		enemy[i]->hp = 10;
		enemy[i]->steps = 1;
		enemy[i]->b_combat = false;
	}

	get_character()->sp->go.position.x = mapOffset[currLvl] + 4;
	get_character()->sp->go.position.y = 9;
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

	if (CP_Input_KeyDown(KEY_1))
	{
		currLvl = 0;
	}
	if (CP_Input_KeyDown(KEY_2))
	{
		currLvl = 1;
	}
	if (CP_Input_KeyDown(KEY_3))
	{
		currLvl = 2;
	}
	transitionPos.x -= dt * 500;


	//get player input
	hardware_handler();

	//update player pos
	UpdateSprite(get_character()->sp, dt);

	for (int i = 0; i < ENEMYSIZE; ++i)
	{
		//set logic for enemy temporary
		if (get_character()->sp->moved)
		{
			for (int j = 0; j <= 20; ++j)
			{
				UpdateEnemy(enemy[i], dt, true);
			}
		}
		else
			UpdateEnemy(enemy[i], dt, false);

		if ((i == ENEMYSIZE - 1) && get_character()->sp->moved)
		{
			get_character()->sp->moved = 0;
			get_character()->turn_done = 0;
		}
		
		UpdateCombat(enemy[i], dt);
	}

	for (int i = 0; i < ENEMYSIZE; ++i)
	{
		if ((enemy[i]->b_combat && !combatStart))
		{
			second_init();
			combat_scene_init();
			combatStart = true;
			combatOver = false;
		}
	}



		//RENDER
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		CP_Vector vec = { CP_System_GetWindowWidth() / 4.5,0 };
		render_map(Level + currLvl, vec);

		//render player
		RenderSpriteOnMap(get_character()->sp, Level + currLvl);

		//render enemy
		for (int i = 0; i < ENEMYSIZE; ++i)
			RenderSpriteOnMap(enemy[i]->sp, Level + currLvl);

		if (!combatStart)
			ManualUpdate(COMBAT_OVERLAY_SCENE);
		if (!sub)
			RenderAsset(matte, 255 - brightposx);
	

		if (combatStart && !combatOver)
		{
			for (int i = 0; i < ENEMYSIZE; ++i)
			{
				UpdateCombat(enemy[i], dt);
			}

			ManualUpdate(BATTLE_SCENE_UI);
			ManualUpdate(BATTLE_SCENE);

			// if enemy dead/player dead do smth

			for (int i = 0; i < ENEMYSIZE; ++i)
			{
				if (!enemy[i]->b_combat)
					continue;
				if (enemy[i]->hp <= 0)
				{
					enemy[i]->sp->go.isAlive = false;
					enemy[i]->b_combat = false;
					battleEnd();
				}
			}

			if (get_character()->hp <= 0)
			{
				battleEnd();
			}
			if (getCombatState())
			{
				combatStart = false;
				combatOver = true;
			}
		}
		CP_Settings_ImageMode(CP_POSITION_CORNER);
		CP_Image_Draw(transition_img, transitionPos.x, transitionPos.y, transitionSize.x, transitionSize.y, 255);
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

const game_map* getMap()
{
	return Level + currLvl;
}

void engage_enemy(CP_Vector dir)
{
	CP_Vector tmp = get_character()->sp->go.position;
	tmp = CP_Vector_Add(tmp, dir);
	for (int i = 0; i < ENEMYSIZE; ++i)
	{
		if (tmp.x == enemy[i]->sp->go.position.x && tmp.y == enemy[i]->sp->go.position.y)
		{
			// fight
			enemy[i]->b_combat = true;
			enemy[i]->enemyState = DEFEND_STATE;
		}
	}
}

void resetTransition()
{
	transitionPos = CP_Vector_Set(0, 0);
	transitionOver = false;
}
