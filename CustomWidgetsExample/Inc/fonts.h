/****************************************************************************
Font created by the LCD Vision V1.05 font & image editor/converter
(C) Copyright 2011-2013 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Font name: Courier New
Fixed font width: 7 pixels
Font height: 8 pixels
First character: 0x20
Last character: 0xFF

Exported font data size:
1796 bytes for displays organized as horizontal rows of bytes
1572 bytes for displays organized as rows of vertical bytes.
****************************************************************************/

#ifndef _FONT_H_
#define _FONT_H_

#ifdef __cpluplus
extern "C"
{
#endif

#include <stdint.h>

	typedef struct
	{
		uint8_t width;
		uint8_t height;
		uint16_t first_character;
		uint16_t number_of_characters;
		const uint8_t *data;
	} sFont;

	//extern const uint8_t font5x8[];

	extern const sFont Font5x8;
	extern const sFont FontDigits8x16;

#ifdef __cpluplus
}
#endif

#endif
