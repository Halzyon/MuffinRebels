#ifndef H_UTILS_H
#define H_UTILS_H

#include "../../GameObject/gameObject.h"
#include "cprocessing.h"
#include "../CombatOverlayUI/combat_overlay.h"

int mouse_in_rect(float rect_x, float rect_y, float rect_width, float rect_height);

void get_image_size(const char* filepath, asset* obj);

static float EaseOutSine(float start, float end, float value);

int IsAreaClickedCentre(const GameObject obj, const CP_Vector position);
int IsAreaClickedCorner(const GameObject obj, const CP_Vector position);

#endif // !H_UTILS_H