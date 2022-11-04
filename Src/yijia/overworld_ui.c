#include "cprocessing.h"
#include "SpriteAnimation/spriteAnimation.h"
GameObject gradientramp; 
GameObject buttonpressed;
GameObject button;
CP_Font myFont;

void overworld_init(void) {
	myFont = CP_Font_Load("Assets/Kenney Pixel.ttf")
}


void overworld_update(void) {
	cp_Graphics_ClearBackground(CP_Color_Create(0,0,0,255))
	
	//render settings text
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(255, 194, 0, 255)); //original text color
	CP_Settings_TextSize(20.0f); //change the text size
	CP_Font_DrawText("WORLD MAP", ); //Settings text 

	//renders gradient 
	CP_Image_Draw(gradientramp, 1037.0f, 197.0f, CP_Image_GetWidth(gradientramp), CP_Image_GetHeight(gradientramp), alpha);
	CP_Settings_BlendMode(CP_BLEND_MULTIPLY); //overlay the gradient 

	// level 1 button
	//text
	//when pressed -->level 1

	// level 2 button
	//text
	//when pressed-->level 2

	// level 3 button
	//text
	//when pressed-->level 3


}


void overworld_shutdown(void) {


}