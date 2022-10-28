#include "cprocessing.h"

int mouse_in_rect(float rect_x, float rect_y, float rect_width, float rect_height)
{
	float mouse_x = CP_Input_GetMouseX();
	float mouse_y = CP_Input_GetMouseY();
	float oob_x = rect_x + rect_width / 2;
	float oob_y = rect_y + rect_height / 2;
	if ((mouse_x < oob_x || mouse_x > -oob_x) && (mouse_y < oob_y || mouse_y > -oob_y))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}