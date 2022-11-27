
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

void combat_overlay_init(void);

void init_rollPos(void);

void combat_overlay_update(void);

void dice_powerup(int powerup_turns);

void choose_to_roll_movement(void);

void choose_powerup(int turns_left, int num_powerups[]);

void settings_button(void);

void movement_window(int movement, float x, float y, float scale);

int isEnemyNearUI(CP_Vector dir);

void item_to_inventory(int item_code);

void combat_overlay_exit(void);



#endif //COMBAT_OVERLAY_H