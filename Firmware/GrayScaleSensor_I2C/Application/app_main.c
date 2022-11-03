/**
 * @file app_main.c
 * @author zenchrer (zenchrer@qq.com)
 * @brief
 * @version 1.0
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "app_main.h"
#include "main.h"
#include "stm32g0xx_it.h"
#include "gpio.h"
#include "adc.h"
#include "i2c.h"
// include the header file
#include "button_behavior.h"
#include "led.h"
#include "Sensor.h"
#include "flash.h"

uint8_t Loop_5msTime_Flag = 0;   // 5ms��ѯʱ��
uint8_t Loop_10msTime_Flag = 0;  // 10ms��ѯʱ��
uint8_t Loop_20msTime_Flag = 0;  // 20ms��ѯʱ��
uint8_t Loop_100msTime_Flag = 0; // 100ms��ѯʱ��
uint8_t Loop_500msTime_Flag = 0; // 500ms��ѯʱ��

uint8_t __setid_tick = 0;
uint8_t __sensor_id = 1;

// I2C Pins
// RX = SDA   TX = SCL
uint8_t aRxBuffer[4] = {0};
uint8_t aTxBuffer[4] = {0};
/**
 * @brief the main initialization function
 *
 */
void app_main_init(void)
{
    Button_init();
    HAL_ADC_Start_DMA(&hadc1, adcValues, SENSOR_NUM);
    HAL_I2C_Slave_Receive_DMA(&hi2c1, aRxBuffer, 4); // open i2c DMA receive.
    led_all_off();
    STMFLASH_Read(FLASH_SECTOR15_START, (uint32_t *)splitThresholds, sizeof(splitThresholds));
}

/**
 * @brief the main loop function
 *
 */
void app_main_loop(void)
{
    if (Loop_5msTime_Flag) // 5ms��ѯ
    {
        Loop_5msTime_Flag = 0; //�����־λ
        led_loop();
    }
    if (Loop_10msTime_Flag) // 10ms��ѯ
    {
        Loop_10msTime_Flag = 0; //�����־λ
    }
    if (Loop_20msTime_Flag) // 20ms��ѯ
    {
        Loop_20msTime_Flag = 0; //�����־λ
        Button_Process();
    }
    if (Loop_100msTime_Flag) // 100ms��ѯ
    {
        Loop_100msTime_Flag = 0; //�����־λ
        if (__setid_tick > 0) {  // start set id timer tick
            __setid_tick--;      //
            if (__setid_tick == 0) {
                Sensor_Mode = SENSOR_MODE_RUN;
            }
        }
    }
    if (Loop_500msTime_Flag) // 500ms��ѯ
    {
        Loop_500msTime_Flag = 0; //�����־λ
    }
}

void app_tick_handler(void)
{
    static uint32_t time;
    time++;
    if (0 == (time % 5)) {
        Loop_5msTime_Flag = 1;
    }
    if (0 == (time % 10)) {
        Loop_10msTime_Flag = 1;
    }
    if (0 == (time % 20)) {
        Loop_20msTime_Flag = 1;
    }
    if (0 == (time % 100)) {
        Loop_100msTime_Flag = 1;
    }
    if (0 == (time % 500)) {
        Loop_500msTime_Flag = 1;
    }
}

// void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//     if (hi2c == &hi2c1) {
//         // i2c1GetDataCount++;
//         uint8_t reg;
//         reg = aRxBuffer[0]; // check master send's command and then receive DMA again. if it need read, put the transmit DMA��
//         switch (reg) {
//             case 0xAA: // frequency reg
//                 // audio_frequecy = aRxBuffer[1];
//                 HAL_I2C_Slave_Receive_DMA(&hi2c1, aRxBuffer, 4);
//                 break;
//             case 0x03: {
//                 // L_Level = aRxBuffer[1];
//                 // R_Level = aRxBuffer[2];
//                 HAL_I2C_Slave_Receive_DMA(&hi2c1, aRxBuffer, 4);
//                 break;
//             }
//             case 0xEE: { // 0xFE���Լ�����ģ�����STM32 �ӻ���Ҫ�����ݣ������������Ϸ���DMA������
//                 aTxBuffer[0] = Sensor_TransData_Digital;
//                 // aTxBuffer[1] = audio_frequecy;
//                 // aTxBuffer[2] = 0x33;
//                 HAL_I2C_Slave_Transmit_DMA(&hi2c1, aTxBuffer, 3);
//                 break;
//             }
//             default:
//                 //��ֹ������û�ж�������ݣ�����I2C������
//                 HAL_I2C_Slave_Receive_DMA(&hi2c1, aRxBuffer, 4);
//                 break;
//         }

//        for (uint8_t i = 0; i < 4; i++) {
//            // ��ջ���
//            aRxBuffer[i] = 0;
//        }
//    }
//}

//����ص�����Ҳ�ر���Ҫ����������һ��Ҫת�ؽ��ա�
// void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//    if (hi2c == &hi2c1) {
//        HAL_I2C_Slave_Receive_DMA(&hi2c1, aRxBuffer, 4);
//    }
//}
