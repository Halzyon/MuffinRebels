
/*-------------------------------------------------------------------------------------

	File: combat_overlay.h
	Project: 1401 Game Project - DiceRebels
	Author: Liew Yeni (yeni.l@digipen.edu)

	All content © 2021 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#ifndef COMBAT_OVERLAY_H
#define COMBAT_OVERLAY_H

#include "cprocessing.h"
#include "../../Character/diceHandler.h"

CP_Sound footsteps;
int powerups[3];

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
};

enum dice
{
	d4 = 2,
	d6 = 1,
	d20 = 0
};

int movement_clicked;

/* 
*  Brief: initializes variables used in combat_overlay.c
*  Param: void
*/

void combat_overlay_init(void);

/*
*  Brief: initializes position where the dice rolls on screen
*  Param: void
*/

void init_rollPos(void);

/*
*  Brief: runs functions in combat_overlay.c to show UI for the movement sequence
*  Param: void
*/

void combat_overlay_update(void);

/*
*  Brief: Renders UI based on player interaction (whether they selected to roll the dice for movement or combat
*		  or they select to use a powerup)
* 
*  Param: powerup_turns - integer variable that denotes the remaining duration that an active powerup has.
*/

void dice_powerup(int powerup_turns);

/*
*  Brief: Runs if player chooses to roll the dice for movement. Rolls a 2d6 and adds it to the player's energy.
*		  Total roll is shown at the side of the screen for players to keep track of their energy.
* 
*  Param: void
*/

void choose_to_roll_movement(void);

/*
*  Brief: Runs if player chooses to select powerup
*		  Shows the contents of the players inventory - which powerups they have, and how many of each.
*		  Further allows player to consume the powerups if they select it. (Use of powerups is only allowed during combat.
* 
*  Param: turns_left - denotes the number of turns the active powerup has remaining
*		  num_powerups[] - array that stores the number of each powerup the 
*/

void choose_powerup(int turns_left, int num_powerups[]);

/*
*  Brief: Renders the 'pause'/'settings' button. Players can press this button to open the pause menu.
*  Param: void
*/

void settings_button(void);

/*
*  Brief: Renders the movement window (display panel with a number which is integer 'movement')
*
*  Param: movement - number to be displayed
*		  x - x-axis position of window
*		  y - y-axis position of window
*		  scale - number the size of the original window is scaled by (make smaller or larger)
*/

void movement_window(int movement, float x, float y, float scale);


/*
*  Brief: Detects if enemy is near the player
*
*  Param: dir - grid position of the character
* 
*  Return: integer value that returns 1 if enemy is near player and 0 if otherwise
*/

int isEnemyNearUI(CP_Vector dir);


/*
*  Brief: Renders items that appear from chests and renders animation sequence of poewrup being
*		  placed into the dice inventory or powerup inventory.
*
*  Param: item_code - number that the item is denoted by
*/

void item_to_inventory(int item_code);


/*
*  Brief: Frees all images used in combat_overlay.c
*  Param: void
*/

void combat_overlay_exit(void);



#endif //COMBAT_OVERLAY_H