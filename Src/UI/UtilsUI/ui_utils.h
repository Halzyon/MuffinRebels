/*-------------------------------------------------------------------------------------

	File: ui_utils.c
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Muhammad Hazim Bin Gazali (m.bingazali@digipen.edu) - IsAreaClickedCentre, IsAreaClickedCorner
			 Foong Jun Wei (f.junwei@digipen.edu) - mouse_in_rect
			 Liew Yeni (yeni.l@digipen.edu) - get_image_size, get_image_size_set, go_to_animation, shrinking_animation

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#ifndef H_UTILS_H
#define H_UTILS_H

#include "../../GameObject/gameObject.h"
#include "cprocessing.h"
#include "../CombatOverlayUI/combat_overlay.h"
#include "../../Character/gameMap.h"
#include <math.h>
#define PI 3.142857f
int mouse_in_rect(float rect_x, float rect_y, float rect_width, float rect_height);

void get_image_size(const char* filepath, asset* obj);

void get_image_size_set(const char* filepath, asset* obj);

static float EaseOutSine(float start, float end, float value)
{
	end -= start;
	return end * sinf(value * (PI * 0.5f)) + start;
}

//int rumbling_animation();

void go_to_animation(float targetX, float targetY, CP_Vector* pos_to_change);

void shrinking_animation(float target, float* to_change);

int IsAreaClickedCentre(const GameObject obj, const CP_Vector position);
int IsAreaClickedCorner(const GameObject obj, const CP_Vector position);

CP_Vector getWorldPos(CP_Vector gridPos, const game_map* gm);
int mouse_in_rect_lvl(float rect_x, float rect_y, float rect_width, float rect_height);
#endif // !H_UTILS_H