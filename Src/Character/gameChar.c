/*-------------------------------------------------------------------------------------

	File: gameChar.c
	Project: 1401 Game Project - Game Name: DiceRebels
	Author: Alwin Moo (moo.g@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <cprocessing.h>

#include "gameChar.h"

my_character* the_player;
int init_char(void)
{
	the_player = malloc(sizeof(my_character));
	if (the_player)
	{
		the_player->sp = CreateSprite("Assets/poke.png", 4, 4, true, false);
		the_player->energy = 0;
		the_player->hp = 100;
		the_player->sp->moved = 0;
		the_player->turn_done = 0;
		the_player->modifier = 0;
		the_player->mod_duration = 0;

		the_player->dice[0] = e_std_D6;
		the_player->dice_size = 1;

		for (int i = 1; i < MAX_DICE; ++i)
		{
			the_player->dice[i] = -1;
		}

		the_player->combat_mode = CHAR_NONE;

		//sprite animation init
		the_player->sp->spriteStates[RIGHT] = 2;
		the_player->sp->spriteStates[BACKWARD] = 1;
		the_player->sp->spriteStates[LEFT] = 3;
		the_player->sp->spriteStates[FORWARD] = 0;
	}

	return the_player;
}

my_character* get_character(void)
{
	return the_player;
}

int free_char(void)
{
	CP_Image_Free(get_character()->sp->go.image);
	free(get_character()->sp);

	the_player = NULL;
	free(the_player);
}