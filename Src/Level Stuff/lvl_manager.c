/*!
 @file level-manager.c
 @author Foong Jun Wei (f.junwei)
 @course 
 @section 
 @tutorial 
 @date 2022-10-25
 @brief 
*//*______________________________________________________________________*/

#include <string.h>
#include <stdlib.h>
#include "lvl_manager.h"

void init_lvl_manager()
{
	if (isInit_lvlmanager)
		return;
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		mapPool[i] = malloc(sizeof(game_map));
		poolStatus[i] = 0;
		if (mapPool[i])
		{
			mapPool[i]->map_arr = malloc(1);
			mapPool[i]->map_arr[0] = '\0';

			mapPool[i]->height = 0;
			mapPool[i]->width = 0;
		}
	}
	isInit_lvlmanager = TRUE;
}

void exit_lvl_manager()
{

	for (int i = 0; i < POOL_SIZE; ++i)
	{
		if (mapPool[i])
		{
			if (mapPool[i]->map_arr)
			{
				free(mapPool[i]->map_arr);
			}
			free(mapPool[i]);
		}
	}
}

void loadNewMapFile(const char* filename) //@TODO open a map through file
{

}

void loadNewMap(game_map map)
{
	if (strlen(map.map_arr) != map.width* map.height)
		return;

	char index = getPoolFreeIndex();
	
	if (!index)
		return;

	newMapIndex(index, map);
}

void newMapIndex(char i,game_map map)
{
	if (!poolStatus[i])
	{
		if (mapPool[i]->map_arr)
		{
			free(mapPool[i]->map_arr);
		}
		mapPool[i]->width = map.width;
		mapPool[i]->height = map.height;
		int arraysize = map.width * map.height;
		char* tmp = malloc((size_t)arraysize);
		if (tmp)
		{
			mapPool[i]->map_arr = tmp;
			if (!map.map_arr)
			{
				memset(mapPool[i]->map_arr, GROUND, strlen(mapPool[i]->map_arr));
			}
			else
			{
				for (int y = 0; y < arraysize; ++y)
				{
					mapPool[i]->map_arr[y] = map.map_arr[y];
				}
			}
		}
	}
}

char getPoolFreeIndex()
{
	for (char i = 0; i < POOL_SIZE; ++i)
	{
		if (!poolStatus[i])
			return i;
	}
	return NULL;
}
