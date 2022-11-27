#include <stdlib.h>
#include <stdio.h>

#include "gameMap.h"

#pragma warning(disable : 6011)
#ifndef _MSC_VER // for linux/all other compilers and apparently release mode
#define FILEPATH "Assets/tiles/"
#endif

#ifdef _MSC_VER // for visual studios/microsoft compiler
#pragma warning(disable : 4996) // microsoft wants you to use their fopen_s but it is not portable at all
//and not really taht much safer lol
#define FILEPATH "Assets/tiles/"
//#define _CRTDBG_MAP_ALLOC
#endif  

CP_Image level_sprites[NUM_TYPES_TILE];
CP_Image fog;

int init_map_obj(game_map* out_obj, unsigned int width_size, unsigned int height_size, float world_width, float world_height)
{
	out_obj->width = width_size;
	out_obj->height = height_size;
	out_obj->map_arr = malloc((size_t)(width_size * height_size) + 1);
	out_obj->map_arr[(width_size * height_size)] = '\0';
	out_obj->world_width = world_width;
	out_obj->world_height = world_height;

	return (int)(out_obj == NULL);
}

int map_get_index(int x, int y, int width)
{
	return x * width + y;
}

CP_Vector map_get_worldpos(int index, game_map* in_map)
{
	return CP_Vector_Set(map_get_x(index, in_map->width) * (in_map->world_width / in_map->width), map_get_y(index, in_map->height) * (in_map->world_height / in_map->height));
}

float map_get_world_x(int x, game_map* in_map)
{
	return x * (in_map->world_width / in_map->width);
}

float map_get_world_y(int y, game_map* in_map)
{
	return y * (in_map->world_height / in_map->height);
}

int map_get_y(int index, int height)
{
	return index / height;    // where "/" is an integer division;
}

int map_get_x(int index, int width)
{
	return index % width;    // % is the "modulo operator", the remainder of i / width;
}

float map_get_tile_size(game_map* in_map)
{
	return (float)(in_map->world_height / in_map->height);
}

void free_map_obj(game_map* map_obj)
{
	free(map_obj->map_arr);
}

void load_map_file(game_map* dst, const char* src)
{
	int len = dst->width * dst->width;
	//dst->world_height = dst->world_width = (int)sqrt(len);
	
	for (int i = 0; i < len; ++i)
	{
		dst->map_arr[i] = src[i];
	}
	return;
}

void render_map(game_map* map, CP_Vector offset)
{
	for (unsigned int i = 0; i < map->height * map->width; ++i)
	{
		double gridsize = (double)(CP_System_GetWindowHeight() / map->height);
		CP_Settings_ImageMode(CP_POSITION_CORNER);
		CP_Image_Draw(level_sprites[map->map_arr[i] - 1], (float)(map_get_y((int)i, map->width) * gridsize) + offset.x, (float)(map_get_x(i, map->height) * (float)gridsize) + offset.y, (float)gridsize, (float)gridsize - 0.5f, 255);
	}
}

void render_mapFog(game_map* map, CP_Vector offset, CP_Vector pos, int range, int mapoffset)
{
	double gridsize = CP_System_GetWindowHeight() / map->height;
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	pos.x -= mapoffset;
	for (unsigned int i = 0; i < map->height * map->width; ++i)
	{
		int y = map_get_x(i, map->width);
		int x = map_get_y(i, map->height);
		if (x >= pos.x - range && x <= pos.x + range)
		{
			if (y >= pos.y - range && y <= pos.y + range)
			{
				continue;
			}
		}
		CP_Image_Draw(fog, (float)(map_get_y((int)i, map->width) * gridsize) + offset.x, (float)(map_get_x(i, map->height) * gridsize) + offset.y, (float)gridsize, (float)gridsize - 0.5f, 245);

	}
}

void loadSprites(void)
{
	int i = 0;
	while (i < NUM_TYPES_TILE - 1)
	{
		char tmp1[100] = FILEPATH; // path of file
		char tmp2[100] = "tile_"; // file name without number 
		char buffer[10]; // contain the number + file extention
		snprintf(buffer, 10, "%d.png", i); // put number and file extention tgt: 0.png, 1.png
		strcat(tmp2, buffer); // put tile_ and number and extension tgt: tile_0.png, tile_1.png
		strcat(tmp1, tmp2); // put tgt with file path: Assets/tiles/tile_0.png
		level_sprites[i] = CP_Image_Load(tmp1);
		++i;
	}
	char tem[] = FILEPATH "tile_fog.png";


	fog = CP_Image_Load(tem);
}
