#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include <stdbool.h>

#define LED_ALL_ON  0xffff
#define LED_ALL_OFF 0x0000

typedef union
{
	uint16_t HalfWord;
	struct
	{
		uint8_t L0:1;
		uint8_t L1:1;
		uint8_t L2:1;
		uint8_t L3:1;
		uint8_t L4:1;
		uint8_t L5:1;
		uint8_t L6:1;
		uint8_t L7:1;
		uint8_t L8:1;
		uint8_t L9:1;
		uint8_t :6;
	}Bit;
}LED_Data_type;

extern LED_Data_type LED;

void LED_Init(void);
void LED_Ctrl(void);
void LED_Flash(void);
void LED_GoUp(void);
void LED_GoDown(void);

#endif