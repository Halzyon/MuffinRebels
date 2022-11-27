/*-------------------------------------------------------------------------------------

	File: encode.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	@brief currently only BASE64 encoding and decoding are implemented. 
	Based off http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#ifndef ENCODE_H
#define ENCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const unsigned char b64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char* b64_encode(const unsigned char* src, size_t length, size_t *outLength);

unsigned char* b64_decode(const unsigned char* src, size_t length, size_t *outLength);

#endif /*ENCODE_H*/