#include "cprocessing.h"
#include "ui_utils.h"
#include "../CombatOverlayUI/combat_overlay.h"
#include <string.h>

float blinkTimer;
float timer;
int alpha;

int mouse_in_rect(float rect_x, float rect_y, float rect_width, float rect_height)
{
	//float mouse_x = CP_Input_GetMouseX();
	//float mouse_y = CP_Input_GetMouseY();
	//float max_dist_rect_sq = ((rect_width / 2) * (rect_width / 2)) + ((rect_height / 2) * (rect_height / 2));	// pythagoras to find diagonal length from center to a corner in the rectangle. value is squared
	//float dist_rect_PointerToCenter_sq = ((rect_x - mouse_x) * (rect_x - mouse_x)) + ((rect_y - mouse_y) * (rect_y - mouse_y));	// distance of pointer from center to pointer. value is squared
	//if (max_dist_rect_sq > dist_rect_PointerToCenter_sq)	// pointer is in the rectangle
	//{
	//	return 1;
	//}
	//else	// pointer is outside of rectangle
	//{
	//	return 0;
	//}

	float x = CP_Input_GetMouseX();
	float y = CP_Input_GetMouseY();
	float x2 = rect_x - rect_width / 2;
	float y2 = rect_y - rect_height / 2;
	float x3 = x2 + rect_width;
	float y3 = y2 + rect_height;
	if (x > x2 && x < x3 && y > y2 && y < y3)
		return true;

	return false;
}

void get_image_size(const char *filepath, asset* obj)
{
	char str[100] = "Assets/combat_overlay_ui/";
	strcat_s(str, 100, filepath);
	obj->image = CP_Image_Load(str);
	obj->size.x = (float)CP_Image_GetWidth(obj->image);
	obj->size.y = (float)CP_Image_GetHeight(obj->image);
}

void get_image_size_set(const char* filepath, asset* obj)
{
	obj->image = CP_Image_Load(filepath);
	obj->size.x = (float)CP_Image_GetWidth(obj->image);
	obj->size.y = (float)CP_Image_GetHeight(obj->image);
}

void go_to_animation(float targetX, float targetY, CP_Vector *pos_to_change)
{
	CP_Vector target;
	target.x = targetX;
	target.y = targetY;									// TODO: Change target positions to the characters position
	CP_Vector displacement = CP_Vector_Subtract(target, *pos_to_change);
	CP_Vector damped_displacement = CP_Vector_Scale(displacement, 0.15f);
	*pos_to_change = CP_Vector_Add(*pos_to_change, damped_displacement);
}

void shrinking_animation(float target, float* to_change)
{
	float shrink_ps = 0.2 * (*to_change - target);
	*to_change -= shrink_ps;
}
/*
int rumbling_animation(void)
{
	blinkTimer += CP_System_GetDt();
	timer += CP_System_GetDt();
	if (timer < 3.0)     // lets say blink for 2 sec
	{
		if (blinkTimer > 0.5)   // flip every 0.5 seconds
		{
			if (!alpha)
			{
				alpha = 255; // max alpha
				timer = 0;
			}
			else
			{
				alpha = 0;
				timer = 0;
			}
		}
	}
}*/

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

CP_Vector getWorldPos(CP_Vector gridPos, const game_map* gm)
{
	float gridsize = CP_System_GetWindowHeight() / gm->height;
	return CP_Vector_Set(gridPos.x * gridsize, gridPos.y * gridsize);
}

int mouse_in_rect_lvl(float rect_x, float rect_y, float rect_width, float rect_height)
{
	float x = CP_Input_GetMouseX();
	float y = CP_Input_GetMouseY();
	float x2 = rect_x - rect_width / 2;
	float y2 = rect_y - rect_height / 2;
	float x3 = x2 + rect_width;
	float y3 = y2 + rect_height;
	if (x > x2 && x < x3 && y > y2 && y < y3)
		return true;

	return false;
}