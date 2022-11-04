#include "cprocessing.h"
#include "../UtilsUI/ui_utils.h"
#include "combat_overlay.h"
#include "../../Character/diceHandler.h"
//#include "../../GameObject/gameObject.h"
#include "../../SpriteAnimation/spriteAnimation.h"
#include <stdio.h>

Sprite* inventory;
Sprite* dice_button;
Sprite* powerup_button;
Sprite* d20;
Sprite* d6;
Sprite* settings;
CP_Vector roll_pos;
int roll;
CP_Font font;
Sprite* cursor;
Sprite* alive_hp;
Sprite* dead_hp;
//CP_Image inv;
int dice_inButton;
float dice_timer;
float buttons_centerpointX;
float buttons_centerpointY;

void combat_init(void)
{

	inventory = CreateSprite("Assets/combat_overlay_ui/inventory_block.png", 1, 1, false, false);
	dice_button = CreateSprite("Assets/combat_overlay_ui/dice_3D_detailed.png", 1, 1, false, false);
	powerup_button = CreateSprite("Assets/combat_overlay_ui/sword.png", 1, 1, false, false);
	d6 = CreateSprite("Assets/dice/d6.png", 1, 1, false, false);
	d20 = CreateSprite("Assets/dice/d20.png", 1, 1, false, false);
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");
	settings = CreateSprite("Assets/combat_overlay_ui/gear.png", 1, 1, false, false);
	//inv = CP_Image_Load("Assets/combat_overlay_ui/inventory_block.png");
	cursor = CreateSprite("Assets/combat_overlay_ui/cursor.png", 1, 1, false, false);
	alive_hp = CreateSprite("Assets/combat_overlay_ui/alive_hp.png", 1, 1, false, false);
	dead_hp = CreateSprite("Assets/combat_overlay_ui/dead_hp.png", 1, 1, false, false);

	//	loads assets
	
	/*inventory.img = CP_Image_Load("Assets/combat_overlay_ui/grey.png");
	dice_button.img = CP_Image_Load("Assets/combat_overlay_ui/dice_3D_detailed.png");
	powerup_button.img = CP_Image_Load("Assets/combat_overlay_ui/sword.png");
	d6.img = CP_Image_Load("Assets/dice/d6.png");
	d20.img = CP_Image_Load("Assets/dice/d20.png");
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");
	settings.img = CP_Image_Load("Assets/combat_overlay_ui/gear.png");*/


	// finds the width and height of each image
	/*
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
	settings.size.x = (float)CP_Image_GetWidth(settings.img);
	settings.size.y = (float)CP_Image_GetHeight(settings.img);
	*/
	// set check for if mouse hovering over button to 0

	//d6.inButton = 0;
	//d20.inButton = 0;
	dice_inButton = 0;

	//	when image is drawn, it will place center of image at the specified location. when text is drawn, center of text will be placed at the location
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_Set(font);

	// set timer and dice timer
	dice_timer = 0;

	// dice randomiser initialise
	init_dice();
}

void init_dicePos(void)
{
	// set location where choosable d6 and d20 die are after player selects the dice button

	d6->go.position.x = buttons_centerpointX - 180.0f;
	d6->go.position.y = buttons_centerpointY - 150.0f;
	d20->go.position.x = buttons_centerpointX + 20.0f;
	d20->go.position.y = buttons_centerpointY - 150.0f;
}

void init_rollPos(void)
{
	// set location where the selected dice rolls

	roll_pos.x = buttons_centerpointX + 20.0f;
	roll_pos.y = buttons_centerpointY - 200.0f;
	d6->go.position.x = d6->go.position.y = d20->go.position.x = d20->go.position.y = 0.0f;
}

void combat_buttons(int num_roll)
{

	// set location of the buttons based on the center of the area where the power up and dice buttons are drawn

	buttons_centerpointX = CP_System_GetWindowWidth() - 180;
	buttons_centerpointY = CP_System_GetWindowHeight() - 100;
	dice_button->go.position.x = buttons_centerpointX + 100;
	dice_button->go.position.y = powerup_button->go.position.y = buttons_centerpointY;	// y position of both power up and dice button are the same
	powerup_button->go.position.x = buttons_centerpointX - 100;

	// draws the interactable buttons based on the set locations

	CP_Image_Draw(dice_button->go.image, dice_button->go.position.x, dice_button->go.position.y, dice_button->go.size.x, dice_button->go.size.y, 255);
	CP_Image_Draw(powerup_button->go.image, powerup_button->go.position.x, powerup_button->go.position.y, powerup_button->go.size.x, powerup_button->go.size.y, 255);

	dice_inButton = mouse_in_rect(dice_button->go.position.x, dice_button->go.position.y, dice_button->go.size.x, dice_button->go.size.y);	//	checks if pointer is in the dice_button image
	
	if (dice_inButton == 1 && CP_Input_MouseClicked())	//	checks if user clicked the dice button
	{
		dice_button->clicked = !dice_button->clicked;
		d6->clicked = 0;
		d20->clicked = 0;
	}
	if (mouse_in_rect(powerup_button->go.position.x, powerup_button->go.position.y, powerup_button->go.size.x, powerup_button->go.size.y) == 1)

	if (dice_button->clicked == 1)	// Draws the window pop up for player to choose dice to roll
	{
		init_dicePos();
		CP_Image_Draw(inventory->go.image, buttons_centerpointX - 80.0f, buttons_centerpointY - 150.0f, (inventory->go.size.x * 10), (inventory->go.size.y * 3), 255);
		CP_Image_Draw(d6->go.image, d6->go.position.x, d6->go.position.y, d6->go.size.x, d6->go.size.y, 255);
		CP_Image_Draw(d20->go.image, d20->go.position.x, d20->go.position.y, d20->go.size.x * 1.05f, d20->go.size.y * 1.05f, 255);
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("d6", d6->go.position.x, d6->go.position.y);
		CP_Font_DrawText("d20", d20->go.position.x, d20->go.position.y);
	}

	//d6.inButton = mouse_in_rect(d6.go.position.x, d6.go.position.y, d6.go.size.x, d6.go.size.y);			//	checks if pointer is in the d6 image
	//d20.inButton = mouse_in_rect(d20.go.position.x, d20.go.position.y, d20.go.size.x, d20.go.size.y);		//	checks if pointer is in the d20 image
	
	if ((mouse_in_rect(d6->go.position.x, d6->go.position.y, d6->go.size.x, d6->go.size.y) == 1) && CP_Input_MouseClicked() && !d20->clicked)	//	checks if user selected to roll d6 dice
	{
		dice_button->clicked = 0;
		d6->clicked = !d6->clicked;
		d20->clicked = 0;
	}
	else if ((mouse_in_rect(d20->go.position.x, d20->go.position.y, d20->go.size.x, d20->go.size.y) == 1) && CP_Input_MouseClicked() && !d6->clicked)	//	checks if user selected d20 dice
	{
		dice_button->clicked = 0;
		d6->clicked = 0;
		d20->clicked = !d20->clicked;
	}
	

	if (d6->clicked > 0)	// draws pop up window for when a dice is selected
	{
		init_rollPos();
		CP_Image_Draw(inventory->go.image, roll_pos.x, roll_pos.y, (inventory->go.size.x * 5), (inventory->go.size.y * 5), 255);
		generate_dice(6, e_std_D6, roll_pos.x, roll_pos.y);

		if (mouse_in_rect(roll_pos.x, roll_pos.y, d6->go.size.x * 1.4, d6->go.size.y * 1.4) == 1 && CP_Input_MouseClicked())
		{
			roll = 1;
		}
		if (roll == 1)
		{
			generate_dice(roll_dice(e_std_D6), e_std_D6, roll_pos.x, roll_pos.y);		// todo: change number to randomiser
			dice_timer += CP_System_GetDt();
			if (dice_timer > 2)
			{
				generate_dice(num_roll, e_std_D6, roll_pos.x, roll_pos.y);
				if (dice_timer > 4)
				{
					dice_timer = 0;
					roll = !roll;
					d6->clicked = !d6->clicked;
				}
			}
		}
	}
	else if (d20->clicked > 0)
	{
		init_rollPos();
		CP_Image_Draw(inventory->go.image, roll_pos.x, roll_pos.y, (inventory->go.size.x * 5), (inventory->go.size.y * 5), 255);
		generate_dice(20, e_std_D20, roll_pos.x, roll_pos.y);

		if (mouse_in_rect(roll_pos.x, roll_pos.y, d20->go.size.x * 1.6, d20->go.size.y * 1.6) == 1 && CP_Input_MouseClicked())
		{
			roll = 1;
		}
		if (roll == 1)
		{
			generate_dice(roll_dice(e_std_D20), e_std_D20, roll_pos.x, roll_pos.y);
			dice_timer += CP_System_GetDt();
			if (dice_timer > 2)
			{
				generate_dice(num_roll, e_std_D20, roll_pos.x, roll_pos.y);
				if (dice_timer > 4)
				{
				dice_timer = 0;
				roll = !roll;
				d20->clicked = !d20->clicked;
				}
			}
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
		CP_Image_Draw(d6->go.image, dice_posX, dice_posY, d6->go.size.x * 1.4, d6->go.size.y * 1.4, 255);
		CP_Font_DrawText(&num_ones, text_posX, text_posY);
	}
	else if (dice == e_std_D20)
	{
		CP_Image_Draw(d20->go.image, dice_posX, dice_posY, d20->go.size.x * 1.6, d20->go.size.y * 1.6, 255);
		if (num_roll / 10 != 0)
		{
			num_ones = '0' + (num_roll % 10);
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


void health_bar(int remaining_hp)
{	
	float positionX;
	float positionY = 60.0f;
	for (int j = 5; j > remaining_hp + 1; j--)
	{
		positionX = 60.0f + ((float)j * 100);
		CP_Image_Draw(dead_hp->go.image, positionX, positionY, dead_hp->go.size.x, dead_hp->go.size.y, 255);
	}
	for (int i = 0; i < remaining_hp; i++)
	{
		positionX = 60.0f + ((float)i * 100);
		CP_Image_Draw(alive_hp->go.image, positionX, positionY, alive_hp->go.size.x, alive_hp->go.size.y, 255);
	}
}

void settings_button(void)
{
	settings->go.position.x = CP_System_GetWindowWidth() - 50.0f;
	settings->go.position.y = 50.0f;
	CP_Image_Draw(settings->go.image, settings->go.position.x, settings->go.position.y, settings->go.size.x, settings->go.size.y, 255);
	// settings.inButton = mouse_in_rect(settings.go.position.x, settings.go.position.y, settings.go.size.x, settings.go.size.y);
	if ((mouse_in_rect(settings->go.position.x, settings->go.position.y, settings->go.size.x, settings->go.size.y) == 1) && CP_Input_MouseClicked())
	{
		settings->clicked = !settings->clicked;
	}
	if (settings->clicked == 1)
	{
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, 500.0f, 500.0f);	//	placeholder menu
		if (CP_Input_KeyDown(KEY_ESCAPE))
		{
			settings->clicked = !settings->clicked;
		}
	}
}

void inventory_window(void)
{
	float position_X[3];
	CP_Settings_RectMode(CP_POSITION_CENTER);
	float position_Y = buttons_centerpointY - 150.0f;
	for (int i = 0; i <= 2; i++)
	{
		position_X[i] = buttons_centerpointX - ((float)i * (100.0f));
		CP_Image_Draw(inventory->go.image, position_X[i], position_Y, CP_Image_GetWidth(inventory->go.image), CP_Image_GetHeight(inventory->go.image), 255);
		//CP_Graphics_DrawRect(position_X[i], position_Y, 100.0f, 100.0f);
	}
	CP_Image_Draw(cursor->go.image, position_X[0], position_Y, cursor->go.size.x, cursor->go.size.y, 255);
}

/*void timer_ui(void)
{
	char display_mins_tens = 
	CP_Font_DrawText(*remaining_time, CP_System_GetWindowWidth() / 2, 50.0f);
}*/


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
	CP_Image_Free(d6->go.image);
	CP_Image_Free(d20->go.image);
	CP_Image_Free(inventory->go.image);
	CP_Image_Free(dice_button->go.image);
	CP_Image_Free(powerup_button->go.image);
	CP_Image_Free(settings->go.image);
	//CP_Image_Free(inv);
}