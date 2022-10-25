#include <stdlib.h>
#include <time.h>

#include "diceHandler.h"

const int std_D6[6] = { 1,2,3,4,5,6 };
const int std_D20[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };

int* dice_list[NUM_TYPES] = {&std_D6, &std_D20};

void init_dice(void)
{
	srand(time(NULL));
}

int roll_dice(dice_types dice)
{
	int number = rand() % (sizeof(*dice_list[dice]) / sizeof(int)) + 1;
	return dice_list[dice][number];
}
