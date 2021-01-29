#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define Left_Rocker_X 0
#define Left_Rocker_Y 1

#define Right_Rocker_X 8
#define Right_Rocker_Y 9

#define _3V3_    12
#define _5V_     11
#define _12V_    10

#define Rocker_minimum 0    //ҡ����Сֵ
#define Rocker_maximum 4095 //ҡ�����ֵ

void Adc_Init(void);
u16 Get_Adc(u8 ch);
int Get_battery_volt(int ad); 
int Rocker_Detection_Drive(u8 _L_R_);//�ж�ҡ�˷������
int Get_Adc_Average(int ch,int times);
#endif 













