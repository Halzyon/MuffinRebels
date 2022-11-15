#ifndef H_UTILS_H
#define H_UTILS_H

#include "../../GameObject/gameObject.h"
#include "cprocessing.h"
#include "../CombatOverlayUI/combat_overlay.h"
#include <math.h>
#define PI 3.142857
int mouse_in_rect(float rect_x, float rect_y, float rect_width, float rect_height);

void get_image_size(const char* filepath, asset* obj);

static float EaseOutSine(float start, float end, float value)
{
	end -= start;
	return end * sinf(value * (PI * 0.5f)) + start;
}

void go_to_animation(float targetX, float targetY, CP_Vector* pos_to_change);

void shrinking_animation(float target, float* to_change);

int IsAreaClickedCentre(const GameObject obj, const CP_Vector position);
int IsAreaClickedCorner(const GameObject obj, const CP_Vector position);

#endif // !H_UTILS_H