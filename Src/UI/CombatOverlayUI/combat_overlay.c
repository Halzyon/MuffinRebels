#include "cprocessing.h"
#include "../UtilsUI/ui_utils.h"
#include "../DiceUI/dice_ui.h"
#include "combat_overlay.h"

asset inventory;
asset dice_button;
asset powerup_button;

void combat_init(void)
{
	inventory.img = CP_Image_Load("Assets/combat_overlay_ui/grey.png");
	dice_button.img = CP_Image_Load("Assets/combat_overlay_ui/dice_3D_detailed.png");
	powerup_button.img = CP_Image_Load("Assets/combat_overlay_ui/sword.png");
	dice_button.size.x = CP_Image_GetWidth(dice_button.img);
	dice_button.size.y = CP_Image_GetHeight(dice_button.img);
	powerup_button.size.x = CP_Image_GetWidth(powerup_button.img);
	powerup_button.size.y = CP_Image_GetHeight(powerup_button.img);
	inventory.size.x = CP_Image_GetWidth(inventory.img);
	inventory.size.y = CP_Image_GetHeight(inventory.img);

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
}

void buttons(void)
{
	float buttons_centerpointX = CP_System_GetWindowWidth() - 200;
	float buttons_centerpointY = CP_System_GetWindowHeight() - 100;
	dice_button.pos.x = buttons_centerpointX + 100;
	dice_button.pos.y = powerup_button.pos.y = buttons_centerpointY;
	powerup_button.pos.x = buttons_centerpointX - 100;
	CP_Image_Draw(dice_button.img, dice_button.pos.x, dice_button.pos.y, dice_button.size.x, dice_button.size.y, 255);
	CP_Image_Draw(powerup_button.img, powerup_button.pos.x, powerup_button.pos.y, powerup_button.size.x, powerup_button.size.y, 255);
	if ((mouse_in_rect(dice_button.pos.x, dice_button.pos.y, dice_button.size.x, dice_button.size.y) == 1) && CP_Input_MouseClicked())
	{
		CP_Image_Draw(inventory.img, buttons_centerpointX - 150, buttons_centerpointY - 200, (inventory.size.x * 15), (inventory.size.y * 5), 255);
		generate_dice(6, e_std_D6, buttons_centerpointX - 200, buttons_centerpointY - 200);
	}
}