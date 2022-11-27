#include "cprocessing.h"
#include <time.h>

clock_t start_time;
clock_t remaining_time;
CP_Font font;

void time_init(void)
{
	start_time = clock() / CLOCKS_PER_SEC;
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");
	CP_Font_Set(font);
}

void time_update(void)
{
	if (remaining_time != 0)
	{
		clock_t difference = (clock() / CLOCKS_PER_SEC) - start_time;
		remaining_time = 600 - difference;		// hard set to 10 mins right now
		int minutes = remaining_time / 60;
		int seconds = remaining_time % 60;
		char text_time[5] = { '0' + (minutes / 10), '0' + (minutes % 10), ':', '0' + (seconds / 10), '0' + (seconds % 10) };
		CP_Font_DrawText(text_time, CP_System_GetWindowWidth() / 2, 50.0f);
	}
	else
	{
		//add a times up game over swquence here
	}
}

void time_exit(void)
{

}