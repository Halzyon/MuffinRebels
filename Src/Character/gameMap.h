#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <cprocessing.h>

typedef struct
{
	char* map_arr;

	unsigned int width;
	unsigned int height;

	float world_width;
	float world_height;

} game_map;

enum TILE_TYPE
{
	DEFAULT = 0, // THIS REPRESENTS EMPTY SPACE
	GROUND = 'g', // THIS IS A NORMAL GROUND TILE
	WALL_HORIZONTAL = '-',
	WALL_VERTICAL = '|',
	WALL_JUNCTION = '+',
	WALL_T_JUNCTION = 'T',
	WALL_T_JUNCTION_INVERTED = '_',
	WATER = 'w', // WOTAH
	CHEST = 'c',
	NUM_TYPES_TILE
};

int init_map_obj(unsigned int width_size, unsigned int height_size, game_map* out_obj, float world_width, float world_height);

int map_get_x(int index, int size);

int map_get_y(int index, int size);

int map_get_index(int x, int y, int size);

CP_Vector map_get_worldpos(int index, game_map* in_map);

float map_get_world_x(int x, game_map* in_map);

float map_get_world_y(int y, game_map* in_map);

void free_map_obj(game_map* map_obj);



#endif // !GAME_MAP_H