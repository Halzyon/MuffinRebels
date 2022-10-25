/*!
 @file lvl_editor.h
 @author Foong Jun Wei (f.junwei)
 @course 
 @section 
 @tutorial 
 @date 2022-10-24
 @brief 
*//*______________________________________________________________________*/

#ifndef LVL_EDITOR_H
#define LVL_EDITOR_H

typedef struct
{
	char* map;

	unsigned char mapWidth;
	unsigned char mapHeight;
}MAP;

void resizeMap(MAP* map, unsigned char width, unsigned char height);


#endif // LVL_EDITOR_H
