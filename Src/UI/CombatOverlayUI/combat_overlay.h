#ifndef COMBAT_OVERLAY_H
#define COMBAT_OVERLAY_H

#include "cprocessing.h"
#include "../../Character/diceHandler.h"

typedef struct
{
	CP_Image image;
	CP_Vector size;
	CP_Vector position;
	int inButton;
	int clicked;
}asset;

void combat_init(void);

void init_dicePos(void);

void init_rollPos(void);

void combat_buttons(int num_roll);

void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY);

void health_bar(int remaining_hp);

void settings_button(void);

void inventory_window(int num_item, float rightmost_box_positionX);

void combat_ui_shutdown(void);

#endif //COMBAT_OVERLAY_H