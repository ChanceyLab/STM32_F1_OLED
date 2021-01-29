#include "timer2_int.h"
#include "usart.h"
#include "led.h"

extern u8 Flag_Time_Num_Dot;
extern u8 Flag_Time_IT_1S;
//extern u8 Flag_Time_IT_5S;
u8 Flag_1s = 0;		//一秒定时器中断标志位
//u8 Flag_5s = 0;		//五秒定时器中断标志位

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

    //定时器TIM3初始化
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


    TIM_Cmd(TIM2, ENABLE);  //使能TIMx
}
//定时器3中断服务程序
void TIM2_IRQHandler(void)   //TIM3中断
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志
		//系统运行指示
		LED0 = ~LED0;
		LED1 = ~LED1;
		//时间界面冒号，检测进入时间查看界面才闪烁显示
		Flag_Time_Num_Dot ++;
		//叠加1秒定时器中断标志位
		Flag_1s ++;
		//叠加5秒定时器中断标志位
//		Flag_5s ++;
		if(Flag_Time_Num_Dot >2)
		{
			Flag_Time_Num_Dot = 0;
		}
		if(Flag_1s == 2)
		{
			Flag_Time_IT_1S = 1;
			Flag_1s = 0;
		}	
//		if(Flag_5s == 10)
//		{
//			Flag_Time_IT_5S = 1;
//		}
//		if(Flag_5s == 20)
//		{
//			Flag_Time_IT_5S = 2;
//			Flag_5s = 0;

//		}	
		//printf("TIM2_IT!!!\r\n");
    }
}












