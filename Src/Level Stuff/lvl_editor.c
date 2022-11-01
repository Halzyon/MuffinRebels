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
#include "../Level Stuff/lvl_manager.h"
#include "../Character/gameMap.h"
#include "cprocessing.h"
#include "../utils.h"

#define WINDOW_HEIGHT 1080
#define LEVEL_EDITOR
game_map* map;
int gridsize;
char mouse_cursor;

void editor_init(void)
{
	CP_System_SetWindowSize(WINDOW_HEIGHT, WINDOW_HEIGHT);
	CP_System_ShowCursor(0);
	init_lvl_manager();

	if (map = malloc(sizeof(map)))
	{
		if (init_map_obj(10, 10, map))
		{
			loadNewMap(*map);
			gridsize = WINDOW_HEIGHT / map->height;
		}
	}
}


void editor_update(void)
{
#ifdef LEVEL_EDITOR
	if (CP_Input_MouseClicked())
	{
		CP_Vector tmp = GetAreaClicked(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY(), gridsize);
		if (tmp.x != 0 && tmp.y != 0)
		{
			map->map_arr[map_get_index(tmp.x, tmp.y, map->width)] = mouse_cursor;
		}
	}
	if (CP_Input_KeyTriggered(KEY_1))
	{
		mouse_cursor = GROUND;
	}
	if (CP_Input_KeyTriggered(KEY_2))
	{
		mouse_cursor = WALL_HORIZONTAL;
	}
	if (CP_Input_KeyTriggered(KEY_3))
	{
		mouse_cursor = WATER;
	}
	if (CP_Input_KeyTriggered(KEY_4))
	{
		mouse_cursor = CHEST;
	}

#endif // LEVEL_EDITOR inputs

#ifdef LEVEL_EDITOR



#endif // LEVEL_EDITOR updates


	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
#ifdef LEVEL_EDITOR

	for (size_t i = 0; i < map->width * map->height; ++i) // row
	{
		switch (map->map_arr[i])
		{
		case GROUND:
		{
			CP_Settings_Fill(CP_Color_Create(255, 150, 70, 255));
		}
		break;
		case WATER:
		{
			CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
		}
		break;
		case CHEST:
		{
			CP_Settings_Fill(CP_Color_Create(139, 69, 19, 255));
		}
		break;
		case WALL_HORIZONTAL:
		{
			CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		}
		break;
		default:
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		}
		break;
		}
		//CP_Settings_NoStroke();
		CP_Settings_StrokeWeight(0.5f);
		CP_Graphics_DrawRectAdvanced(map_get_x(i, map->width) * gridsize + 0.5f, map_get_y(i, map->height) * gridsize + 0.5f, gridsize - 0.5f, gridsize - 0.5f, 0.f, 0.f);
	}

	switch (mouse_cursor)
	{
	case GROUND:
	{
		CP_Settings_Fill(CP_Color_Create(255, 150, 70, 255));
	}
	break;
	case WATER:
	{
		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	}
	break;
	case CHEST:
	{
		CP_Settings_Fill(CP_Color_Create(139, 69, 19, 255));
	}
	break;
	case WALL_HORIZONTAL:
	{
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	}
	break;
	default:
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	}
	break;
	}
	CP_Settings_NoStroke();
	int tmp = gridsize / 4;
	int tmp2 = tmp / 2;
	CP_Graphics_DrawRect(CP_Input_GetMouseX() - tmp2, CP_Input_GetMouseY() - tmp2, tmp, tmp);

#endif // LEVEL_EDITOR render
}

void editor_exit(void)
{
	free_map_obj(map);
	exit_lvl_manager();
}