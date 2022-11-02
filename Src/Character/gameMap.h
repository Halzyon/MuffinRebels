#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <cprocessing.h>

typedef struct
{
	char* map_arr; //1D char map array

	unsigned int width; //grid total width
	unsigned int height; //grid total height

	float world_width; //grid max world width
	float world_height; //grid max world height

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

/*!
 * @brief 
 * @param out_obj empty game_map object to be passed in so that default values can be written in and passed back
 * @param width_size unsigned integer total number of units in the width of the grid
 * @param height_size unsigned integer total number of units in the height of the grid
 * @param world_width float max world width
 * @param world_height float max world height
 * @return integer whether out_obj exists
*/
int init_map_obj(game_map* out_obj,unsigned int width_size, unsigned int height_size, float world_width, float world_height);

/*!
 * @brief converts from 1D array index to 2D array x-axis
 * @param index 1D array index
 * @param size integer max width of map
 * @return integer x-axis in 2D array
*/
int map_get_x(int index, int width);

/*!
 * @brief converts from 1D array index to 2D array y-axis
 * @param index 1D array index
 * @param size 
 * @return integer y-axis in 2D array
*/
int map_get_y(int index, int height);

/*!
 * @brief converts from 2D grid coordinates to 1D array index
 * @param x integer x-coord of grid
 * @param y integer y-coord of grid
 * @param size 
 * @return integer index of 1D array
*/
int map_get_index(int x, int y, int size);

/*!
 * @brief Calculates the world position using 1D array index
 * @param index integer index of 1D array
 * @param in_map map object to access map information
 * @return CP_Vector of position in world positioning
*/
CP_Vector map_get_worldpos(int index, game_map* in_map);

/*!
 * @brief Calculates the world x-coord position using grid x-coord
 * @param x integer x-coord in grid
 * @param in_map map object to access map information
 * @return float of position of x-axis
*/
float map_get_world_x(int x, game_map* in_map);

/*!
 * @brief Calculates the world x-coord position using grid x-coord
 * @param y integer y-coord in grid
 * @param in_map map object to access map information
 * @return float of position of x-axis
*/
float map_get_world_y(int y, game_map* in_map);

/*!
 * @brief destructor to be called in exit
 * @param map_obj map object and its contents to be deleted
*/
void free_map_obj(game_map* map_obj);



#endif // !GAME_MAP_H