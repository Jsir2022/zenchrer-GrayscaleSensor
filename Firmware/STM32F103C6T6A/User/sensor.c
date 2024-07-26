#include "Sensor.h"
#include "app_main.h"
#include "led.h"
#include "btn.h"
#include "flash.h"
#include "com.h"

extern ADC_HandleTypeDef hadc1;

Sensor_Data_type Sensor;
Sensor_Mode_enum Sensor_Mode=SENSOR_RUN;

Button_t BtnFunc;
uint8_t BtnFunc_ReadLevel(void);
void BtnFunc_LongCallback(void *btn);
void BtnFunc_DoubleCallback(void *btn);


void Sensor_Init(void)
{
	//��ʼ������
	Button_Create("BtnFunc",             //��������
                  &BtnFunc,            //�������
                  BtnFunc_ReadLevel,   //������ƽ��⺯���ӿ�
                  GPIO_PIN_RESET);     //������ƽ
	Button_Attach(&BtnFunc, BUTTON_LONG, BtnFunc_LongCallback);
	Button_Attach(&BtnFunc, BUTTON_DOUBLE, BtnFunc_DoubleCallback);
	//��flash��ȡ
	Flash_Read(FLASH_SAVE_START,Sensor.triggerValue,10);
	//����ADC��DMA
	HAL_ADC_Start_DMA(&hadc1,Sensor.adcValue,TOTAL_SENSOR);
}

void Sensor_ClearData(void)
{
	for (uint8_t i = 0; i < TOTAL_SENSOR; i++) 
	{
		Sensor.maxValue[i] = 0;
		Sensor.minValue[i] = ADC_MAX_NUM;
	}
}

void Sensor_Process(void)
{
	switch(Sensor_Mode)
	{
		case SENSOR_RUN:
			LED.HalfWord=LED_ALL_OFF;
			for (uint8_t i = 0; i < TOTAL_SENSOR; i++) 
			{
				LED.HalfWord |= ((Sensor.adcValue[i]>Sensor.triggerValue[i]) << i);
			}
			LED_Ctrl();
			Com_Process();
			break;
		case SENSOR_CALIBRATE:
			for (uint8_t i = 0; i < TOTAL_SENSOR; i++) 
			{
				if(Sensor.maxValue[i] < Sensor.adcValue[i])
				{
					Sensor.maxValue[i]=Sensor.adcValue[i];
				}
				if(Sensor.minValue[i] > Sensor.adcValue[i])
				{
					Sensor.minValue[i]=Sensor.adcValue[i];
				}
				Sensor.triggerValue[i]=((Sensor.maxValue[i]+Sensor.minValue[i]) >> 1);
			}
			break;
	}
	
	//����DMA
	HAL_ADC_Start_DMA(&hadc1, Sensor.adcValue, TOTAL_SENSOR); 
}

uint8_t BtnFunc_ReadLevel(void)
{
    return HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin);
}

void BtnFunc_LongCallback(void *btn)
{
   LED_Flash();
	
}

void BtnFunc_DoubleCallback(void *btn)
{
	switch(Sensor_Mode)
	{
		case SENSOR_RUN:
			LED_GoUp();
			Sensor_ClearData();
			Sensor_Mode = SENSOR_CALIBRATE;
			break;
		case SENSOR_CALIBRATE:
			LED_GoDown();
			Flash_Write(FLASH_SAVE_START,Sensor.triggerValue,10);
			Sensor_Mode = SENSOR_RUN;
			break;
	}
}

