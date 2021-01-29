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
//-----------------OLED IIC�˿ڶ���-----------------//

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_11)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_10)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_10)


#define OLED_CMD  0		//д����
#define OLED_DATA 1		//д����

#define pi 3.1412926 	//����Բ����

/*��ǰ���*/
typedef struct
{
	uint32_t pixel_row_start;		//����ϵ�£�x -> row
	uint32_t pixel_row_end;			//
	uint32_t pixel_column_start;	//����ϵ�£�y -> column
	uint32_t pixel_column_end;		//
}_OLEDZoneHandle;

/*���������������ö��*/
typedef enum
{
    DIRECT_UP 	 = (uint8_t)0x29,
    DIRECT_DOWN  = (uint8_t)0x2A,
    DIRECT_LEFT	 = (uint8_t)0x26,
    DIRECT_RIGHT = (uint8_t)0x27,	
}_OLEDScrollDirect;



//OLED�����ú���Ⱥ
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
//��ɫ��ʾ������ȫ��
void OLED_ColorTurn(u8 i);
//��ɫ�������ַ�������(һ��ʵ��)
void OLED_Invert(_OLEDZoneHandle *zone);
//��ɫ����(��ҳΪ��λ��ɫ)
void OLED_Invert2(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd);
//��Ļ��ת180��
void OLED_DisplayTurn(u8 i);
//ˮƽ��ת����(��ҳΪ��λ��ת)
void OLED_DisplayTurn_Level(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd);
//һ����Բ���OLED��ʾ״��
void OLED_On(void);
//��ʾ����
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
//��ʾ���֣��῿�ұ���ʾ��������ǰȷ�����ֶ���λ���Ա���ʾ����ȷ��λ��
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len);
//��ʾ�����ַ�
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
//��ʾ�ַ���
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);
//��ʾͼƬ����������ͼƬ��С
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
//���ͼƬ��ָ���ĵ㣨ͼƬ���ܱ��Σ�
void OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[]);
//��ʾ�ַ�����ASCII��
void OLED_fuhao_write(u8 x,u8 y,u8 asc);
void OLED_Num_write(u8 x,u8 y,u8 asc) ;
//��ʾС��������NλС��
void OLED_Float(u8 X,u8 Y,double real,u8 N);
//����
void OLED_DrawPoint(u8 x,u8 y,u8 t);
//������
void OLED_ClearPoint(u8 x,u8 y);
//����
u8 OLED_ReadPixelPoint(uint32_t pixelX, uint32_t pixelY);
//����
void OLED_DrawLine(u8 x1, u8 y1, u8 x2,u8 y2,u8 dot);
//������ǵ���
void OLED_DrawAngleLine(u32 x,u32 y,int du,u32 len,u8 c);
//��ʵ��ԲȦ
void OLED_DrawFillCircle(u8 x,u8 y,u8 r);
//��ָ�� x1 y1��ʾ����Բ������ R��ָ�볤�� T��ָ����ָ�̶ȣ��롢��Ϊ60��ʱΪ12��S:ָ�벽�� nĬ��Ϊ1
void OLED_DrawArrow(u8 x1,u8 y1,u8 R,u8 T,u8 S,u8 n);
//��1/4Բ��
void OLED_DrawPartCircle(u16 x0, u16 y0, u8 r, u8 part);
//��Բ
void OLED_DrawCircle(u8 x,u8 y,u8 r);
//�Ľ���Բ(����ͻ��)
void OLED_DrawCircle_Updata(uint32_t xc, uint32_t yc, uint32_t r);
//����Բ
void OLED_DrawEllipse(uint32_t xc, uint32_t yc, uint32_t a, uint32_t b);
//������
void OLED_DrawBlock(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd);
//������
void OLED_DrawRect(uint32_t xStart, uint32_t yStart, uint32_t length, uint32_t width, uint32_t isFill);
//��Բ�Ǿ���
void OLED_DrawRoundRectangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 R);
//��������
void DrawTriangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 x2, u8 y2);
//�ֲ�������ʾ������,�˺���������OLED_Fill��������
void OLED_UpdatePart(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd, uint32_t direct);
//������򣬸��ݶԽ�����
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);

//ֹͣ��������(Ӳ��)
void OLED_MoveStop(void);
//��������(Ӳ��)
void OLED_Move(uint32_t pStart, uint32_t pEnd, _OLEDScrollDirect direct);
//��������(��������)������
void OLED_Move2(uint32_t pStart, uint32_t pEnd , uint32_t cStart, uint32_t cEnd, _OLEDScrollDirect direct, uint32_t loop);

void OLED_RollDisplay(u16 Roll_GRAM[128][8],u16 Roll_GRAM_TEMP[128][8]);


//δ֪������
void fill_picture(u8 fill_Data);
void OLED_Float2(u8 Y,u8 X,double real,u8 N1,u8 N2);


#endif
