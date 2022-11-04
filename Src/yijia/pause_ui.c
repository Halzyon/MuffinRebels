#include "cprocessing.h"
#include "SpriteAnimation/spriteAnimation.h"
CP_Font myFont;   
GameObject popupicon;  
GameObject arrowicon;
GameObject exit_icon;
GameObject settings_icon;

void gamepaused_init(void) {
	myFont = CP_Font_Load("Assets/Kenney Pixel.ttf")
}


void gamepaused_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 255, 0, 255));

	//when settings icon is pressed
	if (CP_Input_Mouselicked())
	{
		if (
			IsAreaClicked(250.0f, 250.0f, 50.0f, 50.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()); //opens settings
			)
	}
	if (
		IsAreaClicked(250.0f, 250.0f, 50.0f, 50.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()); //exits --to change the position
		)
	{
		CP_Engine_Terminate();
	}
}
	//renders settings icon
	
	//renders settings popup

	// exit icon clicked (shut_down) 

	//render text 
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(124, 68, 12, 1)); //original text color
	CP_Settings_TextSize(10.0f); //change the text size
	CP_Font_DrawText("-GAME PAUSED-",50,50 ); //Settings text 

	CP_Settings_Fill(CP_Color_Create(136, 102, 68, 1)); //original text color
	CP_Settings_TextSize(10.0f); //change the text size
	CP_Font_DrawText("Restart",50,50 ); //Settings text 

	CP_Settings_Fill(CP_Color_Create(136, 102, 68, 1)); //original text color
	CP_Settings_TextSize(10.0f); //change the text size
	CP_Font_DrawText("Exit",50,50 ); //Settings text 

	//text hover animation
	if (CP_Input_MouseMoved()) //move over the text 
	{
		CP_Image_Draw(arrowicon, width / 2, height / 2, width / 2, width / 2, 255);
	}
	else
	{
		return 0; //do nothing 
	}

	//when text is clicked --> changes to the respective game state
	if (CP_Input_Mouselicked())
	{
		if (
			IsAreaClicked(250.0f, 250.0f, 50.0f, 50.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()); //opens settings
			)
	}
	if (
		IsAreaClicked(250.0f, 250.0f, 50.0f, 50.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()); //exits --to change the position
		)
	{
		CP_Engine_Terminate();
	}
	


	


}


void gamepaused_shutdown(void) {

	//game continues
}