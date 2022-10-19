#include <stdlib.h>

#include "gameMap.h"

void new_map(int* arr[], int area)
{
	arr = malloc(area);
}

int map_get_index(int x, int y, int size)
{
	return x + size * y;
}

int map_get_y(int index, int size)
{
	return index / size;    // where "/" is an integer division;
}

int map_get_x(int index, int size)
{
	return index % size;    // % is the "modulo operator", the remainder of i / width;
}
