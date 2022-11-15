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
	const char* desc;
	int side_display;
	dice_types type;
}asset;

enum powerup
{
	atk = 0,
	hp = 1,
	extra_d4 = 2
};

enum dice
{
	d4 = 2,
	d6 = 1,
	d20 = 0
};

// initialize assets, finds their sizes, sets all text alighnment and image alignment and initializes dice randomiser
void combat_overlay_init(void);

// initialize d6 d20 dice positions
void init_dicePos(void);

// initialize rolling position
void init_rollPos(void);

void combat_overlay_update(void);

// constantly updates the combat overlay based on player interaction with it - num_roll is pregenerated number that the player rolls
void dice_powerup(int *rng_mov, int *rng_combat, int powerup_turns, int combat_dice[]);

// runs if player chooses to roll dice
void choose_to_roll_movement(int *mov_num);

//void choose_to_roll_combat(int *combat_num, int combat_dice[]);

void side_display(int* mov_num, int turns_left);

// runs if player chooses to select a powerup
void choose_powerup(int turns_left);

// draws dice (d6 or d20) with number corresponding to value num_roll
void generate_dice(int num_roll, asset dice, float dice_posX, float dice_posY, float scale);

// draws hit points of player
void health_bar(int remaining_hp);

// draws settings icon - player can pause the game with this
void settings_button(void);

// draws square boxes for items to be inside. num_item is number of boxes to draw, rightmost_box_positionX is the X position of the rightmost inventory window spawned
void inventory_window(int num_item, float rightmost_box_positionX);

// renders the window for movement
void movement_window(int movement, float x, float y, float scale);

//void timer_ui(void);

// frees all images
void combat_overlay_exit(void);

#endif //COMBAT_OVERLAY_H