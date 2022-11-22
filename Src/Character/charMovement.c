#include <cprocessing.h>

#include <stdio.h>

#include "charMovement.h"
#include "gameChar.h"
#include "diceHandler.h"
#include "../Combat/combatHandler.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"
#include "gameMap.h"
#include "../Scenes/GameScene.h"

int check_limits(CP_Vector dir)
{
	dir.x += get_character()->sp->go.position.x - mapOffset;
	dir.y += get_character()->sp->go.position.y;

	if (dir.x >= 0 && dir.x < getMap()->width && dir.y >= 0 && dir.y < getMap()->height) // check within bounds before checking tile types
	{
		char var = getMap()->map_arr[map_get_index(dir.x, dir.y, getMap()->width)];
		if ((var >= WALL_1 && var <= WALL_17) || (var >= WALL_19 && var <= WALL_22))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

void hardware_handler(void)
{
	if (combatants_present)
		return;

	//while the player has energy, we will say that the player has not completed their turn
	if (get_character()->energy && !movement_clicked && !get_character()->turn_done)
	{
		get_character()->sp->moved = 0;

		if (CP_Input_KeyTriggered(KEY_W) && check_limits(CP_Vector_Set(0, -1)))
		{
			get_character()->sp->go.position.y -= 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[FORWARD];

			printf("walked up 1, energy left: %d\n", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_S) && check_limits(CP_Vector_Set(0, 1)))
		{
			get_character()->sp->go.position.y += 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[BACKWARD];

			printf("walked down 1, energy left: %d\n", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_A) && check_limits(CP_Vector_Set(-1, 0)))
		{
			get_character()->sp->go.position.x -= 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[LEFT];

			printf("walked left 1, energy left: %d\n", get_character()->energy);
		}
		else if (CP_Input_KeyTriggered(KEY_D) && check_limits(CP_Vector_Set(1, 0)))
		{
			get_character()->sp->go.position.x += 1;
			--get_character()->energy;

			get_character()->sp->renderMode = get_character()->sp->spriteStates[RIGHT];

			printf("walked right 1, energy left: %d\n", get_character()->energy);
		}

		if (!get_character()->energy)
		{
			get_character()->turn_done = 1;
		}
	}
	else if (!get_character()->energy && get_character()->turn_done)
	{
		get_character()->sp->moved = 1;
	}

	// GOD MODE
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_MIDDLE))
	{
		get_character()->energy += 20;
	}
}
