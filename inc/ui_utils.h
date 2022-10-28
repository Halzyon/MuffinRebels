#include "gameObject.h"
#include "cprocessing.h"
int mouse_in_rect(float rect_x, float rect_y, float rect_width, float rect_height);

int IsAreaClickedCentre(const GameObject obj,const CP_Vector position)
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
