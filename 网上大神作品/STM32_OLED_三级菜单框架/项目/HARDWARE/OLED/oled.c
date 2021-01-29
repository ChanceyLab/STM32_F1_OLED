#include "math.h"
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
u8 OLED_GRAM[128][8];

//�����Դ浽LCD
void OLED_Refresh_Gram(void)
{
    u8 i, n;
    for(i = 0; i < 8; i++)
    {
        OLED_WR_Byte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
        for(n = 0; n < 128; n++)OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);

    }

}
#if OLED_MODE==1
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat, u8 cmd)
{
    DATAOUT(dat);
    if(cmd)
        OLED_DC_Set();
    else
        OLED_DC_Clr();
    //OLED_CS_Clr();
    OLED_WR_Clr();
    OLED_WR_Set();
    //OLED_CS_Set();
    OLED_DC_Set();
}
#else
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat, u8 cmd)
{
    u8 i;
    if(cmd)
        OLED_DC_Set();
    else
        OLED_DC_Clr();
    //OLED_CS_Clr();
    for(i = 0; i < 8; i++)
    {
        OLED_SCLK_Clr();
        if(dat & 0x80)
            OLED_SDIN_Set();
        else
            OLED_SDIN_Clr();
        OLED_SCLK_Set();
        dat <<= 1;
    }
    //OLED_CS_Set();
    OLED_DC_Set();
}
#endif
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0 + y, OLED_CMD);
    OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
    OLED_WR_Byte((x & 0x0f) | 0x01, OLED_CMD);
}
//����OLED��ʾ
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC����
    OLED_WR_Byte(0X14, OLED_CMD); //DCDC ON
    OLED_WR_Byte(0XAF, OLED_CMD); //DISPLAY ON
}
//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC����
    OLED_WR_Byte(0X10, OLED_CMD); //DCDC OFF
    OLED_WR_Byte(0XAE, OLED_CMD); //DISPLAY OFF
}
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLED_Clear(void)
{
    u8 i, n;
    for(i = 0; i < 8; i++)
    {
        delay_ms(10);
        OLED_WR_Byte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
        for(n = 0; n < 128; n++)OLED_WR_Byte(0, OLED_DATA);
    } //������ʾ
}

//��������,�����һ�к���(16x16)�������ַ�(16x8)
void OLED_Clear1(void)
{
    u8 i, n;
    for(i = 0; i < 2; i++)
    {
        OLED_WR_Byte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
        for(n = 0; n < 128; n++)OLED_WR_Byte(0, OLED_DATA);
    } //������ʾ
}


//��������,����ڶ��к���(16x16)�������ַ�(16x8)
void OLED_Clear2(void)
{
    u8 i, n;
    for(i = 2; i < 4; i++)
    {
        OLED_WR_Byte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
        for(n = 0; n < 128; n++)OLED_WR_Byte(0, OLED_DATA);
    } //������ʾ
}

//��������,��������к���(16x16)�������ַ�(16x8)
void OLED_Clear3(void)
{
    u8 i, n;
    for(i = 4; i < 6; i++)
    {
        OLED_WR_Byte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
        for(n = 0; n < 128; n++)OLED_WR_Byte(0, OLED_DATA);
    } //������ʾ
}

//��������,��������к���(16x16)�������ַ�(16x8)
void OLED_Clear4(void)
{
    u8 i, n;
    for(i = 6; i < 8; i++)
    {
        OLED_WR_Byte (0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00, OLED_CMD);     //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10, OLED_CMD);     //������ʾλ�á��иߵ�ַ
        for(n = 0; n < 128; n++)OLED_WR_Byte(0, OLED_DATA);
    } //������ʾ
}

//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
void OLED_DrawPoint(u8 x, u8 y, u8 t)
{
    u8 pos, bx, temp = 0;
    if(x > 127 || y > 63)return; //������Χ��.
    pos = 7 - y / 8;
    bx = y % 8;
    temp = 1 << (7 - bx);
    if(t)OLED_GRAM[x][pos] |= temp;
    else OLED_GRAM[x][pos] &= ~temp;
}
//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63
//dot:0,���;1,���
void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot)
{
    u8 x, y;
    for(x = x1; x <= x2; x++)
    {
        for(y = y1; y <= y2; y++)OLED_DrawPoint(x, y, dot);
    }
    OLED_Refresh_Gram();//������ʾ
}

//����
//x1,y1:�������
//x2,y2:�յ�����
void OLED_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 n)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;

    delta_x = x2 - x1; //������������
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if(delta_x > 0)incx = 1; //���õ�������
    else if(delta_x == 0)incx = 0; //��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if(delta_y > 0)incy = 1;
    else if(delta_y == 0)incy = 0; //ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if( delta_x > delta_y)distance = delta_x; //ѡȡ��������������
    else distance = delta_y;
    for(t = 0; t <= distance + 1; t++ ) //�������
    {
        OLED_DrawPoint(uRow, uCol, n); //����
        xerr += delta_x ;
        yerr += delta_y ;
        if(xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if(yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size, u8 mode)
{
    unsigned char c = 0, i = 0;
    c = chr - ' '; //�õ�ƫ�ƺ��ֵ
    if(x > Max_Column - 1)
    {
        x = 0;
        y = y + 2;
    }
    if(0 == mode)
    {
        if(size == 16)
        {
            OLED_Set_Pos(x, y);
            for(i = 0; i < 8; i++)
                OLED_WR_Byte(~F8X16[c * 16 + i], OLED_DATA);
            OLED_Set_Pos(x, y + 1);
            for(i = 0; i < 8; i++)
                OLED_WR_Byte(~F8X16[c * 16 + i + 8], OLED_DATA);
        }
        else if(size == 12)
        {
            OLED_Set_Pos(x, y + 1);
            for(i = 0; i < 6; i++)
                OLED_WR_Byte(~F6x8[c][i], OLED_DATA);
        }
    }
    else if(1 == mode)
    {
        if(size == 16)
        {
            OLED_Set_Pos(x, y);
            for(i = 0; i < 8; i++)
                OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
            OLED_Set_Pos(x, y + 1);
            for(i = 0; i < 8; i++)
                OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
        }
        else if(size == 12)
        {
            OLED_Set_Pos(x, y + 1);

            for(i = 0; i < 6; i++)
                OLED_WR_Byte(F6x8[c][i], OLED_DATA);
        }
    }
}
//m^n����
u32 oled_pow(u8 m, u8 n)
{
    u32 result = 1;
    while(n--)result *= m;
    return result;
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:0,������ʾ;1,������ʾ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size, u8 mode)
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
                OLED_ShowChar(x + (size / 2)*t, y, ' ', size, mode);
                continue;
            }
            else enshow = 1;

        }
        OLED_ShowChar(x + (size / 2)*t, y, temp + '0', size, mode);
    }
}


//��ԲȦ
void OLED_DrawCircle(u8 x, u8 y, u8 r)
{
    int x1, y1, r1;
    x1 = 0;
    y1 = r;
    r1 = 1 - r;
    while(x1 <= y1)
    {
        OLED_DrawPoint(x + x1, y + y1, 1);
        OLED_DrawPoint(x + y1, y + x1, 1);
        OLED_DrawPoint(x - y1, y + x1, 1);
        OLED_DrawPoint(x - x1, y + y1, 1);
        OLED_DrawPoint(x - x1, y - y1, 1);
        OLED_DrawPoint(x - y1, y - x1, 1);
        OLED_DrawPoint(x + y1, y - x1, 1);
        OLED_DrawPoint(x + x1, y - y1, 1);
        if(r1 < 0)
        {
            r1 += 2 * x1 + 3;
        }
        else
        {
            r1 += 2 * (x1 - y1) + 5;
            y1--;
        }
        x1++;
    }

}

//��ʵ��ԲȦ
void OLED_DrawFillCircle(u8 x, u8 y, u8 r)
{
    int x1, y1, r1;
    x1 = 0;
    y1 = r;
    r1 = 1 - r;
    while(x1 <= y1)
    {
        OLED_DrawLine(x + x1, y + y1, x - x1, y + y1, 1);
        OLED_DrawLine(x + x1, y - y1, x - x1, y - y1, 1);
        OLED_DrawLine(x + y1, y + x1, x - y1, y + x1, 1);
        OLED_DrawLine(x + y1, y - x1, x - y1, y - x1, 1);

        if(r1 < 0)
        {
            r1 += 2 * x1 + 3;
        }
        else
        {
            r1 += 2 * (x1 - y1) + 5;
            y1--;
        }
        x1++;
    }
}

//��ָ��
void OLED_DrawHand(u8 x1, u8 y1, u8 R, u8 T, u8 S, u8 n)
{
    u16 x, y;
    x = R * sin(T * S * pi / 180 - pi / 2) + x1;
    y = R * cos(T * S * pi / 180 - pi / 2) + y1;
    OLED_DrawLine(x1, y1, x, y, n);
}

//��ʾһ���ַ��Ŵ�
//x,y:�������
//*p:�ַ�����ʼ��ַ
//����ѡ�� mode:0,������ʾ;1,������ʾ
//��16����
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size, u8 mode)
{
    unsigned char j = 0;
    while (chr[j] != '\0')
    {
        OLED_ShowChar(x, y, chr[j], size, mode);
        x += 8;
        if(x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}
//��ʾ����
//x,y:�������
//n:���ֱ��
//��16����
void OLED_ShowCHinese(u8 x, u8 y, u8 no)
{
    u8 t, adder = 0;
    OLED_Set_Pos(x, y);
    for(t = 0; t < 16; t++)
    {
        OLED_WR_Byte(Hzk[2 * no][t], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for(t = 0; t < 16; t++)
    {
        OLED_WR_Byte(Hzk[2 * no + 1][t], OLED_DATA);
        adder += 1;
    }
}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
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
            OLED_WR_Byte(BMP[j++], OLED_DATA);
        }
    }
}

// ------------------------------------------------------------
// D0  ->PB6��SCL��
// D1  ->PB5��SDA��
// RES ->PB4
// DC  ->PB3
// ------------------------------------------------------------
//��ʼ��SSD1306
void OLED_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    /*RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);


    OLED_RST_Set();
    delay_ms(100);
    OLED_RST_Clr();
    delay_ms(100);
    OLED_RST_Set();

    OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
    OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
    OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
    OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
    OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
    OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
    OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
    OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD); //-not offset
    OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
    OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
    OLED_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
    OLED_WR_Byte(0x12, OLED_CMD);
    OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
    OLED_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
    OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD); //
    OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
    OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
    OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
    OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
    OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel
    OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
    OLED_Clear();
    OLED_Set_Pos(0, 0);
}
/*********************************************
�� �� ����OLED_P8x16Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P8x16Ch(unsigned char x, unsigned char y, unsigned int N)
{
    unsigned char wm = 0;
    unsigned int adder = 16 * N;
    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 8; wm++)
    {
        OLED_WR_Byte(Ff8x16[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for(wm = 0; wm < 8; wm++)
    {
        OLED_WR_Byte(Ff8x16[adder], OLED_DATA);
        adder += 1;
    }
}
/*********************************************
�� �� ����OLED_P16x32Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P16x32Ch(unsigned char x, unsigned char y, unsigned int N)
{
    unsigned char wm = 0;
    unsigned int adder = 64 * N;
    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WR_Byte(F16x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1 );
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WR_Byte(F16x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x , y + 2);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WR_Byte(F16x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3 );
    for(wm = 0; wm < 16; wm++)
    {
        OLED_WR_Byte(F16x32[adder], OLED_DATA);
        adder += 1;
    }
}
/*********************************************
�� �� ����OLED_P32x6Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P32x6Ch(u8 x, u8 y, u16 N)
{

    unsigned char wm = 0;
    unsigned int adder = 32 * N;

    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 32; wm++)
    {
        OLED_WR_Byte(F32x6[adder], OLED_DATA);
        adder += 1;
    }

}
/*********************************************
�� �� ����OLED_P64x6Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P64x6Ch(u8 x, u8 y, u16 N)
{
    unsigned char wm = 0;
    unsigned int adder = 64 * N;

    OLED_Set_Pos(x , y);

    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x6[adder], OLED_DATA);
        adder += 1;
    }

}

/*********************************************
�� �� ����OLED_P16x16Ch(u8 x, u8 y, u16 N ,u8 mode)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ�� mode:0,������ʾ;1,������ʾ
*********************************************/
void OLED_P16x16Ch(u8 x, u8 y, u16 N , u8 mode)
{
    unsigned char wm = 0;
    unsigned int adder = 32 * N;

    OLED_Set_Pos(x , y);
    if(0 == mode)
    {
        for(wm = 0; wm < 16; wm++)
        {
            OLED_WR_Byte(~F16x16[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x, y + 1);
        for(wm = 0; wm < 16; wm++)
        {
            OLED_WR_Byte(~F16x16[adder], OLED_DATA);
            adder += 1;
        }
    }
    else if(1 == mode)
    {
        for(wm = 0; wm < 16; wm++)
        {
            OLED_WR_Byte(F16x16[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x, y + 1);
        for(wm = 0; wm < 16; wm++)
        {
            OLED_WR_Byte(F16x16[adder], OLED_DATA);
            adder += 1;
        }
    }


}
/*********************************************
�� �� ����OLED_P32x32Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ�� mode:0,������ʾ;1,������ʾ
*********************************************/
void OLED_P32x32Ch(u8 x, u8 y, u16 N, u8 mode)
{
    unsigned char wm = 0;
    unsigned int adder = 128 * N;
    if(0 == mode)
    {
        OLED_Set_Pos(x , y);
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(~F32x32[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x, y + 1 );
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(~F32x32[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x , y + 2);
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(~F32x32[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x, y + 3 );
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(~F32x32[adder], OLED_DATA);
            adder += 1;
        }
    }
    else if(1 == mode)
    {
        OLED_Set_Pos(x , y);
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(F32x32[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x, y + 1 );
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(F32x32[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x , y + 2);
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(F32x32[adder], OLED_DATA);
            adder += 1;
        }
        OLED_Set_Pos(x, y + 3 );
        for(wm = 0; wm < 32; wm++)
        {
            OLED_WR_Byte(F32x32[adder], OLED_DATA);
            adder += 1;
        }

    }

}
/*********************************************
�� �� ����OLED_P32x32Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P64x32Ch(u8 x, u8 y, u16 N)
{
    unsigned char wm = 0;
    unsigned int adder = 256 * N;

    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1 );
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x , y + 2);
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3);
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x32[adder], OLED_DATA);
        adder += 1;
    }


}
/*********************************************
�� �� ����OLED_P128x32Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P128x32Ch(u8 x, u8 y, u16 N)
{
    unsigned char wm = 0;
    unsigned int adder = 256 * N;

    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WR_Byte(F128x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1 );
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WR_Byte(F128x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x , y + 2);
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WR_Byte(F128x32[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3);
    for(wm = 0; wm < 128; wm++)
    {
        OLED_WR_Byte(F128x32[adder], OLED_DATA);
        adder += 1;
    }

}
/*********************************************
�� �� ����OLED_P64x64Ch(u8 x, u8 y, u16 N)
�������ܣ���ʾ�����Ϣ
���������y ��ʾy������ x ��ʾx������  N ��ʾ����Ϣ ����ѡ��
*********************************************/
void OLED_P64x64Ch(u8 x, u8 y, u16 N)
{
    unsigned char wm = 0;
    unsigned int adder = 512 * N;

    OLED_Set_Pos(x , y);
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1 );
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x , y + 2);
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3);
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 4 );
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 5 );
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 6 );
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 7 );
    for(wm = 0; wm < 64; wm++)
    {
        OLED_WR_Byte(F64x64[adder], OLED_DATA);
        adder += 1;
    }

}
/*********************************************
�� �� ����Draw_BMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
�������ܣ���ʾ�����Ϣ
���������x0 ��ʾ��ʹ x����   y0 ��ʾ��ʹ y����  x1 ��ʾͼƬ���x���꣬y1 ��ʾͼƬy���� Ϊ8  BMP[] ��ʾ����Ҫ��ͼƬ����
*********************************************/
void Draw_BMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
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
            OLED_WR_Byte(BMP[j++], OLED_DATA);
        }
    }

}

/**
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB6��SCL��
//              D1   ��PB5��SDA��
//              RES  ��PB4
//              DC   ��PB3    
//              ----------------------------------------------------------------
**/



