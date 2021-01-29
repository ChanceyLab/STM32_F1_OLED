#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


#define KEY_Rocker_Left      PCin(6)	//PC6 ->左摇杆按键
#define KEY_Rocker_Right     PCin(7)  //PC7 ->右摇杆按键
#define KEY_Menu_Determine   PCin(8)	//PC8 ->菜单 确认按键
#define KEY_Return           PCin(9)	//PC9 ->返回按键

#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//读取按键3
#define KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//读取按键4



#define KEY1_PRES 1	//KEY1按下
#define KEY2_PRES	2	//KEY2按下
#define KEY3_PRES	3	//KEY3按下
#define KEY4_PRES	4	//KEY4按下


void KEY_Init(void);    //IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数
#endif
