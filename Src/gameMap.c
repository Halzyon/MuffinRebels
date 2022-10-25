#include <stdlib.h>

#include "gameMap.h"

int init_map_obj(unsigned int width_size, unsigned int height_size, game_map* out_obj) 
{
	out_obj->width = width_size;
	out_obj->height = height_size;
	out_obj->map_arr = malloc((size_t)(width_size * height_size));

	return out_obj;
}

int map_get_index(int x, int y, int width)
{
	return x + width * y;
}

int map_get_y(int index, int width)
{
	return index / width;    // where "/" is an integer division;
}

int map_get_x(int index, int width)
{
	return index % width;    // % is the "modulo operator", the remainder of i / width;
}

void free_map_obj(game_map* map_obj)
{
	free(map_obj->map_arr);
}
