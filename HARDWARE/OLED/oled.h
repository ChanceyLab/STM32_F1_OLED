/**
  ************************************* Copyright ****************************** 
  *
  *                 (C) Copyright {2021},ChuanQiZhou,China,LN-SY.
  *                            	 All Rights Reserved
  *                              
  *                              By-----SYAU_LAB_501
  *
  *    
  * FileName   : wheeels.c   
  * Version    : v1.0		
  * Author     : Abby_Qi			
  * Date       : 2021-1-29         
  * Description:    
  * Function List:  
  *	1. ....
  *		<version>		: 		
  *		<modify staff>	:
  *		<data>			:
  *		<description>	:  
  *	2. ....
  ******************************************************************************
  **/
#include "stm32f10x.h"
#include "stdlib.h"
#include "sys.h"
#ifndef __OLED_H
#define __OLED_H
#define OLED_MODE 1
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64
//-----------------OLED IIC端口定义-----------------//

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_11)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_10)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_10)


#define OLED_CMD  0		//写命令
#define OLED_DATA 1		//写数据

#define pi 3.1412926 	//定义圆周率

/*当前句柄*/
typedef struct
{
	uint32_t pixel_row_start;		//坐标系下，x -> row
	uint32_t pixel_row_end;			//
	uint32_t pixel_column_start;	//坐标系下，y -> column
	uint32_t pixel_column_end;		//
}_OLEDZoneHandle;

/*界面操作函数参数枚举*/
typedef enum
{
    DIRECT_UP 	 = (uint8_t)0x29,
    DIRECT_DOWN  = (uint8_t)0x2A,
    DIRECT_LEFT	 = (uint8_t)0x26,
    DIRECT_RIGHT = (uint8_t)0x27,	
}_OLEDScrollDirect;



//OLED控制用函数群
void Delay(unsigned  int count);
void Delay_1ms(unsigned int Del_1ms);
void Delay_50ms(unsigned int Del_50ms);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_Write_IIC_Command(u8 IIC_Command);
void OLED_Write_IIC_Data(u8 IIC_Data);
void OLED_Write_IIC_Byte(u8 IIC_Byte);
void OLED_IIC_Wait_Ack(void);
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Refresh(void);
void OLED_Set_Pos(u8 x, u8 y);
//反色显示函数，全域
void OLED_ColorTurn(u8 i);
//反色操作，字符类区域(一般实现)
void OLED_Invert(_OLEDZoneHandle *zone);
//反色操作(以页为单位反色)
void OLED_Invert2(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd);
//屏幕旋转180度
void OLED_DisplayTurn(u8 i);
//水平翻转操作(以页为单位翻转)
void OLED_DisplayTurn_Level(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd);
//一般可以测试OLED显示状况
void OLED_On(void);
//显示中文
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
//显示数字，会靠右边显示，所以提前确认数字多少位，以便显示在正确的位置
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len);
//显示单个字符
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
//显示字符串
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);
//显示图片，从起点根据图片大小
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
//填充图片，指定四点（图片可能变形）
void OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[]);
//显示字符根据ASCII码
void OLED_fuhao_write(u8 x,u8 y,u8 asc);
void OLED_Num_write(u8 x,u8 y,u8 asc) ;
//显示小数并保留N位小数
void OLED_Float(u8 X,u8 Y,double real,u8 N);
//画点
void OLED_DrawPoint(u8 x,u8 y,u8 t);
//擦除点
void OLED_ClearPoint(u8 x,u8 y);
//读点
u8 OLED_ReadPixelPoint(uint32_t pixelX, uint32_t pixelY);
//画线
void OLED_DrawLine(u8 x1, u8 y1, u8 x2,u8 y2,u8 dot);
//画带倾角的线
void OLED_DrawAngleLine(u32 x,u32 y,int du,u32 len,u8 c);
//画实心圆圈
void OLED_DrawFillCircle(u8 x,u8 y,u8 r);
//画指针 x1 y1表示表盘圆心坐标 R：指针长度 T：指针所指刻度（秒、分为60，时为12）S:指针步长 n默认为1
void OLED_DrawArrow(u8 x1,u8 y1,u8 R,u8 T,u8 S,u8 n);
//画1/4圆形
void OLED_DrawPartCircle(u16 x0, u16 y0, u8 r, u8 part);
//画圆
void OLED_DrawCircle(u8 x,u8 y,u8 r);
//改进画圆(避免突起)
void OLED_DrawCircle_Updata(uint32_t xc, uint32_t yc, uint32_t r);
//画椭圆
void OLED_DrawEllipse(uint32_t xc, uint32_t yc, uint32_t a, uint32_t b);
//画方框
void OLED_DrawBlock(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd);
//画矩形
void OLED_DrawRect(uint32_t xStart, uint32_t yStart, uint32_t length, uint32_t width, uint32_t isFill);
//画圆角矩形
void OLED_DrawRoundRectangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 R);
//画三角形
void DrawTriangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 x2, u8 y2);
//局部更新显示（亮起）,此函数可以用OLED_Fill函数代替
void OLED_UpdatePart(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd, uint32_t direct);
//填充区域，根据对角坐标
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);

//停止移屏操作(硬件)
void OLED_MoveStop(void);
//移屏操作(硬件)
void OLED_Move(uint32_t pStart, uint32_t pEnd, _OLEDScrollDirect direct);
//移屏操作(任意区域)？？？
void OLED_Move2(uint32_t pStart, uint32_t pEnd , uint32_t cStart, uint32_t cEnd, _OLEDScrollDirect direct, uint32_t loop);

void OLED_RollDisplay(u16 Roll_GRAM[128][8],u16 Roll_GRAM_TEMP[128][8]);


//未知函数区
void fill_picture(u8 fill_Data);
void OLED_Float2(u8 Y,u8 X,double real,u8 N1,u8 N2);


#endif
