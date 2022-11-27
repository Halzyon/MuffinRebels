/*-------------------------------------------------------------------------------------

	File: encode.c
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	@brief currently only BASE64 encoding and decoding are implemented. 
	Based off http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/


#include "encode.h"

unsigned char* b64_encode(const unsigned char* src, size_t length, size_t *retLength)
{
	unsigned char *ret, *pos;
	const unsigned char *end, *in;
	size_t olength;
	int line_length;

	olength = length * 4 / 3 + 4; // 3-byte blocks to 4 bytes
	olength += olength / 72; // line feeds
	++olength; // null ternimation

	if (olength < length)
	{
		return NULL;
	}

	ret = malloc(olength);

	if (ret == NULL)
	{
		return NULL;
	}

	end = src + length;
	in = src;
	pos = ret;
	line_length = 0;

	while (end - in >= 3)
	{
		*pos++ = b64_table[in[0] >> 2];
		*pos++ = b64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
		*pos++ = b64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
		*pos++ = b64_table[in[2] & 0x3f];
		in += 3;
		line_length += 4;
		if (line_length >= 72)
		{
			*pos++ = '\n';
			line_length = 0;
		}
	}

	if (end - in)
	{
		*pos++ = b64_table[in[0] >> 2];
		if (end - in == 1)
		{
			*pos++ = b64_table[(in[0] & 0x03) << 4];
			*pos++ = '=';
		}
		else
		{
			*pos++ = b64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
			*pos++ = b64_table[(in[1] & 0x0f) << 2];
		}

		*pos++ = '=';
		line_length += 4;
	}

	if (line_length)
	{
		*pos++ = '\n';
	}
	*pos = '\0';
	if (retLength)
	{
		*retLength = pos - ret;
	}
	return ret;
}

unsigned char* b64_decode(const unsigned char* src, size_t length, size_t *retLength)
{
	unsigned char decodeTable[256], * ret, * pos, block[4], tmp;
	size_t i, count, olength;
	int pad = 0;

	memset(decodeTable, 0x80, 256);
	for (i = 0; i < sizeof(b64_table) - 1; i++)
	{
		decodeTable[b64_table[i]] = (unsigned char)i;
	}
	decodeTable['='] = 0;

	count = 0;
	for (i = 0; i < length; i++) 
	{
		if (decodeTable[src[i]] != 0x80)
			count++;
	}

	if (count == 0 || count % 4)
	{
		return NULL;
	}

	olength = count / 4 * 3;
	pos = ret = malloc(olength);
	//ret[olength] = '\0';
	if (ret == NULL)
	{
		return NULL;
	}

	count = 0;

	for (i = 0; i < length; i++) 
	{
		tmp = decodeTable[src[i]];
		if (tmp == 0x80)
		{
			continue;
		}
		if (src[i] == '=')
		{
			pad++;
		}
		block[count] = tmp;
		count++;
		if (count == 4) 
		{
			*pos++ = (block[0] << 2) | (block[1] >> 4);
			*pos++ = (block[1] << 4) | (block[2] >> 2);
			*pos++ = (block[2] << 6) | block[3];
			count = 0;
			if (pad) 
			{
				if (pad == 1)
				{
					pos--;
				}
				else if (pad == 2)
				{
					pos -= 2;
				}
				else 
				{
					// Invalid padding
					free(ret);
					return NULL;
				}
				break;
			}
		}
	}

	*retLength = pos - ret;
	return ret;
}
