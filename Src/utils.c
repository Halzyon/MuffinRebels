#include "utils.h"
#include <math.h>
unsigned int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float minX, maxX, minY, maxY = 0;
	minX = area_center_x;
	maxX = area_center_x + area_width;
	minY = area_center_y;
	maxY = area_center_y + area_height;
	if (click_x > minX && click_x < maxX && click_y > minY && click_y < maxY)
	{
		return 1;
	}
	return 0;
}

unsigned int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	float radius = diameter / 2;
	/*if (click_x < circle_center_x + radius && click_x > circle_center_x - radius && click_y < circle_center_y + radius && click_y > circle_center_y - radius)
	{
		return 1;
	}*/
	CP_Vector click = { click_x, click_y};
	CP_Vector circle = { circle_center_x , circle_center_y };
	
	return CP_Vector_Distance(click, circle) < radius;
}

CP_Vector AngleToVector(float radian_angle)
{
    CP_Vector ret;
	ret = CP_Vector_Set(cosf(radian_angle), sinf(radian_angle));
    return ret;
}

CP_Vector GetAreaClicked(float clickX, float clickY, float gridsize)
{
	return CP_Vector_Set(clickX / gridsize, clickY / gridsize);
}
