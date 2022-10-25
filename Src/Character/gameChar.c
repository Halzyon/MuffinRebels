#include <stdlib.h>
#include <cprocessing.h>

#include "gameChar.h"

my_character* the_player;

int init_char(class_select char_select)
{
	the_player = malloc(sizeof(my_character));
	if (the_player)
	{
		the_player->char_class = char_select;
		the_player->energy = 0;
		the_player->hp = 100;
		the_player->pos = CP_Vector_Zero();
	}

	return the_player;
}

my_character* get_character(void)
{
	return the_player;
}

int free_char(void)
{
	the_player = NULL;
	free(the_player);
}