/*
 * pictures.h
 *
 *  Created on: 20 ���. 2018 �.
 *      Author: Acer
 */

#ifndef INC_PICTURES_H_
#define INC_PICTURES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

	extern const uint8_t dig_size_2[10][22];
	extern const uint8_t dig_size_3[10][57];
	extern const uint8_t menu[33][128];
	extern const char text_menu[4][17];
	//extern  uint8_t cursor;
	extern const uint8_t divider_size_2[];
	extern const uint8_t divider_size_3[];
	extern const uint8_t selection[2][36];

	extern const uint8_t charge[5][16];
	extern const uint8_t light_level[3][18];
	extern const uint8_t stopwatch_icon[];
	extern const uint8_t stepmeter_icon[];
	extern const uint8_t timer_icon[];

	extern const uint8_t playerSoundLevel[4][24];
	extern const uint8_t playButton[32];
	extern const uint8_t pauseButton[32];
	extern const uint8_t stopButton[32];
	extern const uint8_t note5x8[5];
	extern const uint8_t note16x16[32];

	extern const uint8_t calories16x16[];
	extern const uint8_t distance16x16[];
	extern const uint8_t speed16x16[];
	extern const uint8_t steps16x16[];
	extern const uint8_t timeWay16x16[];
	extern const uint8_t stepmeterRun16x16[];
	extern const uint8_t stepmeterStop16x16[];

#ifdef __cplusplus
}
#endif

#endif /* INC_PICTURES_H_ */
