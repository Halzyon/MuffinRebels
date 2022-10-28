#include "cprocessing.h"
#include "..\UtilsUI\ui_utils.h"
#include <stdio.h>
#include "..\..\Character\diceHandler.h"
#include "dice_ui.h"

/*typedef struct
{
	CP_Vector pos;
	CP_Image img;
	float height;
	float width;
}image_asset_properties;

image_asset_properties dice[6];*/
CP_Image d20;
CP_Image d6;
CP_Font dice_font;
float dice_time;

void dice_ui_init(void)
{
	/*dice[0].img = CP_Image_Load("Assets/dice/dieWhite_border1.png");
	dice[1].img = CP_Image_Load("Assets/dice/dieWhite_border2.png");
	dice[2].img = CP_Image_Load("Assets/dice/dieWhite_border3.png");
	dice[3].img = CP_Image_Load("Assets/dice/dieWhite_border4.png");
	dice[4].img = CP_Image_Load("Assets/dice/dieWhite_border5.png");
	dice[5].img = CP_Image_Load("Assets/dice/dieWhite_border6.png");*/
	d6 = CP_Image_Load("Assets/dice/d6.png");
	d20 = CP_Image_Load("Assets/dice/d20.png");
	dice_font = CP_Font_Load("Assets/Kenney_Pixel.ttf");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	/*for (int i = 0; i < 6; i++)
	{
		dice[i].height = CP_Image_GetHeight(dice[i].img);
		dice[i].width = CP_Image_GetWidth(dice[i].img);
	}*/
	dice_time = 0.0f;
}

/*
void player_rolls_dice(int num_roll)
{
	int runthrough_num = num_roll;
	generate_dice(num_roll);
	if ((mouse_in_rect(dice->pos.x, dice->pos.y, dice->width, dice->height) == 1) && CP_Input_MouseClicked())
	{
		while (dice_time < 3)
		{
			float speed = 0.1f * CP_System_GetDt();	//	...GetDt() function gets the time between each frame
			dice_time = dice_time + speed;
			if (runthrough_num < 5)
			{
				runthrough_num += 1;
			}
			else if (runthrough_num > 4)
			{
				runthrough_num -= 1;
			}
			generate_dice(runthrough_num);
			printf("%f , %d\n", dice_time, runthrough_num);
		}
	}
	dice_time = 0;
}*/

void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY)
{
	float text_posX = dice_posX + 5.5;
	float text_posY = dice_posY - 2.5;
	char num_ones = '0' + num_roll;
	char num_tens;
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Font_Set(dice_font);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(100.0f);
	if (dice == e_std_D6)
	{
		CP_Image_Draw(d6, dice_posX, dice_posY, CP_Image_GetWidth(d6) * 1.8, CP_Image_GetHeight(d6) * 1.8, 255);
		CP_Font_DrawText(&num_ones, text_posX, text_posY);
	}
	if (dice == e_std_D20)
	{
		CP_Image_Draw(d20, dice_posX, dice_posY, CP_Image_GetWidth(d20) * 2, CP_Image_GetHeight(d20) * 2, 255);
		if (num_roll / 10 != 0)
		{
			num_ones = '0' + (num_roll - (num_roll / 10) * 10);
			num_tens = '0' + (num_roll / 10);
			CP_Font_DrawText(&num_ones, text_posX + 25, text_posY);
			CP_Font_DrawText(&num_tens, text_posX - 25, text_posY);
		}
		else
		{
			CP_Font_DrawText(&num_ones, dice_posX, dice_posY);
		}
	}
}

void dice_shutdown(void)
{
	/*for (int i = 0; i < 6; i++)
	{
		CP_Image_Free(&dice[i].img);
	}*/
	CP_Image_Free(d6);
	CP_Image_Free(d20);
}