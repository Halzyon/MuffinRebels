/*-------------------------------------------------------------------------------------

	File: gameChar.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Author: Alwin Moo (moo.g@digipen.edu)

	All content � 2021 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/
#ifndef GAME_CHAR_H
#define GAME_CHAR_H
#include "cprocessing.h"

#include "../SpriteAnimation/spriteAnimation.h"
#include "../Character/diceHandler.h"

#define MAX_DICE 5

typedef struct 
{
	Sprite* sp;

	int hp;
	int energy;
	bool turn_done;

	int modifier;
	int mod_duration;

	unsigned int dice_size;
	dice_types dice[MAX_DICE];

	enum
	{
		CHAR_NONE = -1,
		CHAR_ATTACKING,
		CHAR_DEFENDING
	} combat_mode;

} my_character;

enum warrior_loot
{
	//level 0

	//level 1
};

enum tank_loot
{

};

enum rogue_loot
{

};

int init_char(void);

my_character* get_character(void);

int free_char(void);


#endif // !GAME_CHAR_H
