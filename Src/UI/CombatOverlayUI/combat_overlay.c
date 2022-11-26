#include "combat_overlay.h"
#include "../UtilsUI/ui_utils.h"
#include "GameStateManager.h"
#include "second_combat.h"
#include "../../Character/gameChar.h"
#include "../../Scenes/GameScene.h"
#include "../../Items/itemHandler.h"
#include "../../Character/charMovement.h"
#include <stdio.h>



CP_Sound *sound;
#define MAXENEMIES 1
Enemy* enemy[MAXENEMIES];

float buttons_centerpointX;
float buttons_centerpointY;
asset inventory;
asset dice_button;
asset powerup_button;
asset mov_dice;
asset settings;
asset cursor;
asset powerup[maxPowerups];
asset dice_item[maxDiceItems];
asset desc_panel;
CP_Vector roll_pos;
CP_Vector side_display_pos;
CP_Vector item_pos;
CP_Font font;
CP_Sound dice_throw;
CP_Sound dice_shuffle;
CP_Sound click;
CP_Sound chest_open;
float dice_timer;
float powerup_timer;
float item_timer;
int selecting_action;
int rng_mov;
int display_side_dice[2];	// subscript 0: movement, 1: combat
int turns;
int combat_clicked;
int individual_mov_roll[2];
int warning_clicked[2];
int near_enemy;
float powerup_scale;
int powerups[3];
int chest;
int item_num;
bool chest_item;
bool up, upup;
extern b_paused;
bool prevent_powerup;
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
	get_image_size("desc_panel.png", &desc_panel);
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");

	// loads items and finds their sizes
	get_image_size("dice_item[woodensword].png", &dice_item[woodensword]);
	get_image_size("dice_item[woodenshield].png", &dice_item[woodenshield]);
	get_image_size("dice_item[ironsword].png", &dice_item[ironsword]);
	get_image_size("dice_item[ironshield].png", &dice_item[ironshield]);
	get_image_size("dice_item[goldsword].png", &dice_item[goldsword]);
	get_image_size("dice_item[goldshield].png", &dice_item[goldshield]);
	get_image_size("dice_item[diamondsword].png", &dice_item[diamondsword]);
	get_image_size("dice_item[diamondshield].png", &dice_item[diamondshield]);
	get_image_size("dice_item[mastersword].png", &dice_item[mastersword]);

	get_image_size("powerup[strongarm].png", &powerup[strongarm]);
	get_image_size("powerup[leatherskin].png", &powerup[leatherskin]);
	get_image_size("powerup[healthpot].png", &powerup[healthpot]);

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
	chest = 0;

	// dice randomiser initialise
	init_dice();

	// set names
	dice_item[woodensword].name = "Wooden Sword";
	dice_item[woodenshield].name = "Wooden Shield";
	dice_item[ironsword].name = "Iron Sword";
	dice_item[ironshield].name = "Iron Shield";
	dice_item[goldsword].name = "Gold Sword";
	dice_item[goldshield].name = "Gold Shield";
	dice_item[diamondsword].name = "Diamond Sword";
	dice_item[diamondshield].name = "Diamond Shield";
	dice_item[mastersword].name = "Master Sword";

	powerup[strongarm].name = "Attack Booster";
	powerup[leatherskin].name = "Leather Tunic";
	powerup[healthpot].name = "Health Pot";
	

	// set how many dice each powerup gets
	dice_item[woodensword].desc = "+1d6";
	dice_item[woodensword].desc1 = "+1d4";

	dice_item[woodenshield].desc = "+3d4";
	dice_item[ironsword].desc = "+2d6";

	dice_item[ironshield].desc = "+1d6";
	dice_item[ironshield].desc1 = "+3d4";
	
	dice_item[goldsword].desc = "+3d6";

	dice_item[goldshield].desc = "+2d6";
	dice_item[goldshield].desc1 = "+2d4";

	dice_item[diamondsword].desc = "+4d6";
	dice_item[diamondshield].desc = "+5d6";
	dice_item[mastersword].desc = "+2d20";


	mov_dice.type = e_std_D6;

	turns = 3;

	for (int d = 0; d < 3; d++)
	{								//	TODO: replace with number of powerups left accordingly
		powerups[d] = 0;
	}

	display_side_dice[0] = display_side_dice[1] = 0;
	
	// initialize description
	powerup[strongarm].desc = " Attack Booster: Damage +3 for 10 turns";
	powerup[leatherskin].desc = " Leather Tunic: Shield +5 for 10 turns";
	powerup[healthpot].desc = "    Health Pot:    Heals 10 HP.";
	
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);
	
	// set location of the buttons based on the center of the area where the power up and dice buttons are drawn

	buttons_centerpointX = CP_System_GetWindowWidth() - 140.0f;
	buttons_centerpointY = CP_System_GetWindowHeight() - 80.0f;
	dice_button.position.x = buttons_centerpointX + 60.0f;
	dice_button.position.y = powerup_button.position.y = buttons_centerpointY;	// y position of both power up and dice button are the same
	powerup_button.position.x = buttons_centerpointX - 60.0f;

	item_timer = 0;
	dice_timer = 0;
	powerup_timer = 0;

	chest_item = false;

	second_sfx_init();
	
	prevent_powerup = false;
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
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, 0.2f);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	chest = check_Chest(get_character()->sp->go.position);

	if (chest)
	{
		CP_Sound_Play(chest_open);
		item_pos = getWorldPos(get_character()->sp->go.position, getMap());
		float tileSize = CP_System_GetWindowHeight() / getMap()->height;
		item_pos.x += tileSize / 2;
		item_pos.y -= tileSize;
		chest_item = true;
		item_num = 9;
		if (item_num >= 9)
		{
			powerups[item_num - 9]++;
		}
	}

	if (chest_item)
	{
		item_to_inventory(item_num);
	}

	dice_powerup(get_character()->mod_duration);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Movement:", side_display_pos.x + 10.0f, side_display_pos.y + 40.0f);
	CP_Settings_TextSize(50.0f);
	movement_window(get_character()->energy, side_display_pos.x, side_display_pos.y + 100.0f, 0.8f);
	//side_display(get_character()->energy, turns);
	 // double check if it works
	//movement_window(get_character()->energy, float x, float y, float scale)
	
	
	settings_button();
}

void dice_powerup(int powerup_turns)
{
	// draws the interactable buttons based on the set locations

	CP_Image_Draw(dice_button.image, dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.image, powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y, 255);

	//side_display(powerup_turns);

	// branch out to decide if player rolls or not
	for (int d = 0; d < 3; d++)
	{
		if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && !powerup_button.clicked && !mov_dice.clicked && !mov_dice.warning && !powerup_button.warning)	//	checks if user clicked the dice button
		{
			CP_Sound_Play(click);
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
					CP_Settings_TextSize(25.0f);
					CP_Image_Draw(cursor.image, x - 110.0f, y - (i * inventory.size.y), cursor.size.x, cursor.size.y, 255);
					CP_Image_Draw(desc_panel.image, x - 225.0f, y - (i*inventory.size.y), desc_panel.size.x * 2.0, desc_panel.size.y * 1.2, 255);
					if (i == 0)
					{
						CP_Font_DrawTextBox("Ends movement turn and initiates combat if near enemy.", x - 225.0f - desc_panel.size.x + 2.5f, y - 37.5f, desc_panel.size.x * 2.0);
					}
					else if (i == 1)
					{
						CP_Font_DrawTextBox("Roll 2 d6 dice to move around on the map.", x - 225.0f - desc_panel.size.x + 2.5f, y - 25.0f - (i * inventory.size.y), desc_panel.size.x * 2.0);
					}
				}
				near_enemy = isEnemyNearUI(get_character()->sp->go.direction);
				if (!near_enemy && !i)
				{
					CP_Graphics_DrawRect(dice_button.position.x - 20.0f, (dice_button.position.y - 125.0f) - (i * inventory.size.y), inventory.size.x * 1.6, inventory.size.y, 100);
				}
			}
			if (mouse_in_rect(dice_button.position.x - 20.0f, dice_button.position.y - 150.0f - inventory.size.y, inventory.size.x * 1.6, inventory.size.y) && CP_Input_MouseClicked())
			{
				CP_Sound_Play(click);
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
			else if (mouse_in_rect(dice_button.position.x - 20.0f, dice_button.position.y - 150.0f, inventory.size.x * 1.6, inventory.size.y) && CP_Input_MouseClicked() && near_enemy)
			{
				fprintf(stdout, "%lf %lf", get_character()->sp->go.direction.x, get_character()->sp->go.direction.y);

				engage_enemy(get_character()->sp->go.direction);

				CP_Sound_Play(click);

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
	choose_powerup(powerup_turns, powerups);
}

void choose_to_roll_movement()
{
	get_character()->energy = 0;
	get_character()->energy += individual_mov_roll[0] + individual_mov_roll[1];
	//get_character()->sp->moved = 0;
	get_character()->turn_done = 0;
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
		if (dice_timer == CP_System_GetDt())
		{
			CP_Sound_Play(dice_throw);
			CP_Sound_Play(dice_shuffle);
		}
		if (dice_timer < 1.5f)
		{
			for (int d = 0; d < 2; d++)
			{
				generate_dice(roll_dice(e_std_D6), mov_dice.type, mov_dice.position.x + (d * 100.0f), mov_dice.position.y + (d * 100.0f), 1.0f);
			}
		}
		if (3.0f > dice_timer && dice_timer > 1.5f)
		{
			for (int d = 0; d < 2; d++)
			{
				generate_dice(individual_mov_roll[d], mov_dice.type, mov_dice.position.x + (d * 100.0f), mov_dice.position.y + (d * 100.0f), 1.0f);
			}
			CP_Settings_TextSize(50.0f);
			movement_window(get_character()->energy, mov_dice.position.x + 50.0f, mov_dice.position.y - 100.0f, 0.8);
		}
		if (dice_timer > 3.0f)
		{
			dice_timer = 0;
			mov_dice.clicked = !mov_dice.clicked;
			movement_clicked = 0;
			inventory.side_display = 0;
		}
	}
}

/*void side_display(int turns_left)
{
	// for movement side display
	CP_Settings_TextSize(30.0f);

	CP_Settings_TextSize(50.0f);
	movement_window(get_character()->energy, side_display_pos.x, side_display_pos.y + 100.0f, 0.8f);
	if (get_character()->energy <= 0)
	{
		get_character()->energy = 0;
	}
	
	// for combat side_display

}*/

void choose_powerup(int turns_left, int num_powerups[])
{
	char turns[2] = { '0' + turns_left / 10, '0' + turns_left % 10 };
	if (mouse_in_rect(powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y) == 1 && CP_Input_MouseClicked() && !dice_button.clicked && !powerup_button.warning)	//	checks if user clicked the dice button
	{
		CP_Sound_Play(click);
		for (int i = 0; i < maxPowerups; i++)
		{
			if (powerup[i].side_display == 1 && !powerup_button.warning)
			{
				powerup_button.warning = 1;
			}
			else
			{
				powerup_button.clicked = !powerup_button.clicked;
				powerup[strongarm].clicked = powerup[leatherskin].clicked = powerup[healthpot].clicked = 0;
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
		CP_Settings_TextSize(30.0f);
		CP_Font_DrawText("Use in combat only", powerup_button.position.x, powerup_button.position.y - (4 * inventory.size.y));
		inventory_window(3, powerup_button.position.x);
		for (int i = 0; i < maxPowerups; i++)
		{
			powerup[i].position.x = powerup_button.position.x - 1.0f;
			powerup[i].position.y = powerup_button.position.y - 132.5f - ((float)i * (115.0f));
			CP_Image_Draw(powerup[i].image, powerup[i].position.x, powerup[i].position.y + 5.0f, powerup[i].size.x, powerup[i].size.y, 255);
			if (num_powerups[i] == 0)
			{
				CP_Settings_RectMode(CP_POSITION_CENTER);
				CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
				CP_Graphics_DrawRect(powerup[i].position.x, powerup[i].position.y, inventory.size.x, inventory.size.y);
			}
		}
		for (int i = 0; i < maxPowerups; i++)
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
				CP_Image_Draw(desc_panel.image, powerup[i].position.x - 190.0f, powerup[i].position.y, desc_panel.size.x * 2.0, desc_panel.size.y * 1.2, 255);
				CP_Settings_Fill(CP_Color_Create(255,255,255,255));
				CP_Settings_TextSize(25.0f);
				CP_Font_DrawTextBox(powerup[i].desc, powerup[i].position.x - 285.0f, powerup[i].position.y - 22.5f, desc_panel.size.x * 1.9);
			}
		}
		if (mouse_in_rect(powerup[strongarm].position.x, powerup[strongarm].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked() && num_powerups[strongarm] && prevent_powerup)
		{
			powerup[strongarm].clicked = !powerup[strongarm].clicked;
			powerup[leatherskin]. clicked = powerup[healthpot].clicked = 0;
			powerup_button.clicked = !powerup_button.clicked;
			num_powerups[strongarm]--;
			powerup_scale = 1.0f;
		}
		else if (mouse_in_rect(powerup[leatherskin].position.x, powerup[leatherskin].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked() && num_powerups[leatherskin] && prevent_powerup)
		{
			powerup[strongarm].clicked = powerup[healthpot].clicked = 0;
			powerup[leatherskin].clicked = !powerup[leatherskin].clicked;
			powerup_button.clicked = !powerup_button.clicked;
			num_powerups[leatherskin]--;
			powerup_scale = 1.0f;
		}
		else if (mouse_in_rect(powerup[healthpot].position.x, powerup[healthpot].position.y, 80.0f, 80.0f) && CP_Input_MouseClicked() && num_powerups[healthpot] && prevent_powerup)
		{
			powerup[strongarm].clicked = powerup[leatherskin].clicked = 0;
			powerup[healthpot].clicked = !powerup[healthpot].clicked;
			powerup_button.clicked = !powerup_button.clicked;
			num_powerups[healthpot]--;
			powerup_scale = 1.0f;
		}
		
	}

	for (int i = 0; i < maxPowerups; i++)
	{
		if (powerup[i].clicked == 1)
		{
			powerup_timer += CP_System_GetDt();
			CP_Vector pos = getWorldPos(get_character()->sp->go.position, getMap());
			float tileSize = CP_System_GetWindowHeight() / getMap()->height;
			float tileSizeDiv = tileSize / 2;
			if (powerup_timer < 0.8f)
			{
				go_to_animation(pos.x + tileSizeDiv, pos.y + tileSize, &powerup[i].position);		//	TODO: change position to player position
				shrinking_animation(0.5f, &powerup_scale);
				CP_Image_Draw(powerup[i].image, powerup[i].position.x, powerup[i].position.y, powerup[i].size.x * powerup_scale, powerup[i].size.y * powerup_scale, 255);
			}
			else if (powerup_timer > 0.8f && powerup_timer < 1.5f)
			{
				CP_Settings_TextSize(30.0f);
				if (powerup[healthpot].clicked)
				{
					CP_Font_DrawText("+10HP", pos.x + tileSizeDiv, pos.y - tileSize);
				}
				else if (powerup[leatherskin].clicked)
				{
					CP_Font_DrawText("Equipped", pos.x + tileSizeDiv, pos.y - tileSize);
				}
				else if (powerup[strongarm].clicked)
				{
					CP_Font_DrawText("Attack UP", pos.x + tileSizeDiv, pos.y - tileSize);
				}
				else
				{
					CP_Font_DrawText("Power up!", pos.x + tileSizeDiv, pos.y - tileSize);
				}

				if (upup == false)
				{
					up = true;
					upup = true;
				}
				
			}
			else if (powerup_timer > 1.5f)
			{
				powerup[i].side_display = 1;
				powerup_timer = 0;
				powerup[i].clicked = 0;
				upup = false;
			}
			if (up) // TODO: change this so that it plays all the time but just once
			{
				CP_Sound_Play(poweredup);
				up = false;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{	
		if (powerup[i].side_display == 1 && turns_left > 0)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Image_Draw(powerup[i].image, side_display_pos.x, side_display_pos.y + 200.0f, powerup[i].size.x * 0.8f, powerup[i].size.y * 0.8f, 255);
			CP_Settings_TextSize(20.0f);
			CP_Font_DrawText(powerup[i].name, side_display_pos.x+5.0f, side_display_pos.y + 160.0f);
			CP_Settings_TextSize(30.0f);
			CP_Image_Draw(desc_panel.image, side_display_pos.x, side_display_pos.y + 255.0f, 50.0f, 50.0f, 255);
			CP_Font_DrawText(turns, side_display_pos.x, side_display_pos.y + 255.0f);
			CP_Settings_TextSize(20.0f);
			CP_Font_DrawText("Turns left", side_display_pos.x, side_display_pos.y + 300.0f);
		}
		else if (turns_left <= 0)
		{
			powerup[i].side_display = 0;
		}
	}
}

void settings_button(void)		//	draws settings icon
{
	settings.position.x = 50.0f;
	settings.position.y = CP_System_GetWindowHeight() - 50.0f;
	CP_Image_Draw(settings.image, settings.position.x, settings.position.y, settings.size.x, settings.size.y, 255);
	if ((mouse_in_rect(settings.position.x, settings.position.y, settings.size.x, settings.size.y) == 1) && CP_Input_MouseClicked())
	{
		CP_Sound_Play(click);
		GameStateSetNextSubScene(PAUSE_SCENE, true);
	}
}

void movement_window(int movement, float x, float y, float scale)
{
	char total[3] = { '0' + (movement / 10), '0' + (movement % 10), '\0'};
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Image_Draw(desc_panel.image, x, y, desc_panel.size.x * scale, desc_panel.size.y * scale, 255);
	CP_Font_DrawText(total, x, y);
}

int isEnemyNearUI(CP_Vector dir)
{
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
	CP_Vector tmp = get_character()->sp->go.position;
	tmp = CP_Vector_Add(tmp, dir);
	int check = 0;
	
	for (int i = 0; i < numEnemies[currLvl]; ++i)
	{
		if (tmp.x == enemy[i]->sp->go.position.x && tmp.y == enemy[i]->sp->go.position.y)
		{
			check = 1;
			break;
		}
		else
		{
			check = 0;
		}
	}
	return check;
}

void item_to_inventory(int item_code)
{
	item_timer += CP_System_GetDt();

	if (item_code >= 0 && item_code <= 8)
	{
		if (item_timer < 2.0f)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Image_Draw(dice_item[item_code].image, item_pos.x, item_pos.y, dice_item[item_code].size.x, dice_item[item_code].size.y, 255);
		}
		else if (item_timer > 2.0f && item_timer < 3.0f)
		{
			go_to_animation(dice_button.position.x, dice_button.position.y, &item_pos);
			CP_Image_Draw(dice_item[item_code].image, item_pos.x, item_pos.y, dice_item[item_code].size.x, dice_item[item_code].size.y, 255);
		}
		else if (item_timer > 3.0f && item_timer < 5.0f)
		{
			if (item_code == woodensword || item_code == ironshield || item_code == goldshield)
			{
				CP_Image_Draw(dice_item[item_code].image, dice_button.position.x, dice_button.position.y - 250.0f, dice_item[item_code].size.x, dice_item[item_code].size.y, 255);
				CP_Settings_TextSize(35.0f);
				CP_Font_DrawText(dice_item[item_code].name, dice_button.position.x - 25.0f, dice_button.position.y - 200.0f);
				CP_Settings_TextSize(50.0f);
				CP_Font_DrawText(dice_item[item_code].desc, dice_button.position.x, dice_button.position.y - 150.0f);
				CP_Font_DrawText(dice_item[item_code].desc1, dice_button.position.x, dice_button.position.y - 100.0f);
			}
			else
			{
				CP_Image_Draw(dice_item[item_code].image, dice_button.position.x, dice_button.position.y - 200.0f, dice_item[item_code].size.x, dice_item[item_code].size.y, 255);
				CP_Settings_TextSize(35.0f);
				CP_Font_DrawText(dice_item[item_code].name, dice_button.position.x - 25.0f, dice_button.position.y - 150.0f);
				CP_Settings_TextSize(50.0f);
				CP_Font_DrawText(dice_item[item_code].desc, dice_button.position.x, dice_button.position.y - 100.0f);
			}
		}
		else
		{
			chest_item = false;
			item_timer = 0;
		}
	}
	else if (item_code >= 9 && item_code <= 11) // for powerups
	{
		if (item_timer < 2.0f)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Image_Draw(powerup[item_code-9].image, item_pos.x, item_pos.y, powerup[item_code-9].size.x * 0.6, powerup[item_code-9].size.y * 0.6, 255);
			CP_Font_DrawText(powerup[item_code-9].name, get_character()->sp->go.position.x, get_character()->sp->go.position.y - 40.0f);
		}
		else if (item_timer > 2.0f && item_timer < 3.0f)
		{
			go_to_animation(powerup_button.position.x, powerup_button.position.y, &item_pos);
			CP_Image_Draw(powerup[item_code-9].image, item_pos.x, item_pos.y, powerup[item_code-9].size.x * 0.6, powerup[item_code-9].size.y * 0.6, 255);
		}
		else if (item_timer > 3.0f && item_timer < 5.0f)
		{
			CP_Image_Draw(powerup[item_code - 9].image, powerup_button.position.x, powerup_button.position.y - 140.0f, powerup[item_code - 9].size.x, powerup[item_code - 9].size.y, 255);
			CP_Settings_TextSize(35.0f);
			CP_Font_DrawText(powerup[item_code - 9].name, powerup_button.position.x, powerup_button.position.y - 80.0f);
		}
		else
		{
			chest_item = false;
			item_timer = 0;
		}
	}
}

void combat_overlay_exit(void)
{
	CP_Image_Free(&mov_dice.image);
	CP_Image_Free(&inventory.image);
	CP_Image_Free(&dice_button.image);
	CP_Image_Free(&powerup_button.image);
	CP_Image_Free(&settings.image);
	CP_Image_Free(&inventory.image);
	CP_Image_Free(&cursor.image);
	CP_Image_Free(&powerup[strongarm].image);
	CP_Image_Free(&powerup[leatherskin].image);
	CP_Image_Free(&powerup[healthpot].image);
	CP_Image_Free(&desc_panel.image);
}


