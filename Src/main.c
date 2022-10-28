#include "cprocessing.h"
#include "FileIO/fileIO.h"
#include "FileIO/serialization.h"
#include "FileIO/encode.h"
#include "Character/gameMap.h"
#include "Character/gameChar.h"
#include "Character/diceHandler.h"
#include "Character/charMovement.h"    

CP_Image logo;
game_map* map1;

#include "Level Stuff/lvl_manager.h"
    


//CP_Image logo;
 
void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);


	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));

	init_dice();
	init_char(Warrior);
	init_map_obj(10, 10, &map1);
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}

	hardware_handler();
}

void game_exit(void)
{
	CP_Image_Free(&logo);
	free_map_obj(&map1);
	free_char();
}




int main(void)
{
	init_lvl_manager();
	game_map* map = malloc(sizeof(map));
#ifdef _DEBUG
	map->map_arr = malloc(0);
#else
	map->map_arr = malloc(4);
#endif

	map->map_arr[0] = GROUND;
	map->map_arr[1] = GROUND;
	map->map_arr[2] = GROUND;
	map->map_arr[3] = GROUND;
	map->height = 2;
	map->width = 2;
	loadNewMap(*map);

	printf("%s", map->map_arr);
	exit_lvl_manager();

	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();



	return 0;
}
