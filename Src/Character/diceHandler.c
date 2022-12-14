/*-------------------------------------------------------------------------------------

	File: diceHandler.c
	Project: 1401 Game Project - Game Name: DiceRebels
	Author: Alwin Moo (moo.g@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <time.h>

#include "diceHandler.h"

int std_D4[D4_SIZE] = { 1,2,3,4 };
int std_D6[D6_SIZE] = {1,2,3,4,5,6};
int std_D20[D20_SIZE] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };

int* dice_list[NUM_TYPES] = {std_D4, std_D6, std_D20};

void init_dice(void)
{
	srand((unsigned int)time(NULL));
}

int roll_dice(dice_types dice)
{
	int size;
	switch (dice)
	{
		case e_std_D4:
			size = D4_SIZE;
			break;
		case e_std_D6:
			size = D6_SIZE;
			break;
		case e_std_D20:
			size = D20_SIZE;
			break;
		default:
			return 0;
			break;
	}

	int number = (int)(((double)rand() / (RAND_MAX + 1)) * size); //normalise rand values then multiplay by range
	return dice_list[dice][number];
}
