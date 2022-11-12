#include "combat_overlay.h"
#include "../UtilsUI/ui_utils.h"

float buttons_centerpointX;
float buttons_centerpointY;
asset dead_hp;
asset inventory;
asset dice_button;
asset powerup_button;
asset dice[3];
asset settings;
asset cursor;
asset alive_hp;
asset dead_hp;
asset powerup[3];
asset desc_panel;
CP_Vector roll_pos;
CP_Vector side_display_pos;
CP_Font font;
float dice_timer;
float powerup_timer;
int num_roll;
int display_side_dice;
int turns;
int warning_clicked[2];		// subscript 0: dice_button, subscript 1: powerup_button

void combat_overlay_init(void)
{
	//	loads images and finds their sizes
	
	get_image_size("dice_button.png", &dice_button);
	get_image_size("inventory_block.png", &inventory);
	get_image_size("powerup_button.png", &powerup_button);
	get_image_size("dice[d6].png", &dice[d6]);
	get_image_size("dice[d20].png", &dice[d20]);
	get_image_size("settings.png", &settings);
	get_image_size("cursor.png", &cursor);
	get_image_size("alive_hp.png", &alive_hp);
	get_image_size("dead_hp.png", &dead_hp);
	get_image_size("powerup[atk].png", &powerup[atk]);
	get_image_size("powerup[hp].png", &powerup[hp]);
	get_image_size("powerup[extra_d4].png", &powerup[extra_d4]);
	get_image_size("desc_panel.png", &desc_panel);
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");

	// init inbutton values to 0
	dice[d6].inButton = 0;
	dice[d20].inButton = 0;

	//	when image is drawn, it will place center of image at the specified location. when text is drawn, center of text will be placed at the location
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_Set(font);

	// set timer and dice timer
	dice_timer = 0;
	powerup_timer = 0;

	//	set the side displays location
	side_display_pos.x = 60.0f;
	side_display_pos.y = 60.0f;

	// dice randomiser initialise
	init_dice();

	dice[d6].type = e_std_D6;
	dice[d20].type = e_std_D20;

	num_roll = 5;
	turns = 3;

	display_side_dice = 0;
	// initialize description
	powerup[atk].desc = "Increases damage dealt for 3 turns.";
	powerup[hp].desc = "Increases Max HP for 3 turns";
	powerup[extra_d4].desc = "Additional d4 Dice is given. Can be used for 3 turns.";
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);
}

void init_dicePos(void)
{
	// set location where choosable dice[d6] and dice[d20] die are after player selects the dice button

	dice[d20].position.x = buttons_centerpointX + 80.0f;
	dice[d6].position.y =  dice[d20].position.y = buttons_centerpointY - 150.0f;
	dice[d6].position.x = dice[d20].position.x - 125.0f;
}

void init_rollPos(void)
{
	// set location where the selected dice rolls

	roll_pos.x = buttons_centerpointX + 20.0f;
	roll_pos.y = buttons_centerpointY - 200.0f;
	dice[d6].position.x = dice[d6].position.y = dice[d20].position.x = dice[d20].position.y = 0.0f;
	CP_Settings_TextSize(100.0f);
}

void combat_overlay_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	dice_powerup(num_roll, turns);
	if (CP_Input_KeyDown(KEY_D))
	{
		num_roll--;
	}
	if (CP_Input_KeyDown(KEY_S))
	{
		num_roll++;
	}
	if (CP_Input_KeyDown(KEY_A))
	{
		turns--;
	}
	if (CP_Input_KeyDown(KEY_W))
	{
		turns++;
	}

	health_bar(3);
	settings_button();
}

void dice_powerup(int rng_num, int powerup_turns)
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
	choose_powerup(powerup_turns);
}

void choose_to_roll_dice(int num_roll)
{
	for (int d = 0; d < 3; d++)
	{
		if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && !powerup_button.clicked && !dice[d].clicked && !dice[d].side_display)	//	checks if user clicked the dice button
		{
			dice_button.clicked = !dice_button.clicked;
			dice[d].clicked = 0;
			dice[d].side_display = 0;
		}
		if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && dice[d].side_display && !warning_clicked[0])
		{
			warning_clicked[0] = !warning_clicked[0];
		}
		
	}
	if (warning_clicked[0] == 1)
	{
		CP_Image_Draw(desc_panel.image, dice_button.position.x, dice_button.position.y - 150.0f, desc_panel.size.x * 1.7, desc_panel.size.y, 255);
		CP_Settings_TextSize(25.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		dice_timer += CP_System_GetDt();
		if (dice_timer < 2.5f)
		{

			CP_Font_DrawTextBox("You cannot roll twice for movement!", dice_button.position.x - 70.0f, dice_button.position.y - 175.0f, 150.0f);
		}
		else
		{
			dice_timer = 0;
			warning_clicked[0] = 0;
		}
	}
	if (dice_button.clicked)	// Draws the window pop up for player to choose dice to roll
	{
		init_dicePos();
		inventory_window(3, dice_button.position.x);
		CP_Image_Draw(dice[d6].image, dice[d6].position.x, dice[d6].position.y, dice[d6].size.x * 0.95, dice[d6].size.y * 0.95, 255);
		CP_Image_Draw(dice[d20].image, dice[d20].position.x, dice[d20].position.y, dice[d20].size.x * 0.95, dice[d20].size.y * 0.95, 255);
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("d6", dice[d6].position.x, dice[d6].position.y);
		CP_Font_DrawText("d20", dice[d20].position.x, dice[d20].position.y);

		dice[d6].inButton = mouse_in_rect(dice[d6].position.x, dice[d6].position.y, dice[d6].size.x - 30.0f, dice[d6].size.y - 30.0f);			//	checks if pointer is in the dice[d6] image
		dice[d20].inButton = mouse_in_rect(dice[d20].position.x, dice[d20].position.y, dice[d20].size.x - 30.0f, dice[d20].size.y - 30.0f);		//	checks if pointer is in the dice[d20] image
		for (int i = 0; i < 2; i++)
		{
			float x = dice[d20].position.x - ((float)i * (128.0f));
			if (mouse_in_rect(x, dice[d6].position.y, 80, 80))
			{
				CP_Image_Draw(cursor.image, x, dice[d6].position.y, cursor.size.x, cursor.size.y, 255);
			}
		}
		if ((dice[d6].inButton == 1) && CP_Input_MouseClicked() && !dice[d20].clicked)	//	checks if user selected to roll dice[d6] dice
		{
			dice_button.clicked = 0;
			dice[d6].clicked = !dice[d6].clicked;
			dice[d20].clicked = 0;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
		}
		else if ((dice[d20].inButton == 1) && CP_Input_MouseClicked() && !dice[d6].clicked)	//	checks if user selected dice[d20] dice
		{
			dice_button.clicked = 0;
			dice[d6].clicked = 0;
			dice[d20].clicked = !dice[d20].clicked;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
		}
	}
	if (inventory.side_display)
	{
		CP_Image_Draw(inventory.image, roll_pos.x, roll_pos.y, inventory.size.x * 2.0f, inventory.size.y * 2.0f, 255);
	}
	for (int d = 0; d < 3; d++)
	{
		if (dice[d].clicked)
		{	
			CP_Settings_TextSize(100.0f);
			dice_timer += CP_System_GetDt();
			if (dice_timer < 2.0f)
			{
				generate_dice(roll_dice(dice[d].type), dice[d], roll_pos.x, roll_pos.y, 1.4f);
			}
			if (3.0f > dice_timer && dice_timer > 2.0f)
			{
				generate_dice(num_roll, dice[d], roll_pos.x, roll_pos.y, 1.4f);
			}
			if (dice_timer > 3.0f)
			{
				inventory.side_display = 0;
				go_to_animation(50.0f, 150.0f, &roll_pos);
				generate_dice(num_roll, dice[d], roll_pos.x, roll_pos.y, 1.4f);
			}
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				dice[d].clicked = !dice[d].clicked;
				dice[d].side_display = !dice[d].side_display;
			}
		}
		
	}
	for (int d = 0; d < 3; d++)
	{
		float x;
		float y;
		if (dice[d].side_display == 1)
		{
			CP_Settings_TextSize(50.0f);
			generate_dice(num_roll, dice[d], side_display_pos.x, side_display_pos.y + 110.0f, 0.8f);
			if (num_roll <= 0)
			{
				CP_Settings_TextSize(30.0f);
				CP_Font_DrawText("No movement left!", side_display_pos.x + 165.0f, side_display_pos.y + 110.0f);
				CP_Settings_TextSize(50.0f);
				generate_dice(0, dice[d], side_display_pos.x, side_display_pos.y + 110.0f, 0.8f);
				dice_timer += CP_System_GetDt();
				if (dice_timer > 2.0f)
				{
					dice[d].side_display = 0;
				}
			}
		}
	}
}

void choose_powerup(int turns_left)
{
	char* turns[1];
	turns[0] = '0' + turns_left;
	if (mouse_in_rect(powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y) == 1 && CP_Input_MouseClicked() && !dice_button.clicked)	//	checks if user clicked the dice button
	{
		for (int i = 0; i < 3; i++)
		{
			if (powerup[i].side_display == 1 && !warning_clicked[1])
			{
				warning_clicked[1] = !warning_clicked[1];
			}
			else
			{
				powerup_button.clicked = !powerup_button.clicked;
				powerup[atk].clicked = powerup[hp].clicked = powerup[extra_d4].clicked = 0;
				powerup_timer = 0;
			}
		}
	}

	if (warning_clicked[1] == 1)
	{
		CP_Image_Draw(desc_panel.image, powerup_button.position.x, powerup_button.position.y - 130.0f, desc_panel.size.x * 1.7, desc_panel.size.y, 255);
		CP_Settings_TextSize(25.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		powerup_timer += CP_System_GetDt();
		if (powerup_timer < 2.5f)
		{
			CP_Font_DrawTextBox("You can only use one power up at a time!", powerup_button.position.x - 75.0f, powerup_button.position.y - 155.0f, 160.0f);
		}
		else
		{
			powerup_timer = 0;
			warning_clicked[1] = 0;
		}
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

	for (int i = 0; i < 3; i++)
	{
		if (powerup[i].clicked == 1)
		{
			if (powerup_timer < 1.5f)
			{
				go_to_animation(60.0f, 200.0f, &powerup[i].position);
				CP_Image_Draw(powerup[i].image, powerup[i].position.x, powerup[i].position.y, powerup[i].size.x, powerup[i].size.y, 255);
				powerup_timer += CP_System_GetDt();
			}
			else if (powerup_timer > 1.5f)
			{
				powerup[i].side_display = 1;
				powerup_timer = 0;
				powerup[i].clicked = 0;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{	
		if (powerup[i].side_display == 1 && turns_left > 0)
		{
			CP_Settings_TextSize(30.0f);
			if (num_roll > 0)
			{
				CP_Image_Draw(desc_panel.image, side_display_pos.x, side_display_pos.y + 250.0f, 30.0f, 30.0f, 255);
				CP_Image_Draw(powerup[i].image, side_display_pos.x, side_display_pos.y + 200.0f, powerup[i].size.x * 0.8f, powerup[i].size.y * 0.8f, 255);
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				CP_Font_DrawText(turns, side_display_pos.x + 2.0f, side_display_pos.y + 250.0f);
			}
			else if (num_roll <= 0 && dice_timer > 2.0f)
			{
				CP_Image_Draw(desc_panel.image, side_display_pos.x, side_display_pos.y + 160.0f, 30.0f, 30.0f, 255);
				CP_Image_Draw(powerup[i].image, side_display_pos.x, side_display_pos.y + 110.0f, powerup[i].size.x * 0.8f, powerup[i].size.y * 0.8f, 255);
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				CP_Font_DrawText(turns, side_display_pos.x + 2.0f, side_display_pos.y + 160.0f);
			}
		}
		else if (turns_left <= 0)
		{
			powerup[i].side_display = 0;
		}
	}
}

void generate_dice(int num_roll, asset dice, float dice_posX, float dice_posY, float scale) // draws dice (dice[d6] or d20) with number corresponding to value num_roll
{
	float text_posX = dice_posX + 2.0f * scale;
	float text_posY = dice_posY;
	char num_ones = '0' + num_roll;
	char num_tens;
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Font_Set(font);
	if (dice.type == e_std_D6)
	{
		CP_Image_Draw(dice.image, dice_posX, dice_posY, dice.size.x * scale, dice.size.y * scale, 255);
		CP_Font_DrawText(&num_ones, text_posX, text_posY);
	}
	else if (dice.type == e_std_D20)
	{
		CP_Image_Draw(dice.image, dice_posX, dice_posY, dice.size.x * scale, dice.size.y * scale, 255);
		if (num_roll / 10 != 0)
		{
			num_ones = '0' + (num_roll % 10);
			num_tens = '0' + (num_roll / 10);
			CP_Font_DrawText(&num_ones, text_posX + 25, text_posY);
			CP_Font_DrawText(&num_tens, text_posX - 25, text_posY);
		}
		else
		{
			CP_Font_DrawText(&num_ones, text_posX, text_posY);
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
	CP_Image_Free(dice[d6].image);
	CP_Image_Free(dice[d20].image);
	CP_Image_Free(inventory.image);
	CP_Image_Free(dice_button.image);
	CP_Image_Free(powerup_button.image);
	CP_Image_Free(settings.image);
	CP_Image_Free(inventory.image);
	CP_Image_Free(cursor.image);
	CP_Image_Free(alive_hp.image);
	CP_Image_Free(dead_hp.image);
	CP_Image_Free(powerup[atk].image);
	CP_Image_Free(powerup[hp].image);
	CP_Image_Free(powerup[extra_d4].image);
	CP_Image_Free(desc_panel.image);
}