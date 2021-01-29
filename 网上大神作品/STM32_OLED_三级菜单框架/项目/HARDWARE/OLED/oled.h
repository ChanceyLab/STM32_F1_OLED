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
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB6��SCL��
//              D1   ��PB5��SDA��
//              RES  ��PB4
//              DC   ��PB3              
    ----------------------------------------------------------------
********************************************************************************
********************************************************************************/

#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
    	
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define pi 3.1412926 //����Բ����
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
//-----------------OLED�˿ڶ���----------------  

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



 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���

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
void OLED_ShowFont48(u8 x,u8 y,u8 fno,u8 mode);//��ʾ48*24���ַ�
void OLED_DrawCircle(u8 x,u8 y,u8 r);//��ԲȦ
void OLED_DrawFillCircle(u8 x,u8 y,u8 r);//��ʵ��ԲȦ
void OLED_DrawHand(u8 x1,u8 y1,u8 R,u8 T,u8 S,u8 n);//��ָ�� x1 y1��ʾ����Բ������ R��ָ�볤�� T��ָ����ָ�̶ȣ��롢��Ϊ60��ʱΪ12��S:ָ�벽��

void OLED_P8x16Ch(unsigned char x, unsigned char y, unsigned int N);
void OLED_P16x32Ch(unsigned char x, unsigned char y, unsigned int N);
/*********************************************
�� �� ����OLED_P32x6Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P32x6Ch(u8 x, u8 y, u16 N);
/*********************************************
�� �� ����OLED_P64x6Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P64x6Ch(u8 x, u8 y, u16 N);
/*********************************************
�� �� ����OLED_P16x16Ch(u8 x, u8 y, u16 N ,u8 mode)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ�� mode:0,������ʾ;1,������ʾ
*********************************************/
void OLED_P16x16Ch(u8 x, u8 y, u16 N ,u8 mode);
/*********************************************
�� �� ����OLED_P32x32Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ�� mode:0,������ʾ;1,������ʾ
*********************************************/
void OLED_P32x32Ch(u8 x, u8 y, u16 N,u8 mode);
/*********************************************
�� �� ����OLED_P32x32Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P64x32Ch(u8 x, u8 y, u16 N);
/*********************************************
�� �� ����OLED_P128x32Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P128x32Ch(u8 x, u8 y, u16 N);
/*********************************************
�� �� ����OLED_P64x64Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P64x64Ch(u8 x, u8 y, u16 N);
/*********************************************
�� �� ����Draw_BMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
�������ܣ���ʾ�����Ϣ
���������x0 ��ʾ��ʹ x����   y0 ��ʾ��ʹ y����  x1 ��ʾͼƬ���x���꣬y1 ��ʾͼƬy���� Ϊ8  BMP[] ��ʾ����Ҫ��ͼƬ����
*********************************************/
void Draw_BMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);
#endif  
	 



