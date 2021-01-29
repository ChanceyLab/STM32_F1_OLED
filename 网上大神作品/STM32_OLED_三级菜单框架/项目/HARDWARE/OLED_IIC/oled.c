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
    delay_ms(500);//��ʼ��֮ǰ����ʱ����Ҫ

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PC�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	//�˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    OLED_WrCmd(0xae);//--turn off oled panel
    OLED_WrCmd(0x00);//---set low column address
    OLED_WrCmd(0x10);//---set high column address
    OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd(0x81);//--set contrast control register
    OLED_WrCmd(0XFF); // Set SEG Output Current Brightness ���ȵ��� 0x00~0xff
    OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
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
    OLED_Fill(0x00); //��ʼ����
    OLED_Set_Pos(0, 0);
}


/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Start(void)
*��������:		����IIC��ʼ�ź�
*******************************************************************************/
void OLED_IIC_Start(void)
{
    OLED_IIC_SDA = 1;
    OLED_IIC_SCL = 1;
    delay_us(1);
    OLED_IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
    delay_us(1);
    OLED_IIC_SCL = 0; //ǯסI2C���ߣ�׼�����ͻ��������
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Stop(void)
*��������:	    //����IICֹͣ�ź�
*******************************************************************************/
void  OLED_IIC_Stop(void)
{
    OLED_IIC_SCL = 0;
    OLED_IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
    delay_us(1);
    OLED_IIC_SCL = 1;
    OLED_IIC_SDA = 1; //����I2C���߽����ź�
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
        delay_us(1);  //�����б���SCL�������ʱ
        OLED_IIC_SCL = 0;
        IIC_Byte <<= 1;
    }
    OLED_IIC_SDA = 1;//ԭ����������һ������SDA������OLED��DATASHEET���˾����ȥ����
    OLED_IIC_SCL = 1;
    delay_us(1);
    OLED_IIC_SCL = 0;
}
/*********************OLEDд����************************************/
void OLED_WrDat(unsigned char IIC_Data)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);
    Write_IIC_Byte(0x40);			//write data
    Write_IIC_Byte(IIC_Data);
    OLED_IIC_Stop();
}
/*********************OLEDд����************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
    OLED_IIC_Start();
    Write_IIC_Byte(0x78);            //Slave address,SA0=0
    Write_IIC_Byte(0x00);			//write command
    Write_IIC_Byte(IIC_Command);
    OLED_IIC_Stop();
}
/*********************OLED ��������************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WrCmd(0xb0 + y);
    OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WrCmd((x & 0x0f) | 0x01);
}
/*********************OLEDȫ��************************************/
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
/*********************OLED��λ************************************/
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
// Description    : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
    OLED_WrCmd(0X8D);  //���õ�ɱ�
    OLED_WrCmd(0X10);  //�رյ�ɱ�
    OLED_WrCmd(0XAE);  //OLED����
}
//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          :
// Parameters     : none
// Description    : ��OLED�������л���
//--------------------------------------------------------------
void OLED_ON(void)
{
    OLED_WrCmd(0X8D);  //���õ�ɱ�
    OLED_WrCmd(0X14);  //������ɱ�
    OLED_WrCmd(0XAF);  //OLED����
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
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
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
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x, u8 y, u8 chr)
{
    unsigned char c = 0, i = 0;
    c = chr - ' '; //�õ�ƫ�ƺ��ֵ
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
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
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
/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
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
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); N:������codetab.h�е�����
// Description    : ��ʾcodetab.h�еĺ���,16*16����
//--------------------------------------------------------------

/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
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
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
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
// D0  ->PB6��SCL��
// D1  ->PB5��SDA��
// RES ->PB4
// DC  ->PB3
// ------------------------------------------------------------
