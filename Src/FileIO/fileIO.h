/*-------------------------------------------------------------------------------------

	File: fileIO.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/



#ifndef IO_H  //header/include guard
#define IO_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "serialization.h"

#define MAXFILES 10
typedef enum
{
    TYPE_0 = 0, // DO NOT CLOSE RANDOMLY
    TYPE_1 = 1, // basically single use
    TYPE_2 = 2
}TYPEFILE;

typedef struct 
{
    FILE *file;
    unsigned char index; // used to identify the age of the file
    TYPEFILE type; // used to identify the importance of a file smaller == higher importance
    unsigned char name[32];
}fileObj;

fileObj *files;
//FILE* files;
bool poolIndex[MAXFILES];
Buffer* buffer;
struct stat sb;
int isInitIO;



/*!
 @brief 
 
 @param filepath 
 @param mode 
 @param name 
 @param type 
 @return int returns the file index for use in other code
*//*______________________________________________________________________*/
int addFile(const unsigned char *filepath, const unsigned char *mode, const unsigned char *name, TYPEFILE type);

/*!
 @brief Get the File object by name
 
 @param name 
 @return FILE* 
*//*______________________________________________________________________*/
FILE *getFile(const unsigned char *name);



/*!
 @brief looks for the file by name and opens if needed.
 
 @param name 
 @return const unsigned char* is the contents of the file
*//*______________________________________________________________________*/
const unsigned char* readFile(const unsigned char *name);


/*!
 @brief looks for and writes to file, opens if needed, creates if needed.
 
 @param name 
 @param input 
 @param mode 
*//*______________________________________________________________________*/
int writeFile(const unsigned char *name, const unsigned char* input, const unsigned char* mode);



/*!
 @brief 
 
*//*______________________________________________________________________*/
void exit_IO(void);

int init_IO(void);



#endif /*IO_H*/
