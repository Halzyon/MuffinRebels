#include <stdlib.h>

#include "gameMap.h"

int init_map_obj(unsigned int width_size, unsigned int height_size, game_map* out_obj, float world_width, float world_height)
{
	out_obj->width = width_size;
	out_obj->height = height_size;
	out_obj->map_arr = malloc((size_t)(width_size * height_size));

	out_obj->world_width = world_width;
	out_obj->world_height = world_height;

	return (int)out_obj;
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

void free_map_obj(game_map* map_obj)
{
	free(map_obj->map_arr);
}

