#include "com.h"
#include "app_main.h"
#include "led.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;

void print_binary(uint32_t number) {
    // 打印前导 '0b' 表示二进制
    printf("0b");

    // 打印 32 位二进制数
    for (int i = 31; i >= 0; i--) {
        // 根据每一位的值打印 '0' 或 '1'
				if((number >> i) & 1)
				{
					putchar('1');
				}
				else
				{
					putchar('0');
				}
    }

    putchar('\n');
}

void Com_Process(void)
{
	uint8_t TX_Buff[4];
	
	TX_Buff[0]=COM_ADDR;
	TX_Buff[1]=LED.HalfWord>>8;
	TX_Buff[2]=LED.HalfWord;
	TX_Buff[3]='C';
	
	HAL_UART_Transmit(&huart1,TX_Buff,4,1);
}