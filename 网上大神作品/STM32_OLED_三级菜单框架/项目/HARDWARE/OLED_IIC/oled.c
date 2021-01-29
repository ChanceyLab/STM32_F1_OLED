#include "oled.h"
#include "codetab.h"



u8 OLED_GRAM[128][8];

// ------------------------------------------------------------
// SCL->PC12
// SDA->PC11
// ------------------------------------------------------------

void OLED_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    delay_ms(500);//初始化之前的延时很重要

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PC端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	//端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    OLED_WrCmd(0xae);//--turn off oled panel
    OLED_WrCmd(0x00);//---set low column address
    OLED_WrCmd(0x10);//---set high column address
    OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd(0x81);//--set contrast control register
    OLED_WrCmd(0XFF); // Set SEG Output Current Brightness 亮度调节 0x00~0xff
    OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WrCmd(0xa6);//--set normal display
    OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
    OLED_WrCmd(0x3f);//--1/64 duty
    OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrCmd(0x00);//-not offset
    OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd(0xd9);//--set pre-charge period
    OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd(0xda);//--set com pins hardware configuration
    OLED_WrCmd(0x12);
    OLED_WrCmd(0xdb);//--set vcomh
    OLED_WrCmd(0x40);//Set VCOM Deselect Level
    OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd(0x02);//
    OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
    OLED_WrCmd(0x14);//--set(0x10) disable
    OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
    OLED_WrCmd(0xaf);//--turn on oled panel
    OLED_Fill(0x00); //初始清屏
    OLED_Set_Pos(0, 0);
}


/**************************实现函数********************************************
*函数原型:		void IIC_Start(void)
*功　　能:		产生IIC起始信号
*******************************************************************************/
void OLED_IIC_Start(void)
{
    OLED_IIC_SDA = 1;
    OLED_IIC_SCL = 1;
    delay_us(1);
    OLED_IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
    delay_us(1);
    OLED_IIC_SCL = 0; //钳住I2C总线，准备发送或接收数据
}
/**************************实现函数********************************************
*函数原型:		void IIC_Stop(void)
*功　　能:	    //产生IIC停止信号
*******************************************************************************/
void  OLED_IIC_Stop(void)
{
    OLED_IIC_SCL = 0;
    OLED_IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
    delay_us(1);
    OLED_IIC_SCL = 1;
    OLED_IIC_SDA = 1; //发送I2C总线结束信号
    delay_us(1);
}
void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        if(IIC_Byte & 0x80)
            OLED_IIC_SDA = 1;
        else
            OLED_IIC_SDA = 0;
        OLED_IIC_SCL = 1;
        delay_us(1);  //必须有保持SCL脉冲的延时
        OLED_IIC_SCL = 0;
        IIC_Byte <<= 1;
    }
    OLED_IIC_SDA = 1;//原程序这里有一个拉高SDA，根据OLED的DATASHEET，此句必须去掉。
    OLED_IIC_SCL = 1;
    delay_us(1);
    OLED_IIC_SCL = 0;
}
/*********************OLED写数据************************************/
void OLED_WrDat(unsigned char IIC_Data)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);
    Write_IIC_Byte(0x40);			//write data
    Write_IIC_Byte(IIC_Data);
    OLED_IIC_Stop();
}
/*********************OLED写命令************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);            //Slave address,SA0=0
    Write_IIC_Byte(0x00);			//write command
    Write_IIC_Byte(IIC_Command);
    OLED_IIC_Stop();
}
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WrCmd(0xb0 + y);
    OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WrCmd((x & 0x0f) | 0x01);
}
/*********************OLED全屏************************************/
void OLED_Fill(unsigned char bmp_dat)
{
    unsigned char y, x;
    for(y = 0; y < 8; y++)
    {
        OLED_WrCmd(0xb0 + y);
        OLED_WrCmd(0x01);
        OLED_WrCmd(0x10);
        for(x = 0; x < X_WIDTH; x++)
            OLED_WrDat(bmp_dat);
    }
}
/*********************OLED复位************************************/
void OLED_CLS(void)
{
    unsigned char y, x;
    for(y = 0; y < 8; y++)
    {
        OLED_WrCmd(0xb0 + y);
        OLED_WrCmd(0x01);
        OLED_WrCmd(0x10);
        for(x = 0; x < X_WIDTH; x++)
            OLED_WrDat(0);
    }
}
//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          :
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
    OLED_WrCmd(0X8D);  //设置电荷泵
    OLED_WrCmd(0X10);  //关闭电荷泵
    OLED_WrCmd(0XAE);  //OLED休眠
}
//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          :
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
    OLED_WrCmd(0X8D);  //设置电荷泵
    OLED_WrCmd(0X14);  //开启电荷泵
    OLED_WrCmd(0XAF);  //OLED唤醒
}
//m^n函数
u32 oled_pow(u8 m, u8 n)
{
    u32 result = 1;
    while(n--)result *= m;
    return result;
}
//显示2个数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size)
{
    u8 t, temp;
    u8 enshow = 0;
    for(t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1))
        {
            if(temp == 0)
            {
                OLED_ShowChar(x + (size / 2)*t, y, ' ');
                continue;
            }
            else enshow = 1;
        }
        OLED_ShowChar(x + (size / 2)*t, y, temp + '0');
    }
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_ShowChar(u8 x, u8 y, u8 chr)
{
    unsigned char c = 0, i = 0;
    c = chr - ' '; //得到偏移后的值
    if(x > Max_Column - 1)
    {
        x = 0;
        y = y + 2;
    }
    if(SIZE == 0)
    {
        OLED_Set_Pos(x, y);
        for(i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i]);
        OLED_Set_Pos(x, y + 1);
        for(i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i + 8]);
    }
    else
    {
        OLED_Set_Pos(x, y + 1);
        for(i = 0; i < 6; i++)
            OLED_WrDat(F6x8[c][i]);
    };
}
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void OLED_P6x8Str(unsigned char x, unsigned char y, unsigned char ch[])
{
    unsigned char c = 0, i = 0, j = 0;
    while (ch[j] != '\0')
    {
        c = ch[j] - 32;
        if(x > 126)
        {
            x = 0;
            y++;
        }
        OLED_Set_Pos(x, y);
        for(i = 0; i < 6; i++)
            OLED_WrDat(F6x8[c][i]);
        x += 6;
        j++;
    }
}
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(unsigned char x, unsigned  char y, unsigned char ch[])
{
    unsigned char c = 0, i = 0, j = 0;
    while (ch[j] != '\0')
    {
        c = ch[j] - 32;
        if(x > 120)
        {
            x = 0;
            y++;
        }
        OLED_Set_Pos(x, y);
        for(i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i]);
        OLED_Set_Pos(x, y + 1);
        for(i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i + 8]);
        x += 8;
        j++;
    }
}


void OLED_P8x16Ch(unsigned char x, unsigned char y, unsigned int N)
{
    unsigned char wm = 0;
    unsigned int adder = 16 * N;
    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 8; wm++)
    {
        OLED_WrDat(Ff8x16[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for(wm = 0; wm < 8; wm++)
    {
        OLED_WrDat(Ff8x16[adder]);
        adder += 1;
    }
}
//--------------------------------------------------------------
// Prototype      : OLED_P16x16Ch(unsigned char x, unsigned char y, unsigned char N)
// Calls          :
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------

/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void OLED_P16x16Ch(unsigned char x, unsigned char y, unsigned int N)
{
    unsigned char wm = 0;
    unsigned int adder = 32 * N;
    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x16[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x16[adder]);
        adder += 1;
    }
}

void OLED_P16x32Ch(unsigned char x, unsigned char y, unsigned int N)
{
    unsigned char wm = 0;
    unsigned int adder = 64 * N;
    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1 );
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x , y + 2);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3 );
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
}
void OLED_P32x32Ch(unsigned char x, unsigned char y, unsigned int N)
{
    unsigned char wm = 0;
    unsigned int adder = 128 * N;
    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1 );
    for(wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x , y + 2);
    for(wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3 );
    for(wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
}
void OLED_P128x48Ch(unsigned char x, unsigned char y, unsigned int N)
{
    unsigned char wm = 0;
    unsigned int adder = 768 * N;
    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x , y + 2);
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3 );
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 4 );
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 5 );
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void Draw_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{

    unsigned int j = 0;
    unsigned char x, y;
    if(y1 % 8 == 0) y = y1 / 8;
    else y = y1 / 8 + 1;
    for(y = y0; y < y1; y++)
    {
        OLED_Set_Pos(x0, y);
        for(x = x0; x < x1; x++)
        {
            OLED_WrDat(BMP[j++]);
        }
    }
}



// ------------------------------------------------------------
// D0  ->PB6（SCL）
// D1  ->PB5（SDA）
// RES ->PB4
// DC  ->PB3
// ------------------------------------------------------------
