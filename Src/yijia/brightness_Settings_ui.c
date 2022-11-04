#include "cprocessing.h"
#include "brightness_Settings_ui.h"
CP_Font myFont;  

void brightness_init() {
	myFont = CP_Font_Load("Assets/Kenney Pixel.ttf"); 
}


void brightness_update() {
	
	CP_Font_Set(myFont);
	
	//render slider 
	void CP_Graphics_DrawRectAdvanced(382.0f, 410.0f, 429.0f, 6.0f, 0.0, 50.0f);
	CP_Settings_Fill(CP_Color_Create(157, 250, 166, 255));

	//render slider icon
	
	//render text
	
	//render bg
	
	//when the slider moves , brightness changes accordingly 
	//if (true)
	//{

	//}
}

void brightness_shutdown() {
	CP_Font_Free(myFont);  

}