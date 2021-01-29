#include "stm32f10x.h"
#include "delay.h"

static __IO u32 ms_counter=0;
void DelayInit()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	
	if (SysTick_Config(SystemCoreClock / 1000))        // ST3.5.0��汾
	{
					/* Capture error */
					while (1);
	}
	          
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;// ʹ�ܵδ�ʱ��  

}
		    								   

void DelayMs(unsigned int nms)
{
	ms_counter=nms;
	while(ms_counter);
}

void DelayS(unsigned int ns)//��ʱ��
{
	unsigned char i;
	for(i=0;i<ns;i++)
	{
		DelayMs(1000);
	}
}

void TimingDelay_Decrement(void)
{
	if (ms_counter != 0x00)
	{ 
		ms_counter--;
	}
}
