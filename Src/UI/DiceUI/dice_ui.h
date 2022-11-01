#pragma once
#include "../../Character/diceHandler.h"

void dice_ui_init(void);

//void player_rolls_dice(int num_roll);

void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY);

void dice_shutdown(void);