#include "combat_overlay.h"
#include "../UtilsUI/ui_utils.h"
#include "second_combat.h"
#include "../../GameStateManager.h"
#include "../../Combat/combatHandler.h"
#include "../../Combat/combat_scene.h"
#include "../../Scenes/GameScene.h"
#include <stdio.h>
#include <string.h>
#ifdef _MSC_VER // for visual studios/microsoft compiler
#pragma warning(disable : 4996)
#endif

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
asset enemy_alive_hp;
asset powerup[3];
asset desc_panel;
asset sword;
asset shield;
asset clash1;
asset clash2;
asset slash;
asset parried;
CP_Vector roll_pos;
CP_Vector side_display_pos;
CP_Vector player_rumble;
CP_Vector enemy_dice_pos;
CP_Font font;
CP_Vector rect;
CP_Sound dice_throw;
CP_Sound dice_shuffle;
CP_Sound attack;
CP_Sound parry;
CP_Sound click;
CP_Sound footsteps;
CP_Sound poweredup;
float dice_timer;
float powerup_timer;
int num_roll;
int turns;
int warning_clicked[2];		// subscript 0: dice_button, subscript 1: powerup_button
float dice_scale;
int combat_dice[3];
int count_rolls;
int powerups[3];
int enemy_turn;
int fight;
float enemy_timer;
int enemy_turn_end;
int enemy_hp;
int player_hp;
int enemys_roll;
int alpha;
float blinkTimer;
float timer;
float cutin_timer;
float fighting_timer;
//int player_roll;



void second_init(void)
{
	//	loads images and finds their sizes

	get_image_size("dice_button.png", &dice_button);
	get_image_size("inventory_block.png", &inventory);
	get_image_size("powerup_button.png", &powerup_button);
	get_image_size("dice[d4].png", &dice[d4]);
	get_image_size("dice[d6].png", &dice[d6]);
	get_image_size("dice[d20].png", &dice[d20]);
	get_image_size("alive_hp.png", &alive_hp);
	get_image_size("enemy_alive_hp.png", &enemy_alive_hp);
	get_image_size("sword.png", &sword);
	get_image_size("shield.png", &shield);
	get_image_size("clash1.png", &clash1);
	get_image_size("clash2.png", &clash2);
	get_image_size("slash.png", &slash);
	get_image_size("parried.png", &parried);
	font = CP_Font_Load("Assets/Kenney_Pixel.ttf");

	combat_overlay_init();

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
	count_rolls = 0;
	alpha = 255;

	CP_System_SetWindowSize(1280, 720);

	// initializes the counter for the dice and powerups

	for (int d = 0; d < MAX_DICE; d++)
	{
		switch (get_character()->dice[d])
		{
		case e_std_D4:
		{
			combat_dice[d4]++;
			break;
		}
		case e_std_D6:
		{
			combat_dice[d6]++;
			break;
		}
		case e_std_D20:
		{
			combat_dice[d20]++;
			break;
		}
		default:
		{
			d = MAX_DICE;
			break;
		}
		}
	}
	// TODO: Add powerup counter


	// set location of the buttons based on the center of the area where the power up and dice buttons are drawn

	buttons_centerpointX = CP_System_GetWindowWidth() - 140.0f;
	buttons_centerpointY = CP_System_GetWindowHeight() - 80.0f;
	dice_button.position.x = buttons_centerpointX + 60.0f;
	dice_button.position.y = powerup_button.position.y = sword.position.y = shield.position.y = buttons_centerpointY;	// y position of both power up and dice button are the same
	powerup_button.position.x = buttons_centerpointX - 60.0f;
	sword.position.x = shield.position.x = CP_System_GetWindowWidth()/2;
	playerRolled = false;
	enemyRolled = false;
	enemy_timer = 0.0f;
	//player_roll = 0;
	second_sfx_init();
}

void second_sfx_init(void)
{
	dice_throw = CP_Sound_Load("Assets/SFX/dice_throw.ogg");
	dice_shuffle = CP_Sound_Load("Assets/SFX/dice_shuffle.ogg");
	attack = CP_Sound_Load("Assets/SFX/attack.ogg");
	parry = CP_Sound_Load("Assets/SFX/parry.ogg");
	footsteps = CP_Sound_Load("Assets/SFX/footsteps.ogg");
	poweredup = CP_Sound_Load("Assets/SFX/poweredup.ogg");
	click = CP_Sound_Load("Assets/SFX/click.ogg");
}

void second_init_dicePos(void)
{
	// set location where choosable dice[d6] and dice[d20] die are after player selects the dice button
	for (int d = 0; d < 3; d++)
	{
		dice[d].position.x = dice_button.position.x;
		dice[d].position.y = dice_button.position.y - 130.0f - (115.0f * d);
	}
	enemy_dice_pos = getWorldPos(the_enemy->sp->go.position, getMap());
	enemy_dice_pos.x += 40.0f;
	enemy_dice_pos.y -= 50.0f;
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

/*void clash_init(void)
{
	clash1.position.x = clash2.position.x = CP_System_GetWindowWidth() / 2;
	clash1.position.y = clash2.position.y = rect.y = CP_System_GetWindowHeight() / 2;
	rect.x = -10.0f;
}*/

void second_update(void)
{
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	second_dice_powerup(&num_roll, combat_dice, turns);				// TODO: replace turns with turns left for powerup
	if (get_character()->combat_mode == CHAR_ATTACKING)
	{
		CP_Settings_TextSize(40.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("State: Attacking", 150.0f, 150.0f);
	}
	else
	{
		CP_Settings_TextSize(40.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("State: Defending", 150.0f, 150.0f);
	}
	if (enemy_turn)
	{
		enemy_ui(e_std_D6, enemys_roll, 1.0f);
	}
	
	if (enemy_turn_end) //TODO
	{
		//attacker's roll
		if (get_character()->combat_mode == CHAR_ATTACKING)
		{
			attacker_sum = num_roll;
		}
		else if (the_enemy->enemyState == ATTACK_STATE)
		{
			attacker_sum = enemys_roll;
		}

		//defender's roll
		if (get_character()->combat_mode == CHAR_DEFENDING)
		{
			defender_sum = num_roll;
		}
		else if (the_enemy->enemyState == DEFEND_STATE)
		{
			defender_sum = enemys_roll;
		}

		++count_rolls;
		combat_phase();

		if (count_rolls >= max_combat_size) //reached the end of this combat phase, so we alternate
		{
			count_rolls = 0;
			combatants_present = 0;
			for (int d = 0; d < 3; d++)
			{
				combat_dice[d] = 0;
			}

			if (the_enemy->enemyState == ATTACK_STATE)
				the_enemy->enemyState = DEFEND_STATE;
			else if (the_enemy->enemyState == DEFEND_STATE)
				the_enemy->enemyState = ATTACK_STATE;

			for (int d = 0; d < MAX_DICE; d++)
			{
				switch (get_character()->dice[d])
				{
				case e_std_D4:
				{
					combat_dice[d4]++;
					break;
				}
				case e_std_D6:
				{
					combat_dice[d6]++;
					break;
				}
				case e_std_D20:
				{
					combat_dice[d20]++;
					break;
				}
				default:
				{
					d = MAX_DICE;
					break;
				}
				}
			}
			//TODO: add powerup counter
		}
		enemy_turn_end = !enemy_turn_end;
	}
	
	CP_Settings_RectMode(CP_POSITION_CORNER);
	health_bar(get_character()->hp);					//	TODO: replace with remaining hp
	enemy_health_bar(the_enemy->hp, getWorldPos(the_enemy->sp->go.position, getMap()));
	if (fight)
	{
		blinkTimer += CP_System_GetDt();
		timer += CP_System_GetDt();
		if (timer < 2.0)     // lets say blink for 2 sec
		{
			if (blinkTimer > 0.5)   // flip every 0.5 seconds
			{
				if (!alpha)
				{
					alpha = 255; // max alpha
					timer = 0;
				}
				else
				{
					alpha = 0;
					timer = 0;
				}
			}
		}
		fighting_animation(num_roll, enemys_roll);
	}
	bottom_display(num_roll, enemys_roll);
	settings_button();
}

void second_dice_powerup(int *rng_num, int powerup_turns)
{
	// draws the interactable buttons based on the set locations

	CP_Image_Draw(dice_button.image, dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.image, powerup_button.position.x, powerup_button.position.y, powerup_button.size.x, powerup_button.size.y, 255);

	// branch out to decide if player rolls or not

	second_choose_to_roll_dice(rng_num);
	choose_powerup(powerup_turns, powerups);
}

void second_choose_to_roll_dice(int *num_roll)
{
	for (int d = 0; d < 3; d++)
	{
		*dice[d].num = '0' + combat_dice[d];
		if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && !powerup_button.clicked && !dice[d].clicked && !enemy_turn)	//	checks if user clicked the dice button
		{
			CP_Sound_Play(click);
			dice_button.clicked = 1;
			dice[d].clicked = 0;
			dice[d].side_display = 0;
		}
		/*if (mouse_in_rect(dice_button.position.x, dice_button.position.y, dice_button.size.x, dice_button.size.y) == 1 && CP_Input_MouseClicked() && count_rolls == 1 && !warning_clicked[0])
		{
			warning_clicked[0] = !warning_clicked[0];
		}*/
	}
	/*if (warning_clicked[0] == 1)
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
	}*/
	if (dice_button.clicked)	// Draws the window pop up for player to choose dice to roll
	{
		second_init_dicePos();
		inventory_window(3, dice_button.position.x);
		for (int d = 0; d < 3; d++)
		{
			CP_Image_Draw(dice[d].image, dice[d].position.x, dice[d].position.y, dice[d].size.x * 0.95, dice[d].size.y * 0.95, 255);
			dice[d].inButton = mouse_in_rect(dice[d].position.x, dice[d].position.y, dice[d].size.x - 30.0f, dice[d].size.y - 30.0f);
			CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
			CP_Settings_TextSize(45.0f);
			CP_Font_DrawText("d4", dice[d4].position.x, dice[d4].position.y + 12.5f);
			CP_Font_DrawText("d6", dice[d6].position.x, dice[d6].position.y);
			CP_Font_DrawText("d20", dice[d20].position.x, dice[d20].position.y);
			if (combat_dice[d] == 0)
			{
				CP_Settings_RectMode(CP_POSITION_CENTER);
				CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
				CP_Graphics_DrawRect(dice[d].position.x, dice[d].position.y, inventory.size.x, inventory.size.y);
			}
			CP_Image_Draw(desc_panel.image, dice[d].position.x - 50.0f, dice[d].position.y + 50.0f, desc_panel.size.x * 0.4, desc_panel.size.y * 0.4, 255);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize(40.0f);
			CP_Font_DrawText(dice[d].num, dice[d].position.x - 50.0f, dice[d].position.y + 50.0f);
			if (dice[d].inButton)
			{
				CP_Image_Draw(cursor.image, dice[d].position.x - 80.0f, dice[d].position.y, cursor.size.x, cursor.size.y, 255);
			}
		}
		CP_Settings_RectMode(CP_POSITION_CENTER);
		if ((dice[d4].inButton == 1) && CP_Input_MouseClicked() && !dice[d6].clicked && !dice[d20].clicked && combat_dice[d4] != 0)			//	checks if user selected to roll dice[d4] dice
		{
			CP_Sound_Play(click);
			dice_button.clicked = dice[d6].clicked = dice[d20].clicked = 0;
			dice[d4].clicked = !dice[d4].clicked;
			second_init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*num_roll = roll_dice(dice[d4].type);
		}
		else if ((dice[d6].inButton == 1) && CP_Input_MouseClicked() && !dice[d20].clicked && !dice[d4].clicked && combat_dice[d6] != 0)	//	checks if user selected to roll dice[d6] dice
		{
			CP_Sound_Play(click);
			dice_button.clicked = dice[d4].clicked = dice[d20].clicked = 0;
			dice[d6].clicked = !dice[d6].clicked;
			second_init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*num_roll = roll_dice(dice[d6].type);
		}
		else if ((dice[d20].inButton == 1) && CP_Input_MouseClicked() && !dice[d6].clicked && !dice[d4].clicked && combat_dice[d20] != 0)	//	checks if user selected dice[d20] dice
		{
			CP_Sound_Play(click);
			dice_button.clicked = dice[d6].clicked = dice[d4].clicked = 0;
			dice[d20].clicked = !dice[d20].clicked;
			second_init_rollPos();
			inventory.side_display = !inventory.side_display;	// this is for the 'floor' that the dice rolls on
			*num_roll = roll_dice(dice[d20].type);
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
			if (dice_timer == CP_System_GetDt())
			{
				CP_Sound_Play(dice_throw);
				CP_Sound_Play(dice_shuffle);
			}
			if (dice_timer < 1.5f)
			{
				generate_dice(roll_dice(dice[d].type), dice[d].type, roll_pos.x, roll_pos.y, dice_scale);
			}
			if (2.5f > dice_timer && dice_timer > 1.5f)
			{
				generate_dice(*num_roll, dice[d].type, roll_pos.x, roll_pos.y, dice_scale);
			}
			if (dice_timer > 2.5f)
			{
				inventory.side_display = 0;
				go_to_animation(((CP_System_GetWindowWidth()/2) - 200.0f), buttons_centerpointY, &roll_pos);
				shrinking_animation(0.1f, &dice_scale);
				generate_dice(*num_roll, dice[d].type, roll_pos.x, roll_pos.y, dice_scale);
			}
			if (dice_timer > 3.5f)
			{
				enemys_roll = roll_dice(the_enemy->dice[count_rolls - 1]);
				dice_timer = 0;
				dice[d].clicked = !dice[d].clicked;
				enemy_turn = !enemy_turn;
			}
		}
	}
}

void bottom_display(int player_roll, int enemy_roll)
{
	char player[3] = { '0' + (player_roll / 10), '0' + (player_roll % 10), '\0'};
	char enemy[3] = { '0' + (enemy_roll / 10), '0' + (enemy_roll % 10), '\0'};
	CP_Settings_TextSize(65.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (the_enemy->enemyState == DEFEND_STATE)
	{
		CP_Image_Draw(sword.image, sword.position.x - 200.0f, sword.position.y, sword.size.x, sword.size.y, 255);
		CP_Font_DrawText(player, sword.position.x - 160.0f, sword.position.y - 2.5f);
		CP_Image_Draw(shield.image, shield.position.x + 200.0f, shield.position.y, shield.size.x, shield.size.y, 255);
		CP_Font_DrawText(enemy, shield.position.x + 240.0f, sword.position.y - 2.5f);
	}
	else if (the_enemy->enemyState == ATTACK_STATE)
	{
		CP_Image_Draw(shield.image, shield.position.x - 200.0f, shield.position.y, shield.size.x, shield.size.y, 255);
		CP_Font_DrawText(player, shield.position.x - 160.0f, shield.position.y - 2.5f);
		CP_Image_Draw(sword.image, sword.position.x + 200.0f, sword.position.y, sword.size.x, sword.size.y, 255);
		CP_Font_DrawText(enemy, sword.position.x + 240.0f, sword.position.y - 2.5f);
	}
}

void generate_dice(int num_roll, dice_types dice_rolled, float dice_posX, float dice_posY, float scale) // draws dice (dice[d6] or d20) with number corresponding to value num_roll
{
	float text_posX = dice_posX + 2.0f * scale;
	float text_posY = dice_posY;
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	switch (dice_rolled)
	{
		case e_std_D4:
		{
			CP_Image_Draw(dice[d4].image, dice_posX, dice_posY, dice[d4].size.x * scale, dice[d4].size.y * scale, 255);
			char num_text[2] = { '0' + num_roll, '\0'};
			CP_Font_DrawText(num_text, text_posX + (2.0f * scale), text_posY + 12.5f);
			break;
		}
		case e_std_D6:
		{
			CP_Image_Draw(dice[d6].image, dice_posX, dice_posY, dice[d6].size.x * scale, dice[d6].size.y * scale, 255);
			char num_text[2] = { '0' + num_roll, '\0'};
			CP_Font_DrawText(num_text, text_posX, text_posY);
			break;
		}
		case e_std_D20:
		{
			CP_Image_Draw(dice[d20].image, dice_posX, dice_posY, dice[d20].size.x * scale, dice[d20].size.y * scale, 255);
			if (num_roll >= 10)
			{
				char num_text[3] = { '0' + (num_roll / 10), '0' + (num_roll % 10), '\0'};
				CP_Font_DrawText(num_text, text_posX, text_posY);
			}
			else
			{
				char num_text[2] = { '0' + num_roll, '\0'};
				CP_Font_DrawText(num_text, text_posX, text_posY);
			}
			break;
		}
		default:
		{
			CP_Image_Draw(dice[d6].image, dice_posX, dice_posY, dice[d20].size.x * scale, dice[d20].size.y * scale, 255);
			char num_text[2] = { '0' + num_roll, '\0'};
			CP_Font_DrawText(num_text, text_posX, text_posY);
			break;
		}
	}
}

void enemy_ui(dice_types enemy_dice, int enemy_roll, float enemy_dice_scale)
{
	enemy_timer += CP_System_GetDt();
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Settings_TextSize(50.0f);
	if (enemy_timer < 1.0f)
	{
		switch (enemy_dice)
		{
			case e_std_D4:
			{
				CP_Image_Draw(dice[d4].image, enemy_dice_pos.x, enemy_dice_pos.y, dice[d4].size.x * enemy_dice_scale, dice[d4].size.y * enemy_dice_scale, 255);
				CP_Font_DrawText("d4", enemy_dice_pos.x, enemy_dice_pos.y);
			}
			case e_std_D6:
			{
				CP_Image_Draw(dice[d6].image, enemy_dice_pos.x, enemy_dice_pos.y, dice[d6].size.x * enemy_dice_scale, dice[d6].size.y * enemy_dice_scale, 255);
				CP_Font_DrawText("d6", enemy_dice_pos.x, enemy_dice_pos.y);
				break;
			}
			case e_std_D20:
			{
				CP_Image_Draw(dice[d20].image, enemy_dice_pos.x, enemy_dice_pos.y, dice[d20].size.x * enemy_dice_scale, dice[d20].size.y * enemy_dice_scale, 255);
				CP_Font_DrawText("d20", enemy_dice_pos.x, enemy_dice_pos.y);
				break;
			}
			default:
			{
				CP_Font_DrawText("d6", enemy_dice_pos.x, enemy_dice_pos.y);
				break;
			}
		}
	}
	else if (enemy_timer > 1.0f)
	{
		CP_Settings_TextSize(62.5f);
		if (enemy_timer > 1.0f && enemy_timer < 3.0f)
		{
			generate_dice(roll_dice(enemy_dice), enemy_dice, enemy_dice_pos.x, enemy_dice_pos.y, enemy_dice_scale);
		}
		if (4.0f > enemy_timer && enemy_timer > 3.0f)
		{
			generate_dice(enemy_roll, enemy_dice, enemy_dice_pos.x, enemy_dice_pos.y, enemy_dice_scale);
		}
		if (enemy_timer > 4.0f)
		{
			go_to_animation(((CP_System_GetWindowWidth() / 2) + 200.0f), buttons_centerpointY, &enemy_dice_pos);
			shrinking_animation(0.1f, &enemy_dice_scale);
			generate_dice(enemy_roll, enemy_dice, enemy_dice_pos.x, enemy_dice_pos.y, enemy_dice_scale);
		}
		if (enemy_timer > 5.0f)
		{
			fight = !fight;
			enemy_turn = !enemy_turn;
			enemy_turn_end = 1;
			//clash_init();
			enemy_timer = 0.0f;
		}
	}
}

void fighting_animation(int num_roll, int enemys_roll)
{
	fighting_timer += CP_System_GetDt();
	CP_Vector player_pos = getWorldPos(get_character()->sp->go.position, getMap());
	CP_Vector enemy_pos = getWorldPos(the_enemy->sp->go.position, getMap());
	if (num_roll == enemys_roll)
	{
		if (fighting_timer == CP_System_GetDt())
		{
			CP_Sound_Play(parry);
		}
		if (fighting_timer < 1.0f)
		{
			if (enemy_pos.x > player_pos.x || player_pos.x > enemy_pos.x)
			{
				CP_Image_Draw(parried.image, (player_pos.x + enemy_pos.x) / 2 + 27.5f, player_pos.y + 24.0f, parried.size.x, parried.size.y, 255);
			}
			else if (enemy_pos.y > player_pos.y || player_pos.y > enemy_pos.y)
			{
				CP_Image_Draw(parried.image, player_pos.x + 27.5f, (player_pos.y + enemy_pos.y)/2 + 24.0f, parried.size.x, parried.size.y, 255);
			}
		}
	}
	else if (num_roll != enemys_roll)
	{
		if (fighting_timer == CP_System_GetDt())
		{
			CP_Sound_Play(attack);
		}
		if (fighting_timer < 1.0f)
		{
			if (num_roll < enemys_roll)
			{
				CP_Image_Draw(slash.image, player_pos.x + 27.5f, player_pos.y + 24.0f, slash.size.x, slash.size.y, 255);
			}
			else if (enemys_roll < num_roll)
			{
				CP_Image_Draw(slash.image, enemy_pos.x + 27.5f, enemy_pos.y + 24.0f, slash.size.x, slash.size.y, 255);
			}
		}
	}
	if (fighting_timer > 2.0f)
	{
		fighting_timer = 0;
		fight = !fight;
	}
}

/*void cut_in(int num_roll, int enemys_roll)
{
	cutin_timer += CP_System_GetDt();
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	if (cutin_timer < 2.0f)
	{
		if (the_enemy->enemyState == DEFEND_STATE)
		{
			CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
			CP_Image_Draw(clash1.image, rect.x, rect.y, clash1.size.x, clash1.size.y, 255);
			go_to_animation(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, &rect);
		}
		else if (the_enemy->enemyState == ATTACK_STATE)
		{
			CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
			CP_Image_Draw(clash2.image, rect.x, rect.y, clash2.size.x, clash2.size.y, 255);
			go_to_animation(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, &rect);
		}
	}
	if (cutin_timer > 2.0f && cutin_timer < 4.0f)
	{
		if (the_enemy->enemyState == DEFEND_STATE)
		{
			if (num_roll < enemys_roll)
			{
				CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
				CP_Image_Draw(clash1.image, clash1.position.x, clash1.position.y, clash1.size.x, clash1.size.y, 255);
				go_to_animation(CP_System_GetWindowWidth(), CP_System_GetWindowHeight() / 2, &clash1.position);
				go_to_animation(CP_System_GetWindowWidth(), CP_System_GetWindowHeight() / 2, &rect);
			}
			else if (enemys_roll > num_roll)
			{
				CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
				CP_Image_Draw(clash1.image, clash1.position.x, clash1.position.y, clash1.size.x, clash1.size.y, 255);
				go_to_animation(0.0f, CP_System_GetWindowHeight() / 2, &clash1.position);
				go_to_animation(0.0f, CP_System_GetWindowHeight() / 2, &rect);
			}
			else
			{
				CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
				CP_Image_Draw(clash1.image, clash1.position.x, clash1.position.y, clash1.size.x, clash1.size.y, 255);
			}
		}
		else if (the_enemy->enemyState == ATTACK_STATE)
		{
			if (num_roll < enemys_roll)
			{
				CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
				CP_Image_Draw(clash2.image, clash2.position.x, clash2.position.y, clash2.size.x, clash2.size.y, 255);
				go_to_animation(CP_System_GetWindowWidth(), CP_System_GetWindowHeight() / 2, &clash2.position);
				go_to_animation(CP_System_GetWindowWidth(), CP_System_GetWindowHeight() / 2, &rect);
			}
			else if (enemys_roll > num_roll)
			{
				CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
				CP_Image_Draw(clash2.image, clash2.position.x, clash2.position.y, clash2.size.x, clash2.size.y, 255);
				go_to_animation(0.0f, CP_System_GetWindowHeight() / 2, &clash2.position);
				go_to_animation(0.0f, CP_System_GetWindowHeight() / 2, &rect);
			}
			else
			{
				CP_Graphics_DrawRect(rect.x, rect.y, CP_System_GetWindowWidth(), 200.0f);
				CP_Image_Draw(clash2.image, clash2.position.x, clash2.position.y, clash2.size.x, clash2.size.y, 255);
			}
		}
	}
	else if (cutin_timer > 4.0f)
	{
		cutin_timer = 0;
		fight = !fight;
	}
}*/

void health_bar(int remaining_hp)	//	draws hp bar (max is currently 5)
{
	char hp_text[50] = {'P', 'l', 'a', 'y', 'e', 'r', ' ', 'H', 'P', ':', ' ',
						'0' + remaining_hp / 100, '0' + ((remaining_hp % 100) / 10), '0' + (remaining_hp % 10),
						'/', '1', '0', '0'};
	CP_Font_DrawText((const char*)hp_text, 150.0f, 120.0f);

	float width = CP_System_GetWindowWidth() * 0.30f;
	if (num_roll < enemys_roll && fight)
	{
		//rumbling_animation(alpha);
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, alpha));
		CP_Graphics_DrawRect(player_rumble.x, player_rumble.y - 20.0f, width, 50.0f);
		CP_Settings_Fill(CP_Color_Create(200, 50, 50, alpha));
		CP_Graphics_DrawRect(player_rumble.x, player_rumble.y - 20.0f, ((float)remaining_hp / 100) * width, 50.0f);
		CP_Image_Draw(alive_hp.image, player_rumble.x, player_rumble.y, alive_hp.size.x, alive_hp.size.y, alpha);
	}
	else
	{
		player_rumble.x = 50.0f;
		player_rumble.y = 50.0f;
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
		CP_Graphics_DrawRect(player_rumble.x, player_rumble.y - 20.0f, width, 50.0f);
		CP_Settings_Fill(CP_Color_Create(200, 50, 50, 255));
		CP_Graphics_DrawRect(player_rumble.x, player_rumble.y - 20.0f, ((float)remaining_hp / 100) * width, 50.0f);
		CP_Image_Draw(alive_hp.image, player_rumble.x, player_rumble.y, alive_hp.size.x, alive_hp.size.y, 255);
	}
}

void enemy_health_bar(int enemy_hp, CP_Vector position)
{
	
	float positionX = CP_System_GetWindowWidth() - 50.0f;
	float positionY = 50.0f;
	float width = CP_System_GetWindowWidth() * 0.30f;
	if (enemys_roll < num_roll && fight)
	{
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, alpha));
		CP_Graphics_DrawRect(positionX - width, positionY - 20.0f, width, 50.0f);
		CP_Settings_Fill(CP_Color_Create(50, 50, 200, alpha));
		CP_Graphics_DrawRect(positionX - width, positionY - 20.0f, ((float)enemy_hp / 20) * width, 50.0f);
		CP_Image_Draw(enemy_alive_hp.image, positionX, positionY, alive_hp.size.x, alive_hp.size.y, alpha);
	}
	else
	{
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
		CP_Graphics_DrawRect(positionX - width, positionY - 20.0f, width, 50.0f);
		CP_Settings_Fill(CP_Color_Create(50, 50, 200, 255));
		CP_Graphics_DrawRect(positionX - width, positionY - 20.0f, ((float)enemy_hp / 20) * width, 50.0f);
		CP_Image_Draw(enemy_alive_hp.image, positionX, positionY, alive_hp.size.x, alive_hp.size.y, 255);
	}
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
	CP_Image_Free(&powerup[strongarm].image);
	CP_Image_Free(&powerup[leatherskin].image);
	CP_Image_Free(&powerup[healthpot].image);
	CP_Image_Free(&desc_panel.image);
	CP_Image_Free(&sword.image);
	CP_Image_Free(&shield.image);
	CP_Image_Free(&clash1.image);
	CP_Image_Free(&clash2.image);
	CP_Image_Free(&enemy_alive_hp.image);
}