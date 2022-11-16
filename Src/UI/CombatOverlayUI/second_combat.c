#include "combat_overlay.h"
#include "../UtilsUI/ui_utils.h"
#include "second_combat.h"
#include "../../GameStateManager.h"

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
asset powerup[3];
asset desc_panel;
asset sword;
asset shield;
CP_Vector roll_pos;
CP_Vector side_display_pos;
CP_Font font;
float dice_timer;
float powerup_timer;
int num_roll;
int display_side_dice;
int turns;
int warning_clicked[2];		// subscript 0: dice_button, subscript 1: powerup_button
int individual_roll;
int attacking;
float dice_scale;
int combat_dice[3];
int count_rolls;
int powerups[3];

void second_init(void)
{
	//	loads images and finds their sizes

	get_image_size("dice_button.png", &dice_button);
	get_image_size("inventory_block.png", &inventory);
	get_image_size("powerup_button.png", &powerup_button);
	get_image_size("dice[d4].png", &dice[d4]);
	get_image_size("dice[d6].png", &dice[d6]);
	get_image_size("dice[d20].png", &dice[d20]);
	get_image_size("settings.png", &settings);
	get_image_size("cursor.png", &cursor);
	get_image_size("alive_hp.png", &alive_hp);
	get_image_size("powerup[atk].png", &powerup[atk]);
	get_image_size("powerup[hp].png", &powerup[hp]);
	get_image_size("powerup[movement].png", &powerup[movement]);
	get_image_size("desc_panel.png", &desc_panel);
	get_image_size("sword.png", &sword);
	get_image_size("shield.png", &shield);
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");

	// init inbutton values to 0
	dice[d4].inButton = 0;
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

	dice[d4].type = e_std_D4;
	dice[d6].type = e_std_D6;
	dice[d20].type = e_std_D20;

	num_roll = 0;
	turns = 3;
	attacking = 0;
	count_rolls = 0;
	display_side_dice = 0;

	// initialize description
	powerup[atk].desc = "Increases damage dealt for 3 turns.";
	powerup[hp].desc = "Increases Max HP for 3 turns";
	powerup[movement].desc = "Increase movement by 3.";

	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);

	for (int d = 1; d <= 3; d++)
	{
		combat_dice[d-1] = d;		//	TODO: replace with number of dice left accordingly
		powerups[d-1] = d;
	}

	// set location of the buttons based on the center of the area where the power up and dice buttons are drawn

	buttons_centerpointX = CP_System_GetWindowWidth() - 140.0f;
	buttons_centerpointY = CP_System_GetWindowHeight() - 80.0f;
	dice_button.position.x = buttons_centerpointX + 60.0f;
	dice_button.position.y = powerup_button.position.y = sword.position.y = shield.position.y = buttons_centerpointY;	// y position of both power up and dice button are the same
	powerup_button.position.x = buttons_centerpointX - 60.0f;
	sword.position.x = shield.position.x = CP_System_GetWindowWidth()/2;
}

void second_init_dicePos(void)
{
	// set location where choosable dice[d6] and dice[d20] die are after player selects the dice button
	for (int d = 0; d < 3; d++)
	{
		dice[d].position.x = dice_button.position.x;
		dice[d].position.y = dice_button.position.y - 130.0f - (115.0f * d);
	}
}

void second_init_rollPos(void)
{
	// set location where the selected dice rolls

	roll_pos.x = buttons_centerpointX + 20.0f;
	roll_pos.y = buttons_centerpointY - 200.0f;
	dice[d6].position.x = dice[d6].position.y = dice[d20].position.x = dice[d20].position.y = 0.0f;
	dice_scale = 1.6f;
	CP_Settings_TextSize(100.0f);
}

void second_update(void)
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	int enemy = 25;													// TODO: replace with enemy's total damage
	second_dice_powerup(&num_roll, combat_dice, turns);
	bottom_display(num_roll, enemy);
	if (CP_Input_KeyDown(KEY_A))
	{
		turns--;
	}
	if (CP_Input_KeyDown(KEY_W))
	{
		turns++;
	}

	health_bar(80);					//	TODO: replace with remaining hp
	settings_button();
}

void second_dice_powerup(int *rng_num, int num_dice[], int powerup_turns)
{
	// draws the interactable buttons based on the set locations

	CP_Image_Draw(dice_button.image, dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.image, powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y, 255);

	// branch out to decide if player rolls or not

	second_choose_to_roll_dice(rng_num, num_dice);
	choose_powerup(powerup_turns, powerups);
}

void second_choose_to_roll_dice(int *num_roll, int num_dice[])
{
	for (int d = 0; d < 3; d++)
	{
		*dice[d].num = '0' + num_dice[d];
		if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && !powerup_button.clicked && !dice[d].clicked && count_rolls < 3)	//	checks if user clicked the dice button
		{
			dice_button.clicked = !dice_button.clicked;
			dice[d].clicked = 0;
			dice[d].side_display = 0;
		}
		if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && count_rolls > 2 && !warning_clicked[0])
		{
			warning_clicked[0] = !warning_clicked[0];
		}
	}
	if (warning_clicked[0] == 1)
	{
		CP_Image_Draw(desc_panel.image, dice_button.position.x - 20.0f, dice_button.position.y - 150.0f, desc_panel.size.x * 1.7, desc_panel.size.y, 255);
		CP_Settings_TextSize(25.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		dice_timer += CP_System_GetDt();
		if (dice_timer < 2.5f)
		{

			CP_Font_DrawTextBox("You cannot roll more than thrice!", dice_button.position.x - 90.0f, dice_button.position.y - 175.0f, 150.0f);
		}
		else
		{
			dice_timer = 0;
			warning_clicked[0] = 0;
		}
	}
	if (dice_button.clicked)	// Draws the window pop up for player to choose dice to roll
	{
		second_init_dicePos();
		inventory_window(3, dice_button.position.x);
		for (int d = 0; d < 3; d++)
		{
			CP_Image_Draw(dice[d].image, dice[d].position.x, dice[d].position.y, dice[d].size.x * 0.95, dice[d].size.y * 0.95, 255);
			dice[d].inButton = mouse_in_rect(dice[d].position.x, dice[d].position.y, dice[d].size.x - 30.0f, dice[d].size.y - 30.0f);
			CP_Image_Draw(desc_panel.image, dice[d].position.x - 50.0f, dice[d].position.y + 50.0f, desc_panel.size.x * 0.4, desc_panel.size.y * 0.4, 255);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize(40.0f);
			CP_Font_DrawText(dice[d].num, dice[d].position.x - 50.0f, dice[d].position.y + 50.0f);
			if (dice[d].inButton)
			{
				CP_Image_Draw(cursor.image, dice[d].position.x - 80.0f, dice[d].position.y, cursor.size.x, cursor.size.y, 255);
			}
		}
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(45.0f);
		CP_Font_DrawText("d4", dice[d4].position.x, dice[d4].position.y + 12.5f);
		CP_Font_DrawText("d6", dice[d6].position.x, dice[d6].position.y);
		CP_Font_DrawText("d20", dice[d20].position.x, dice[d20].position.y);

		if ((dice[d4].inButton == 1) && CP_Input_MouseClicked() && !dice[d6].clicked && !dice[d20].clicked && num_dice[d4])			//	checks if user selected to roll dice[d4] dice
		{
			dice_button.clicked = dice[d6].clicked = dice[d20].clicked = 0;
			dice[d4].clicked = !dice[d4].clicked;
			second_init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			individual_roll = roll_dice(dice[d4].type);
			num_dice[d4]--;
			count_rolls++;
		}
		else if ((dice[d6].inButton == 1) && CP_Input_MouseClicked() && !dice[d20].clicked && !dice[d4].clicked && num_dice[d6])	//	checks if user selected to roll dice[d6] dice
		{
			dice_button.clicked = dice[d4].clicked = dice[d20].clicked = 0;
			dice[d6].clicked = !dice[d6].clicked;
			second_init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			individual_roll = roll_dice(dice[d6].type);
			num_dice[d6]--;
			count_rolls++;
		}
		else if ((dice[d20].inButton == 1) && CP_Input_MouseClicked() && !dice[d6].clicked && !dice[d4].clicked && num_dice[d20])	//	checks if user selected dice[d20] dice
		{
			dice_button.clicked = dice[d6].clicked = dice[d4].clicked = 0;
			dice[d20].clicked = !dice[d20].clicked;
			second_init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			individual_roll = roll_dice(dice[d20].type);
			num_dice[d20]--;
			count_rolls++;
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
			CP_Settings_TextSize(62.5f*dice_scale);
			dice_timer += CP_System_GetDt();
			if (dice_timer < 2.0f)
			{
				generate_dice(roll_dice(dice[d].type), dice[d], roll_pos.x, roll_pos.y, dice_scale);
			}
			if (3.0f > dice_timer && dice_timer > 2.0f)
			{
				generate_dice(individual_roll, dice[d], roll_pos.x, roll_pos.y, dice_scale);
			}
			if (dice_timer > 3.0f)
			{
				inventory.side_display = 0;
				go_to_animation(((CP_System_GetWindowWidth()/2) - 200.0f), buttons_centerpointY, &roll_pos);
				shrinking_animation(0.8f, &dice_scale);
				generate_dice(individual_roll, dice[d], roll_pos.x, roll_pos.y, dice_scale);
			}
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				dice[d].clicked = !dice[d].clicked;
				*num_roll += individual_roll;
			}
		}
	}
}

void bottom_display(int player_roll, int enemy_roll)
{
	char player[2] = { '0' + (player_roll / 10), '0' + (player_roll % 10) };
	char enemy[2] = { '0' + (enemy_roll / 10), '0' + (enemy_roll % 10) };
	CP_Settings_TextSize(65.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (attacking)
	{
		CP_Image_Draw(sword.image, sword.position.x - 200.0f, sword.position.y, sword.size.x, sword.size.y, 255);
		CP_Font_DrawText(player, sword.position.x - 160.0f, sword.position.y - 2.5f);
		CP_Image_Draw(shield.image, shield.position.x + 200.0f, shield.position.y, shield.size.x, shield.size.y, 255);
		CP_Font_DrawText(enemy, shield.position.x + 240.0f, sword.position.y - 2.5f);
	}
	else
	{
		CP_Image_Draw(shield.image, shield.position.x - 200.0f, shield.position.y, shield.size.x, shield.size.y, 255);
		CP_Font_DrawText(player, shield.position.x - 160.0f, shield.position.y - 2.5f);
		CP_Image_Draw(sword.image, sword.position.x + 200.0f, sword.position.y, sword.size.x, sword.size.y, 255);
		CP_Font_DrawText(enemy, sword.position.x + 240.0f, sword.position.y - 2.5f);
	}
	/*if (attacking && (*player_roll - *enemy_roll) > 0 && count_rolls > 2)
	{
		dice_timer += CP_System_GetDt();
		if (dice_timer < 2.0f)
		{
			CP_Image_Draw(sword.image, CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, sword.size.x * 0.8, sword.size.y * 0.8, 255);
			char damage[3] = { '-', '0' + ((*player_roll - *enemy_roll) / 10), '0' + ((*player_roll - *enemy_roll) % 10) };
			CP_Font_DrawText(damage, CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2);
		}
		else
		{
			*player_roll = 0;
			*enemy_roll = 0;
		}
	}*/
}

void generate_dice(int num_roll, asset dice, float dice_posX, float dice_posY, float scale) // draws dice (dice[d6] or d20) with number corresponding to value num_roll
{
	float text_posX = dice_posX + 2.0f * scale;
	float text_posY = dice_posY;
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Image_Draw(dice.image, dice_posX, dice_posY, dice.size.x * scale, dice.size.y * scale, 255);
	switch (dice.type)
	{
		case e_std_D4:
		{
			char num_text[1] = { '0' + num_roll };
			CP_Font_DrawText(num_text, text_posX + (2.0f * scale), text_posY + 12.5f);
			break;
		}
		case e_std_D6:
		{
			char num_text[1] = { '0' + num_roll };
			CP_Font_DrawText(num_text, text_posX, text_posY);
			break;
		}
		case e_std_D20:
		{
			if (num_roll >= 10)
			{
				char num_text[2] = { '0' + (num_roll / 10), '0' + (num_roll % 10) };
				CP_Font_DrawText(num_text, text_posX, text_posY);
			}
			else
			{
				char num_text[1] = { '0' + num_roll };
				CP_Font_DrawText(num_text, text_posX, text_posY);
			}
			break;
		}
		default:
		{
			CP_Image_Draw(dice.image, dice_posX, dice_posY, dice.size.x * scale, dice.size.y * scale, 255);
			char num_text[1] = { '0' + num_roll };
			CP_Font_DrawText(num_text, text_posX, text_posY);
			break;
		}
	}
}

void health_bar(int remaining_hp)	//	draws hp bar (max is currently 5)
{
	float positionX = 50.0f;
	float positionY = 50.0f;
	float width = CP_System_GetWindowWidth() * 0.30f;
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRect(positionX, positionY - 20.0f, width, 50.0f);
	CP_Settings_Fill(CP_Color_Create(200, 50, 50, 255));
	CP_Graphics_DrawRect(positionX, positionY - 20.0f, ((float)remaining_hp / 100) * width, 50.0f);
	CP_Image_Draw(alive_hp.image, positionX, positionY, alive_hp.size.x, alive_hp.size.y, 255);
}

void inventory_window(int num_item, float position_X)
{
	for (int i = 0; i < num_item; i++)
	{
		float position_Y = buttons_centerpointY - 130.0f - ((float)i * (115.0f));
		CP_Image_Draw(inventory.image, position_X, position_Y, inventory.size.x, inventory.size.y, 255);
	}
}


void second_exit(void)
{
	CP_Image_Free(&dice[d4].image);
	CP_Image_Free(&dice[d6].image);
	CP_Image_Free(&dice[d20].image);
	CP_Image_Free(&inventory.image);
	CP_Image_Free(&dice_button.image);
	CP_Image_Free(&powerup_button.image);
	CP_Image_Free(&settings.image);
	CP_Image_Free(&inventory.image);
	CP_Image_Free(&cursor.image);
	CP_Image_Free(&alive_hp.image);
	CP_Image_Free(&powerup[atk].image);
	CP_Image_Free(&powerup[hp].image);
	CP_Image_Free(&powerup[movement].image);
	CP_Image_Free(&desc_panel.image);
	CP_Image_Free(&sword.image);
	CP_Image_Free(&shield.image);
}

/*
void choose_to_roll_combat(int* combat_num, int num_dice[])
{
	for (int w = 0; w < 3; w++)
	{
		if (!combat_dice[w].warning) // TODO: add if statement for whether the player is close enough to the enemy
		{
			combat_dice[w].warning = !combat_dice[w].warning;
		}
		else
		{
			dice_button.clicked = 1;
		}
		if (combat_dice[w].warning == 1)
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
				combat_dice[w].warning = 0;
			}
		}
	}
	if (dice_button.clicked)	// Draws the window pop up for player to choose dice to roll
	{
		init_dicePos();
		CP_Image_Draw(cursor.image, dice_button.position.x - 130.0f, dice_button.position.y - 125.0f, cursor.size.x, cursor.size.y, 255);
		inventory_window(3, dice_button.position.x);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		for (int d = 0; d < 3; d++)
		{
			combat_dice[d].used
			char diceUsed_outofMax[3] = { '0' + combat_dice[d].used, '/', '0' }
			CP_Image_Draw(combat_dice[d].image, combat_dice[d].position.x, combat_dice[d].position.y, combat_dice[d].size.x * 0.95, combat_dice[d].size.y * 0.95, 255);
			CP_Image_Draw(desc_panel.image, combat_dice[d].position.x, combat_dice[d].position.y, desc_panel.size.x * 0.5, desc_panel.size.y * 0.5, 255);
			CP_Font_DrawText('0' + num_dice[d], combat_dice[d].position.x, combat_dice[d].position.y);
			combat_dice[d].inButton = mouse_in_rect(combat_dice[d].position.x, combat_dice[d].position.y, combat_dice[d].size.x - 30.0f, combat_dice[d].size.y - 30.0f);
			if (combat_dice[d].inButton)
			{
				CP_Image_Draw(cursor.image, combat_dice[d].position.x - 80.0f, combat_dice[d].position.y, cursor.size.x, cursor.size.y, 255);
			}
		}
		CP_Settings_Fill(CP_Color_Create(100, 255, 100, 255));
		CP_Settings_TextSize(45.0f);
		CP_Font_DrawText("d4", combat_dice[d4].position.x, combat_dice[d4].position.y + 12.5f);
		CP_Font_DrawText("d6", combat_dice[d6].position.x, combat_dice[d6].position.y);
		CP_Font_DrawText("d20", combat_dice[d20].position.x, combat_dice[d20].position.y);

		if ((combat_dice[d4].inButton == 1) && CP_Input_MouseClicked() && !combat_dice[d6].clicked && !combat_dice[d20].clicked)			//	checks if user selected to roll combat_dice[d4] dice
		{
			dice_button.clicked = combat_dice[d6].clicked = combat_dice[d20].clicked = 0;
			combat_dice[d4].clicked = !combat_dice[d4].clicked;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*combat_num = roll_dice(dice[d4].type);
		}
		else if ((combat_dice[d6].inButton == 1) && CP_Input_MouseClicked() && !combat_dice[d20].clicked && !combat_dice[d4].clicked)	//	checks if user selected to roll combat_dice[d6] dice
		{
			dice_button.clicked = combat_dice[d4].clicked = combat_dice[d20].clicked = 0;
			combat_dice[d6].clicked = !combat_dice[d6].clicked;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*combat_num = roll_dice(combat_dice[d6].type);
		}
		else if ((combat_dice[d20].inButton == 1) && CP_Input_MouseClicked() && !combat_dice[d6].clicked && !combat_dice[d4].clicked)	//	checks if user selected dice[d20] dice
		{
			dice_button.clicked = combat_dice[d6].clicked = combat_dice[d4].clicked = 0;
			combat_dice[d20].clicked = !combat_dice[d20].clicked;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*combat_num = roll_dice(combat_dice[d20].type);
		}
	}
	if (inventory.side_display)
	{
		CP_Image_Draw(inventory.image, roll_pos.x, roll_pos.y, inventory.size.x * 2.0f, inventory.size.y * 2.0f, 255);
	}
	for (int d = 0; d < 3; d++)
	{
		if (combat_dice[d].clicked)
		{
			CP_Settings_TextSize(100.0f);
			dice_timer += CP_System_GetDt();
			if (dice_timer < 2.0f)
			{
				generate_dice(roll_dice(combat_dice[d].type), combat_dice[d], roll_pos.x, roll_pos.y, 1.6f);
			}
			if (3.0f > dice_timer && dice_timer > 2.0f)
			{
				generate_dice(*combat_num, combat_dice[d], roll_pos.x, roll_pos.y, 1.6f);
			}
			if (dice_timer > 3.0f)
			{
				inventory.side_display = 0;
				go_to_animation(50.0f, 250.0f, &roll_pos);
				generate_dice(*combat_num, combat_dice[d], roll_pos.x, roll_pos.y, 1.6f);
			}
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				combat_dice[d].clicked = !combat_dice[d].clicked;
				combat_dice[d].side_display = !combat_dice[d].side_display;
			}
		}

	}
}*/

/*init_dicePos();
		inventory_window(3, dice_button.position.x);
		CP_Settings_TextSize(50.0f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		for (int d = 0; d < 3; d++)
		{
			CP_Image_Draw(mov_dice[d].image, mov_dice[d].position.x, mov_dice[d].position.y, mov_dice[d].size.x * 0.95, mov_dice[d].size.y * 0.95, 255);

			char amt_of_dice[1] = { '0' + num_dice[d] };
			float x = mov_dice[d].position.x + 40.0f;
			float y = mov_dice[d].position.y + 40.0f;
			CP_Settings_TextSize(30.0f);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Image_Draw(desc_panel.image, x, y, desc_panel.size.x * 0.3, desc_panel.size.y * 0.3, 255);
			CP_Font_DrawText(amt_of_dice, x, y);
			mov_dice[d].inButton = mouse_in_rect(mov_dice[d].position.x, mov_dice[d].position.y, mov_dice[d].size.x - 30.0f, mov_dice[d].size.y - 30.0f);
			if (mov_dice[d].inButton)
			{
				CP_Image_Draw(cursor.image, mov_dice[d].position.x - 80.0f, mov_dice[d].position.y, cursor.size.x, cursor.size.y, 255);
			}
		}
		CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
		CP_Settings_TextSize(45.0f);
		CP_Font_DrawText("d4", mov_dice[d4].position.x, mov_dice[d4].position.y + 12.5f);
		CP_Font_DrawText("d6", mov_dice[d6].position.x, mov_dice[d6].position.y);
		CP_Font_DrawText("d20", mov_dice[d20].position.x, mov_dice[d20].position.y);

		if ((mov_dice[d4].inButton == 1) && CP_Input_MouseClicked() && !mov_dice[d6].clicked && !mov_dice[d20].clicked)			//	checks if user selected to roll dice[d4] dice
		{
			selecting_action = dice_button.clicked = mov_dice[d6].clicked = mov_dice[d20].clicked = 0;
			mov_dice[d4].clicked = !mov_dice[d4].clicked;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*mov_num = roll_dice(mov_dice[d4].type);
		}
		else if ((mov_dice[d6].inButton == 1) && CP_Input_MouseClicked() && !mov_dice[d20].clicked && !mov_dice[d4].clicked)	//	checks if user selected to roll dice[d6] dice
		{
			selecting_action = dice_button.clicked = mov_dice[d4].clicked = mov_dice[d20].clicked = 0;
			mov_dice[d6].clicked = !mov_dice[d6].clicked;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*mov_num = roll_dice(mov_dice[d6].type);
		}
		else if ((mov_dice[d20].inButton == 1) && CP_Input_MouseClicked() && !mov_dice[d6].clicked && !mov_dice[d4].clicked)	//	checks if user selected dice[d20] dice
		{
			selecting_action = dice_button.clicked = mov_dice[d6].clicked = mov_dice[d4].clicked = 0;
			mov_dice[d20].clicked = !mov_dice[d20].clicked;
			init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*mov_num = roll_dice(mov_dice[d20].type);
		}
	}
	if (inventory.side_display)
	{
		CP_Image_Draw(inventory.image, roll_pos.x, roll_pos.y, inventory.size.x * 2.0f, inventory.size.y * 2.0f, 255);
	}
	for (int d = 0; d < 3; d++)
	{
		if (mov_dice[d].clicked)
		{
			CP_Settings_TextSize(100.0f);
			dice_timer += CP_System_GetDt();
			if (dice_timer < 2.0f)
			{
				generate_dice(roll_dice(mov_dice[d].type), mov_dice[d], roll_pos.x, roll_pos.y, 1.6f);
			}
			if (3.0f > dice_timer && dice_timer > 2.0f)
			{
				generate_dice(*mov_num, mov_dice[d], roll_pos.x, roll_pos.y, 1.6f);
			}
			if (dice_timer > 3.0f)
			{
				inventory.side_display = 0;
				go_to_animation(50.0f, 150.0f, &roll_pos);
				generate_dice(*mov_num, mov_dice[d], roll_pos.x, roll_pos.y, 1.6f);
			}
			if (dice_timer > 4.0f)
			{
				dice_timer = 0;
				mov_dice[d].clicked = !mov_dice[d].clicked;
				mov_dice[d].side_display = !mov_dice[d].side_display;
				movement_clicked = 0;
			}
		}
	}*/