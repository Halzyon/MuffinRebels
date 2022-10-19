#ifndef GAME_MAP_H
#define GAME_MAP_H

typedef struct
{
	int* map_arr;

	int size;

} game_map;

void new_map(int* arr[], int area);

int map_get_x(int index, int size);

int map_get_y(int index, int size);

int map_get_index(int x, int y, int size);

#endif // !GAME_MAP_H