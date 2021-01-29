#ifndef _OLED_H
#define _OLED_H
#include "sys.h"


/**-----------------------------------IIC---------------------------------------
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              SDA  接PC11
//              SCL  接PC12       
//              ----------------------------------------------------------------
**/
/**********IIC 接口*************/
#define OLED_IIC_SCL  PBout(6) //SCL   串行时钟
#define OLED_IIC_SDA  PBout(7) //SDA	  串行数据

/**-----------------------------------SPI---------------------------------------
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PB6（SCL）
//              D1   接PB5（SDA）
//              RES  接PB4
//              DC   接PB3        
//              ----------------------------------------------------------------
**/
/**********SPI 接口**************/
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
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define pi 3.1412926 //定义圆周率

void OLED_IIC_Init(void);
void IIC_Start(void);// -- 开启I2C总线
void IIC_Stop(void);// -- 关闭I2C总线
void Write_IIC_Byte(unsigned char IIC_Byte);// -- 通过I2C总线写一个byte的数据
void OLED_WrDat(unsigned char dat);// -- 向OLED屏写数据
void OLED_WrCmd(unsigned char cmd);// -- 向OLED屏写命令
void OLED_Set_Pos(unsigned char x, unsigned char y);// -- 设置显示坐标
void OLED_Fill(unsigned char bmp_dat);// -- 全屏显示(显示BMP图片时才会用到此功能)
void OLED_CLS(void);// -- 复位/清屏
// -- 6x8点整，用于显示ASCII码的最小阵列，不太清晰
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
// -- 8x16点整，用于显示ASCII码，非常清晰
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
// -- 16x16点整，用于显示汉字的最小阵列，可设置各种字体、加粗、倾斜、下划线等
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned int N);
// -- 将128x64像素的BMP位图在取字软件中算出字表，然后复制到codetab中，此函数调用即可
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void OLED_P32x32Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_P8x16Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P16x32Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P128x48Ch(unsigned char x,unsigned char y,unsigned int N);
void OLED_P128x64Ch(unsigned char x,unsigned char y,unsigned int N);




#endif
