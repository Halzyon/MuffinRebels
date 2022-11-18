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
	int warning;
	char num[1];

}asset;

enum powerup
{
	atk = 0,
	hp = 1,
	movement = 2
};

enum dice
{
	d4 = 2,
	d6 = 1,
	d20 = 0
};

int movement_clicked;

// initialize assets, finds their sizes, sets all text alighnment and image alignment and initializes dice randomiser
void combat_overlay_init(void);

// initialize rolling position
void init_rollPos(void);

void combat_overlay_update(void);

// constantly updates the combat overlay based on player interaction with it - num_roll is pregenerated number that the player rolls
void dice_powerup(int powerup_turns, int combat_dice[]);

// runs if player chooses to roll dice for movement
void choose_to_roll_movement(void);

void side_display(int turns_left);

// runs if player chooses to select a powerup
void choose_powerup(int turns_left, int num_powerups[]);

// draws settings icon - player can pause the game with this
void settings_button(void);

// renders the window for movement
void movement_window(int movement, float x, float y, float scale);

// frees all images
void combat_overlay_exit(void);

#endif //COMBAT_OVERLAY_H