#include "cprocessing.h"
#include "../UtilsUI/ui_utils.h"
#include "combat_overlay.h"
#include "../../Character/diceHandler.h"

float buttons_centerpointX;
float buttons_centerpointY;
asset dead_hp;
asset inventory;
asset dice_button;
asset powerup_button;
asset d20;
asset d6;
asset settings;
asset cursor;
asset alive_hp;
asset dead_hp;
CP_Vector roll_pos;
int roll;
CP_Font font;
float dice_timer;

void combat_overlay_init(void)
{
	//	loads assets
	
	inventory.image = CP_Image_Load("Assets/combat_overlay_ui/inventory_block.png");
	dice_button.image = CP_Image_Load("Assets/combat_overlay_ui/dice_3D_detailed.png");
	powerup_button.image = CP_Image_Load("Assets/combat_overlay_ui/sword.png");
	d6.image = CP_Image_Load("Assets/dice/d6.png");
	d20.image = CP_Image_Load("Assets/dice/d20.png");
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");
	settings.image = CP_Image_Load("Assets/combat_overlay_ui/gear.png");
	cursor.image = CP_Image_Load("Assets/combat_overlay_ui/cursor.png");
	alive_hp.image = CP_Image_Load("Assets/combat_overlay_ui/alive_hp.png");
	dead_hp.image = CP_Image_Load("Assets/combat_overlay_ui/dead_hp.png");


	// finds the width and height of each image
	
	dice_button.size.x = (float)CP_Image_GetWidth(dice_button.image);
	dice_button.size.y = (float)CP_Image_GetHeight(dice_button.image);
	powerup_button.size.x = (float)CP_Image_GetWidth(powerup_button.image);
	powerup_button.size.y = (float)CP_Image_GetHeight(powerup_button.image);
	inventory.size.x = (float)CP_Image_GetWidth(inventory.image);
	inventory.size.y = (float)CP_Image_GetHeight(inventory.image);
	d20.size.x = (float)CP_Image_GetWidth(d20.image);
	d20.size.y = (float)CP_Image_GetHeight(d20.image);
	d6.size.x = (float)CP_Image_GetWidth(d6.image);
	d6.size.y = (float)CP_Image_GetHeight(d6.image);
	settings.size.x = (float)CP_Image_GetWidth(settings.image);
	settings.size.y = (float)CP_Image_GetHeight(settings.image);
	cursor.size.x = (float)CP_Image_GetWidth(cursor.image);
	cursor.size.y = (float)CP_Image_GetHeight(cursor.image);
	alive_hp.size.x = (float)CP_Image_GetWidth(alive_hp.image);
	alive_hp.size.y = (float)CP_Image_GetHeight(alive_hp.image);
	dead_hp.size.x = (float)CP_Image_GetWidth(dead_hp.image);
	dead_hp.size.y = (float)CP_Image_GetHeight(dead_hp.image);

	d6.inButton = 0;
	d20.inButton = 0;

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

	d20.position.x = buttons_centerpointX + 80.0f;
	d6.position.y =  d20.position.y = buttons_centerpointY - 130.0f;
	d6.position.x = d20.position.x - 125.0f;
}

void init_rollPos(void)
{
	// set location where the selected dice rolls

	roll_pos.x = buttons_centerpointX + 20.0f;
	roll_pos.y = buttons_centerpointY - 200.0f;
	d6.position.x = d6.position.y = d20.position.x = d20.position.y = 0.0f;
}

void combat_overlay_update(int num_roll)
{

	// set location of the buttons based on the center of the area where the power up and dice buttons are drawn

	buttons_centerpointX = CP_System_GetWindowWidth() - 180.0f;
	buttons_centerpointY = CP_System_GetWindowHeight() - 80.0f;
	dice_button.position.x = buttons_centerpointX + 80.0f;
	dice_button.position.y = powerup_button.position.y = buttons_centerpointY;	// y position of both power up and dice button are the same
	powerup_button.position.x = buttons_centerpointX - 80.0f;

	// draws the interactable buttons based on the set locations

	CP_Image_Draw(dice_button.image, dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.image, powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y, 255);

	// branch out to decide if player rolls or not
	if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && !powerup_button.clicked)	//	checks if user clicked the dice button
	{
		dice_button.clicked = !dice_button.clicked;
		d6.clicked = 0;
		d20.clicked = 0;
	}

	if (powerup_button.clicked)	// Draws the window pop up for player to choose dice to roll
	{
		inventory_window(3, powerup_button.position.x);
	}

	if (dice_button.clicked)	// Draws the window pop up for player to choose dice to roll
	{
		init_dicePos();
		inventory_window(2, dice_button.position.x);
		CP_Image_Draw(d6.image, d6.position.x, d6.position.y, d6.size.x * 0.95, d6.size.y * 0.95, 255);
		CP_Image_Draw(d20.image, d20.position.x, d20.position.y, d20.size.x, d20.size.y, 255);
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("d6", d6.position.x, d6.position.y);
		CP_Font_DrawText("d20", d20.position.x, d20.position.y);
	}

	d6.inButton = mouse_in_rect(d6.position.x, d6.position.y, d6.size.x - 30.0f, d6.size.y - 30.0f);			//	checks if pointer is in the d6 image
	d20.inButton = mouse_in_rect(d20.position.x, d20.position.y, d20.size.x - 30.0f, d20.size.y - 30.0f);		//	checks if pointer is in the d20 image

	if (d6.inButton == 1)
	{
		CP_Image_Draw(cursor.image, d6.position.x, d6.position.y, cursor.size.x, cursor.size.y, 255);
	}
	if (d20.inButton == 1)
	{
		CP_Image_Draw(cursor.image, d20.position.x, d20.position.y, cursor.size.x, cursor.size.y, 255);
	}

	if ((d6.inButton == 1) && CP_Input_MouseClicked() && !d20.clicked)	//	checks if user selected to roll d6 dice
	{
		dice_button.clicked = 0;
		d6.clicked = !d6.clicked;
		d20.clicked = 0;
	}
	else if ((d20.inButton == 1) && CP_Input_MouseClicked() && !d6.clicked)	//	checks if user selected d20 dice
	{
		dice_button.clicked = 0;
		d6.clicked = 0;
		d20.clicked = !d20.clicked;
	}

	if (d6.clicked)	// draws pop up window for when a dice is selected
	{
		init_rollPos();
		CP_Image_Draw(inventory.image, roll_pos.x, roll_pos.y, inventory.size.x * 2.0f, inventory.size.y * 2.0f, 255);
		generate_dice(roll_dice(e_std_D6), e_std_D6, roll_pos.x, roll_pos.y);		// todo: change number to randomiser
		dice_timer += CP_System_GetDt();
		if (dice_timer > 2.0f)
		{
			generate_dice(num_roll, e_std_D6, roll_pos.x, roll_pos.y);
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				roll = !roll;
				d6.clicked = !d6.clicked;
			}
		}
	}
	else if (d20.clicked)
	{
		init_rollPos();
		CP_Image_Draw(inventory.image, roll_pos.x, roll_pos.y, inventory.size.x * 1.8f, inventory.size.y * 1.8f, 255);
		generate_dice(roll_dice(e_std_D20), e_std_D20, roll_pos.x, roll_pos.y);
		dice_timer += CP_System_GetDt();
		if (dice_timer > 2.0f)
		{
			generate_dice(num_roll, e_std_D20, roll_pos.x, roll_pos.y);
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				roll = !roll;
				d20.clicked = !d20.clicked;
			}
		}
	}
}
/*
void choose_to_roll_dice(int num_roll)
{
	if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && powerup_button.clicked == 0)	//	checks if user clicked the dice button
	{
		dice_button.clicked = !dice_button.clicked;
		d6.clicked = 0;
		d20.clicked = 0;
	}

	if (dice_button.clicked == 1)	// Draws the window pop up for player to choose dice to roll
	{
		init_dicePos();
		inventory_window(2, dice_button.position.x);
		CP_Image_Draw(d6.image, d6.position.x, d6.position.y, d6.size.x * 0.95, d6.size.y * 0.95, 255);
		CP_Image_Draw(d20.image, d20.position.x, d20.position.y, d20.size.x, d20.size.y, 255);
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("d6", d6.position.x, d6.position.y);
		CP_Font_DrawText("d20", d20.position.x, d20.position.y);
	}

	d6.inButton = mouse_in_rect(d6.position.x, d6.position.y, d6.size.x - 30.0f, d6.size.y - 30.0f);			//	checks if pointer is in the d6 image
	d20.inButton = mouse_in_rect(d20.position.x, d20.position.y, d20.size.x - 30.0f, d20.size.y - 30.0f);		//	checks if pointer is in the d20 image

	if (d6.inButton == 1)
	{
		CP_Image_Draw(cursor.image, d6.position.x, d6.position.y, cursor.size.x, cursor.size.y, 255);
	}
	if (d20.inButton == 1)
	{
		CP_Image_Draw(cursor.image, d20.position.x, d20.position.y, cursor.size.x, cursor.size.y, 255);
	}

	if ((d6.inButton == 1) && CP_Input_MouseClicked() && !d20.clicked)	//	checks if user selected to roll d6 dice
	{
		dice_button.clicked = 0;
		d6.clicked = !d6.clicked;
		d20.clicked = 0;
	}
	else if ((d20.inButton == 1) && CP_Input_MouseClicked() && !d6.clicked)	//	checks if user selected d20 dice
	{
		dice_button.clicked = 0;
		d6.clicked = 0;
		d20.clicked = !d20.clicked;
	}


	if (d6.clicked > 0)	// draws pop up window for when a dice is selected
	{
		init_rollPos();
		CP_Image_Draw(inventory.image, roll_pos.x, roll_pos.y, inventory.size.x * 2.0f, inventory.size.y * 2.0f, 255);
		generate_dice(roll_dice(e_std_D6), e_std_D6, roll_pos.x, roll_pos.y);		// todo: change number to randomiser
		dice_timer += CP_System_GetDt();
		if (dice_timer > 2.0f)
		{
			generate_dice(num_roll, e_std_D6, roll_pos.x, roll_pos.y);
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				roll = !roll;
				d6.clicked = !d6.clicked;
			}
		}
	}
	else if (d20.clicked > 0)
	{
		init_rollPos();
		CP_Image_Draw(inventory.image, roll_pos.x, roll_pos.y, inventory.size.x * 1.8f, inventory.size.y * 1.8f, 255);
		generate_dice(roll_dice(e_std_D20), e_std_D20, roll_pos.x, roll_pos.y);
		dice_timer += CP_System_GetDt();
		if (dice_timer > 2.0f)
		{
			generate_dice(num_roll, e_std_D20, roll_pos.x, roll_pos.y);
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				roll = !roll;
				d20.clicked = !d20.clicked;
			}
		}
	}
}

void choose_powerup(void)
{
	if (mouse_in_rect(powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y) == 1 && CP_Input_MouseClicked() && dice_button.clicked == 0)	//	checks if user clicked the dice button
	{
		powerup_button.clicked = !powerup_button.clicked;
	}

	if (powerup_button.clicked == 1)	// Draws the window pop up for player to choose dice to roll
	{
		inventory_window(3, powerup_button.position.x);
		for (int i = 0; i < 3; i++)
		{
			float x = powerup_button.position.x - ((float)i * 125.0f);
			float y = buttons_centerpointY - 130.0f;
			CP_Graphics_DrawRect(x, y, 100.0f, 100.0f);
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		float x = powerup_button.position.x - ((float)i * 125.0f);
		float y = buttons_centerpointY - 130.0f;
		if (mouse_in_rect(x, y, 60.0f, 60.0f) == 1)
		{
			CP_Image_Draw(cursor.image, x, y, cursor.size.x, cursor.size.y, 255);
		}
	}
}*/

void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY) // draws dice (d6 or d20) with number corresponding to value num_roll
{
	float text_posX = dice_posX + 5.5f;
	float text_posY = dice_posY - 2.5f;
	char num_ones = '0' + num_roll;
	char num_tens;
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Font_Set(font);
	CP_Settings_TextSize(100.0f);
	if (dice == e_std_D6)
	{
		CP_Image_Draw(d6.image, dice_posX, dice_posY, d6.size.x * 1.6f, d6.size.y * 1.6f, 255);
		CP_Font_DrawText(&num_ones, text_posX, text_posY);
	}
	else if (dice == e_std_D20)
	{
		CP_Image_Draw(d20.image, dice_posX, dice_posY, d20.size.x * 1.6f, d20.size.y * 1.6f, 255);
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


void health_bar(int remaining_hp)	//	draws hp bar (max is currently 5)
{	
	float positionX;
	float positionY = 60.0f;
	for (int j = 5; j > remaining_hp; j--)
	{
		positionX = 60.0f + ((float)(j-1) * 100.0f);
		CP_Image_Draw(dead_hp.image, positionX, positionY, dead_hp.size.x, dead_hp.size.y, 255);
	}
	for (int i = 0; i < remaining_hp; i++)
	{
		positionX = 60.0f + ((float)i * 100.0f);
		CP_Image_Draw(alive_hp.image, positionX, positionY, alive_hp.size.x, alive_hp.size.y, 255);
	}
}

void settings_button(void)		//	draws settings icon
{
	settings.position.x = CP_System_GetWindowWidth() - 50.0f;
	settings.position.y = 50.0f;
	CP_Image_Draw(settings.image, settings.position.x, settings.position.y, settings.size.x, settings.size.y, 255);
	if ((mouse_in_rect(settings.position.x, settings.position.y, settings.size.x, settings.size.y) == 1) && CP_Input_MouseClicked())
	{
		settings.clicked = !settings.clicked;
	}
	if (settings.clicked == 1)
	{
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, 500.0f, 500.0f);	//	placeholder menu
		if (CP_Input_KeyDown(KEY_ESCAPE))
		{
			settings.clicked = !settings.clicked;
		}
	}
}

void inventory_window(int num_item, float rightmost_box_positionX)
{
	float position_Y = buttons_centerpointY - 130.0f;
	for (int i = 0; i < num_item; i++)
	{
		float position_X = rightmost_box_positionX - ((float)i * (125.0f));
		CP_Image_Draw(inventory.image, position_X, position_Y, inventory.size.x, inventory.size.y, 255);
	}
}

/*void timer_ui(void)
{
	char display_mins_tens = 
	CP_Font_DrawText(*remaining_time, CP_System_GetWindowWidth() / 2, 50.0f);
}*/


void combat_ui_shutdown(void)
{
	CP_Image_Free(d6.image);
	CP_Image_Free(d20.image);
	CP_Image_Free(inventory.image);
	CP_Image_Free(dice_button.image);
	CP_Image_Free(powerup_button.image);
	CP_Image_Free(settings.image);
	CP_Image_Free(inventory.image);
	CP_Image_Free(cursor.image);
	CP_Image_Free(alive_hp.image);
	CP_Image_Free(dead_hp.image);
	//CP_Image_Free(inv);
}