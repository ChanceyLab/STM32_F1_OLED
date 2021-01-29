#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer2_int.h"
#include "timer3_int.h"
#include "oled.h"
#include "bmp.h"
/* home->alarm->set->map */
#include "math.h"
#include "io.h"
#include "led.h"
#include "key.h"
#include "rtc.h"

#define TIME_NUM1_LEFT 2
#define TIME_NUM1_RIGHT 24
#define TIME_NUM2_LEFT 33
#define TIME_NUM2_RIGHT 55
#define TIME_NUM3_LEFT 73
#define TIME_NUM3_RIGHT 95
#define TIME_NUM4_LEFT 102
#define TIME_NUM4_RIGHT 124
//Ԥ������ʾ����λ��
#define MID_ROW 63
#define MID_COL 31
//Ԥ����ָ�볤��
#define LEN_ARR_HOR 20
#define LEN_ARR_MIN 26 
#define LEN_ARR_SEC 32 

//ʱ����ʾģʽ�������������и���(Ĭ��0������ʾģʽ)
u8 Time_Mode = 0;

//ʱ�����ð��ˢ�±�־λ
u8 Flag_Time_Num_Dot = 0;
//һ��ˢ��ʱ���־λ
u8 Flag_Time_IT_1S = 0;
//����ˢ��ʱ���־λ
//u8 Flag_Time_IT_5S = 0;
//��¼��ʱ���жϱ�־λ���±�־λ
u8 key = 0;
//����ʱ�������̬�����������жϺ�ʱ����
u8 Time_Now_Min_G;
u8 Time_Now_Min_S;
u8 Time_Now_Hor_G;
u8 Time_Now_Hor_S;

//����ʱ�侲̬�����������жϺ�ʱ����ָ��
u8 Time_Now_Sec = 0;
u8 Time_Now_Min = 0;
u8 Time_Now_Hor = 0;

//���̽Ƕȱ���0-360��u16
//��ֱ����Ϊ0��˳ʱ�����
//u16 Time_Dish_Arrow_Angle_H = 0;
//u16 Time_Dish_Arrow_Angle_M = 0;
//u16 Time_Dish_Arrow_Angle_S = 0;

void Time_Num_Dot_Display(void)
{
    //ð����ʾ��ͨ����ʱ��������ʾ
    if(Flag_Time_Num_Dot == 1)
    {
        //ð����ʾ����ֲ�ˢ��
        OLED_Fill(58,14,68,54,0);
    }
    else if (Flag_Time_Num_Dot == 2)
    {
        OLED_DrawFillCircle(63,19,2);
        OLED_DrawFillCircle(63,52,2);
    }
}
void Time_Num_Display(void)
{
    OLED_ShowPicture(TIME_NUM1_LEFT,8,22,56,gImage_0[calendar.hour/10],1);
    OLED_ShowPicture(TIME_NUM2_LEFT,8,22,56,gImage_0[calendar.hour%10],1);
    OLED_ShowPicture(TIME_NUM3_LEFT,8,22,56,gImage_0[calendar.min/10],1);
    OLED_ShowPicture(TIME_NUM4_LEFT,8,22,56,gImage_0[calendar.min%10],1);
}
void Time_Dish_Display(void)
{
    //�����ϻ���0�ȷ�����ֵĶ��һ��һ���Ե�������������ˢ��
	OLED_DrawLine(MID_ROW,0,MID_ROW,MID_COL,0);
	//����
    OLED_DrawEllipse(MID_ROW,MID_COL,62,31);
    //�̶�
    OLED_DrawLine( 64, 0, 64, 3,1);
    OLED_DrawLine( 64,64, 64,61,1);
    OLED_DrawLine(  0,32,  3,32,1);
    OLED_DrawLine(128,32,123,32,1);
    //���ĵ�
    OLED_DrawFillCircle(MID_ROW,MID_COL,3);
	
    //����ˢ�� 
    OLED_DrawAngleLine(MID_ROW,MID_COL,calendar.sec * 6,LEN_ARR_SEC,1);
    //��������ϴ�
	if (calendar.sec == 0)
	{
		OLED_DrawAngleLine(MID_ROW,MID_COL,59 * 6,LEN_ARR_SEC,0);
	}
	else
	{
		OLED_DrawAngleLine(MID_ROW,MID_COL,(calendar.sec - 1) * 6,LEN_ARR_SEC,0);
	}
    
	//����ˢ��
    OLED_DrawAngleLine(MID_ROW,MID_COL,calendar.min * 6,LEN_ARR_MIN,1);
	//��������ϴ�
	if (calendar.min == 0)
	{
		OLED_DrawAngleLine(MID_ROW,MID_COL,59 * 6,LEN_ARR_MIN,0);
	}
	else
	{
		OLED_DrawAngleLine(MID_ROW,MID_COL,(calendar.min - 1) * 6,LEN_ARR_MIN,0);
	}
    
	//ʱ��ˢ��
    OLED_DrawAngleLine(MID_ROW,MID_COL,calendar.hour % 12 * 30,LEN_ARR_HOR,1);
	//ʱ������ϴ�
	if (calendar.hour % 12 == 0)
	{
		OLED_DrawAngleLine(MID_ROW,MID_COL,11 * 30,LEN_ARR_HOR,0);
	}
	else
	{
		OLED_DrawAngleLine(MID_ROW,MID_COL,(calendar.hour - 1) % 12 * 30,LEN_ARR_HOR,0);
	}
}


void Time_Num_Updata(void);
/*****************************UI�л���������*****************************/
void BMP_HomeToAlarm(void);



int main(void)
{
    //u8 SET[2][4] = {{"ON "},{"OFF"}};
    delay_init();	    	 	//��ʱ������ʼ��
    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);	 		//���ڳ�ʼ��Ϊ115200
    delay_ms(1000);				//�ϵ���ʱ�������ϵ�׼���׶�
    TIM2_Int_Init(4999,7199);	//72000000/(7199+1)/(5000) = 2hz
    TIM3_Int_Init(499,7199);	//72000000/(7199+1)/(500) = 20hz
    RTC_Init();	  				//RTC��ʼ��
    //IO_Init();
    LED_Init();			     	//LED�˿ڳ�ʼ��
    KEY_Init();          		//��ʼ���밴�����ӵ�Ӳ���ӿ�
    OLED_Init();
    OLED_Refresh();				//��ʾһ���ַ���֮����Ҫ�����ˢ���Դ�
    OLED_Clear();
	//Upadta Flag
	Time_Now_Min_G = calendar.min % 10;
	Time_Now_Min_S = calendar.min / 10;
	Time_Now_Hor_G = calendar.hour % 10;
	Time_Now_Hor_S = calendar.hour / 10;
//	printf("%d-%d-%d-%d\r\n",Time_Now_Min_G,Time_Now_Min_S,Time_Now_Hor_G,Time_Now_Hor_S);
//	while(1);
	
	//�Լ��ô���
    while(1)
    {
		//������
		OLED_DrawBMP(0,0,128,8,gImage_home);
		switch (key)
        {
        case 1:
			OLED_DrawBMP(0,0,128,8,gImage_set);
            break;
        case 2:
            //���ɶ���
            BMP_HomeToAlarm();
            //��ʱһ��ʱ�����ʱ����Ϣ
            delay_ms(800);
			Time_Num_Display();
            OLED_Fill(0,0,128,64,0);
            while(1)
            {
                if(Time_Mode == 0)
                {
                    OLED_Refresh();
                    //���ֽ���
                    Time_Num_Updata();
                    Time_Num_Display();
                    Time_Num_Dot_Display();
                }
                else
                {
                    OLED_Refresh();
                    //���̽���
                    Time_Dish_Display();
                }
				if(key == 1)
				{
					break;
				}
            }
            break;
        case 3:
            break;
        }


    }
}

/***********
  * @BRIEF :[ ����ʱ����º��� ]
  * @NOTE  :-
			-
  * @INPUT :>
			>
  * @RETURN:void
  *
  * @DATE  :2021/01/29
  * @DESIGN:
***********/
void Time_Num_Updata(void)
{
    u8 i;
    //��λһ���
    if (Time_Now_Min_G != calendar.min % 10 &&
		Time_Now_Min_S != calendar.min / 10 &&
		Time_Now_Hor_G != calendar.hour % 10 &&
		Time_Now_Hor_S != calendar.hour / 10 )
    {
        //��ʼ����,����
        for(i = 60; i > 8; i -= 3)
        {
            //������������������ע���Ⱥ�
            OLED_ShowPicture(TIME_NUM4_LEFT,i,22,56,gImage_0[calendar.min %10],1);
            OLED_ShowPicture(TIME_NUM3_LEFT,i,22,56,gImage_0[calendar.min /10],1);
            OLED_ShowPicture(TIME_NUM2_LEFT,i,22,56,gImage_0[calendar.hour%10],1);
            OLED_ShowPicture(TIME_NUM1_LEFT,i,22,56,gImage_0[calendar.hour/10],1);
            OLED_Fill(TIME_NUM4_LEFT,0,TIME_NUM4_RIGHT,i - 1,0);
            OLED_Fill(TIME_NUM3_LEFT,0,TIME_NUM3_RIGHT,i - 1,0);
            OLED_Fill(TIME_NUM2_LEFT,0,TIME_NUM2_RIGHT,i - 1,0);
            OLED_Fill(TIME_NUM1_LEFT,0,TIME_NUM1_RIGHT,i - 1,0);
            OLED_Refresh();
        }
    }
    //��λһ���
    else if(Time_Now_Min_G != calendar.min % 10 &&
            Time_Now_Min_S != calendar.min / 10 &&
            Time_Now_Hor_G != calendar.hour % 10)
    {
        //��ʼ����,����
        for(i = 60; i > 8; i -= 3)
        {
            //������������������ע���Ⱥ�
            OLED_ShowPicture(TIME_NUM4_LEFT,i,22,56,gImage_0[calendar.min%10],1);
            OLED_ShowPicture(TIME_NUM3_LEFT,i,22,56,gImage_0[calendar.min/10],1);
            OLED_ShowPicture(TIME_NUM2_LEFT,i,22,56,gImage_0[calendar.hour%10],1);
            OLED_Fill(TIME_NUM4_LEFT,0,TIME_NUM4_RIGHT,i - 1,0);
            OLED_Fill(TIME_NUM3_LEFT,0,TIME_NUM3_RIGHT,i - 1,0);
            OLED_Fill(TIME_NUM2_LEFT,0,TIME_NUM2_RIGHT,i - 1,0);
            OLED_Refresh();
        }
    }
    //��λһ���
    else if(Time_Now_Min_G != calendar.min % 10 &&
            Time_Now_Min_S != calendar.min / 10)
    {
        //��ʼ����,����
        for(i = 60; i > 8; i -= 3)
        {
            //������������������ע���Ⱥ�
            OLED_ShowPicture(TIME_NUM4_LEFT,i,22,56,gImage_0[calendar.min%10],1);
            OLED_ShowPicture(TIME_NUM3_LEFT,i,22,56,gImage_0[calendar.min/10],1);
            OLED_Fill(TIME_NUM4_LEFT,0,TIME_NUM4_RIGHT,i - 1,0);
            OLED_Fill(TIME_NUM3_LEFT,0,TIME_NUM3_RIGHT,i - 1,0);
            OLED_Refresh();
        }
    }
    //һλ��
    else if(Time_Now_Min_G != calendar.min % 10)
    {
        //��ʼ����,����
        for(i = 60; i > 8; i -= 3)
        {
            //������������������ע���Ⱥ�
            OLED_ShowPicture(TIME_NUM4_LEFT,i,22,56,gImage_0[calendar.min%10],1);
            OLED_Fill(TIME_NUM4_LEFT,0,TIME_NUM4_RIGHT,i - 1,0);
            OLED_Refresh();
        }
    }
	Time_Now_Min_G = calendar.min % 10;
	Time_Now_Min_S = calendar.min / 10;
	Time_Now_Hor_G = calendar.hour % 10;
	Time_Now_Hor_S = calendar.hour / 10;
}

/***********
  * @BRIEF :[ͼ��UI�л�����]
  * @NOTE  :-�л������д��Ż�
			-
  * @INPUT :>
			>
  * @RETURN:void
  *
  * @DATE  :2021/01/29
  * @DESIGN:
***********/
void BMP_HomeToAlarm(void)
{
    u8 i;
	OLED_Fill(0,0,128,64,0);
	OLED_Refresh();
    //��ʼ����,����
    for(i = 128; i > 0; i -= 4)
    {
        /*ԭͼ���ƣ���ͼ���ƣ����ԭͼ��������
        if(i % 2 == 0)
        {
            OLED_ShowPicture(0,64 - i / 2,128,64,gImage_home,1);
        }
        OLED_ShowPicture(i,0,128,64,gImage_alarm,1);
        OLED_Fill(0,0,i,64 - i / 2,0);
        OLED_Refresh();
        */
        //ԭͼ��������ͼ���ƣ����ԭͼ��������
        OLED_Fill(0,0,i -1,8,0);
        OLED_ShowPicture(i,0,128,64,gImage_alarm,1);
        OLED_Refresh();
    }
}




