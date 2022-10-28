#pragma once
#include "cprocessing.h"

typedef struct
{
	CP_Image img;
	CP_Vector size;
	CP_Vector pos;
}asset;

void combat_init(void);

void buttons(void);