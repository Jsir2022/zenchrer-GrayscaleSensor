#include "led.h"
#include "main.h"
#include "sensor.h"

LED_Data_type LED;

void LED_Init(void)
{
	LED.HalfWord=LED_ALL_OFF;
	LED_Ctrl();
}

void LED_Flash(void)
{
	LED.HalfWord=LED_ALL_ON;
	LED_Ctrl();
	HAL_Delay(100);
	LED.HalfWord=LED_ALL_OFF;
	LED_Ctrl();
	HAL_Delay(100);
	LED.HalfWord=LED_ALL_ON;
	LED_Ctrl();
	HAL_Delay(100);
	LED.HalfWord=LED_ALL_OFF;
	LED_Ctrl();
}

void LED_GoUp(void)
{
	LED.HalfWord=LED_ALL_OFF;
	LED_Ctrl();
	for(uint8_t i=0;i<TOTAL_SENSOR;i++)
	{
		LED.HalfWord|=1<<i;
		LED_Ctrl();
		HAL_Delay(40);
	}
}

void LED_GoDown(void)
{
	LED.HalfWord=LED_ALL_ON;
	LED_Ctrl();
	for(uint8_t i=0;i<TOTAL_SENSOR;i++)
	{
		LED.HalfWord>>=1;
		LED_Ctrl();
		HAL_Delay(40);
	}
}
	
void LED_Ctrl(void)
{
	LED_Data_type temp;
	temp.HalfWord=~LED.HalfWord;
	
	HAL_GPIO_WritePin(L0_GPIO_Port,L0_Pin,temp.Bit.L0);
	HAL_GPIO_WritePin(L1_GPIO_Port,L1_Pin,temp.Bit.L1);
	HAL_GPIO_WritePin(L2_GPIO_Port,L2_Pin,temp.Bit.L2);
	HAL_GPIO_WritePin(L3_GPIO_Port,L3_Pin,temp.Bit.L3);
	HAL_GPIO_WritePin(L4_GPIO_Port,L4_Pin,temp.Bit.L4);
	HAL_GPIO_WritePin(L5_GPIO_Port,L5_Pin,temp.Bit.L5);
	HAL_GPIO_WritePin(L6_GPIO_Port,L6_Pin,temp.Bit.L6);
	HAL_GPIO_WritePin(L7_GPIO_Port,L7_Pin,temp.Bit.L7);
	HAL_GPIO_WritePin(L8_GPIO_Port,L8_Pin,temp.Bit.L8);
	HAL_GPIO_WritePin(L9_GPIO_Port,L9_Pin,temp.Bit.L9);
}