#ifndef GAME_CHAR_H
#define GAME_CHAR_H
#include "cprocessing.h"

typedef struct 
{
	CP_Vector pos;

	int hp;
	int energy;
	unsigned int character_class;

} my_character;

enum class_select
{
	Warrior,
	Tank,
	Rouge
};

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

#endif // !GAME_CHAR_H
