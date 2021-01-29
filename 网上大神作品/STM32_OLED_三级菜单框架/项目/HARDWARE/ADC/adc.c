#include "adc.h"



//-----ADC0 ->左摇杆X
//-----ADC1 ->左摇杆Y

//-----ADC8 ->右摇杆X
//-----ADC9 ->右摇杆Y

//-----ADC10->12V
//-----ADC11->5V
//-----ADC12->3.3V

void  Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1	, ENABLE );	 //使能ADC1通道时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
    //设置模拟通道输入引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
    ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
    ADC_ResetCalibration(ADC1);	//使能复位校准
    while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
    ADC_StartCalibration(ADC1);	 //开启AD校准
    while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
}

/**************************************************************************
函数功能：AD采样
入口参数：ADC1 的通道
返回  值：AD转换结果
**************************************************************************/
u16 Get_Adc(u8 ch)
{
    //设置指定ADC的规则组通道，一个序列，采样时间
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
    return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}


/**************************************************************************
函数功能：读取电池电压
入口参数：对应的电压
返回  值：电池电压 单位MV
**************************************************************************/
int Get_battery_volt(int ad)
{
    int Volt = 0; //电池电压
    if(_3V3_ == ad)
        Volt = Get_Adc(ad) * 3.3 * 11 * 100 / 4096;	//电阻分压，具体根据原理图简单分析可以得到
    else if(_5V_ == ad)
        Volt = Get_Adc(ad) * 5.0 * 11 * 100  / 4096;	//电阻分压，具体根据原理图简单分析可以得到
    else if(_12V_ == ad)
        Volt = Get_Adc(ad) * 12.0 * 11 * 100 / 4096;	//电阻分压，具体根据原理图简单分析可以得到
    return Volt;
}

/***************************************
 ->int Rocker_Detection_Drive(u8 _L_R_)
 ->判断摇杆方向控制
 ->输入参数 : 摇杆
 ->输出参数 : 方向值
***************************************/
int Rocker_Detection_Drive(u8 _L_R_)//判断摇杆方向控制
{
    static u8 Left_Rocker_Sign = 0, Left_Rocker_Data = 0;
    static u8 Right_Rocker_Sign = 0, Right_Rocker_Data = 0;
    /*****************************************摇杆控制*************************************************/
    if(_Left_Rocker_ == _L_R_)    //读取左摇杆方向值
    {
        if(!Left_Rocker_Sign)
        {
            //判断左摇杆在中心位置
            if(Left_Rocker_Center)
            {
                Left_Rocker_Sign = 1;
                Left_Rocker_Data = 0;
            }
        }
        else if(Left_Rocker_Sign)
        {
            //判断摇杆向右滑杆
            if(Rocker_minimum == Get_Adc(Left_Rocker_X))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = Right_Double;
            }
            //判断摇杆向左滑杆
            else if(Rocker_maximum == Get_Adc(Left_Rocker_X))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = Left_Double;
            }
            //判断摇杆向上滑杆
            else if(Rocker_maximum == Get_Adc(Left_Rocker_Y))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = On_Double;
            }
            //判断摇杆向下滑杆
            else if(Rocker_minimum == Get_Adc(Left_Rocker_Y))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = Under_Double;
            }
        }
    }
    else if(_Right_Rocker_ == _L_R_)//读取右摇杆方向值
    {
        if(!Right_Rocker_Sign)
        {
            //判断摇杆在中心位置
            if(Right_Rocker_Center)
            {
                Right_Rocker_Sign = 1;
                Right_Rocker_Data = 0;
            }
        }
        else if(Right_Rocker_Sign)
        {
            //判断摇杆向右滑杆
            if(Rocker_minimum == Get_Adc(Right_Rocker_X))
            {
                Right_Rocker_Sign = 0;
                Right_Rocker_Data = Right_Double;
            }
            //判断摇杆向左滑杆
            else if(Rocker_maximum == Get_Adc(Right_Rocker_X))
            {
                Right_Rocker_Sign = 0;
                Right_Rocker_Data = Left_Double;
            }
            //判断摇杆向上滑杆
            else if(Rocker_maximum == Get_Adc(Right_Rocker_Y))
            {
                Right_Rocker_Sign = 0;
                Right_Rocker_Data = On_Double;
            }
            //判断摇杆向下滑杆
            else if(Rocker_minimum == Get_Adc(Right_Rocker_Y))
            {
                Right_Rocker_Sign = 0;
                Right_Rocker_Data = Under_Double;
            }
        }
    }

    /************************************************************************/
    return ((_Left_Rocker_ == _L_R_) ? Left_Rocker_Data : Right_Rocker_Data);
    /***********************************************************************************************/

}
int Get_Adc_Average(int ch, int times)
{
    int temp_val = 0;
    u8 t = 0;
    for(t = 0; t < times; t++)
    {
        temp_val += ch;
        delay_ms(10);
    }
    return temp_val / times;
}
