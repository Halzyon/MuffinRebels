#include <cprocessing.h>

#include <stdio.h>

#include "charMovement.h"
#include "gameChar.h"
#include "diceHandler.h"

int check_limits(void)
{
	return 0;
}

void hardware_handler(void)
{
	if (get_character()->energy)
	{
		if (CP_Input_KeyTriggered(KEY_W))
		{
			get_character()->sp->go.position.y -= 1;
			--get_character()->energy;
			
			get_character()->sp->renderMode = get_character()->sp->spriteStates[FORWARD];
			get_character()->sp->moved = 1;

			printf("walked up 1, energy left: %d", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_S))
		{
			get_character()->sp->go.position.y += 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[BACKWARD];
			get_character()->sp->moved = 1;

			printf("walked down 1, energy left: %d", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_A))
		{
			get_character()->sp->go.position.x -= 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[LEFT];
			get_character()->sp->moved = 1;

			printf("walked left 1, energy left: %d", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_D))
		{
			get_character()->sp->go.position.x += 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[RIGHT];
			get_character()->sp->moved = 1;

			printf("walked right 1, energy left: %d", get_character()->energy);
		}
		else
		{
			get_character()->sp->moved = 0;
		}
	}

	//TODO: check if dice clicked. Roll dice. Update values
	if (/* clicked dice on screen */CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
	{
		get_character()->energy = roll_dice(e_std_D6);
		printf("%d", get_character()->energy);
	}
	if (/* clicked dice on screen */CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
	{
		get_character()->energy = roll_dice(e_std_D20);
		printf("%d", get_character()->energy);
	}
}
