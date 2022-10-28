#ifndef H_GAMEOBJECT_H
#define H_GAMEOBJECT_H
#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	CP_Vector position;
	CP_Vector direction;
	CP_Vector scale;
	CP_Vector size;
	float rotation;
	float speed;
}GameObject;






#endif