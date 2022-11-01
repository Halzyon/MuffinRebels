#ifndef GAME_MAP_H
#define GAME_MAP_H

typedef struct
{
	char* map_arr;

	unsigned int width;
	unsigned int height;

} game_map;

int init_map_obj(unsigned int width_size, unsigned int height_size, game_map* out_obj);

int map_get_x(int index, int size);

int map_get_y(int index, int size);

int map_get_index(int x, int y, int size);

void free_map_obj(game_map* map_obj);

#endif // !GAME_MAP_H