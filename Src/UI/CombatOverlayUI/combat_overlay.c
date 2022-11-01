#include "cprocessing.h"
#include "../UtilsUI/ui_utils.h"
#include "combat_overlay.h"
#include "../../Character/diceHandler.h"

asset inventory;
asset dice_button;
asset powerup_button;
asset d20;
asset d6;
CP_Vector roll_pos;
CP_Font font;

void combat_init(void)
{
	inventory.img = CP_Image_Load("Assets/combat_overlay_ui/grey.png");
	dice_button.img = CP_Image_Load("Assets/combat_overlay_ui/dice_3D_detailed.png");
	powerup_button.img = CP_Image_Load("Assets/combat_overlay_ui/sword.png");
	d6.img = CP_Image_Load("Assets/dice/d6.png");
	d20.img = CP_Image_Load("Assets/dice/d20.png");
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");
	dice_button.size.x = (float)CP_Image_GetWidth(dice_button.img);
	dice_button.size.y = (float)CP_Image_GetHeight(dice_button.img);
	powerup_button.size.x = (float)CP_Image_GetWidth(powerup_button.img);
	powerup_button.size.y = (float)CP_Image_GetHeight(powerup_button.img);
	inventory.size.x = (float)CP_Image_GetWidth(inventory.img);
	inventory.size.y = (float)CP_Image_GetHeight(inventory.img);
	d20.size.x = (float)CP_Image_GetWidth(d20.img);
	d20.size.y = (float)CP_Image_GetWidth(d6.img);
	d6.size.x = (float)CP_Image_GetWidth(d6.img);
	d6.size.y = (float)CP_Image_GetHeight(d6.img);
	d6.inButton = 0;
	d20.inButton = 0;
	dice_button.inButton = 0;
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_Set(font);
}

void buttons(void)
{
	float buttons_centerpointX = CP_System_GetWindowWidth() - 180;
	float buttons_centerpointY = CP_System_GetWindowHeight() - 100;
	roll_pos.x = buttons_centerpointX + 20.0f;
	roll_pos.y = buttons_centerpointY - 200.0f;
	dice_button.pos.x = buttons_centerpointX + 100;
	dice_button.pos.y = powerup_button.pos.y = buttons_centerpointY;
	powerup_button.pos.x = buttons_centerpointX - 100;
	d6.pos.x = buttons_centerpointX - 180.0f;
	d6.pos.y = buttons_centerpointY - 150.0f;
	d20.pos.x = buttons_centerpointX + 20.0f;
	d20.pos.y = buttons_centerpointY - 150.0f;
	CP_Image_Draw(dice_button.img, dice_button.pos.x, dice_button.pos.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.img, powerup_button.pos.x, powerup_button.pos.y, powerup_button.size.x, powerup_button.size.y, 255);
	dice_button.inButton = mouse_in_rect(dice_button.pos.x, dice_button.pos.y, dice_button.size.x, dice_button.size.y);
	if (dice_button.inButton == 1 && CP_Input_MouseClicked())
	{
		dice_button.clicked = !dice_button.clicked;
		d6.clicked = 0;
		d20.clicked = 0;
	}
	if (dice_button.clicked == 1)	// Draws the window pop up for player to choose dice to roll
	{
		CP_Image_Draw(inventory.img, buttons_centerpointX - 80.0f, buttons_centerpointY - 150.0f, (inventory.size.x * 10), (inventory.size.y * 3), 255);
		CP_Image_Draw(d6.img, d6.pos.x, d6.pos.y, d6.size.x, d6.size.y, 255);
		CP_Image_Draw(d20.img, d20.pos.x, d20.pos.y, d20.size.x * 1.05f, d20.size.y * 1.05f, 255);
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("d6", d6.pos.x, d6.pos.y);
		CP_Font_DrawText("d20", d20.pos.x, d20.pos.y);
	}


	d6.inButton = mouse_in_rect(d6.pos.x, d6.pos.y, d6.size.x, d6.size.y);
	d20.inButton = mouse_in_rect(d20.pos.x, d20.pos.y, d20.size.x, d20.size.y);
	if            ((d6.inButton == 1) && CP_Input_MouseClicked())
	{
		dice_button.clicked = 0;
		d6.clicked = !d6.clicked;
		d20.clicked = 0;
	}
	else if ((d20.inButton == 1) && CP_Input_MouseClicked())
	{
		dice_button.clicked = 0;
		d6.clicked = 0;
		d20.clicked = !d20.clicked;
	}
	if (d6.clicked == 1)
	{
		CP_Image_Draw(inventory.img, roll_pos.x, roll_pos.y, (inventory.size.x * 5), (inventory.size.y * 5), 255);
		generate_dice(6, e_std_D6, roll_pos.x, roll_pos.y);
		if (mouse_in_rect(roll_pos.x, roll_pos.y, d6.size.x * 1.5, d6.size.y * 1.5) == 1 && CP_Input_MouseClicked())
		{
			generate_dice(4, e_std_D6, roll_pos.x, roll_pos.y);
		}
	}
	else if (d20.clicked == 1)
	{
		CP_Image_Draw(inventory.img, buttons_centerpointX + 20.0f, buttons_centerpointY - 200.0f, (inventory.size.x * 5), (inventory.size.y * 5), 255);
		generate_dice(20, e_std_D20, buttons_centerpointX + 20.0f, buttons_centerpointY - 200.0f);
		if (mouse_in_rect(roll_pos.x, roll_pos.y, d6.size.x * 1.5, d6.size.y * 1.5) == 1 && CP_Input_MouseClicked())
		{
			generate_dice(14, e_std_D20, roll_pos.x, roll_pos.y);
		}
	}
}

void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY)
{
	float text_posX = dice_posX + 5.5;
	float text_posY = dice_posY - 2.5;
	char num_ones = '0' + num_roll;
	char num_tens;
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Font_Set(font);
	CP_Settings_TextSize(100.0f);
	if (dice == e_std_D6)
	{
		CP_Image_Draw(d6.img, dice_posX, dice_posY, d6.size.x * 1.5, d6.size.y * 1.5, 255);
		CP_Font_DrawText(&num_ones, text_posX, text_posY);
	}
	if (dice == e_std_D20)
	{
		CP_Image_Draw(d20.img, dice_posX, dice_posY, d20.size.x * 1.7, d20.size.y * 1.7, 255);
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



void combat_ui_shutdown(void)
{
	CP_Image_Free(d6.img);
	CP_Image_Free(d20.img);
	CP_Image_Free(inventory.img);
	CP_Image_Free(dice_button.img);
	CP_Image_Free(powerup_button.img);
}