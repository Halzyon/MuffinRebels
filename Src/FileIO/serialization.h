/*-------------------------------------------------------------------------------------

	File: serialization.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DEFAULT_SIZE 32

typedef struct
{
    unsigned char *data;
    size_t next;
    size_t size;
}Buffer;

typedef struct 
{
    int var1;
    double var2;
    unsigned char *str;
}ExampleStruct;
void serialize_Ex(ExampleStruct exStruct, Buffer *output);

void serializeInt(int i, Buffer *b);

void serializeDouble(double d, Buffer *b);

void serializeString(const unsigned char* c, Buffer *b);

Buffer *newBuffer();

void closeBuffer(Buffer *b);
void clearBuffer(Buffer* b);

void reserveSpace(Buffer *b, size_t bytes);

void readSerialize_Ex(const unsigned char * file, ExampleStruct* ex);


int deSerializeInt(const unsigned char* c);
double deSerializeDouble(const unsigned char* c);

void serializeMap(char* c, Buffer* b);

#endif
