#include "cprocessing.h"
#include "UI/DiceUI/dice_ui.h"
#include "Character/diceHandler.h"
#include <stdio.h>

CP_Image logo;

void game_init(void)
{
	dice_ui_init();
	init_dice();
	CP_System_Fullscreen();
}



void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));

	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
}

void game_exit(void)
{
	dice_shutdown();
	CP_Image_Free(&logo);
}


int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}