#include "timer2_int.h"
#include "usart.h"
#include "led.h"

extern u8 Flag_Time_Num_Dot;
extern u8 Flag_Time_IT_1S;
//extern u8 Flag_Time_IT_5S;
u8 Flag_1s = 0;		//һ�붨ʱ���жϱ�־λ
//u8 Flag_5s = 0;		//���붨ʱ���жϱ�־λ

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

    //��ʱ��TIM3��ʼ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx
}
//��ʱ��3�жϷ������
void TIM2_IRQHandler(void)   //TIM3�ж�
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־
		//ϵͳ����ָʾ
		LED0 = ~LED0;
		LED1 = ~LED1;
		//ʱ�����ð�ţ�������ʱ��鿴�������˸��ʾ
		Flag_Time_Num_Dot ++;
		//����1�붨ʱ���жϱ�־λ
		Flag_1s ++;
		//����5�붨ʱ���жϱ�־λ
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












