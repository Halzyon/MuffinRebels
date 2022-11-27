/*-------------------------------------------------------------------------------------

	File: charMovement.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Author: Alwin Moo (moo.g@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/
#ifndef CHAR_MOVEMENT_H
#define CHAR_MOVEMENT_H

int check_limits(CP_Vector dir);

void hardware_handler(void);

int check_Chest(CP_Vector pos);

#endif // !CHAR_MOVEMENT_H
