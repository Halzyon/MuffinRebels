#ifndef H_GAMEOBJECT_H
#define H_GAMEOBJECT_H
#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Character/gameEnemy.h"
#include "../Character/gameChar.h"

typedef struct {
	CP_Image image;
	CP_Vector position;
	CP_Vector direction;
	CP_Vector scale;
	CP_Vector size;
	float rotation;
	float speed;
	bool isAlive;
	float alpha;

	my_character* this_character;
	Enemy* this_enemy;

}GameObject;





#endif