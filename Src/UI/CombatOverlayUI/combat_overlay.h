#pragma once
#include "cprocessing.h"
#include "../../Character/diceHandler.h"

typedef struct
{
	CP_Image img;
	CP_Vector size;
	CP_Vector pos;
	int inButton;
	int clicked;
}asset;

void combat_init(void);

void buttons(void);

void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY);

void combat_ui_shutdown(void);