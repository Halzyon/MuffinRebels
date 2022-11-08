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

// initialize assets, finds their sizes, sets all text alighnment and image alignment and initializes dice randomiser
void combat_overlay_init(void);

// initialize d6 d20 dice positions
void init_dicePos(void);

// initialize rolling position
void init_rollPos(void);

// constantly updates the combat overlay based on player interaction with it - num_roll is pregenerated number that the player rolls
void combat_overlay_update(int num_roll);

// runs if player chooses to roll dice
//void choose_to_roll_dice(int num_roll);

// runs if player chooses to select a powerup
//void choose_powerup(void);

// generates the dice that is rolling
void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY);

// draws hit points of player
void health_bar(int remaining_hp);

// draws settings icon - player can pause the game with this
void settings_button(void);

// draws square boxes for items to be inside. num_item is number of boxes to draw, rightmost_box_positionX is the X position of the rightmost inventory window spawned
void inventory_window(int num_item, float rightmost_box_positionX);

// frees all images
void combat_ui_shutdown(void);

#endif //COMBAT_OVERLAY_H