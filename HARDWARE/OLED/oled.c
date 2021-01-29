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
#include "delay.h"
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"
#include "math.h"

u8 OLED_GRAM[128][8];

/**
  * @brief	:Delay_xxx
  * @note   :	--
  * @param	:	>>
  * @return	:void
  * @date   :2021/01/29
  * @design :
  **/

void Delay(u32 count)
{
    u32 i=0;
    for(; i<count; i++);
}
void Delay_1ms(unsigned int Del_1ms)
{
    u8 j;
    while(Del_1ms--)
    {
        for(j=0; j<123; j++);
    }
}
void Delay_50ms(unsigned int Del_50ms)
{
    unsigned int m;
    for(; Del_50ms>0; Del_50ms--)
        for(m=6245; m>0; m--);
}

/**********************************************
//IIC Start
**********************************************/
void OLED_IIC_Start()
{

    OLED_SCLK_Set() ;
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void OLED_IIC_Stop()
{
    OLED_SCLK_Set() ;
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

void OLED_IIC_Wait_Ack()
{
    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}

/**********************************************
// IIC Write byte
**********************************************/
void OLED_Write_IIC_Byte(u8 IIC_Byte)
{
    u8 i;
    u8 m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();
    for(i=0; i<8; i++)
    {
        m=da;
        m=m&0x80;
        if(m==0x80)
        {
            OLED_SDIN_Set();
        }
        else OLED_SDIN_Clr();
        da=da<<1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
    }
}

/**********************************************
// IIC Write Command
**********************************************/
void OLED_Write_IIC_Command(u8 IIC_Command)
{
    OLED_IIC_Start();
    OLED_Write_IIC_Byte(0x78);				//Slave address,SA0=0
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(0x00);				//write command
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(IIC_Command);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}

/**********************************************
// IIC Write Data
**********************************************/
void OLED_Write_IIC_Data(u8 IIC_Data)
{
    OLED_IIC_Start();
    OLED_Write_IIC_Byte(0x78);				//D/C#=0; R/W#=0
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(0x40);				//write data
    OLED_IIC_Wait_Ack();
    OLED_Write_IIC_Byte(IIC_Data);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}

/**********************************************
// OLED_WR_Byte
**********************************************/
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
    {
        OLED_Write_IIC_Data(dat);
    }
    else
    {
        OLED_Write_IIC_Command(dat);
    }
}

/**********************************************
//m^n����
**********************************************/
u32 oled_pow(uint8_t m,uint8_t n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}

/**********************************************
// OLED_On
**********************************************/
void OLED_On(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
        for(n=0; n<128; n++)OLED_WR_Byte(1,OLED_DATA);
    }
}

/**
  * @brief	:OLED_Refresh
  * @note   :	--�����Դ浽OLED
  * @param	:	>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/

void OLED_Refresh(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
        OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
        OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
        for(n=0; n<128; n++)
            OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
    }
}

/**
  * @brief	:OLED_Set_Pos
  * @note   :	--��������
  * @param	:	>>
				>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_Set_Pos(u8 x, u8 y)
{   OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

/**
  * @brief	:OLED_Display_On
  * @note   :	--����OLED��ʾ
  * @param	:	>>
				>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/**
  * @brief	:OLED_Display_off
  * @note   :	--�ر�OLED��ʾ
  * @param	:	>>
				>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

/**
  * @brief	:OLED_Clear
  * @note   :	--��������
				--������,������Ļ�Ǻ�ɫ��!��û����һ��
  * @param	:	>>
				>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
        for(n=0; n<128; n++)OLED_WR_Byte(0,OLED_DATA);
    } 
	//������ʾ
}

/**
  * @brief	:OLED_DrawPoint
  * @note   :	--����
				--����ĩβ���ܼ�ˢ���Դ溯�����ᵼ��������ʾ����һ��һ�����к���
  * @param	:	>>x:0~127
				>>y:0~63
				>>t:���״̬����0����������1��������(Ĭ��)
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
    u8 i,m,n;
    i=y/8;
    m=y%8;
    n=1<<m;
    if(t) {
        OLED_GRAM[x][i]|=n;
    }
    else
    {
        OLED_GRAM[x][i]=~OLED_GRAM[x][i];
        OLED_GRAM[x][i]|=n;
        OLED_GRAM[x][i]=~OLED_GRAM[x][i];
    }
}

/**
  * @brief	:OLED_ClearPoint
  * @note   :	--���һ����
				--����ĩβ���ܼ�ˢ���Դ溯�����ᵼ��������ʾ����һ��һ�����к���
  * @param	:	>>x:0~127
				>>y:0~63
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_ClearPoint(u8 x,u8 y)
{
    u8 i,m,n;
    i=y/8;
    m=y%8;
    n=1<<m;
    OLED_GRAM[x][i]=~OLED_GRAM[x][i];
    OLED_GRAM[x][i]|=n;
    OLED_GRAM[x][i]=~OLED_GRAM[x][i];
    OLED_Refresh();
}

/**
  * @brief	:OLED_ShowNumber
  * @note   :	--��ʾ����
				--���磺OLED_ShowNumber(0,0,45125215,10);
  * @param	:	>>x,y :�������
				>>len :���ֵ�λ��
				>>size:�����СĬ��16
				>>num:��ֵ(0~4294967295);
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len)
{
    u8 size2 = 16;
    uint8_t t,temp;
    uint8_t enshow=0;
    for(t=0; t<len; t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
                continue;
            } else enshow=1;

        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
    }
}

/**
  * @brief	:OLED_ShowChar
  * @note   :	--��ָ��λ����ʾһ���ַ�,���������ַ�
				--���磺OLED_ShowChar(20,6,'A',16);
  * @param	:	>>
				>>x:0~127
				>>y:0~6
				>>mode:0,������ʾ;1,������ʾ
				>>size:ѡ������ 8/16
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{
    u8 c=0,i=0;
    c=chr-' ';//�õ�ƫ�ƺ��ֵ
    if(x>Max_Column-1) {
        x=0;
        y=y+2;
    }
    if(Char_Size ==16)
    {
        OLED_Set_Pos(x,y);
        for(i=0; i<8; i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0; i<8; i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
    }
    else
    {
        OLED_Set_Pos(x,y);
        for(i=0; i<6; i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);

    }
}

/**
  * @brief	:OLED_ShowString
  * @note   :	--��ʾһ���ַ��Ŵ�
				--���磺
						u8 SET[2][3] = {{"ON "},{"OFF"}};
						OLED_ShowString(0,0,SET[0],8);
  * @param	:	>>
				>>size:ѡ������ 8/16
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
    while (*chr!='\0')
    {   OLED_ShowChar(x,y,*chr,Char_Size);
        x+=8;
        if(x>120) {
            x=0;
            y+=2;
        }
        chr++;
    }
}

/********************************************
// fill_Picture
********************************************/
void fill_picture(u8 fill_Data)
{
    u8 m,n;
    for(m=0; m<8; m++)
    {
        OLED_WR_Byte(0xb0+m,0);		//page0-page1
        OLED_WR_Byte(0x00,0);		//low column start address
        OLED_WR_Byte(0x10,0);		//high column start address
        for(n=0; n<128; n++)
        {
            OLED_WR_Byte(fill_Data,1);
        }
    }
}

/**
  * @brief	:OLED_DrawBMP
  * @note   :	--��ʾ��ʾBMPͼƬ128��64
  * @param	:	>>��ʼ������(x,y)
				>>x�ķ�Χ0��127
				>>yΪҳ�ķ�Χ0��8
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[])
{
    unsigned int j=0;
    u8 x,y;

    if(y1%8==0) y=y1/8;
    else y=y1/8+1;
    for(y=y0; y<y1; y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0; x<x1; x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}

/**
  * @brief	:OLED_fuhao_write
  * @note   :	--����ASCII����ʾ�ַ�/����
				--Ĭ��8x����
  * @param	:	>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_fuhao_write(u8 x,u8 y,u8 asc)
{
    int i=0;
    OLED_Set_Pos(x*6,y);
    for(i=0; i<6; i++)
    {
        OLED_WR_Byte(F6x8[asc][i],OLED_DATA);
    }
}
void OLED_Num_write(u8 x,u8 y,u8 asc)
{
    int i=0;
    OLED_Set_Pos(x*6,y);
    for(i=0; i<6; i++)
    {
        OLED_WR_Byte(F6x8[asc+16][i],OLED_DATA);
    }
}

/**
  * @brief	:OLED_Float
  * @note   :	--��ʾС��
				--����NλС��
				--��ʾ�����Զ�����
  * @param	:	>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_Float(u8 X,u8 Y,double real,u8 N)
{
    u8   i_Count=1;
    u8   n[12]= {0};
    long   j=1;
    int    real_int=0;
    double decimal=0;
    unsigned int   real_decimal=0;
    if(real<0)
    {
        real_int=(int)(-real);
    }
    else
    {
        real_int=(int)real;
    }
    decimal=real-real_int;
    real_decimal=decimal*1e4;
    while(real_int/10/j!=0)
    {
        j=j*10;
        i_Count++;
    }
    n[0]=(real_int/10000)%10;
    n[1]=(real_int/1000)%10;
    n[2]=(real_int/100)%10;
    n[3]=(real_int/10)%10;
    n[4]=(real_int/1)%10;
    n[5]='.';
    n[6]=(real_decimal/1000)%10;
    n[7]=(real_decimal/100)%10;
    n[8]=(real_decimal/10)%10;
    n[9]=real_decimal%10;
    n[6+N]='\0';
    for(j=0; j<10; j++) n[j]=n[j]+16+32;
    if(real<0)
    {
        i_Count+=1;
        n[5-i_Count]='-';
    }
    n[5]='.';
    n[6+N]='\0';
    OLED_ShowString(X,Y,&n[5-i_Count],16);
}

//δ֪
void OLED_Float2(u8 Y,u8 X,double real,u8 N1,u8 N2)
{
    u8   i_Count=1;
    u8   n[12]= {0};
    long   j=1;
    unsigned int   real_int=0;
    double decimal=0;
    unsigned int   real_decimal=0;
    X=X*8;
    real_int=(int)real;
    //Dis_Num(2,0,real_int,5);
    decimal=real-real_int;
    real_decimal=decimal*1e4;
    //Dis_Num(2,6,real_decimal,4);
    while(real_int/10/j!=0)
    {
        j=j*10;
        i_Count++;
    }
    n[0]=(real_int/10000)%10;
    n[1]=(real_int/1000)%10;
    n[2]=(real_int/100)%10;
    n[3]=(real_int/10)%10;

    n[5]='.';
    n[6]=(real_decimal/1000)%10;
    n[7]=(real_decimal/100)%10;
    n[8]=(real_decimal/10)%10;
    n[9]=real_decimal%10;
    n[6+N2]='\0';
    for(j=0; j<10; j++) n[j]=n[j]+16+32;
    n[5]='.';
    n[6+N2]='\0';
    OLED_ShowString(X,Y,&n[5-N1],12);
}

/**
  * @brief	:OLED_DrawLine
  * @note   :	--���ߺ���
				--
  * @param	:	>>x1������x���ꣻ
				>>y1������y���ꣻ
				>>x2���յ��x���ꣻ
				>>y2���յ��y���ꣻ
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_DrawLine(u8 x1, u8 y1, u8 x2,u8 y2,u8 dot)
{
    unsigned int t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x=x2-x1; //������������
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1; //���õ�������
    else if(delta_x==0)incx=0;//��ֱ��
    else {
        incx=-1;
        delta_x=-delta_x;
    }
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;//ˮƽ��
    else {
        incy=-1;
        delta_y=-delta_y;
    }
    if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
    else distance=delta_y;
    for(t=0; t<=distance+1; t++ ) //�������
    {
        OLED_DrawPoint(uRow,uCol,dot);//����
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}

/**********************************************
//���Ժ���
**********************************************/
void OLED_ColorTurn(u8 i)
{
    if(i==0)
    {
        OLED_WR_Byte(0xA6,OLED_CMD);//������ʾ
    }
    if(i==1)
    {
        OLED_WR_Byte(0xA7,OLED_CMD);//��ɫ��ʾ
    }
}

/**********************************************
//��Ļ��ת180��
**********************************************/
void OLED_DisplayTurn(u8 i)
{
    if(i==0)
    {
        OLED_WR_Byte(0xC8,OLED_CMD);//������ʾ
        OLED_WR_Byte(0xA1,OLED_CMD);
    }
    if(i==1)
    {
        OLED_WR_Byte(0xC0,OLED_CMD);//��ת��ʾ
        OLED_WR_Byte(0xA0,OLED_CMD);
    }
}

/**
  * @brief	:OLED_Fill
  * @note   :	--ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63
				--
  * @param	:	>>x1,y1,x2,y2 �������ĶԽ�����
				>>dot:0,���;1,���
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
    u8 x,y;
    for(x=x1; x<=x2; x++)
    {
        for(y=y1; y<=y2; y++)OLED_DrawPoint(x,y,dot);
    }
}

/**
  * @brief	:OLED_DrawCircle
  * @note   :	--
				--
  * @param	:	>>x,y:Բ������
				>>r:Բ�İ뾶
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_DrawCircle(u8 x,u8 y,u8 r)
{
    int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)
    {
        OLED_DrawPoint(x + a, y - b,1);
        OLED_DrawPoint(x - a, y - b,1);
        OLED_DrawPoint(x - a, y + b,1);
        OLED_DrawPoint(x + a, y + b,1);

        OLED_DrawPoint(x + b, y + a,1);
        OLED_DrawPoint(x + b, y - a,1);
        OLED_DrawPoint(x - b, y - a,1);
        OLED_DrawPoint(x - b, y + a,1);

        a++;
        num = (a * a + b * b) - r*r;//���㻭�ĵ���Բ�ĵľ���
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}

/**
  * @brief	:�˷ֶԳƷ�(��������)
  * @note   :	--����������İ˷ֶԳƵ�(��Բ�����㷨)
  * @param	:	>>xc, Բ��������
				>>yc, Բ��������
				>>x , ������
				 >>y , ������
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
static void Circle8Point(uint32_t xc, uint32_t yc, uint32_t x, uint32_t y)
{
    //ֱ������ϵ��һ����x�Ὺʼ����ʱ����ת��
    OLED_DrawPoint((xc+x), (yc+y), 1);//1
    OLED_DrawPoint((xc+y), (yc+x), 1);//2
    OLED_DrawPoint((xc-y), (yc+x), 1);//3
    OLED_DrawPoint((xc-x), (yc+y), 1);//4
    OLED_DrawPoint((xc-x), (yc-y), 1);//5
    OLED_DrawPoint((xc-y), (yc-x), 1);//6
    OLED_DrawPoint((xc+y), (yc-x), 1);//7
    OLED_DrawPoint((xc+x), (yc-y), 1);//8
}

/**
  * @brief	:�Ľ���Բ(��������)
  * @note   :	--���⸡������(���ϵ㲻ͻ����)��
  * @param	:	>>xc, Բ��������
				>>yc, Բ��������
				>>r , �뾶
  * @return	:void
  *
  * @date   :2017/01/02
  * @design :
  **/
void OLED_DrawCircle_Updata(uint32_t xc, uint32_t yc, uint32_t r)
{
    uint32_t x=0, y=0;
    int32_t d=0;//�Ľ������⸡�����㣡

    x = 0;
    y = r;
    d = 3-2*r;

    Circle8Point(xc ,yc, x, y);
    while(x < y)
    {
        if(d < 0)
        {
            d += 4*x+6;
        } else {
            d += 4*(x-y)+10;
            --y;
        }
        ++x;
        Circle8Point(xc, yc, x, y);
    }
}

/**
  * @brief	:��ʾ����
  * @note   :	--
  * @param	:	>>x,y:�������
				>>num:���ֶ�Ӧ�����
				>>size:16,24,32,64
				>>mode:0,��ɫ��ʾ;1,������ʾ
  * @return	:void
  *
  * @date   :2017/01/02
  * @design :
  **/
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode)
{
    u8 m,temp;
    u8 x0=x,y0=y;
    u16 i,size3=(size1/8+((size1%8)?1:0))*size1;  //�õ�����һ���ַ���Ӧ������ռ���ֽ���
    for(i=0; i<size3; i++)
    {
        if(size1==16)
        {
            temp=Chinese_Word_16[num][i];   //����16*16����
        }
        else if(size1==24)
        {
            temp=Chinese_Word_24[num][i];   //����24*24����
        }
        else if(size1==32)
        {
            temp=Chinese_Word_32[num][i];   //����32*32����
        }
        else if(size1==64)
        {
            temp=Chinese_Word_64[num][i];   //����64*64����
        }
        else return;
        for(m=0; m<8; m++)
        {
            if(temp&0x01)OLED_DrawPoint(x,y,mode);
            else OLED_DrawPoint(x,y,!mode);
            temp>>=1;
            y++;
        }
        x++;
        if((x-x0)==size1)
        {
            x=x0;
            y0=y0+8;
        }
        y=y0;
    }

}

//

/**
  * @brief	:OLED_ShowPicture
  * @note   :	--
  * @param	:	>>x,y���������
				>>sizex,sizey,ͼƬ����
				>>BMP[]��Ҫд���ͼƬ����
				>>mode:0,��ɫ��ʾ;1,������ʾ
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode)
{
    u16 j=0;
    u8 i,n,temp,m;
    u8 x0=x,y0=y;
    sizey=sizey/8+((sizey%8)?1:0);
    for(n=0; n<sizey; n++)
    {
        for(i=0; i<sizex; i++)
        {
            temp=BMP[j];
            j++;
            for(m=0; m<8; m++)
            {
                if(temp&0x01)OLED_DrawPoint(x,y,mode);
                else OLED_DrawPoint(x,y,!mode);
                temp>>=1;
                y++;
            }
            x++;
            if((x-x0)==sizex)
            {
                x=x0;
                y0=y0+8;
            }
            y=y0;
        }
    }
}

/**
  * @brief	:�����ص�
  * @note   :	--����֧��emWin���ã�
  * @param	:	>>pixelX, ������
				>>pixelY, ������
  * @return	:uint8_t, ��ȡ�������ɫֵ
  *
  * @date   :2018/01/21
  * @design :
  **/
uint8_t OLED_ReadPixelPoint(uint32_t pixelX, uint32_t pixelY)
{
    uint32_t page=0, page_data=0;
    uint8_t temp=0;

#if OLED_ORIGIN_SET == 0
    page	  = 7 - pixelY/8;
    page_data = pixelY%8;
#else
    page	  = pixelY/8;
    page_data = pixelY%8;
#endif
    temp = OLED_GRAM[pixelX][page];
    if(temp & page_data)
    {
        return 1;
    } else {
        return 0;
    }
}

/**
  * @brief	:oled�ֲ�������ʾ
  * @note   :	--v10.0��ʼ������ʹ�ñ�������
				--����̫�Ͻ�������������ҳѰַģʽ��-- by liang_seri 2018.01.21
  * @param	:	>>pStart, ��ʼҳ0-7
				>>pEnd  , ��ֹҳ0-7
				>>cStart, ��ʼ��0-128
				>>cEnd  , ��ֹ��0-128
				>>direct, ѡ��ˢ�·���(1����  0����)
  * @return	:void
  *
  * @date   :2019/01/19
  * @design :
  **/
void OLED_UpdatePart(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd, uint32_t direct)
{
    uint32_t column=0, page=0;

    if(direct)						//����ˢ��
    {
        OLED_Write_IIC_Command(0x20);	//����ΪˮƽѰַģʽ����ΪҳѰַ�µ��ƶ�������λ����(ˢ��ʱ��̫����)
        OLED_Write_IIC_Command(0x00);
        OLED_Write_IIC_Command(0x21);	//����ˮƽѰַ��ʼ�к���ֹ��
        OLED_Write_IIC_Command(cStart);
        OLED_Write_IIC_Command(cEnd);
        OLED_Write_IIC_Command(0x22);	//����ˮƽѰַ��ʼҳ����ֹҳ
        OLED_Write_IIC_Command(pStart);
        OLED_Write_IIC_Command(pEnd);

        for(page=pStart; page<=pEnd; page++)
        {
            for(column=cStart; column<=cEnd; column++) {
                OLED_Write_IIC_Data(OLED_GRAM[column][page]);
            }
        }
    } else {							//����ˢ��
        OLED_Write_IIC_Command(0x20);	//����Ϊ��ֱѰַģʽ����ΪҳѰַ�µ��ƶ�������λ����(ˢ��ʱ��̫����)
        OLED_Write_IIC_Command(0x01);
        OLED_Write_IIC_Command(0x21);	//���ô�ֱѰַ��ʼ�к���ֹ��
        OLED_Write_IIC_Command(cStart);
        OLED_Write_IIC_Command(cEnd);
        OLED_Write_IIC_Command(0x22);	//���ô�ֱѰַ��ʼҳ����ֹҳ
        OLED_Write_IIC_Command(pStart);
        OLED_Write_IIC_Command(pEnd);

        for(column=cStart; column<=cEnd; column++) {
            {
                for(page=pStart; page<=pEnd; page++)
                    OLED_Write_IIC_Data(OLED_GRAM[column][page]);
            }
        }
    }
    OLED_Write_IIC_Command(0x20);		//�ָ�Ĭ��Ѱַģʽ��ҳѰַģʽ��
    OLED_Write_IIC_Command(0x02);
    OLED_Write_IIC_Command(0x21);		//������ʼ�к���ֹ��
    OLED_Write_IIC_Command(0);
    OLED_Write_IIC_Command(127);
    OLED_Write_IIC_Command(0x22);		//������ʼҳ����ֹҳ
    OLED_Write_IIC_Command(0);
    OLED_Write_IIC_Command(7);
}

/**
  * @brief	:�ķֶԳƷ�
  * @note   :	--������������ķֶԳƵ�(����Բ�����㷨)
  * @param	:	>>xc, ��Բ����������
				>>yc, ��Բ����������
				>>x , ������
				>>y , ������
  * @return	:void
  *
  * @date   :2017/01/04
  * @design :
  **/
static void Ellipse4Point(uint32_t xc, uint32_t yc, uint32_t x, uint32_t y)
{
    //ֱ������ϵ��һ���޿�ʼ����ʱ����ת��
    OLED_DrawPoint((xc+x), (yc+y), 1);//1
    OLED_DrawPoint((xc-x), (yc+y), 1);//2
    OLED_DrawPoint((xc-x), (yc-y), 1);//3
    OLED_DrawPoint((xc+x), (yc-y), 1);//4
}


/**
  * @brief	:����Բ
  * @note   :	--
  * @param	:	>>xc, ��Բ����������
				>>yc, ��Բ����������
				>>a , �볤�᳤��
				>>b , ����᳤��
  * @return	:void
  *
  * @date   :2017/01/04
  * @design :
  **/
void OLED_DrawEllipse(uint32_t xc, uint32_t yc, uint32_t a, uint32_t b)
{
    int32_t x=0;
    int32_t y=b;
    int32_t b2=(int32_t)b;

    float sqa=a*a;
    float sqb=b*b;
    float d=sqb+sqa*(-b2+0.25f);

    Ellipse4Point(xc, yc, x, y);
    while((sqb*(x+1)) < (sqa*(y-0.5f)))
    {
        if(d < 0)
        {
            d += sqb*(2*x+3);
        } else {
            d += sqb*(2*x+3)+sqa*(-2*y+2);
            --y;
        }
        ++x;
        Ellipse4Point(xc, yc, x, y);
    }

    d = (b*(x+0.5))*2 + (a*(y-1))*2 - (a*b)*2;
    while(y > 0)
    {
        if(d < 0)
        {
            d += sqb*(2*x+2)+sqa*(-2*y+3);
            ++x;
        } else {
            d += sqa*(-2*y+3);
        }
        --y;
        Ellipse4Point(xc, yc, x, y);
    }
}

/**
  * @brief	:������(��������)
  * @note   :--
  * @param	:xStart, ����ʼ����
			 yStart, ����ʼ����
			 xEnd  , ����ֹ����
			 yEnd  , ����ֹ����
  * @return	:void
  *
  * @date   :2016/09/09
  * @design :
  **/
void OLED_DrawBlock(uint32_t xStart, uint32_t yStart, uint32_t xEnd, uint32_t yEnd)
{
	OLED_DrawLine(xStart, yStart, xStart, yEnd,1);//���
	OLED_DrawLine(xEnd, yStart, xEnd, yEnd,1);//�ҽ�
	OLED_DrawLine(xStart, yStart, xEnd, yStart,1);//�Ͻ�
	OLED_DrawLine(xStart, yEnd, xEnd, yEnd,1);//�½�
}

/**
  * @brief	:������(��������)
  * @note   :--
  * @param	:xStart , ����ʼ����
			 yStart , ����ʼ����
			 length , ���γ���
			 width  , ���ο��
			 isFill , �Ƿ����(0����� 1���)
  * @return	:void
  *
  * @date   :2016/09/09
  * @design :
  **/
void OLED_DrawRect(uint32_t xStart, uint32_t yStart, uint32_t length, uint32_t width, uint32_t isFill)
{
	uint32_t rect_xs=xStart;
	uint32_t rect_ys=yStart;
	uint32_t rect_xe=xStart+length-1;
	uint32_t rect_ye=yStart+width-1;
	uint32_t x=0, y=0;
	
	OLED_DrawBlock(rect_xs, rect_ys, rect_xe, rect_ye);//���Ʊ߿�
	
	if(isFill)//�ж��Ƿ����
	{
		for(x=xStart; x<(rect_xe+1); x++)
		{
			for(y=yStart; y<(rect_ye+1); y++){
				OLED_DrawPoint(x, y, 1);
			}
		}
	}
}	

/**
  * @brief	:��ɫ����(һ��ʵ��)
  * @note   :--ע�⣺��ɫ����������ַ������򣬼���С�任�����СΪ6*8��С�ڴ�ֵ���δ֪��
			 --�޸ģ�v7.0�汾��Ժ��������޸ģ���֧��������ʾ��
			 --���飺�ɸ�����������򻯳����羡������ҳ�в�����������Ҫ��ҳ��
  * @param	:*zone, ��������
  * @return	:void
  *
  * @date   :2017/12/22
  * @design :
  **/
void OLED_Invert(_OLEDZoneHandle *zone)
{
	uint32_t page[2], column[2];
	uint32_t i, j;
	uint8_t mask;
	uint8_t temp[2];
	
	page[0]	  = zone->pixel_column_start/8;
	page[1]	  = zone->pixel_column_end/8;
	column[0] = zone->pixel_row_start;
	column[1] = zone->pixel_row_end;	
		
	for(j=column[0]; j<=column[1]; j++)
	{
		//��ʼһҳ�����������⴦����ֲ�����ʽ������⣡*/
		mask	 =	0xFF;
		temp[0]  =  OLED_GRAM[j][page[0]];
		temp[1]  =  temp[0];
		temp[0]  = ~temp[0];//���ֽڵĸ�λ����ȡ����
		mask	 =  mask<<(zone->pixel_column_start%8);
		temp[0] &=  mask;
		mask  	 = ~mask;
		temp[1] &=  mask;
		temp[0]  =  temp[1] | temp[0];
		OLED_GRAM[j][page[0]] = temp[0];
		///��ʼһҳ�����������⴦��*/
		if(page[1] != (page[0]+1))
		{
			for(i=page[0]+1; i<page[1]; i++)
			{
				temp[0] = OLED_GRAM[j][i];
				temp[0] = ~temp[0];
				OLED_GRAM[j][i] = temp[0];
			}		
		}
		///���һҳ�����������⴦����ֲ�����ʽ������⣡*/
		if(page[1] != (page[0]))//��ֹ��ҳ��βҳ�ظ�����ɫ��
		{
			mask	 =	0xFF;
			temp[0]  =  OLED_GRAM[j][page[1]];
			temp[1]  =  temp[0];
			temp[0]  = ~temp[0];//���ֽڵĵ�λ����ȡ����
			mask	 =  mask>>(7 - zone->pixel_column_end%8);
			temp[0] &=  mask;
			mask	 = ~mask;
			temp[1] &=  mask;
			temp[0]  =  temp[1] | temp[0];
			OLED_GRAM[j][page[1]] = temp[0];
		}
	}
}

/**
  * @brief	:��ɫ����(��ҳΪ��λ��ɫ)
  * @note   :--������λΪҳ*�У�
  * @param	:pStart, ��ʼҳ
             pEnd  , ��ֹҳ
             cStart, ��ʼ��
             cEnd  , ��ֹ��
  * @return	:void
  *
  * @date   :2017/12/22
  * @design :
  **/
void OLED_Invert2(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd)
{
	uint32_t column=0, page=0;
	uint8_t temp=0;
	
	for(page=pStart; page<=pEnd; page++)
	{
		for(column=cStart; column<=cEnd; column++)
		{
			temp = OLED_GRAM[column][page];
			temp = ~temp;
			OLED_GRAM[column][page] = temp;
		}
	}
}

/**
  * @brief	:ˮƽ��ת����(��ҳΪ��λ��ת)
  * @note   :--������λΪҳ*�У�
  * @param	:pStart, ��ʼҳ
             pEnd  , ��ֹҳ
             cStart, ��ʼ��
             cEnd  , ��ֹ��
  * @return	:void
  *
  * @date   :2016/12/24
  * @design :
  **/
void OLED_DisplayTurn_Level(uint32_t pStart, uint32_t pEnd, uint32_t cStart, uint32_t cEnd)
{
	uint32_t column=0, page=0;
	uint8_t temp=0;
	
    for(column=0; column<(cEnd - cStart)/2; column++)
    {
        for(page=pStart; page<=pEnd; page++)
        {
            temp = OLED_GRAM[column][page];
            OLED_GRAM[column][page]		 = OLED_GRAM[cEnd-column][page];
            OLED_GRAM[cEnd-column][page] = temp;
        }
    }
}

/**
  * @brief	:��������(Ӳ��)
  * @note   :--Ӳ��������ֻ�ܵ���һ�Σ���
			 --//���Ϳ�ʼ������2f��ǰҪ�ȴ������ʾ���ݣ�����ڹ�����ʱ������ʾ����RAM�е����ݿ��ܱ��𻵡�
				//��������ܷ���while(1)����

			 --ˮƽ��������ֻ�ܰ�ҳ����������OLED_Move(0, 1, DIRECT_LEFT);//0��1ҳȫ�������������
			 --����ʵ�ִ�ֱ�������������²�����OLED_Move(0, 0, DIRECT_UP);//ҳ0�в��������ݣ�
			 --�������ʣ�
				000��5	 frames
				001��64  frames
				010��128 frames
				011��256 frames
				100��3	 frames
				101��4	 frames
				110��25	 frames
				111��2	 frames
  * @param	:pStart, ��ʼҳ
             pEnd  , ��ֹҳ
			 direct, ��Ļ�ƶ�����(_OLEDScrollDirectö���ж������ͣ�)
  * @return	:void
  *
  * @date   :2018/01/19
  * @design :
  **/
void OLED_Move(uint32_t start, uint32_t end, _OLEDScrollDirect direct)
{
	uint32_t temp=0, mask=0;
	start &= 0x07;				//�������ƣ���֤Ϊ0~7
	end   &= 0x07;
	if(start > end)				//��֤pStar<pEnd��
	{
		temp  = start;
		start = end;
		end   = temp;
	}
	///0x29��0x2Aָ��Ҫ��ByteEΪ1����0x26��0x27Ҫ��Ϊ0��
	mask  = (uint32_t)direct & 0x04;
	mask  =  mask>>2;
	mask  = ~mask;
	mask &=  0x01;
	OLED_Write_IIC_Command(direct);	//scroll direction
	OLED_Write_IIC_Command(0x00);
	OLED_Write_IIC_Command(start);	//start address
	OLED_Write_IIC_Command(0x07);	
	OLED_Write_IIC_Command(end);	//end address
	OLED_Write_IIC_Command(mask);
	OLED_Write_IIC_Command(0xFF);
	OLED_Write_IIC_Command(0x2F);	//active scroll!
}

/**
  * @brief	:������������(��������)
  * @note   :--��ֹ�ⲿ���ã�
  * @param	:pStart, ��ʼҳ
             pEnd  , ��ֹҳ
             cStart, ��ʼ��
             cEnd  , ��ֹ��
			 direct, ��Ļ�ƶ�����(_OLEDScrollDirectö���ж������ͣ�)
             loop  , �Ƿ�ѭ��(1ѭ��  0��ѭ��)
  * @return	:void
  *
  * @date   :2016/12/24
  * @design :
  **/
static void oled_move_horizontal(uint32_t pStart, uint32_t pEnd , uint32_t cStart, uint32_t cEnd, _OLEDScrollDirect direct, uint32_t loop)
{
    uint32_t page=0, column=0;
    uint32_t column_inc=0;
    uint8_t temp=0;
    	
	column_inc = (direct == DIRECT_LEFT) ? 127 : 1;
        
    for(page=pStart; page<=pEnd; page++)
    {
        if(direct == DIRECT_RIGHT)
        {
            temp = OLED_GRAM[cStart][page];//������cStart������

            for(column=cStart; column<=cEnd; column++){
                OLED_GRAM[column][page] = OLED_GRAM[(column+column_inc)%128][page]; 
            }

            if(loop)//����ѭ��ģʽ
            {
                OLED_GRAM[cEnd][page] = temp;
            }else{
                OLED_GRAM[cEnd][page] = 0;
            }
        }else if(direct == DIRECT_LEFT){
            temp = OLED_GRAM[cEnd][page];//������cEnd������

            for(column=cEnd; column>cStart; column--){
                OLED_GRAM[column][page] = OLED_GRAM[(column+column_inc)%128][page]; 
            }

            if(loop)//����ѭ��ģʽ
            {
                OLED_GRAM[cStart][page] = temp;
            }else{
                OLED_GRAM[cStart][page] = 0;
            }
        }
    }   
    
    OLED_UpdatePart(pStart, pEnd, cStart, cEnd, 0);
}

/**
  * @brief	:������������(��������)
  * @note   :--��ֹ�ⲿ���ã�
  * @param	:pStart, ��ʼҳ
             pEnd  , ��ֹҳ
             cStart, ��ʼ��
             cEnd  , ��ֹ��
			 direct, ��Ļ�ƶ�����(_OLEDScrollDirectö���ж������ͣ�)
             loop  , �Ƿ�ѭ��(1ѭ��  0��ѭ��)
  * @return	:void
  *
  * @date   :2016/12/24
  * @design :
  **/
static void oled_move_vertical(uint32_t pStart, uint32_t pEnd , uint32_t cStart, uint32_t cEnd, _OLEDScrollDirect direct, uint32_t loop)
{
    uint32_t page=0, column=0;
    uint8_t temp[8]={0};
    
    for(column=cStart; column<=cEnd; column++)
    {
        if(direct == DIRECT_UP)
        {
            for(page=pStart; page<=pEnd; page++)
            {
                temp[page] = (OLED_GRAM[column][page]&0x01)<<7;//ȡ�����λ�����ƶ������λ
                OLED_GRAM[column][page] >>= 1;//�������λ�ƶ����������ƶ�
            }
            
            for(page=pStart; page<=pEnd; page++)
            {
                if(loop)//����ѭ��ģʽ
                {
                    OLED_GRAM[column][page] |= temp[(page+1)%8];
                }else{
                    OLED_GRAM[column][page] |= 0;
                }
            }    
            
            OLED_GRAM[column][pEnd] |= temp[pStart]; 
        }else if(direct == DIRECT_DOWN)
        {
            for(page=pStart; page<=pEnd; page++)
            {
                temp[page] = (OLED_GRAM[column][page]&0x80)>>7;//ȡ�����λ�����ƶ������λ
                OLED_GRAM[column][page] <<= 1;//�������λ�ƶ����������ƶ�
            }
            
            for(page=pStart; page<=pEnd; page++)
            {
                if(loop)//����ѭ��ģʽ
                {
                    OLED_GRAM[column][page] |= temp[(page+7)%8];
                }else{
                    OLED_GRAM[column][page] |= 0;
                }
            }   
            
            OLED_GRAM[column][pStart] |= temp[pEnd]; 
        }        
    }

    OLED_UpdatePart(pStart, pEnd, cStart, cEnd, 1);
}

/**
  * @brief	:��������(��������)
  * @note   :--��С��λΪҳ*�У�
  * @param	:pStart, ��ʼҳ
             pEnd  , ��ֹҳ
             cStart, ��ʼ��
             cEnd  , ��ֹ��
			 direct, ��Ļ�ƶ�����(_OLEDScrollDirectö���ж������ͣ�)
             loop  , �Ƿ�ѭ��(1ѭ��  0��ѭ��)
  * @return	:void
  *
  * @date   :2016/12/24
  * @design :
  **/
void OLED_Move2(uint32_t pStart, uint32_t pEnd , uint32_t cStart, uint32_t cEnd, _OLEDScrollDirect direct, uint32_t loop)
{
    switch(direct)
    {
        case DIRECT_UP    : oled_move_vertical(pStart, pEnd, cStart, cEnd, DIRECT_UP, loop); break;
        case DIRECT_DOWN  : oled_move_vertical(pStart, pEnd, cStart, cEnd, DIRECT_DOWN, loop); break;
        case DIRECT_LEFT  : oled_move_horizontal(pStart, pEnd, cStart, cEnd, DIRECT_LEFT, loop); break;
        case DIRECT_RIGHT : oled_move_horizontal(pStart, pEnd, cStart, cEnd, DIRECT_RIGHT, loop); break;
        
        default : break;
    }
}

/**
  * @brief	:��������
  * @note   :	--��������������
				--
  * @param	:	>>
				>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
void DrawTriangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 x2, u8 y2)
{
  OLED_DrawLine(x0, y0, x1, y1,1);
  OLED_DrawLine(x1, y1, x2, y2,1);
  OLED_DrawLine(x2, y2, x0, y0,1);
}

/**
  * @brief	:��������ǵ�ֱ��
  * @note   :	--�Ƕ�˳ʱ�뿪ʼ
				--0��365
  * @param	:	>>
				>>
  * @return	:void
  *
  * @date   :2021/01/29
  * @design :
  **/
 
/*
�������ܣ�����ǶȻ�ֱ�� 
��    ����
	x,y:����
	du :����
	len :�߶εĳ���
	c  :��ɫֵ 0����1
*/
void OLED_DrawAngleLine(u32 x,u32 y,int du,u32 len,u8 c)
{
	int i;
	int x0,y0;
	//x��������--->Ϊ0��
//	double k=du*(3.1415926535L/180);
//	for(i=0;i<len;i++)
//	{
//		x0=cos(k)*i;
//		y0=sin(k)*i;
//		OLED_DrawPoint(x+x0,y+y0,c);
//	}
	//��ֱ���Ϸ���Ϊ0��
	double k=(du-90)*(3.1415926535L/180);
	for(i=0;i<len;i++)
	{
		x0=cos(k)*i;
		y0=sin(k)*i;
		OLED_DrawPoint(x+x0,y+y0,c);
	}
}

//��1/4Բ����Բ�ģ��뾶��λ�ã���������1234
void OLED_DrawPartCircle(u16 x0, u16 y0, u8 r, u8 part)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);         //�ж��¸���λ�õı�־
    while(a <= b)
    {
        switch(part)
        {
            case 1:
                OLED_DrawPoint(x0 + b, y0 + a,1);   
                OLED_DrawPoint(x0 + a, y0 + b,1);      
                break;
            case 2:
                OLED_DrawPoint(x0 - a, y0 + b,1);
                OLED_DrawPoint(x0 - b, y0 + a,1);
                break;
            case 3:
                OLED_DrawPoint(x0 - a, y0 - b,1);
                OLED_DrawPoint(x0 - b, y0 - a,1);
                break;
            case 4:
                OLED_DrawPoint(x0 + a, y0 - b,1);    
                OLED_DrawPoint(x0 + b, y0 - a,1);  
                break;
            default:
                break;
        }
        a++;
        //ʹ��Bresenham�㷨��Բ
        if(di < 0)di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}
//����ֱ���߶Σ����ͳ���,����Ϊ�������»�
void OLED_DrawVLine(u8 x0, u8 y0,int length)
{
    OLED_DrawLine(x0,y0,x0,y0+length,1);   
}

//��ˮƽ���߶�
void OLED_DrawHLine(u8 x0, u8 y0,int length)
{
    OLED_DrawLine(x0,y0,x0+length,y0,1);   
}

//��Բ�Ǿ��Σ������Բ�ǰ뾶
void OLED_DrawRoundRectangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 R)
{
    u8 L,W;
    L = x1 - x0 - 2 * R;
    W = y1 - y0 - 2 * R;
    OLED_DrawHLine(x0 + R, y0, L);
    OLED_DrawHLine(x0 + R, y1, L);
    OLED_DrawVLine(x0, y0 + R, W);
    OLED_DrawVLine(x1, y0 + R, W);
    
    OLED_DrawPartCircle(x1 - R, y1 - R, R, 1);
    OLED_DrawPartCircle(x0 + R, y1 - R, R, 2);
    OLED_DrawPartCircle(x0 + R, y0 + R, R, 3);
    OLED_DrawPartCircle(x1 - R, y0 + R, R, 4);
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
void OLED_DrawArrow(u8 x1, u8 y1, u8 R, u8 T, u8 S, u8 n)
{
    u16 x, y;
    x = R * sin(T * S * pi / 180 - pi / 2) + x1;
    y = R * cos(T * S * pi / 180 - pi / 2) + y1;
    OLED_DrawLine(x1, y1, x, y, n);
}





//��ʼ��SSD1306
void OLED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��B�˿�ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOB8,9
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
    Delay(400000);
    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--128
    OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
    OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//
    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//
    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//
    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);//
    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);//
    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}









