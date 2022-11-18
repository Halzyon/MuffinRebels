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
	GROUND_1 = 1, // THIS IS A NORMAL GROUND TILE
	GROUND_2,
	GROUND_3,
	GROUND_4,
	GROUND_5,
	GROUND_6,
	GROUND_7,
	GROUND_8,
	GROUND_9,
	GROUND_10,
	WALL_1,
	WALL_2,
	WALL_3,
	WALL_4,
	WALL_5,
	WALL_6,
	WALL_7,
	WALL_8,
	WALL_9,
	WALL_10,
	WALL_11,
	WALL_12,
	WALL_13,
	WALL_14,
	WALL_15,
	WALL_16, 
	WALL_17,// this is not a hard thinggy
	WALL_18,
	WALL_19,
	WALL_20,
	WALL_21,
	WALL_22,
	WATER_1, // WOTAH
	CHEST_1,
	CHEST_2,
	NUM_TYPES_TILE
};

/*!
 * @brief initialises out parameter (out_obj) with default values and makes sure it exists
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

void load_map_file(game_map* dst, const char* src);

void loadSprites(void);

void render_map(game_map* map, CP_Vector offset);


#endif // !GAME_MAP_H