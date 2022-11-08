#ifndef DICE_HANDLER_H
#define DICE_HANDLER_H
#include <cprocessing.h>

#define D6_SIZE 6
#define D20_SIZE 20

typedef enum
{
	e_std_D6,
	e_std_D20,

	NUM_TYPES
} dice_types;

void init_dice(void);

int roll_dice(dice_types dice);

#endif // !DICE_HANDLER_H
