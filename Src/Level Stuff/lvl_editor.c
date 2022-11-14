/*!
 @file lvl_editor.c
 @author Foong Jun Wei (f.junwei)
 @course 
 @section 
 @tutorial 
 @date 2022-10-24
 @brief 
*//*______________________________________________________________________*/

#include "lvl_editor.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Character/gameMap.h"
#include "cprocessing.h"
#include "../utils.h"
#include "../FileIO/serialization.h"
#include "../FileIO/fileIO.h"
#include "../FileIO/encode.h"

#ifndef _MSC_VER // for linux/all other compilers and apparently release mode
#define FILEPATH "Assets/tiles/"
#endif

#ifdef _MSC_VER // for visual studios/microsoft compiler
#pragma warning(disable : 4996) // microsoft wants you to use their fopen_s but it is not portable at all
//and not really taht much safer lol
#define FILEPATH "Assets/tiles/"
//#define _CRTDBG_MAP_ALLOC
#endif  


#define WINDOW_HEIGHT 1080
#define LEVEL_EDITOR
game_map* map;
int gridsize;
char mouse_cursor = 1;

void editor_init(void)
{
	CP_System_SetWindowSize(WINDOW_HEIGHT, WINDOW_HEIGHT);
	CP_System_ShowCursor(0);
	init_lvl_manager();
	loadSprites();

	if (map = malloc(sizeof(map)))
	{
		if (init_map_obj(map, 10, 10, WINDOW_HEIGHT, WINDOW_HEIGHT))
		{
			int size = map->height * map->width;
			loadNewMap(*map);
			for (int i = 0; i < size; ++i)
			{
				map->map_arr[i] = GROUND;
			}
			gridsize = WINDOW_HEIGHT / map->height;
		}
	}
}


void editor_update(void)
{
#ifdef LEVEL_EDITOR
	if (CP_Input_MouseClicked())
	{
		CP_Vector tmp = GetAreaClicked(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY(), (float)gridsize);
		if (tmp.x != 0 && tmp.y != 0)
		{
			map->map_arr[map_get_index((int)tmp.x, (int)tmp.y, map->width)] = mouse_cursor;
		}
	}
	if (CP_Input_MouseWheel())
	{
		mouse_cursor += CP_Input_MouseWheel();
		if (mouse_cursor < 1)
			mouse_cursor = NUM_TYPES_TILE - 1;
		if (mouse_cursor > NUM_TYPES_TILE - 1)
			mouse_cursor = 1;
	}
	if (CP_Input_KeyTriggered(KEY_S))
	{
		// save map
		if (map)
		{
			Buffer* b = newBuffer();
			serializeMap(map->map_arr, b);
			size_t encodedLen = 0;
			//b->data = b64_encode(b->data, strlen(b->data), &encodedLen);
 			writeFile("map.dat", b->data, "w");
			clearBuffer(b);
			fclose(getFile("map.dat"));
		}
	}
	if (CP_Input_KeyTriggered(KEY_L))
	{
		Buffer* b = newBuffer();
		b->data = readFile("map.dat");
		size_t len = 0;
		//b->data = b64_decode(b->data, strlen(b->data), &len);
		load_map_file(map, b->data);
		clearBuffer(b);
		fclose(getFile("map.dat"));
	}

#endif // LEVEL_EDITOR inputs

#ifdef LEVEL_EDITOR



#endif // LEVEL_EDITOR updates

	CP_Settings_NoStroke();
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	// change rendered tile to tile 49 in pack.
#ifdef LEVEL_EDITOR

	//for (size_t i = 0; i < map->width * map->height; ++i) // row
	//{
	//	CP_Settings_ImageMode(CP_POSITION_CORNER);
	//	CP_Image_Draw(level_sprites[map->map_arr[i] - 1], (float)(map_get_y((int)i, map->width) * gridsize), (float)(map_get_x((float)i, map->height) * gridsize), gridsize, gridsize, 255);
	//	//CP_Graphics_DrawRectAdvanced((float)(map_get_y((int)i, map->width) * gridsize + 0.5f), (float)(map_get_x((float)i, map->height) * gridsize + 0.5f), gridsize - 0.5f, gridsize - 0.5f, 0.f, 0.f);
	//}
	CP_Vector vec = { 0,0 };
	render_map(map, vec);

	CP_Settings_NoStroke();
	//int tmp = gridsize / 4;
	int tmp2 = gridsize / 2;
	CP_Image_Draw(level_sprites[mouse_cursor - 1], CP_Input_GetMouseX() - tmp2, CP_Input_GetMouseY() - tmp2, (float)gridsize, (float)gridsize, 255);
	//CP_Graphics_DrawRect(CP_Input_GetMouseX() - tmp2, CP_Input_GetMouseY() - tmp2, (float)tmp, (float)tmp);

#endif // LEVEL_EDITOR render
}

void editor_exit(void)
{
	free_map_obj(map);
	exit_lvl_manager();
	for (int i = 0; i < NUM_TYPES_TILE - 1; ++i)
	{
		CP_Image_Free(level_sprites[i]);
	}
}

//void loadSprites(void)
//{
//	int i = 0;
//	while (i < NUM_TYPES_TILE - 1)
//	{
//		char tmp1[100] = FILEPATH; // path of file
//		char tmp2[100] = "tile_"; // file name without number 
//		char buffer[10]; // contain the number + file extention
//		snprintf(buffer, 10, "%d.png", i); // put number and file extention tgt: 0.png, 1.png
//		strcat(tmp2, buffer); // put tile_ and number and extension tgt: tile_0.png, tile_1.png
//		strcat(tmp1, tmp2); // put tgt with file path: Assets/tiles/tile_0.png
//		level_sprites[i] = CP_Image_Load(tmp1); 
//		++i;
//	}
//}
