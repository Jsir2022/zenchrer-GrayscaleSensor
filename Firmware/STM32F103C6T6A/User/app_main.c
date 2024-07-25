#include "app_main.h"
#include "led.h"

uint32_t g_Millisecond=0;

void Main_Init(void)
{
#ifdef DEBUG_MODE
	/* 初始化 EventRecorder 并开启 */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
#endif
	
	LED_Init();
}

void Main_Process(void)
{
	if(g_Millisecond%2==0)
	{
		LED_Ctrl();
	}
}