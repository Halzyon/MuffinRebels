#ifndef H_SPRITEANIMATION_H
#define H_SPRITEANIMATION_H
#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameObject.h"
typedef enum {

	CONTINUOUS,
	BACKWARD,	
	LEFT,
	RIGHT,
	FORWARD,
	IDLE,
	IDLELEFT,
	IDLERIGHT,
	IDLEFORWARD,
	IDLEBACKWARD,
	MAX_STATES

}STATES;



typedef struct {
	GameObject go;
	CP_Image image;
	int row;
	int col;
	int id;
	CP_Vector tL;
	CP_Vector bR;
	double time_elapsed;
	float time;
	bool moved;
	UINT8 spriteStates[MAX_STATES];
	UINT8 renderMode;
}Sprite;

void UpdateSprite(Sprite* sprite, float dt);

void RenderSprite(Sprite* sprite);

Sprite* CreateSprite(char* imgPath, UINT8 row, UINT8 col, bool SPRITESHEET, bool dir);






#endif