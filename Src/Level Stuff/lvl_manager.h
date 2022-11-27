/*-------------------------------------------------------------------------------------

	File: lvl_manager.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H
#include "../Character/gameMap.h"
#include "cprocessing.h"
#define POOL_SIZE 3 // increase this number to allow more maps/levels 
					// to be loaded at once
#define DEFAULT_LEVEL_SIZE 5



game_map *mapPool[POOL_SIZE];
char poolStatus[POOL_SIZE];

void init_lvl_manager();
void exit_lvl_manager();

void loadNewMapFile(const char* filename);
void loadNewMap(game_map map);
void newMapIndex(char i, game_map map);

char getPoolFreeIndex();

CP_BOOL isInit_lvlmanager;
#endif // !LEVEL_MANAGER_H

