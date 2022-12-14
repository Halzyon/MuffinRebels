#pragma once
#include "CProcessing.h"


unsigned int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
unsigned int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
union CP_Vector AngleToVector(float radian_angle);
CP_Vector GetAreaClicked(float clickX, float clickY, float gridsize);