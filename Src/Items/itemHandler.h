#ifndef ITEM_HANDLER_H
#define ITEM_HANDLER_H

#include "../Character/diceHandler.h"
#include "../Character/gameChar.h"

typedef enum ITEMS
{
	WOODEN_SWORD,
	WOODEN_SHIELD,
	IRON_SWORD,
	IRON_SHIELD,
	GOLD_SWORD,
	GOLD_SHIELD,
	DIAMOND_SWORD,
	DIAMOND_SHIELD,

	NUM_ITEMS,

	NONE_ITEMS,
	MASTER_SWORD
};

typedef enum POWERUPS
{
	STRONG_ARM,
	LEATHER_SKIN,
	HEALTH_POT,

	NUM_POWERUPS,

	NONE_POWERUPS
};

int current_item;
int current_powerup;

int randomise_all(int current_level);

void reset_items(void);

void reset_modifier(void);

void init_woodensword(void);

void init_woodenshield(void);

void init_ironsword(void);

void init_ironshield(void);

void init_goldsword(void);

void init_goldshield(void);

void init_diamondsword(void);

void init_diamondshield(void);

void init_mastersword(void);

/*!
 * @brief increases damage/defence
 * @param  void
*/
void modifier_strongarm(void);

/*!
 * @brief increases health while fighting
 * @param  void
*/
void modifier_leatherskin(void);

/*!
 * @brief on pick up, immediately call this function, add modifier to health, then reset_modifier
 * @param  void
*/
void modifier_healthpot(void);

#endif // !ITEM_HANDLER_H

