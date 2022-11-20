#include "combat_overlay.h"
#include "../UtilsUI/ui_utils.h"
#include "GameStateManager.h"
#include "second_combat.h"
#include "../../Character/gameChar.h"

float buttons_centerpointX;
float buttons_centerpointY;
asset inventory;
asset dice_button;
asset powerup_button;
asset mov_dice;
asset settings;
asset cursor;
asset powerup[3];
asset desc_panel;
CP_Vector roll_pos;
CP_Vector side_display_pos;
CP_Font font;
float dice_timer;
float powerup_timer;
int selecting_action;
int rng_mov, rng_combat;
int display_side_dice[2];	// subscript 0: movement, 1: combat
int turns;
int combat_clicked;
int individual_mov_roll[2];
int warning_clicked[2];
float powerup_scale;
int powerups[3];

void combat_overlay_init(void)
{
	//	loads images and finds their sizes
	
	get_image_size("dice_button.png", &dice_button);
	get_image_size("inventory_block.png", &inventory);
	get_image_size("powerup_button.png", &powerup_button);
	get_image_size("dice[d6].png", &mov_dice);
	get_image_size("settings.png", &settings);
	get_image_size("cursor.png", &cursor);
	get_image_size("powerup[atk].png", &powerup[atk]);
	get_image_size("powerup[hp].png", &powerup[hp]);
	get_image_size("powerup[movement].png", &powerup[movement]);
	get_image_size("desc_panel.png", &desc_panel);
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");

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

	mov_dice.type = e_std_D6;

	turns = 3;

	for (int d = 1; d <= 3; d++)
	{								//	TODO: replace with number of powerups left accordingly
		powerups[d - 1] = d;
	}

	display_side_dice[0] = display_side_dice[1] = 0;
	
	// initialize description
	powerup[atk].desc = "Increases damage dealt for 3 turns.";
	powerup[hp].desc = "Increases Max HP for 3 turns";
	powerup[movement].desc = "Increase movement by 3.";
	
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);
	
	// set location of the buttons based on the center of the area where the power up and dice buttons are drawn

	buttons_centerpointX = CP_System_GetWindowWidth() - 140.0f;
	buttons_centerpointY = CP_System_GetWindowHeight() - 80.0f;
	dice_button.position.x = buttons_centerpointX + 60.0f;
	dice_button.position.y = powerup_button.position.y = buttons_centerpointY;	// y position of both power up and dice button are the same
	powerup_button.position.x = buttons_centerpointX - 60.0f;
}

void init_rollPos(void)
{
	// set location where the selected dice rolls

	roll_pos.x = buttons_centerpointX - 100.0f;
	roll_pos.y = buttons_centerpointY - 400.0f;

	CP_Settings_TextSize(100.0f);
}

void combat_overlay_update(void)
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	int combat_dice[3] = { 2,3,4 };
	dice_powerup(turns, combat_dice);
	side_display(get_character()->energy, turns);

	settings_button();
}

//void init_dicePos(void)
//{
//	// set location where choosable d6 and d20 die are after player selects the dice button
//
//	d20.position.x = buttons_centerpointX + 80.0f;
//	d6.position.y =  d20.position.y = buttons_centerpointY - 150.0f;
//	d6.position.x = d20.position.x - 125.0f;
//}
//
//void init_rollPos(void)
//{
//	// set location where the selected dice rolls
//
//	roll_pos.x = buttons_centerpointX + 20.0f;
//	roll_pos.y = buttons_centerpointY - 200.0f;
//	d6.position.x = d6.position.y = d20.position.x = d20.position.y = 0.0f;
//	CP_Settings_TextSize(100.0f);
//}

void dice_powerup(int powerup_turns, int combat_dices[])
{
	// draws the interactable buttons based on the set locations

	CP_Image_Draw(dice_button.image, dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.image, powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y, 255);

	side_display(powerup_turns);

	// branch out to decide if player rolls or not
	for (int d = 0; d < 3; d++)
	{
		if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && !powerup_button.clicked && !mov_dice.clicked && !mov_dice.warning && !powerup_button.warning)	//	checks if user clicked the dice button
		{
			selecting_action = !selecting_action;
			dice_timer = 0;
		}
		if (selecting_action == 1)
		{
			for (int i = 0; i < 2; i++)
			{
				float x = dice_button.position.x - 20.0f;
				float y = dice_button.position.y - 125.0f;
				CP_Image_Draw(inventory.image, x, y - (i * inventory.size.y), inventory.size.x * 1.6, inventory.size.y, 255);
				CP_Settings_Fill(CP_Color_Create(255,255,255, 255));
				CP_Settings_TextSize(35.0f);
				CP_Font_DrawText("Movement", x + 2.0f, y - inventory.size.y);
				CP_Font_DrawText("Combat", x + 2.0f, y);
				if (mouse_in_rect(x + 2.0f, y - (i * inventory.size.y), inventory.size.x * 1.6 * 0.5, inventory.size.y * 0.5))
				{
					CP_Settings_TextSize(22.5f);
					CP_Image_Draw(cursor.image, x - 110.0f, y - (i * inventory.size.y), cursor.size.x, cursor.size.y, 255);
					CP_Image_Draw(desc_panel.image, x - 200.0f, y - (i*inventory.size.y), desc_panel.size.x * 1.7, desc_panel.size.y, 255);
					if (i == 0)
					{
						CP_Font_DrawTextBox("Ends movement turn and initiates combat.", dice_button.position.x - 298.0f, y - 22.5f, desc_panel.size.x * 1.6);
					}
					else if (i == 1)
					{
						CP_Font_DrawTextBox("Roll 2 d6 dice to move around on the map.", dice_button.position.x - 298.0f, y - 22.5f - (i*inventory.size.y), desc_panel.size.x * 1.6);
					}
				}
			}
			if (mouse_in_rect(dice_button.position.x - 20.0f, dice_button.position.y - 150.0f - inventory.size.y, inventory.size.x * 1.6, inventory.size.y) && CP_Input_MouseClicked())
			{
				movement_clicked = 1;
				selecting_action = 0;
				mov_dice.position.x = dice_button.position.x - inventory.size.x + 15.0f;
				mov_dice.position.y = dice_button.position.y - (inventory.size.y * 1.90f);
				if (!mov_dice.side_display)
				{
					individual_mov_roll[0] = roll_dice(mov_dice.type);
					individual_mov_roll[1] = roll_dice(mov_dice.type);
				}
			}
			else if (mouse_in_rect(dice_button.position.x - 20.0f, dice_button.position.y - 150.0f, inventory.size.x * 1.6, inventory.size.y) && CP_Input_MouseClicked())
			{
				combat_clicked = !combat_clicked;
				mov_dice.side_display = 0;
				get_character()->energy = 0;
			}
		}
	}
	if (movement_clicked)
	{
		choose_to_roll_movement();
	}
	else if (combat_clicked)
	{
		/*if (within combat range)
		{
			change to second combat game scene
		else
		{
			CP_Image_Draw(desc_panel.image, dice_button.position.x - 20.0f, dice_button.position.y - 150.0f, desc_panel.size.x * 1.7, desc_panel.size.y, 255);
			CP_Settings_TextSize(25.0f);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			dice_timer += CP_System_GetDt();
			if (dice_timer < 2.5f)
			{
				CP_Font_DrawTextBox("Not close enough to the enemy to attack!", dice_button.position.x - 90.0f, dice_button.position.y - 175.0f, 150.0f);
			}
			else
			{
				dice_timer = 0;
			}
		}
		*/
	}
	choose_powerup(powerup_turns, powerups);
}

void choose_to_roll_movement()
{
	get_character()->energy = 0;
	get_character()->energy += individual_mov_roll[0] + individual_mov_roll[1];
	if (mov_dice.side_display && !mov_dice.warning)
	{
		mov_dice.warning = !mov_dice.warning;
	}
	else if (!mov_dice.side_display && !mov_dice.warning)
	{
		inventory.side_display = 1;
		mov_dice.clicked = 1;
	}
	if (mov_dice.warning == 1)
	{
		CP_Image_Draw(desc_panel.image, dice_button.position.x - 20.0f, dice_button.position.y - 150.0f, desc_panel.size.x * 1.7, desc_panel.size.y, 255);
		CP_Settings_TextSize(25.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		dice_timer += CP_System_GetDt();
		if (dice_timer < 2.5f)
		{
			selecting_action = 0;
			CP_Font_DrawTextBox("You cannot roll twice for movement!", dice_button.position.x - 90.0f, dice_button.position.y - 175.0f, 150.0f);
		}
		else
		{
			dice_timer = 0;
			mov_dice.warning = 0;
			movement_clicked = 0;
		}
	}
	if (inventory.side_display)
	{
		CP_Image_Draw(inventory.image, dice_button.position.x - 50.0f, dice_button.position.y - (inventory.size.y * 1.5f), inventory.size.x * 2.0f, inventory.size.y * 2.0f, 255);
	}
	if (mov_dice.clicked)
	{	
		CP_Settings_TextSize(80.0f);
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		dice_timer += CP_System_GetDt();
		if (dice_timer < 1.5f)
		{
			for (int d = 0; d < 2; d++)
			{
				generate_dice(roll_dice(e_std_D6), mov_dice.type, mov_dice.position.x + (d * 100.0f), mov_dice.position.y + (d * 100.0f), 1.0f);
			}
		}
		if (2.5f > dice_timer && dice_timer > 1.5f)
		{
			for (int d = 0; d < 2; d++)
			{
				generate_dice(individual_mov_roll[d], mov_dice.type, mov_dice.position.x + (d * 100.0f), mov_dice.position.y + (d * 100.0f), 1.0f);
			}
			CP_Settings_TextSize(50.0f);
			movement_window(get_character()->energy, mov_dice.position.x + 50.0f, mov_dice.position.y - 100.0f, 0.8);
		}
		if (dice_timer > 2.5f)
		{
			inventory.side_display = 0;
			go_to_animation(side_display_pos.x - 58.0f, side_display_pos.y + 202.5f, &mov_dice.position);
			CP_Settings_TextSize(50.0f);
			movement_window(get_character()->energy, mov_dice.position.x + 50.0f, mov_dice.position.y - 100.0f, 0.8);
		}
		if (dice_timer > 3.5f)
		{
			dice_timer = 0;
			mov_dice.clicked = !mov_dice.clicked;
			mov_dice.side_display = !mov_dice.side_display;
			movement_clicked = 0;
		}
	}
}

void side_display(int turns_left)
{
	// for movement side display
	
	if (mov_dice.side_display == 1)
	{
		CP_Settings_TextSize(50.0f);
		movement_window(get_character()->energy, side_display_pos.x, side_display_pos.y + 100.0f, 0.8f);
		if (get_character()->energy <= 0)
		{
			get_character()->energy = 0;
			CP_Settings_TextSize(40.0f);
			CP_Font_DrawText("No movement left!", side_display_pos.x + 200.0f, side_display_pos.y + 100.0f);
			
			dice_timer += CP_System_GetDt();
			if (dice_timer > 2.0f)
			{
				mov_dice.side_display = 0;
			}
		}
	}
	
	// for combat side_display

}

void choose_powerup(int turns_left, int num_powerups[])
{
	char* turns[1];
	turns[0] = '0' + turns_left;
	if (mouse_in_rect(powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y) == 1 && CP_Input_MouseClicked() && !dice_button.clicked && !powerup_button.warning)	//	checks if user clicked the dice button
	{
		for (int i = 0; i < 3; i++)
		{
			if (powerup[i].side_display == 1 && !powerup_button.warning)
			{
				powerup_button.warning = 1;
			}
			else
			{
				powerup_button.clicked = !powerup_button.clicked;
				powerup[atk].clicked = powerup[hp].clicked = powerup[movement].clicked = 0;
				powerup_timer = 0;
			}
		}
	}

	if (powerup_button.warning == 1)
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
			powerup_button.warning = 0;
		}
	}

	if (powerup_button.clicked)	// Draws the window pop up for player to choose power up
	{
		inventory_window(3, powerup_button.position.x);
		for (int i = 0; i < 3; i++)
		{
			powerup[i].position.x = powerup_button.position.x - 1.0f;
			powerup[i].position.y = powerup_button.position.y - 132.5f - ((float)i * (115.0f));
			CP_Image_Draw(powerup[i].image, powerup[i].position.x, powerup[i].position.y, powerup[i].size.x, powerup[i].size.y, 255);
		}
		for (int i = 0; i < 3; i++)
		{
			*powerup[i].num = '0' + num_powerups[i];
			//float x = powerup_button.position.x - ((float)i * (128.0f));
			CP_Image_Draw(desc_panel.image, powerup[i].position.x - 50.0f, powerup[i].position.y + 50.0f, desc_panel.size.x * 0.4, desc_panel.size.y * 0.4, 255);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize(40.0f);
			CP_Font_DrawText(powerup[i].num, powerup[i].position.x - 50.0f, powerup[i].position.y + 50.0f);
			if (mouse_in_rect(powerup[i].position.x, powerup[i].position.y, 80.0f, 80.0f))
			{
				CP_Image_Draw(cursor.image, powerup[i].position.x - 80.0f, powerup[i].position.y, cursor.size.x, cursor.size.y, 255);
				CP_Image_Draw(desc_panel.image, powerup[i].position.x - 190.0f, powerup[i].position.y, desc_panel.size.x * 1.9, desc_panel.size.y, 255);
				CP_Settings_Fill(CP_Color_Create(255,255,255,255));
				CP_Settings_TextSize(22.5f);
				CP_Font_DrawTextBox(powerup[i].desc, powerup[i].position.x - 274.0f, powerup[i].position.y - 15.0f, 170.0f);
			}
		}
		if (mouse_in_rect(powerup[atk].position.x, powerup[atk].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked() && num_powerups[atk])
		{
			powerup[atk].clicked = !powerup[atk].clicked;
			powerup[hp]. clicked = powerup[movement].clicked = 0;
			powerup_button.clicked = !powerup_button.clicked;
			num_powerups[atk]--;
			powerup_scale = 1.0f;
		}
		else if (mouse_in_rect(powerup[hp].position.x, powerup[hp].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked() && num_powerups[hp])
		{
			powerup[atk].clicked = powerup[movement].clicked = 0;
			powerup[hp].clicked = !powerup[hp].clicked;
			powerup_button.clicked = !powerup_button.clicked;
			num_powerups[hp]--;
			powerup_scale = 1.0f;
		}
		else if (mouse_in_rect(powerup[movement].position.x, powerup[movement].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked() && num_powerups[movement])
		{
			powerup[atk].clicked = powerup[hp].clicked = 0;
			powerup[movement].clicked = !powerup[movement].clicked;
			powerup_button.clicked = !powerup_button.clicked;
			num_powerups[movement]--;
			powerup_scale = 1.0f;
		}
		
	}

	for (int i = 0; i < 3; i++)
	{
		if (powerup[i].clicked == 1)
		{
			powerup_timer += CP_System_GetDt();
			CP_Vector pos = getWorldPos(get_character()->sp->go.position, getMap());
			if (powerup_timer < 0.8f)
			{
				go_to_animation(pos.x + 20.0f, pos.y + 40.0f, &powerup[i].position);		//	TODO: change position to player position
				shrinking_animation(0.5f, &powerup_scale);
				CP_Image_Draw(powerup[i].image, powerup[i].position.x, powerup[i].position.y, powerup[i].size.x * powerup_scale, powerup[i].size.y * powerup_scale, 255);
			}
			else if (powerup_timer > 0.8f && powerup_timer < 1.5f)
			{
				CP_Settings_TextSize(30.0f);
				CP_Font_DrawText("Power up!", pos.x + 40.0f, pos.y);
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
			CP_Image_Draw(desc_panel.image, side_display_pos.x, side_display_pos.y + 250.0f, 30.0f, 30.0f, 255);
			CP_Image_Draw(powerup[i].image, side_display_pos.x, side_display_pos.y + 200.0f, powerup[i].size.x * 0.8f, powerup[i].size.y * 0.8f, 255);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Font_DrawText(turns, side_display_pos.x + 2.0f, side_display_pos.y + 250.0f);
		}
		else if (turns_left <= 0)
		{
			powerup[i].side_display = 0;
		}
	}
}

// void generate_dice(int num_roll, dice_types dice, float dice_posX, float dice_posY, float scale) // draws dice (d6 or d20) with number corresponding to value num_roll
// {
// 	float text_posX = dice_posX + 2.0f * scale;
// 	float text_posY = dice_posY;
// 	char num_ones = '0' + num_roll;
// 	char num_tens;
// 	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
// 	CP_Font_Set(font);
// 	if (dice == e_std_D6)
// 	{
// 		CP_Image_Draw(d6.image, dice_posX, dice_posY, d6.size.x * scale, d6.size.y * scale, 255);
// 		CP_Font_DrawText(&num_ones, text_posX, text_posY);
// 	}
// 	else if (dice == e_std_D20)
// 	{
// 		CP_Image_Draw(d20.image, dice_posX, dice_posY, d20.size.x * scale, d20.size.y * scale, 255);
// 		if (num_roll / 10 != 0)
// 		{
// 			num_ones = '0' + (num_roll % 10);
// 			num_tens = '0' + (num_roll / 10);
// 			CP_Font_DrawText(&num_ones, text_posX + 25, text_posY);
// 			CP_Font_DrawText(&num_tens, text_posX - 25, text_posY);
// 		}
// 		else
// 		{
// 			CP_Font_DrawText(&num_ones, text_posX, text_posY);
// 		}
// 	}
// }

// void health_bar(int remaining_hp)	//	draws hp bar (max is currently 5)
// {	
// 	float positionX;
// 	float positionY = 50.0f;
// 	for (int j = 5; j > remaining_hp; j--)
// 	{
// 		positionX = 50.0f + ((float)(j-1) * 80.0f);
// 		CP_Image_Draw(dead_hp.image, positionX, positionY, dead_hp.size.x, dead_hp.size.y, 255);
// 	}
// 	for (int i = 0; i < remaining_hp; i++)
// 	{
// 		positionX = 50.0f + ((float)i * 80.0f);
// 		CP_Image_Draw(alive_hp.image, positionX, positionY, alive_hp.size.x, alive_hp.size.y, 255);
// 	}
// }

void settings_button(void)		//	draws settings icon
{
	settings.position.x = CP_System_GetWindowWidth() - 50.0f;
	settings.position.y = 50.0f;
	CP_Image_Draw(settings.image, settings.position.x, settings.position.y, settings.size.x, settings.size.y, 255);
	if ((mouse_in_rect(settings.position.x, settings.position.y, settings.size.x, settings.size.y) == 1) && CP_Input_MouseClicked())
	{
		GameStateSetNextSubScene(SETTINGS_SCENE, true);
	}
}

void movement_window(int movement, float x, float y, float scale)
{
	char total[3] = { '0' + (movement / 10), '0' + (movement % 10), '\0'};
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Image_Draw(desc_panel.image, x, y, desc_panel.size.x * scale, desc_panel.size.y * scale, 255);
	CP_Font_DrawText(total, x, y);
}

/*void timer_ui(void)
{
	clock_t difference = clock() - start_time;
	clock_t remaining_time = 600 - difference;
	char minutes[50];
	sprintf(minutes, "%d", remaining_time / 60);
	char seconds[50];
	sprintf(seconds, "%d", remaining_time % 60);
	strcat(minutes, seconds);
	CP_Font_DrawText(minutes, CP_System_GetWindowWidth() / 2, 20.0f);
}*/


void combat_overlay_exit(void)
{
	CP_Image_Free(&mov_dice.image);
	CP_Image_Free(&inventory.image);
	CP_Image_Free(&dice_button.image);
	CP_Image_Free(&powerup_button.image);
	CP_Image_Free(&settings.image);
	CP_Image_Free(&inventory.image);
	CP_Image_Free(&cursor.image);
	CP_Image_Free(&powerup[atk].image);
	CP_Image_Free(&powerup[hp].image);
	CP_Image_Free(&powerup[movement].image);
	CP_Image_Free(&desc_panel.image);
}