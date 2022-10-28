#include "cprocessing.h"
#include "FileIO/fileIO.h"
#include "FileIO/serialization.h"
#include "FileIO/encode.h"
#include "Character/gameMap.h"
#include "Character/gameChar.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"   
#include "utils.h"

CP_Image logo;
game_map* map1;

#include "Level Stuff/lvl_manager.h"

#define WINDOW_HEIGHT 1080
#define LEVEL_EDITOR

//CP_Image logo;
game_map* map;
int gridsize;

void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);


	CP_System_SetWindowSize(WINDOW_HEIGHT, WINDOW_HEIGHT);

	init_dice();
	init_char(Warrior);
	init_map_obj(10, 10, &map1);
	//CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));

	init_lvl_manager();
	map = malloc(sizeof(map));
#ifdef _DEBUG
	map->map_arr = malloc(0);
#else
	map->map_arr = malloc(4);
#endif

	map->map_arr[0] = GROUND;
	map->map_arr[1] = GROUND;
	map->map_arr[2] = GROUND;
	map->map_arr[3] = GROUND;
	map->height = 10;
	map->width = 10;
	loadNewMap(*map);

	printf("%s", map->map_arr);
	gridsize = WINDOW_HEIGHT / map->height;
}

void game_update(void)
{
	// INPUT
	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
	// UPDATE
#ifdef LEVEL_EDITOR
	if (CP_Input_MouseClicked())
	{
	
	}

#endif // LEVEL_EDITOR inputs

	// RENDER 
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
#ifdef LEVEL_EDITOR

	for (size_t i = 0; i < map->width * map->height; ++i) // row
	{
		if (map->map_arr[i] == GROUND)
		{
			CP_Settings_Fill(CP_Color_Create(139, 69, 19, 255));
		}
		else
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		}
		//CP_Settings_NoStroke();
		CP_Settings_StrokeWeight(0.5f);
		CP_Graphics_DrawRectAdvanced(map_get_x(i, map->width) * gridsize + 0.5f, map_get_y(i, map->height) * gridsize + 0.5f, gridsize - 0.5f, gridsize - 0.5f, 0.f, 0.f);
	}

#endif // LEVEL_EDITOR render

	//hardware_handler();
}

void game_exit(void)
{
	CP_Image_Free(&logo);
	free_map_obj(&map1);
	//free_char();
	exit_lvl_manager();
}




int main(void)
{


	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();

	return 0;
}
