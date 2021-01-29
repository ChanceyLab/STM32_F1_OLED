#ifndef _OLED_H
#define _OLED_H
#include "sys.h"


/**-----------------------------------IIC---------------------------------------
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              SDA  ��PC11
//              SCL  ��PC12       
//              ----------------------------------------------------------------
**/
/**********IIC �ӿ�*************/
#define OLED_IIC_SCL  PBout(6) //SCL   ����ʱ��
#define OLED_IIC_SDA  PBout(7) //SDA	  ��������

/**-----------------------------------SPI---------------------------------------
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB6��SCL��
//              D1   ��PB5��SDA��
//              RES  ��PB4
//              DC   ��PB3        
//              ----------------------------------------------------------------
**/
/**********SPI �ӿ�**************/
//#define OLED_RST_Clr() PBout(3)=0    //RST
//#define OLED_RST_Set() PBout(3)=1    //RST
//#define OLED_RS_Clr() PAout(15)=0    //DC
//#define OLED_RS_Set() PAout(15)=1    //DC
//#define OLED_SCLK_Clr()  PBout(5)=0  //SCL
//#define OLED_SCLK_Set()  PBout(5)=1  //SCL
//#define OLED_SDIN_Clr()  PBout(4)=0  //SDA
//#define OLED_SDIN_Set()  PBout(4)=1  //SDA

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_11)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_10)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define high 1
#define low 0
#define OLED_MODE 0
#define SIZE 1
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define X_WIDTH 	128
#define Y_WIDTH 	64 
//#define X_WIDTH 	128
//#define Y_WIDTH 	64

#define SPI 0
#define IIC 1
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define pi 3.1412926 //����Բ����

void OLED_IIC_Init(void);
void IIC_Start(void);// -- ����I2C����
void IIC_Stop(void);// -- �ر�I2C����
void Write_IIC_Byte(unsigned char IIC_Byte);// -- ͨ��I2C����дһ��byte������
void OLED_WrDat(unsigned char dat);// -- ��OLED��д����
void OLED_WrCmd(unsigned char cmd);// -- ��OLED��д����
void OLED_Set_Pos(unsigned char x, unsigned char y);// -- ������ʾ����
void OLED_Fill(unsigned char bmp_dat);// -- ȫ����ʾ(��ʾBMPͼƬʱ�Ż��õ��˹���)
void OLED_CLS(void);// -- ��λ/����
// -- 6x8������������ʾASCII�����С���У���̫����
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
// -- 8x16������������ʾASCII�룬�ǳ�����
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
// -- 16x16������������ʾ���ֵ���С���У������ø������塢�Ӵ֡���б���»��ߵ�
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned int N);
// -- ��128x64���ص�BMPλͼ��ȡ�����������ֱ�Ȼ���Ƶ�codetab�У��˺������ü���
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_P32x32Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_P8x16Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P16x32Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P128x48Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P128x64Ch(unsigned char x,unsigned char y,unsigned int N);




#endif
