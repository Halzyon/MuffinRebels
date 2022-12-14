/*-------------------------------------------------------------------------------------

	File: fileIO.c
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#include "fileIO.h"



#ifndef _MSC_VER // for linux/all other compilers and apparently release mode
#define FILEPATH "Assets/GameData/"
#endif

#ifdef _MSC_VER // for visual studios/microsoft compiler
    #pragma warning(disable : 4996) // microsoft wants you to use their fopen_s but it is not portable at all
                                    //and not really taht much safer lol
#define FILEPATH "Assets/GameData/"
#define _CRTDBG_MAP_ALLOC
#endif       




/*!
 @brief 
 
 @return int 
*//*______________________________________________________________________*/
int init_IO(void)
{
    files = malloc(sizeof(fileObj) * MAXFILES);
    //*poolIndex = malloc(sizeof(bool) * MAXFILES);
    int i = 0;
    while (i < MAXFILES && files != NULL)
    {
        files[i].file = NULL;
        files[i].type = TYPE_2;
        ++i;
    }
    // fputs( "suck my cock", file);
    // fclose(file);
    isInitIO = 1;
    return 0;
}

/*!
 @brief 
 
 @param filepath 
 @param mode 
 @param name 
 @param type 
*//*______________________________________________________________________*/
int addFile(const unsigned char *filepath, const unsigned char* mode, const unsigned char *name, TYPEFILE type)
{
    if (!isInitIO)
    {
        init_IO();
    }
    int i = 0;
    while (i < MAXFILES)
    {
        if (files[i].file == NULL)
        {
            //printf("%s\n", filepath);
            files[i].file = fopen(filepath, mode);
            strcpy(files[i].name, name);
            files[i].index = i;
            files[i].type = type;
            if (files[i].file != NULL)
            {
                //printf("file %s was opened\n", name);
                return i;
            }
            else
            {
                //printf("file %s could not be opened\n", name);
                return MAXFILES + 1;
            }
        }
        else if (files[i].type == TYPE_1)
        {
            if (files[i].file != NULL)
                fclose(files[i].file);
            //printf("%s\n", filepath);
            files[i].file = fopen(filepath, mode);
            strcpy(files[i].name, name);
            files[i].index = i;
            files[i].type = type;
            if (files[i].file != NULL)
            {
                //printf("file %s was opened\n", name);
                return i;
            }
            else
            {
                //printf("file %s could not be opened\n", name);
                return MAXFILES + 1;
            }
        }
        ++i;
    }
    return MAXFILES + 1;
}

/*!
 @brief Get the File object by name
 
 @param name 
 @return FILE* 
*//*______________________________________________________________________*/
FILE *getFile(const unsigned char *name)
{
    if (!isInitIO)
    {
        init_IO();
    }
    int i = 0;
    while (i < MAXFILES)
    {
        if (strcmp(files[i].name, name) == 0)
        {
            //printf("file %s was found\n", name);
            return files[i].file;
        }
        ++i;
    }
    return NULL;
}


/*!
 @brief looks for the file by name and opens if needed.
 
 @param name 
 @return const unsigned char* is the contents of the file
*//*______________________________________________________________________*/
const unsigned char* readFile(const unsigned char *name)
{
    if (!isInitIO)
    {
        init_IO();
    }
    if (getFile(name) != NULL)
    {
        fclose(getFile(name));
    }
    unsigned char tmp1[100] = FILEPATH;
    strcat(tmp1, name);
    //printf("%s\n", tmp1);
    if (addFile(tmp1, "r", name, TYPE_1) != MAXFILES + 1)
    {
        fseek(getFile(name), 0L, SEEK_END); // move to end of file
        size_t sz = ftell(getFile(name)) + 1; // record the index of the final position + 1
        fseek(getFile(name), 0L, SEEK_SET); // move back to start of file
        buffer = newBuffer();
        reserveSpace(buffer, sz * sizeof(unsigned char));
        memset(buffer->data, '\0', sz);
        //buffer = malloc(sz * sizeof(unsigned char));
        //unsigned char* buffer2 = malloc(sz * sizeof(unsigned char));
        size_t tmp = 0;
        if (buffer)
        {
            size_t i = 0;
            //int c = getc(getFile(name));
            while (i < sz)
            {
                //fseek(getFile(name), -1L, SEEK_CUR);
                *(buffer->data + i) = fgetc(getFile(name));
                //fputs(c, getFile(name));
                char tmp2 = *(buffer->data + i);

                ++i;
                //buffer2 = getc(getFile(name));
                tmp = strlen(buffer->data);
            }
            //fseek(getFile(name), 0L, SEEK_SET); // move back to start of file
            //free(buffer2);
            return buffer->data;
        }
    }
    else
    {
        //printf("File not found! Wrong Diretory OR file name!\n");
        return NULL;
    }
    return NULL;
}

/*!
 @brief 
 
 @param name 
 @param input 
 @param mode 
*//*______________________________________________________________________*/
int writeFile(const unsigned char *name, const unsigned char* input, const unsigned char* mode)
{
    if (!isInitIO)
    {
        init_IO();
    }
    if (getFile(name) != NULL)
    {
        fclose(getFile(name));
    }
    unsigned char tmp1[100] = FILEPATH;
    strcat(tmp1, name);
    if (addFile(tmp1, mode, name, TYPE_1) != MAXFILES + 1)
    {
        int tmp = fputs(input, getFile(name));
        fputc('\0', getFile(name));
        return tmp;
    }
    return 0;
}

/*!
 @brief used for freeing up pointers
 
*//*______________________________________________________________________*/
void exit_IO(void)
{
    //for (int i = 0; i < MAXFILES; ++i)
    //{
    //    if (files != NULL && files[i].file != NULL)
    //    {
    //        fclose(files[i].file);
    //        //free(files[i].file);
    //    }
    //}
    fcloseall();
    if (buffer->data != NULL)
        free(buffer->data);
    if (files != NULL) 
        free(files);
    if (buffer != NULL)
        free(buffer);
    isInitIO = 0;
        
}

#define ntest
#ifdef test
int main(void)
{
    init_IO();

    //addFile("../Assets/GameData/data.dat", "r", "data.dat", TYPE_0);
    //getFileI(0);
    //getFile("data.dat");
    //printf("%s\n", readFile("data.dat"));
    //fclose(getFile("data.dat"));
    //printf("%s\n", readFile("data1.dat"));
    //printf("%s\n", readFile("data2.dat"));
    //printf("%s\n", readFile("data3.dat"));
    //printf("%s\n", readFile("data4.dat"));
    //printf("%s\n", readFile("data5.dat"));
    //printf("%s\n", readFile("data6.dat"));
    //printf("%s\n", readFile("data7.dat"));
    //printf("%s\n", readFile("data8.dat"));
    //printf("%s\n", readFile("data9.dat"));
    //printf("%s\n", readFile("data10.dat"));
    // writeFile("data.dat", "this is file 0\n", "w");
    // writeFile("data1.dat", "this is file 1\n", "w");
    // writeFile("data2.dat", "this is file 2\n", "w");
    // writeFile("data3.dat", "this is file 3\n", "w");
    // writeFile("data4.dat", "this is file 4\n", "w");
    // writeFile("data5.dat", "this is file 5\n", "w");
    // writeFile("data6.dat", "this is file 6\n", "w");
    // writeFile("data7.dat", "this is file 7\n", "w");
    // writeFile("data8.dat", "this is file 8\n", "w");
    // writeFile("data9.dat", "this is file 9\n", "w");
    // writeFile("data10.dat", "this is file 10\n", "w");
    // writeFile("data11.dat", "this is file 11\n", "w");
    // writeFile("data12.dat", "this is file 12\n", "w");
    // writeFile("data13.dat","this is file 13\n", "w");
    // writeFile("data14.dat","this is file 14\n", "w");
    // writeFile("data15.dat","this is file 15\n", "w");
    // writeFile("data16.dat","this is file 16\n", "w");

    const unsigned char* tmp = readFile("data12.dat");
    if (tmp != NULL)
        printf("%s\n", tmp);

    /*;
    addFile("Assets/GameData/data3.dat", "w+", "data3.dat", TYPE_0);
    addFile("Assets/GameData/data4.dat", "w+", "data4.dat", TYPE_0);*/

    exit_IO();
    return 0;
}
#endif
