#ifndef GAME_CHAR_H
#define GAME_CHAR_H
#include "cprocessing.h"

#include "../SpriteAnimation/spriteAnimation.h"
#include "../Character/diceHandler.h"

#define MAX_DICE 5

typedef enum
{
	Warrior,
	Tank,
	Rouge
} class_select;

typedef struct 
{
	Sprite* sp;

	int hp;
	int energy;
	unsigned int char_class;
	bool turn_done;

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

int init_char(class_select char_select);

my_character* get_character(void);

int free_char(void);


#endif // !GAME_CHAR_H
