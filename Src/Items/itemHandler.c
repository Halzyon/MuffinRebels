#include "itemHandler.h"

void reset_items(void)
{
	current_item = NONE_ITEMS;
	get_character()->dice[0] = e_std_D6;
	
	for (int i = 1; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void reset_modifier(void)
{
	current_powerup = NONE_POWERUPS;
	get_character()->modifier = 0;
}

void init_woodensword(void)
{
	current_item = WOODEN_SWORD;
	get_character()->dice[0] = e_std_D6;
	get_character()->dice[1] = e_std_D4;

	get_character()->dice_size = 2;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_woodenshield(void)
{
	current_item = WOODEN_SHIELD;
	get_character()->dice[0] = e_std_D4;
	get_character()->dice[1] = e_std_D4;
	get_character()->dice[2] = e_std_D4;

	get_character()->dice_size = 3;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_ironsword(void)
{
	current_item = IRON_SWORD;
	get_character()->dice[0] = e_std_D6;
	get_character()->dice[1] = e_std_D6;

	get_character()->dice_size = 2;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_ironshield(void)
{
	current_item = IRON_SHIELD;
	get_character()->dice[0] = e_std_D6;
	get_character()->dice[1] = e_std_D4;
	get_character()->dice[2] = e_std_D4;
	get_character()->dice[3] = e_std_D4;

	get_character()->dice_size = 4;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_goldsword(void)
{
	current_item = GOLD_SWORD;
	get_character()->dice[0] = e_std_D6;
	get_character()->dice[1] = e_std_D6;
	get_character()->dice[2] = e_std_D6;

	get_character()->dice_size = 3;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_goldshield(void)
{
	current_item = GOLD_SHIELD;
	get_character()->dice[0] = e_std_D6;
	get_character()->dice[1] = e_std_D6;
	get_character()->dice[2] = e_std_D4;
	get_character()->dice[3] = e_std_D4;

	get_character()->dice_size = 4;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_diamondsword(void)
{
	current_item = DIAMOND_SWORD;
	get_character()->dice[0] = e_std_D6;
	get_character()->dice[1] = e_std_D6;
	get_character()->dice[2] = e_std_D6;
	get_character()->dice[3] = e_std_D6;

	get_character()->dice_size = 4;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_diamondshield(void)
{
	current_item = DIAMOND_SHIELD;
	get_character()->dice[0] = e_std_D6;
	get_character()->dice[1] = e_std_D6;
	get_character()->dice[2] = e_std_D6;
	get_character()->dice[3] = e_std_D6;
	get_character()->dice[4] = e_std_D6;

	get_character()->dice_size = 4;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void init_mastersword(void)
{
	current_item = MASTER_SWORD;
	get_character()->dice[0] = e_std_D20;
	get_character()->dice[1] = e_std_D20;

	get_character()->dice_size = 2;

	for (int i = get_character()->dice_size; i < MAX_DICE; ++i)
	{
		get_character()->dice[i] = -1;
	}
}

void modifier_strongarm(void)
{
	current_powerup = STRONG_ARM;
	get_character()->modifier = 3;
	get_character()->mod_duration = 10;
}

void modifier_leatherskin(void)
{
	current_powerup = LEATHER_SKIN;
	get_character()->modifier = 5;
	get_character()->mod_duration = 10;
}

void modifier_healthpot(void)
{
	current_powerup = HEALTH_POT;
	get_character()->modifier = 10;
}
