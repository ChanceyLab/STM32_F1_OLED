/**
  ******************************************************************************
  * File Name          : oled.h
  *
  * ETA:  --------------------------                     
  ******************************************************************************
	**/
/*******************************************************************************
 *******************************************************************************
     ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PB6（SCL）
//              D1   接PB5（SDA）
//              RES  接PB4
//              DC   接PB3              
    ----------------------------------------------------------------
********************************************************************************
********************************************************************************/

#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
    	
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define pi 3.1412926 //定义圆周率
#define OLED_MODE 0
#define SIZE_8X16 16
#define SIZE_6X8 12
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  

/*#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_11)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_10)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_12)*/





#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//SCL-D0
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_5)//SDA-D1
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_4)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_3)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_3)



 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数

void OLED_Refresh_Gram(void);
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear1(void);
void OLED_Clear2(void);
void OLED_Clear3(void);
void OLED_Clear4(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 n);
void OLED_ShowChar(u8 x, u8 y, u8 chr,u8 size,u8 mode);
//void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size,u8 mode);
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size,u8 mode);
//void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_ShowFont48(u8 x,u8 y,u8 fno,u8 mode);//显示48*24的字符
void OLED_DrawCircle(u8 x,u8 y,u8 r);//画圆圈
void OLED_DrawFillCircle(u8 x,u8 y,u8 r);//画实心圆圈
void OLED_DrawHand(u8 x1,u8 y1,u8 R,u8 T,u8 S,u8 n);//画指针 x1 y1表示表盘圆心坐标 R：指针长度 T：指针所指刻度（秒、分为60，时为12）S:指针步长

void OLED_P8x16Ch(unsigned char x, unsigned char y, unsigned int N);
void OLED_P16x32Ch(unsigned char x, unsigned char y, unsigned int N);
/*********************************************
函 数 名：OLED_P32x6Ch(u8 x, u8 y, u16 N)
函数功能：显示相关信息
输入参数：y 显示y的坐标 x 显示x的坐标  N 显示的信息 数组选择
*********************************************/
void OLED_P32x6Ch(u8 x, u8 y, u16 N);
/*********************************************
函 数 名：OLED_P64x6Ch(u8 x, u8 y, u16 N)
函数功能：显示相关信息
输入参数：y 显示y的坐标 x 显示x的坐标  N 显示的信息 数组选择
*********************************************/
void OLED_P64x6Ch(u8 x, u8 y, u16 N);
/*********************************************
函 数 名：OLED_P16x16Ch(u8 x, u8 y, u16 N ,u8 mode)
函数功能：显示相关信息
输入参数：y 显示y的坐标 x 显示x的坐标  N 显示的信息 数组选择 mode:0,反白显示;1,正常显示
*********************************************/
void OLED_P16x16Ch(u8 x, u8 y, u16 N ,u8 mode);
/*********************************************
函 数 名：OLED_P32x32Ch(u8 x, u8 y, u16 N)
函数功能：显示相关信息
输入参数：y 显示y的坐标 x 显示x的坐标  N 显示的信息 数组选择 mode:0,反白显示;1,正常显示
*********************************************/
void OLED_P32x32Ch(u8 x, u8 y, u16 N,u8 mode);
/*********************************************
函 数 名：OLED_P32x32Ch(u8 x, u8 y, u16 N)
函数功能：显示相关信息
输入参数：y 显示y的坐标 x 显示x的坐标  N 显示的信息 数组选择
*********************************************/
void OLED_P64x32Ch(u8 x, u8 y, u16 N);
/*********************************************
函 数 名：OLED_P128x32Ch(u8 x, u8 y, u16 N)
函数功能：显示相关信息
输入参数：y 显示y的坐标 x 显示x的坐标  N 显示的信息 数组选择
*********************************************/
void OLED_P128x32Ch(u8 x, u8 y, u16 N);
/*********************************************
函 数 名：OLED_P64x64Ch(u8 x, u8 y, u16 N)
函数功能：显示相关信息
输入参数：y 显示y的坐标 x 显示x的坐标  N 显示的信息 数组选择
*********************************************/
void OLED_P64x64Ch(u8 x, u8 y, u16 N);
/*********************************************
函 数 名：Draw_BMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
函数功能：显示相关信息
输入参数：x0 显示启使 x坐标   y0 显示启使 y坐标  x1 显示图片最大x坐标，y1 显示图片y坐标 为8  BMP[] 显示你需要的图片数组
*********************************************/
void Draw_BMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);
#endif  
	 



