#include "app_main.h"
#include "led.h"
#include "btn.h"
#include "sensor.h"

uint32_t g_Millisecond=0;
bool g_SysTickFlag=false;

void Main_Init(void)
{
#ifdef DEBUG_MODE
	/* 初始化 EventRecorder 并开启 */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
#endif
	
	LED_Init();
	Sensor_Init();
}

void Main_Process(void)
{
	if(g_SysTickFlag==true)
	{
		if(g_Millisecond%20==0)
		{
			Button_Process();
		}
		if(g_Millisecond%SCAN_TRAS==0)
		{
			Sensor_Process();
		}
		g_SysTickFlag=false;
	}
}
