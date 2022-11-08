#include "cprocessing.h"
#include "ui_utils.h"
#include "../CombatOverlayUI/combat_overlay.h"
#include <string.h>
#include <math.h>
#define PI 3.142857

int mouse_in_rect(float rect_x, float rect_y, float rect_width, float rect_height)
{
	float mouse_x = CP_Input_GetMouseX();
	float mouse_y = CP_Input_GetMouseY();
	float max_dist_rect_sq = ((rect_width / 2) * (rect_width / 2)) + ((rect_height / 2) * (rect_height / 2));	// pythagoras to find diagonal length from center to a corner in the rectangle. value is squared
	float dist_rect_PointerToCenter_sq = ((rect_x - mouse_x) * (rect_x - mouse_x)) + ((rect_y - mouse_y) * (rect_y - mouse_y));	// distance of pointer from center to pointer. value is squared
	if (max_dist_rect_sq > dist_rect_PointerToCenter_sq)	// pointer is in the rectangle
	{
		return 1;
	}
	else	// pointer is outside of rectangle
	{
		return 0;
	}
}

void get_image_size(const char *filepath, asset* obj)
{
	char str[100] = "Assets/combat_overlay_ui/";
	strcat_s(str, 100, filepath);
	obj->image = CP_Image_Load(str);
	obj->size.x = (float)CP_Image_GetWidth(obj->image);
	obj->size.y = (float)CP_Image_GetHeight(obj->image);
}

float EaseOutSine(float start, float end, float value)
{
	end -= start;
	return end * sinf(value * (PI * 0.5f)) + start;
}

int IsAreaClickedCentre(const GameObject obj, const CP_Vector position)
{
	float minX = obj.position.x - (obj.scale.x * obj.size.x * 0.5f);
	float minY = obj.position.y - (obj.scale.y * obj.size.y * 0.5f);
	float maxX = obj.position.x + (obj.scale.x * obj.size.x * 0.5f);
	float maxY = obj.position.y + (obj.scale.y * obj.size.y * 0.5f);
	if (position.x > minX && position.y < maxX)
		if (position.x > minY && position.y < maxY)
			return 1;
	return 0;
}

int IsAreaClickedCorner(const GameObject obj, const CP_Vector position)
{
	float minX = obj.position.x;
	float minY = obj.position.y;
	float maxX = obj.position.x + (obj.scale.x * obj.size.x);
	float maxY = obj.position.y + (obj.scale.y * obj.size.y);
	if (position.x > minX && position.y < maxX)
		if (position.x > minY && position.y < maxY)
			return 1;
	return 0;
}