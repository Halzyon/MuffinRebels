/*!
 @file serialization.c
 @author Foong Jun Wei (f.junwei)
 @course CSD1401
 @section A
 @tutorial 
 @date 2022-10-18
 @brief 
*//*______________________________________________________________________*/

#ifndef _MSC_VER // for linux/all other compilers and apparently release mode
#endif

#ifdef _MSC_VER // for visual studios/microsoft compiler
#pragma warning(disable : 4996) // microsoft wants you to use their fopen_s but it is not portable at all
//and not really taht much safer lol
#endif        


#include "serialization.h"
#define IDENTIFIER_INT "int="
#define IDENTIFIER_DBL "dbl="
#define IDENTIFIER_STR "str="
#define IDENTIFIER_EOS '\n'

/*!
 @brief 
 
 @return Buffer* 
*//*______________________________________________________________________*/
Buffer *newBuffer()
{
    Buffer *b = malloc(sizeof(Buffer));
    if (b == NULL)
        return NULL;
    b->data = malloc(DEFAULT_SIZE);
    if (b->data != NULL)
        *b->data = NULL;
    b->size = DEFAULT_SIZE;
    b->next = 0;
    return b;
}

/*!
 @brief 
 
 @param b 
 @param bytes 
*//*______________________________________________________________________*/
void reserveSpace(Buffer *b, size_t bytes)
{
    if (b == NULL)
        return;
    if ((b->next + bytes) > b->size)
    {
        unsigned char* tmp = realloc(b->data, b->size + bytes);
        if (tmp != NULL)
        {
            // in the event that the data is larger than the buffer, doulbe the buffer in size
            b->data = tmp;
            b->size += bytes;
        }
        //free(tmp); // might not need to free as it will be used later on?
    }   
}

/*!
 @brief 
 
 @param b 
*//*______________________________________________________________________*/
void closeBuffer(Buffer *b)
{
    if (b != NULL)
    {
        if (b->data != NULL)
        {
            free(b->data);
        }
        free(b);
    }
}

/*!
 @brief 
 
 @param i 
 @param b 
*//*______________________________________________________________________*/
void serializeInt(int i, Buffer *b)
{
    reserveSpace(b, 16);
    unsigned char tmp[16];
    if (tmp != NULL)
    {
        snprintf(tmp, 16, "int=%X\n", i);
        strncat(b->data, tmp, strlen(tmp));
        b->next += 14 ;
    }
}

/*!
 @brief 
 
 @param d 
 @param b 
*//*______________________________________________________________________*/
void serializeDouble(double d, Buffer *b)
{
    reserveSpace(b, 29);
    unsigned char tmp[29];
    if (tmp != NULL)
    {
        snprintf(tmp, 29, "dbl=%A\n", d);
        strncat(b->data, tmp, strlen(tmp));
        b->next += 27;
    }
}

/*!
 @brief 
 
 @param c 
 @param b 
*//*______________________________________________________________________*/
void serializeString(const unsigned char* c, Buffer *b)
{
    int size = strlen(c) + 1 + 4 + 2;
    reserveSpace(b, size);


    unsigned char *tmp = malloc(size);
    snprintf(tmp, size, "str=%s\n", c);
    if (tmp != NULL)
    {
        strncat(b->data, tmp, size);
    }
    b->next += size;
}

/*!
 @brief 
 
 @param exStruct 
 @param output 
*//*______________________________________________________________________*/
void serialize_Ex(ExampleStruct exStruct, Buffer *output)
{
    serializeInt(exStruct.var1, output);
    //clearBuffer(output);

    serializeDouble(exStruct.var2,output);
    //clearBuffer(output);

    serializeString(exStruct.str, output);
    //clearBuffer(output);
}

/*!
 @brief 
 
 @param file 
 @param ex 
*//*______________________________________________________________________*/
void readSerialize_Ex(const unsigned char* file, ExampleStruct *ex)
{
    int size = strlen(file) + 1;
    unsigned char buffer[5];
    buffer[4] = '\0';
    if (file != NULL)
    {
        for (int i = 0; i < size; ++i)
        {
            buffer[0] = file[i];
            if (i + 1 < size)
                buffer[1] = file[i + 1];
            if (i + 2 < size)
                buffer[2] = file[i + 2];
            if (i + 3 < size)
                buffer[3] = file[i + 3];
            //buffer[4] = '\0';
            //int tmp3 = strcmp(buffer, "int=");
            if (strcmp(buffer, IDENTIFIER_INT) == 0)
            {
                i += 4;
                int j = 0;
                unsigned char tmpBuffer[8];
                while (j < 8 && (i + j + 8) < size)
                {
                    tmpBuffer[j] = file[i + j];
                    ++j;
                }
                ex->var1 = deSerializeInt(tmpBuffer);
                i += j - 1; // skip over what was already used for reading the int
            }
            if (strcmp(buffer, IDENTIFIER_DBL) == 0)
            {
                i += 4;
                int j = 0;
                unsigned char tmpBuffer2[21];
                while (j < 21)
                {
                    tmpBuffer2[j] = file[i + j];
                    ++j;
                }
                ex->var2 = deSerializeDouble(tmpBuffer2);
                i += j - 1; // skip over what was already used for reading the double
            }
            if (strcmp(buffer, IDENTIFIER_STR) == 0)
            {

                
                size_t j, k;
                i += 4;
                j = i;
                
                unsigned char c = file[j];
                while (c != IDENTIFIER_EOS)
                {
                    ++j;
                    c = file[j];
                }
                k = j - i;
                unsigned char* buffer2 = malloc(sizeof(unsigned char) * k);
                for (int x = 0; x < k&& buffer2 != NULL; ++x)
                {
                    if (file[i + x] != NULL)
                        buffer2[x] = file[i + x];
                }
                ex->str = malloc(k);
                if (ex->str != NULL && buffer2 != NULL)
                {
                    for (int y = 0; y < k; ++y)
                    {
                        if (buffer2[y] != NULL)
                            ex->str[y] = buffer2[y];

                        #ifdef _DEBUG
                        #pragma warning(disable : 6386) // its technically out of array but fk it
                            ex->str[y + 1] = '\0'; // debug has like 4 extra unsigned characters at the end, this is to prevent it from borking the data during testing
                        #endif
                    }
                }
                free(buffer2);
            }
        }
    }
    //free(buffer);
}


/*!
 @brief 
 
 @param c 
 @return int 
*//*______________________________________________________________________*/
int deSerializeInt(const unsigned char* c)
{
    unsigned int tmp = (unsigned int)strtoul(c, NULL, 16);
    int tmp2 = (int)strtol(c, NULL, 16);
    int ret;
    if ((tmp2 & 0x80000000) > 0) // check if 2's complement msb is bigger than 8 lel
    {
        ret = tmp;
        ret = -ret;
    }
    else
        ret = tmp;
    return ret;
}

/*!
 @brief 
 
 @param c 
 @return double 
*//*______________________________________________________________________*/
double deSerializeDouble(const unsigned char* c)
{
    return strtod(c, NULL, 16);
}

void serializeMap(char* c, Buffer* b)
{
    int size = strlen(c) + 2;
    reserveSpace(b, size);

    //unsigned char* tmp = malloc(size);
    if (b->data != NULL)
    {
        strncat(b->data, c, size);
    }
    b->next += size;
}


/*!
 @brief 
 
 @param b 
*//*______________________________________________________________________*/
void clearBuffer(Buffer* b)
{
    if (b == NULL)
        return;
    
    if (b->data != NULL)
        free(b->data);
    free(b);
}
