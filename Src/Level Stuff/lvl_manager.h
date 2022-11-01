/*!
 @file level_manager.h
 @author Foong Jun Wei (f.junwei)
 @course 
 @section 
 @tutorial 
 @date 2022-10-25
 @brief 
*//*______________________________________________________________________*/

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

CP_BOOL isInit = FALSE;
#endif // !LEVEL_MANAGER_H

