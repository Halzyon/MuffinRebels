/*!
 @file serialization.h
 @author Foong Jun Wei (f.junwei)
 @course CSD1401
 @section A
 @tutorial 
 @date 2022-10-13
 @brief 
*//*______________________________________________________________________*/

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DEFAULT_SIZE 32

typedef struct
{
    char *data;
    size_t next;
    size_t size;
}Buffer;

typedef struct 
{
    int var1;
    double var2;
    char *str;
}ExampleStruct;
void serialize_Ex(ExampleStruct exStruct, Buffer *output);

void serializeInt(int i, Buffer *b);

void serializeDouble(double d, Buffer *b);

void serializeString(const char* c, Buffer *b);

Buffer *newBuffer();

void closeBuffer(Buffer *b);
void clearBuffer(Buffer* b);

void reserveSpace(Buffer *b, size_t bytes);

void readSerialize_Ex(const char * file, ExampleStruct* ex);


int deSerializeInt(const char* c);
double deSerializeDouble(const char* c);

#endif
