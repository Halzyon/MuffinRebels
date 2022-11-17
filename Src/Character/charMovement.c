#include <cprocessing.h>

#include <stdio.h>

#include "charMovement.h"
#include "gameChar.h"
#include "diceHandler.h"
#include "../Combat/combatHandler.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"

int check_limits(void)
{
	return 0;
}

int check_enemy(void)
{

}

void hardware_handler(void)
{
	if (combatants_present)
		return;

	if (get_character()->energy && !movement_clicked)
	{
		if (CP_Input_KeyTriggered(KEY_W))
		{
			get_character()->sp->go.position.y -= 1;
			--get_character()->energy;
			
			get_character()->sp->renderMode = get_character()->sp->spriteStates[FORWARD];
			get_character()->sp->moved = 1;

			printf("walked up 1, energy left: %d\n", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_S))
		{
			get_character()->sp->go.position.y += 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[BACKWARD];
			get_character()->sp->moved = 1;

			printf("walked down 1, energy left: %d\n", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_A))
		{
			get_character()->sp->go.position.x -= 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[LEFT];
			get_character()->sp->moved = 1;

			printf("walked left 1, energy left: %d\n", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_D))
		{
			get_character()->sp->go.position.x += 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[RIGHT];
			get_character()->sp->moved = 1;

			printf("walked right 1, energy left: %d\n", get_character()->energy);
		}
		else
		{
			get_character()->sp->moved = 0;
		}
	}
	else
		get_character()->sp->moved = 0;

	// GOD MODE
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_MIDDLE))
	{
		get_character()->energy += 20;
	}
}
