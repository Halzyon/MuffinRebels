#ifndef COMBAT_OVERLAY_H
#define COMBAT_OVERLAY_H

#include "cprocessing.h"
#include "../../Character/diceHandler.h"

CP_Sound footsteps;

typedef struct
{
	CP_Image image;
	CP_Vector size;
	CP_Vector position;
	int inButton;
	int clicked;
	const char* desc;
	const char* desc1;
	const char* name;
	int side_display;
	dice_types type;
	int warning;
	char num[1];

}asset;

enum powerup
{
	strongarm = 0,
	leatherskin = 1,
	healthpot = 2,
	maxPowerups = 3
};

enum dice_items
{
	woodensword = 0,
	woodenshield = 1,
	ironsword = 2,
	ironshield = 3,
	goldsword = 4,
	goldshield = 5,
	diamondsword = 6,
	diamondshield = 7,
	mastersword = 8,
	maxDiceItems = 9
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
void dice_powerup(int powerup_turns);

// runs if player chooses to roll dice for movement
void choose_to_roll_movement(void);

// runs if player chooses to select a powerup
void choose_powerup(int turns_left, int num_powerups[]);

// draws settings icon - player can pause the game with this
void settings_button(void);

// renders the window for movement
void movement_window(int movement, float x, float y, float scale);

// detects if enemy is near for UI
int isEnemyNearUI(CP_Vector dir);

void item_to_inventory(int item_code);

// frees all images
void combat_overlay_exit(void);



#endif //COMBAT_OVERLAY_H