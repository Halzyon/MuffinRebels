/*-------------------------------------------------------------------------------------

	File: diceHandler.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Author: Alwin Moo (moo.g@digipen.edu)

	All content � 2021 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/
#ifndef DICE_HANDLER_H
#define DICE_HANDLER_H
#include <cprocessing.h>

#define D4_SIZE 4
#define D6_SIZE 6
#define D20_SIZE 20

typedef enum
{
	e_std_D4,
	e_std_D6,
	e_std_D20,

	NUM_TYPES
} dice_types;

void init_dice(void);

int roll_dice(dice_types dice);

#endif // !DICE_HANDLER_H
