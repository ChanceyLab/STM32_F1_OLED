#include "adc.h"



//-----ADC0 ->��ҡ��X
//-----ADC1 ->��ҡ��Y

//-----ADC8 ->��ҡ��X
//-----ADC9 ->��ҡ��Y

//-----ADC10->12V
//-----ADC11->5V
//-----ADC12->3.3V

void  Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1	, ENABLE );	 //ʹ��ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
    //����ģ��ͨ����������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
    ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
    ADC_StartCalibration(ADC1);	 //����ADУ׼
    while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
}

/**************************************************************************
�������ܣ�AD����
��ڲ�����ADC1 ��ͨ��
����  ֵ��ADת�����
**************************************************************************/
u16 Get_Adc(u8 ch)
{
    //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
    return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}


/**************************************************************************
�������ܣ���ȡ��ص�ѹ
��ڲ�������Ӧ�ĵ�ѹ
����  ֵ����ص�ѹ ��λMV
**************************************************************************/
int Get_battery_volt(int ad)
{
    int Volt = 0; //��ص�ѹ
    if(_3V3_ == ad)
        Volt = Get_Adc(ad) * 3.3 * 11 * 100 / 4096;	//�����ѹ���������ԭ��ͼ�򵥷������Եõ�
    else if(_5V_ == ad)
        Volt = Get_Adc(ad) * 5.0 * 11 * 100  / 4096;	//�����ѹ���������ԭ��ͼ�򵥷������Եõ�
    else if(_12V_ == ad)
        Volt = Get_Adc(ad) * 12.0 * 11 * 100 / 4096;	//�����ѹ���������ԭ��ͼ�򵥷������Եõ�
    return Volt;
}

/***************************************
 ->int Rocker_Detection_Drive(u8 _L_R_)
 ->�ж�ҡ�˷������
 ->������� : ҡ��
 ->������� : ����ֵ
***************************************/
int Rocker_Detection_Drive(u8 _L_R_)//�ж�ҡ�˷������
{
    static u8 Left_Rocker_Sign = 0, Left_Rocker_Data = 0;
    static u8 Right_Rocker_Sign = 0, Right_Rocker_Data = 0;
    /*****************************************ҡ�˿���*************************************************/
    if(_Left_Rocker_ == _L_R_)    //��ȡ��ҡ�˷���ֵ
    {
        if(!Left_Rocker_Sign)
        {
            //�ж���ҡ��������λ��
            if(Left_Rocker_Center)
            {
                Left_Rocker_Sign = 1;
                Left_Rocker_Data = 0;
            }
        }
        else if(Left_Rocker_Sign)
        {
            //�ж�ҡ�����һ���
            if(Rocker_minimum == Get_Adc(Left_Rocker_X))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = Right_Double;
            }
            //�ж�ҡ�����󻬸�
            else if(Rocker_maximum == Get_Adc(Left_Rocker_X))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = Left_Double;
            }
            //�ж�ҡ�����ϻ���
            else if(Rocker_maximum == Get_Adc(Left_Rocker_Y))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = On_Double;
            }
            //�ж�ҡ�����»���
            else if(Rocker_minimum == Get_Adc(Left_Rocker_Y))
            {
                Left_Rocker_Sign = 0;
                Left_Rocker_Data = Under_Double;
            }
        }
    }
    else if(_Right_Rocker_ == _L_R_)//��ȡ��ҡ�˷���ֵ
    {
        if(!Right_Rocker_Sign)
        {
            //�ж�ҡ��������λ��
            if(Right_Rocker_Center)
            {
                Right_Rocker_Sign = 1;
                Right_Rocker_Data = 0;
            }
        }
        else if(Right_Rocker_Sign)
        {
            //�ж�ҡ�����һ���
            if(Rocker_minimum == Get_Adc(Right_Rocker_X))
            {
                Right_Rocker_Sign = 0;
                Right_Rocker_Data = Right_Double;
            }
            //�ж�ҡ�����󻬸�
            else if(Rocker_maximum == Get_Adc(Right_Rocker_X))
            {
                Right_Rocker_Sign = 0;
                Right_Rocker_Data = Left_Double;
            }
            //�ж�ҡ�����ϻ���
            else if(Rocker_maximum == Get_Adc(Right_Rocker_Y))
            {
                Right_Rocker_Sign = 0;
                Right_Rocker_Data = On_Double;
            }
            //�ж�ҡ�����»���
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
