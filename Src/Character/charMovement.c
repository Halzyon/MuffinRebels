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
			get_character()->pos = CP_Vector_Set(get_character()->pos.x, get_character()->pos.y - 1);
			--get_character()->energy;
			printf("walked up 1, energy left: %d", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_S))
		{
			get_character()->pos = CP_Vector_Set(get_character()->pos.x, get_character()->pos.y + 1);
			--get_character()->energy;
			printf("walked down 1, energy left: %d", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_A))
		{
			get_character()->pos = CP_Vector_Set(get_character()->pos.x - 1, get_character()->pos.y);
			--get_character()->energy;
			printf("walked left 1, energy left: %d", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_D))
		{
			get_character()->pos = CP_Vector_Set(get_character()->pos.x + 1, get_character()->pos.y);
			--get_character()->energy;
			printf("walked right 1, energy left: %d", get_character()->energy);
		}
	}

	//TODO: check if dice clicked. Roll dice. Update values
	if (/* clicked dice on screen */CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
	{
		get_character()->energy = roll_dice(e_std_D6);
		printf("%d", get_character()->energy);
	}
}
