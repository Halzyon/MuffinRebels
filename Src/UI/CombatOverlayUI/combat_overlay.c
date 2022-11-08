#include "combat_overlay.h"
#include "../UtilsUI/ui_utils.h"

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
asset powerup[3];
CP_Vector roll_pos;
int roll;
CP_Font font;
float dice_timer;

void combat_overlay_init(void)
{
	//	loads images and finds their sizes
	
	get_image_size("dice_button.png", &dice_button);
	get_image_size("inventory_block.png", &inventory);
	get_image_size("powerup_button.png", &powerup_button);
	get_image_size("d6.png", &d6);
	get_image_size("d20.png", &d20);
	get_image_size("settings.png", &settings);
	get_image_size("cursor.png", &cursor);
	get_image_size("alive_hp.png", &alive_hp);
	get_image_size("dead_hp.png", &dead_hp);
	get_image_size("powerup[atk].png", &powerup[atk]);
	get_image_size("powerup[hp].png", &powerup[hp]);
	get_image_size("powerup[extra_d4].png", &powerup[extra_d4]);
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");

	// init inbutton values to 0
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

	// initialize description
	powerup[atk].desc = "Increases damage dealt for 3 turns.";
	powerup[hp].desc = "Increases Max HP for 3 turns";
	powerup[extra_d4].desc = "Additional d4 Dice is given. Can be used for 3 turns.";
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);
}

void init_dicePos(void)
{
	// set location where choosable d6 and d20 die are after player selects the dice button

	d20.position.x = buttons_centerpointX + 80.0f;
	d6.position.y =  d20.position.y = buttons_centerpointY - 150.0f;
	d6.position.x = d20.position.x - 125.0f;
}

void init_rollPos(void)
{
	// set location where the selected dice rolls

	roll_pos.x = buttons_centerpointX + 20.0f;
	roll_pos.y = buttons_centerpointY - 200.0f;
	d6.position.x = d6.position.y = d20.position.x = d20.position.y = 0.0f;
}

void combat_overlay_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 255));
	dice_powerup(5);
	health_bar(4);
	settings_button();
}

void dice_powerup(int rng_num)
{

	// set location of the buttons based on the center of the area where the power up and dice buttons are drawn

	buttons_centerpointX = CP_System_GetWindowWidth() - 180.0f;
	buttons_centerpointY = CP_System_GetWindowHeight() - 100.0f;
	dice_button.position.x = buttons_centerpointX + 80.0f;
	dice_button.position.y = powerup_button.position.y = buttons_centerpointY;	// y position of both power up and dice button are the same
	powerup_button.position.x = buttons_centerpointX - 80.0f;

	// draws the interactable buttons based on the set locations

	CP_Image_Draw(dice_button.image, dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.image, powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y, 255);

	// branch out to decide if player rolls or not
	
	choose_to_roll_dice(rng_num);
	choose_powerup();
}

void choose_to_roll_dice(int num_roll)
{
	if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && !powerup_button.clicked)	//	checks if user clicked the dice button
	{
		dice_button.clicked = !dice_button.clicked;
		d6.clicked = 0;
		d20.clicked = 0;
	}
	if (dice_button.clicked)	// Draws the window pop up for player to choose dice to roll
	{
		init_dicePos();
		inventory_window(2, dice_button.position.x);
		CP_Image_Draw(d6.image, d6.position.x, d6.position.y, d6.size.x * 0.95, d6.size.y * 0.95, 255);
		CP_Image_Draw(d20.image, d20.position.x, d20.position.y, d20.size.x * 0.95, d20.size.y * 0.95, 255);
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("d6", d6.position.x, d6.position.y);
		CP_Font_DrawText("d20", d20.position.x, d20.position.y);

		d6.inButton = mouse_in_rect(d6.position.x, d6.position.y, d6.size.x - 30.0f, d6.size.y - 30.0f);			//	checks if pointer is in the d6 image
		d20.inButton = mouse_in_rect(d20.position.x, d20.position.y, d20.size.x - 30.0f, d20.size.y - 30.0f);		//	checks if pointer is in the d20 image
		for (int i = 0; i < 2; i++)
		{
			float x = d20.position.x - ((float)i * (128.0f));
			if (mouse_in_rect(x, d6.position.y, 80, 80))
			{
				CP_Image_Draw(cursor.image, x, d6.position.y, cursor.size.x, cursor.size.y, 255);
			}
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

void choose_powerup(void)
{
	if (mouse_in_rect(powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y) == 1 && CP_Input_MouseClicked() && !dice_button.clicked)	//	checks if user clicked the dice button
	{
		powerup_button.clicked = !powerup_button.clicked;
	}

	if (powerup_button.clicked)	// Draws the window pop up for player to choose power up
	{
		inventory_window(3, powerup_button.position.x);
		powerup[atk].position.y = powerup[hp].position.y = powerup[extra_d4].position.y = buttons_centerpointY - 150.0f;
		for (int i = 0; i < 3; i++)
		{
			powerup[i].position.x = powerup_button.position.x - ((float)i * (128.0f));
			CP_Image_Draw(powerup[i].image, powerup[i].position.x, powerup[i].position.y, powerup[i].size.x, powerup[i].size.y, 255);
		}
		for (int i = 0; i < 3; i++)
		{
			//float x = powerup_button.position.x - ((float)i * (128.0f));
			if (mouse_in_rect(powerup[i].position.x, powerup[i].position.y, 80.0f, 80.0f))
			{
				CP_Image_Draw(cursor.image, powerup[i].position.x, powerup[i].position.y, cursor.size.x, cursor.size.y, 255);
				CP_Settings_Fill(CP_Color_Create(255,255,255, 255));
				CP_Settings_TextSize(20.0f);
				CP_Font_DrawTextBox(powerup[i].desc, powerup[i].position.x - (128.0*3/4), powerup[i].position.y - 125.0f, 200.0f);
			}
		}
		if (mouse_in_rect(powerup[atk].position.x, powerup[atk].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked())
		{
			powerup[atk].clicked = !powerup[atk].clicked;
			powerup[hp]. clicked = 0;
			powerup[extra_d4].clicked = 0;
			powerup_button.clicked = !powerup_button.clicked;
		}
		else if (mouse_in_rect(powerup[hp].position.x, powerup[hp].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked())
		{
			powerup[atk].clicked = 0;
			powerup[hp].clicked = !powerup[hp].clicked;
			powerup[extra_d4].clicked = 0;
			powerup_button.clicked = !powerup_button.clicked;
		}
		else if (mouse_in_rect(powerup[extra_d4].position.x, powerup[extra_d4].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked())
		{
			powerup[atk].clicked = 0;
			powerup[hp].clicked = 0;
			powerup[extra_d4].clicked = !powerup[extra_d4].clicked;
			powerup_button.clicked = !powerup_button.clicked;
		}
		
	}
	float value = 0;
	for (int i = 0, value = 0; i < 3; i++)
	{
		
		if (powerup[i].clicked == 1)
		{
			value += CP_System_GetDt();
			CP_Image_Draw(powerup[i].image, EaseOutSine(powerup[i].position.x, 40.0f, value), EaseOutSine(powerup[i].position.y, 40.0f, value), powerup[i].size.x, powerup[i].size.y, 255);
		}
	}
}

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
	float position_Y = buttons_centerpointY - 150.0f;
	for (int i = 0; i < num_item; i++)
	{
		float position_X = rightmost_box_positionX - ((float)i * (128.0f));
		CP_Image_Draw(inventory.image, position_X, position_Y, inventory.size.x, inventory.size.y, 255);
	}
}

/*void timer_ui(void)
{
	char display_mins_tens = 
	CP_Font_DrawText(*remaining_time, CP_System_GetWindowWidth() / 2, 50.0f);
}*/


void combat_overlay_exit(void)
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
}