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

#include "../gameMap.h"
#define POOL_SIZE 3 // increase this number to allow more maps/levels 
					// to be loaded at once
#define DEFAULT_LEVEL_SIZE 5

enum TILE_TYPE
{
	DEFAULT = 0, // HTIS REPRESENTS EMPTY SPACE
	GROUND = 'g', // THIS IS A NORMAL GROUND TILE
	WALL_HORIZONTAL = '-',
	WALL_VERTICAL = '|',
	WALL_JUNCTION = '+',
	WALL_T_JUNCTION = 'T',
	WALL_T_JUNCTION_INVERTED = '_',
	WATER = 'w', // WOTAH
	NUM_TYPES
};

game_map *mapPool[POOL_SIZE];
char poolStatus[POOL_SIZE];

void init_lvl_manager();
void exit_lvl_manager();

void loadNewMapFile(const char* filename);
void loadNewMap(const char* map, unsigned int width, unsigned int height);


#endif // !LEVEL_MANAGER_H

