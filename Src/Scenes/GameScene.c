#include "SpriteAnimation/spriteAnimation.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"
#include "Character/gameChar.h"
#include "Character/gameEnemy.h"
#include "GameStateManager.h"
#include "../Combat/combatHandler.h"
#include "../Character/gameMap.h"
#include "../FileIO/fileIO.h"

#define MAXENEMIES 8
#define FILEPATH "Assets/"

char numEnemies[3] = {2, 4 ,8};

double speed = 5000;
Sprite* ash;
game_map* Level;
Enemy* enemy[MAXENEMIES];

bool b_paused = false;
bool goNextLvl = false;
bool transitionOver = false;
bool startTransition = true;
bool flipDir = false;

CP_Image transition_img;
CP_Vector transitionPos;
CP_Vector transitionSize;
CP_Vector targetPos;

extern asset matte;
extern int brightposx;
extern bool sub;
CP_BOOL combatStart = false;
CP_BOOL combatOver = false;
int enemykilled = 0;
char targetLevel = 0;
char playerWon = 0; // -1 lose, 1 win;
bool clearedLevel = false;
char enemyCount = 0;

bool isInitScene = false;

void move_transition(CP_Vector* curr, CP_Vector dst);

void game_init(void)
{
	if (isInitScene)
		return;

	currLvl = 0;
	transition_img = CP_Image_Load(FILEPATH "transition.png");
	transitionSize = CP_Vector_Set(CP_Image_GetWidth(transition_img), CP_Image_GetHeight(transition_img));
	transitionPos = CP_Vector_Set(transitionSize.x, transitionSize.y);

	// set draw settings
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	// create and initialise cplayer
	init_dice();
	init_char();
	
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
	for (int i = 0; i < MAXENEMIES; ++i)
	{
		enemy[i] = CreateEnemy();
				//enemy[i]->sp->go.position.x = i * (9) + mapOffset[currLvl];
		//enemy[i]->sp->go.position.y = 4;
		//enemy[i]->sp->go.scale.x = 0.5;
		//enemy[i]->sp->go.scale.y = 0.5;
		//enemy[i]->hp = 10;
		//enemy[i]->steps = 1;
		//enemy[i]->b_combat = false;
		//if (i < numEnemies[currLvl])
		//{
		//	enemy[i]->sp->go.isAlive = true;
		//}
		//else
		//{
		//	enemy[i]->sp->go.isAlive = false;
		//}
	}

	


	loadSprites();

	//set sub scenes to run 
	GameStateSetNextSubScene(PAUSE_SCENE, false);
	GameStateSetNextSubScene(COMBAT_OVERLAY_SCENE, false);
	GameStateSetNextSubScene(OVERWORLD_UI_SCENE, false);
	GameStateSetNextSubScene(BATTLE_SCENE, false);
	GameStateSetNextSubScene(BATTLE_SCENE_UI, false);
	GameStateSetNextSubScene(MAX_SCENE, true);
	isInitScene = true;
	//setNextLvl(targetLevel);
}

void game_update(void)
{
	if (!enemyCount)
	{
		playerWon = 1;
	}

	if (playerWon == 1)
	{
		setNextLvl(currLvl + 1);
	}
	if ((get_character()->hp <= 0  && !sub) || CP_Input_KeyTriggered(KEY_H) || CP_Input_KeyTriggered(KEY_J))
	{
		sub = true;
		if (!CP_Input_KeyDown(KEY_H))
			get_character()->hp = 0;
		else
			get_character()->hp = 5;
		GameStateSetNextSubScene(GAMEOVER_SCENE,false);
	}
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
		setNextLvl(0);
		return;
	}
	if (CP_Input_KeyDown(KEY_2))
	{
		setNextLvl(1);
		return;
	}
	if (CP_Input_KeyDown(KEY_3))
	{
		setNextLvl(2);
		return;
	}

	//get player input
	hardware_handler();

	//update player pos
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	UpdateSprite(get_character()->sp, dt);

	if (!transitionOver && startTransition)
	{
		// need to update here as well so as to not have the sprite sheet appear
		for (int i = 0; i < numEnemies[currLvl]; ++i)
		{
			UpdateEnemy(enemy[i], dt, false);
		}
		//RENDER
		CP_Vector vec = { CP_System_GetWindowWidth() / 4.5,0 };

		render_map(Level + currLvl, vec);
		render_mapFog(Level + currLvl, vec, get_character()->sp->go.position, 3 + currLvl, mapOffset[currLvl]);
		//render player
		RenderSpriteOnMap(get_character()->sp, Level + currLvl);


		//move_transition(&transitionPos, CP_Vector_Set(-transitionSize.x, 0));
		if (goNextLvl)
		{
			flipDir = true;
			goNextLvl = false;
		}

		if (!flipDir)
		{
			transitionPos.x -= dt * (float)speed;
			if (transitionPos.x <= -transitionSize.x)
			{
				transitionOver = true;
				startTransition = false;
			}
		}
		else
		{
			transitionPos.x += dt * (float)speed;
			if (transitionPos.x >= 0)
			{
				flipDir = false;
				currLvl = targetLevel;
			}
		}


		CP_Settings_ImageMode(CP_POSITION_CORNER);
		CP_Image_Draw(transition_img, transitionPos.x, transitionPos.y, transitionSize.x, transitionSize.y, 255);
	}
	else
	{
		//RENDER
		CP_Vector vec = { CP_System_GetWindowWidth() / 4.5,0 };
		render_map(Level + currLvl, vec);

		bool enemy_done = false;
		//update player pos
		for (int i = 0; i < numEnemies[currLvl]; ++i)
		{
			//set logic for enemy temporary
			if (get_character()->sp->moved)
			{
				if (enemy[i]->energy)
				{
					UpdateEnemy(enemy[i], dt, true);

					if (enemy[i]->sp->go.isAlive && enemy[i]->energy == 0)
						enemy_done = true;
				}
			}
			else
			{
				enemy[i]->energy = 8;
				UpdateEnemy(enemy[i], dt, false);
			}

			UpdateCombat(enemy[i], dt);
		}

		if (enemy_done)
		{
			get_character()->sp->moved = 0;
			get_character()->turn_done = 0;
		}

		for (int i = 0; i < numEnemies[currLvl]; ++i)
		{
			if ((enemy[i]->b_combat && !combatStart))
			{
				second_init();
				combat_scene_init();
				combatStart = true;
				combatOver = false;
			}
		}

		//render enemy
		for (int i = 0; i < numEnemies[currLvl]; ++i)
			RenderSpriteOnMap(enemy[i]->sp, Level + currLvl);

		render_mapFog(Level + currLvl, vec, get_character()->sp->go.position, 3 + currLvl, mapOffset[currLvl]);

		//render player
		RenderSpriteOnMap(get_character()->sp, Level + currLvl);

		if (!combatStart)
			ManualUpdate(COMBAT_OVERLAY_SCENE);
		if (!sub)
			RenderAsset(matte, 255 - brightposx);


		if (combatStart && !combatOver)
		{
			for (int i = 0; i < numEnemies[currLvl]; ++i)
			{
				UpdateCombat(enemy[i], dt);
			}
			CP_Settings_ImageMode(CP_POSITION_CENTER);
			ManualUpdate(BATTLE_SCENE_UI);
			ManualUpdate(BATTLE_SCENE);

			// if enemy dead/player dead do smth

			for (int i = 0; i < numEnemies[currLvl]; ++i)
			{
				if (!enemy[i]->b_combat)
					continue;
				if (enemy[i]->hp <= 0)
				{
					enemy[i]->sp->go.isAlive = false;
					enemy[i]->b_combat = false;
					battleEnd();

					get_character()->sp->moved = 0;
					get_character()->turn_done = 0;
					--enemyCount;
				}
			}

			if (get_character()->hp <= 0)
			{
				battleEnd();

				get_character()->sp->moved = 0;
				get_character()->turn_done = 0;
				playerWon = -1; // player died
			}
			if (getCombatState())
			{
				combatStart = false;
				combatOver = true;
			}
		}
	}


}

void game_exit(void)
{
	free(Level);
	free_char();
	for(int i = 0; i < MAXENEMIES; ++i)
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
	for (int i = 0; i < numEnemies[currLvl]; ++i)
	{
		if (tmp.x == enemy[i]->sp->go.position.x && tmp.y == enemy[i]->sp->go.position.y)
		{
			// fight
			enemy[i]->b_combat = true;
			enemy[i]->enemyState = DEFEND_STATE;
		}
	}
}

void setNextLvl(char next)
{
	if (!isInitScene)
		game_init();

	get_character()->combat_mode = CHAR_NONE;
	combatants_present = false;
	goNextLvl = true;
	transitionOver = false;
	startTransition = true;
	clearedLevel = false;
	playerWon = 0;
	combatStart = false;
	combatOver = true;
	targetLevel = next;
	enemyCount = 0;




	for (int i = 0; i < MAXENEMIES; ++i)
	{
		enemy[i]->hp = 20;
		enemy[i]->steps = 1;
		enemy[i]->b_combat = false;
		if (i < numEnemies[next])
		{
			enemy[i]->sp->go.isAlive = true;
			++enemyCount;
		}
		else
		{
			enemy[i]->sp->go.isAlive = false;
		}
	}
	switch (next)
	{
	case 0:
	{
		get_character()->sp->go.position.x = mapOffset[targetLevel] + 7;
		get_character()->sp->go.position.y = 14;

		enemy[0]->sp->go.position.x = 7 + mapOffset[targetLevel];
		enemy[0]->sp->go.position.y = 8;
		enemy[0]->enemyState = PATROL_LEFTRIGHT_STATE;
		enemy[1]->sp->go.position.x = 13 + mapOffset[targetLevel];
		enemy[1]->sp->go.position.y = 8;
		enemy[1]->enemyState = PATROL_LEFTRIGHT_STATE;
	}
		break;
	case 1:
	{
		get_character()->sp->go.position.x = mapOffset[targetLevel] + 2;
		get_character()->sp->go.position.y = 18;

		enemy[0]->sp->go.position.x = 8 + mapOffset[targetLevel];
		enemy[0]->sp->go.position.y = 8;
		enemy[0]->enemyState = PATROL_UPDOWN_STATE;

		enemy[1]->sp->go.position.x = 13 + mapOffset[targetLevel];
		enemy[1]->sp->go.position.y = 9;
		enemy[1]->enemyState = PATROL_LEFTRIGHT_STATE;

		enemy[2]->sp->go.position.x = 12 + mapOffset[targetLevel];
		enemy[2]->sp->go.position.y = 13;
		enemy[2]->enemyState = PATROL_LEFTRIGHT_STATE;

		enemy[3]->sp->go.position.x = 15 + mapOffset[targetLevel];
		enemy[3]->sp->go.position.y = 1;
		enemy[3]->enemyState = PATROL_LEFTRIGHT_STATE;
	}
		break;
	case 2:
	{
		get_character()->sp->go.position.x = mapOffset[targetLevel] + 2;
		get_character()->sp->go.position.y = 28;

		enemy[0]->sp->go.position.x = 1 + mapOffset[targetLevel];
		enemy[0]->sp->go.position.y = 6;
		enemy[0]->enemyState = PATROL_UPDOWN_STATE;

		enemy[1]->sp->go.position.x = 2 + mapOffset[targetLevel];
		enemy[1]->sp->go.position.y = 12;
		enemy[1]->enemyState = PATROL_UPDOWN_STATE;

		enemy[2]->sp->go.position.x = 17 + mapOffset[targetLevel];
		enemy[2]->sp->go.position.y = 8;
		enemy[2]->enemyState = PATROL_LEFTRIGHT_STATE;

		enemy[3]->sp->go.position.x = 18 + mapOffset[targetLevel];
		enemy[3]->sp->go.position.y = 3;
		enemy[3]->enemyState = PATROL_LEFTRIGHT_STATE;

		enemy[4]->sp->go.position.x = 26 + mapOffset[targetLevel];
		enemy[4]->sp->go.position.y = 22;
		enemy[4]->enemyState = PATROL_LEFTRIGHT_STATE;

		enemy[5]->sp->go.position.x = 29 + mapOffset[targetLevel];
		enemy[5]->sp->go.position.y = 24;
		enemy[5]->enemyState = PATROL_LEFTRIGHT_STATE;

		enemy[6]->sp->go.position.x = 19 + mapOffset[targetLevel];
		enemy[6]->sp->go.position.y = 19;
		enemy[6]->enemyState = PATROL_UPDOWN_STATE;

		enemy[7]->sp->go.position.x = 13 + mapOffset[targetLevel];
		enemy[7]->sp->go.position.y = 17;
		enemy[7]->enemyState = PATROL_LEFTRIGHT_STATE;
	}
		break;
	default:
		break;
	}
}

void setInitScene(bool b)
{
	isInitScene = b;
}
