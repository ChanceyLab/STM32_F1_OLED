#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


#define KEY_Rocker_Left      PCin(6)	//PC6 ->��ҡ�˰���
#define KEY_Rocker_Right     PCin(7)  //PC7 ->��ҡ�˰���
#define KEY_Menu_Determine   PCin(8)	//PC8 ->�˵� ȷ�ϰ���
#define KEY_Return           PCin(9)	//PC9 ->���ذ���

#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//��ȡ����2
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//��ȡ����3
#define KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//��ȡ����4



#define KEY1_PRES 1	//KEY1����
#define KEY2_PRES	2	//KEY2����
#define KEY3_PRES	3	//KEY3����
#define KEY4_PRES	4	//KEY4����


void KEY_Init(void);    //IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��
#endif
