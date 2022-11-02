#ifndef GAME_CHAR_H
#define GAME_CHAR_H
#include "cprocessing.h"

#include "../SpriteAnimation/spriteAnimation.h"

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
