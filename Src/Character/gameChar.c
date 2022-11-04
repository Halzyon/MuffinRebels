#include <stdlib.h>
#include <cprocessing.h>

#include "gameChar.h"

my_character* the_player;

int init_char(class_select char_select)
{
	the_player = malloc(sizeof(my_character));
	if (the_player)
	{
		the_player->sp = CreateSprite("Assets/poke.png", 4, 4, true, true);
		the_player->char_class = char_select;
		the_player->energy = 0;
		the_player->hp = 100;

		//sprite animation init
		the_player->sp->spriteStates[RIGHT] = 2;
		the_player->sp->spriteStates[BACKWARD] = 0;
		the_player->sp->spriteStates[LEFT] = 1;
		the_player->sp->spriteStates[FORWARD] = 3;
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