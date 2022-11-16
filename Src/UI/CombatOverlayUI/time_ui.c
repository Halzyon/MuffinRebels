#include "cprocessing.h"
#include <stdbool.h>
#include <time.h>

clock_t start_time;
clock_t remaining_time = 600;
CP_Font font;
bool paused;
clock_t difference;
int minutes;
int seconds;
char text_time[5];

void time_init(void)
{
	CP_System_SetWindowSize(1280, 720);
	start_time = clock() / CLOCKS_PER_SEC;
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");
	CP_Font_Set(font);
	CP_Settings_TextSize(50.0f);
	paused = FALSE;
}

void time_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (CP_Input_KeyTriggered(KEY_ANY))
	{
		paused = !paused;
	}
	if (remaining_time != 0 && !paused)
	{
		difference = (clock() / CLOCKS_PER_SEC) - start_time;
		remaining_time = 600 - difference;		// hard set to 10 mins right now
		minutes = remaining_time / 60;
		seconds = remaining_time % 60;
		text_time[0] = '0' + (minutes / 10);
		text_time[1] = '0' + (minutes % 10);
		text_time[2] = ':';
		text_time[3] = '0' + (seconds / 10);
		text_time[4] ='0' + (seconds % 10);
		
	}
	else if (remaining_time == 0)
	{
		//add a times up game over swquence here
	}
	else if (paused)
	{
	}

	CP_Font_DrawText(text_time, (CP_System_GetWindowWidth() / 2) - 30.0f, 50.0f);
}

void time_exit(void)
{

}