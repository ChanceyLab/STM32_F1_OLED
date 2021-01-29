#include <DISPLAY.H>
#include "BMP.h"

Mark Mark_Sign;//״̬��־λ
Module_mark Module_Mark;//ģ��״̬
Module_choose Module_Choose;//ѡ��
/************************
 ->u8 Detection_Hardware_Drive()
 ->�ж�Ӳ��״̬
 ->������� : ��
 ->������� : Ӳ��״̬
 ->
***********************/
u8 Detection_Hardware_Drive(void)//�ж�Ӳ��״̬
{
    static u8 sign = 0;
    //�ж�Ӳ�����״μ���
    if(0 == sign)
    {
        if(0 == Module_Mark.NRF24L01_Mark) //��ⲻ��24L01
        {
            OLED_P32x32Ch(3 * 16, 2, 7, 1); //��ʾ2.4Gģ�����ʧ��
            //��ʾ����  ģ�����ʧ��
            OLED_P16x16Ch(1 * 16, 6, 88, 1);
            OLED_P16x16Ch(2 * 16, 6, 89, 1);
            OLED_P16x16Ch(3 * 16, 6, 92, 1);
            OLED_P16x16Ch(4 * 16, 6, 93, 1);
            OLED_P16x16Ch(5 * 16, 6, 90, 1);
            OLED_P16x16Ch(6 * 16, 6, 91, 1);
            Module_Mark.NRF24L01_Mark = 0; //2.4Gģ��״̬��0��˵��ģ�����ʧ��
            delay_ms(1000);
        }
        else if(1 == Module_Mark.NRF24L01_Mark)//��⵽24L01
        {
            OLED_P32x32Ch(3 * 16, 2, 8, 1); //��ʾ2.4Gģ����سɹ�
            //��ʾ����  ģ����سɹ�
            OLED_P16x16Ch(1 * 16, 6, 88, 1);
            OLED_P16x16Ch(2 * 16, 6, 89, 1);
            OLED_P16x16Ch(3 * 16, 6, 92, 1);
            OLED_P16x16Ch(4 * 16, 6, 93, 1);
            OLED_P16x16Ch(5 * 16, 6, 77, 1);
            OLED_P16x16Ch(6 * 16, 6, 78, 1);
            Module_Mark.NRF24L01_Mark = 1; //2.4Gģ��״̬��1��˵��ģ����سɹ�
            delay_ms(1000);
        }
        OLED_Clear();
        sign = 1; //��־λ��1��˵���Ѿ����ع�һ��
    }
    //���Ӳ�������״μ���
    if(1 == sign)
    {
        if(Module_Mark.NRF24L01_Mark)
            OLED_P16x16Ch(0 * 16, 0, 38, 1);       //��ʾ2.4Gͼ��
        else
            OLED_P16x16Ch(0 * 16, 0, 37, 1);      //��ʾ
    }


    //    OLED_P16x16Ch(3.4 * 16, 6, 87, 1);     //��ʾUSBͼ��
    OLED_P16x16Ch(1 * 16, 0, 33, 1);       //��ʾWIFIͼ��
    OLED_P16x16Ch(2 * 16, 0, 5, 1);        //��ʾ����ͼ��
    OLED_P16x16Ch(111, 0, 86, 1);           //��ʾ3V3
    return 0;
}


/************************
 ->void Picture(u8 picture)
 ->��ʾ���ͼƬ
 ->������� : ͼƬ��
 ->������� : ��
 ->
***********************/
void Picture(u8 picture)
{
    switch(picture)
    {
    case NRF24L01_Picture:

        break;
    case Bluetooth_Picture:

        break;
    case WIFI_Picture:
        Draw_BMP(0, 0, 128, 8, WIFI);      //��ʾWIFIͼƬ
        break;
    case USB_Picture:

        break;
    case Set_Picture:

        break;
    default:
        break;
    }

}


/************************
 ->void Main_Interface_APP()
 ->��ʾ������
 ->������� : ��
 ->������� : ��
***********************/
void Main_Interface_APP(void)//��ʾ������
{
    OLED_Clear();
    OLED_P128x32Ch(0, 3, 0);//��ʾETAͼ��
    while(Main_Interface == Mark_Sign.Interface_Mark) //����״̬ ������
    {
        OLED_P16x16Ch(0 * 16, 6, 84, 1);       //��ʾ�˵�ͼ��
        Detection_Hardware_Drive();            //��ʾӲ��״̬
        OLED_P16x16Ch(112, 6, 87, 1);          //��ʾUSBͼ��


        OLED_P8x16Ch(5.5 * 8, 2, Teme.Points / 10); //��ʾ���Ӹ�λ
        OLED_P8x16Ch(6.5 * 8, 2, Teme.Points % 10); //��ʾ���ӵ�λ
        OLED_P8x16Ch(8.5 * 8, 2, Teme.Seconds / 10); //��ʾ���Ӹ�λ
        OLED_P8x16Ch(9.5 * 8, 2, Teme.Seconds % 10); //��ʾ���ӵ�λ
        /**********�м��С����һ����һ��*************/
        if(Teme.Point)
            OLED_P8x16Ch(7.5 * 8, 2, 10);
        else
            OLED_P8x16Ch(7.5 * 8, 2, 11);
        /*********************************************/
    }
}


/************************
 ->void Menu_Interface_APP()
 ->��ʾ�˵�����
 ->������� : ��
 ->������� : ��
***********************/
void Menu_Interface_APP(void)//��ʾ�˵�����
{
    static int  Menu_Sign = 0, Menu_Mark = 0;
    OLED_Clear();
    while(Menu_Interface == Mark_Sign.Interface_Mark) //����״̬ �˵�����
    {
        OLED_P16x16Ch(0 * 16, 0, 38, 1);       //��ʾ2.4Gͼ��
        OLED_P16x16Ch(1 * 16, 0, 33, 1);       //��ʾWIFIͼ��
        OLED_P16x16Ch(2 * 16, 0, 5, 1);        //��ʾ����ͼ��
        OLED_P16x16Ch(111, 0, 4, 1);           //��ʾ����ͼ��

        //��ʾȷ��
        OLED_P16x16Ch(0 * 16, 6, 31, 1);
        OLED_P16x16Ch(1 * 16, 6, 32, 1);
        //��ʾ����ͼ��
        OLED_P16x16Ch(112, 6, 83, 1);

        OLED_P32x32Ch(0, 2, 5, 1); //��ʾ�����ͷ
        OLED_P32x32Ch(95, 2, 6, 1); //��ʾ���Ҽ�ͷ

        /****************��ʾ��Ӧ�˵���*******************/
        switch(Menu_Sign)
        {
        case NRF24L01_Task:
            OLED_P32x32Ch(48, 2, 0, 1); //��ʾ2.4Gң����ͼ��
            //��ʾ2.4G�ַ�
            OLED_ShowString(3 * 16, 6, "2.4G", 16, 1);
            break;
        case Bluetooth_Task:
            OLED_P32x32Ch(48, 2, 1, 1); //��ʾ����ͼ��
            //��ʾ��������
            OLED_P16x16Ch(3 * 16, 6, 65, 1);
            OLED_P16x16Ch(4 * 16, 6, 66, 1);
            break;
        case WIFI_Task:
            OLED_P32x32Ch(48, 2, 2, 1); //��ʾWIFIͼ��
            //��ʾWIFI�ַ�
            OLED_ShowString(3 * 16, 6, "WIFI", 16, 1);
            break;
        case USB_Task:
            OLED_P32x32Ch(48, 2, 3, 1); //��ʾUSBͼ��
            //��ʾUSB�ַ�
            OLED_ShowString(2.8 * 16, 6, " USB ", 16, 1);
            break;
        case Set_Task:
            OLED_P32x32Ch(48, 2, 4, 1); //��ʾ����ͼ��
            //��ʾ���ú���
            OLED_P16x16Ch(3 * 16, 6, 50, 1);
            OLED_P16x16Ch(4 * 16, 6, 51, 1);
            break;
        default:
            break;
        }
        /*****************************************ҡ�˿���*************************************************/
        //�ж�ҡ�����һ���
        if(Right_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Menu_Mark)
        {
            Menu_Sign++;
            Menu_Mark = 1;
            if(Menu_Sign > number)
                Menu_Sign = 0;
        }
        //�ж�ҡ�����󻬸�
        else if(Left_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Menu_Mark)
        {
            Menu_Mark = 1;
            Menu_Sign--;
            if(Menu_Sign < 0)
                Menu_Sign = number;
        }
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == Menu_Mark)
        {
            Menu_Mark = 0;
        }

        Mark_Sign.Task_Mark = Menu_Sign; //��ȡ��ǰѡ�������
    }
    /***********************************************************************************************/
}


/************************
 ->void Function_Menu()
 ->��ʾ���ܽ���
 ->������� : ��
 ->������� : ��
***********************/
void Function_Menu_APP(void)//��ʾ���ܽ���
{
    while(Task_Interface == Mark_Sign.Interface_Mark) //����״̬ �������
    {
        /**********��ʼ���ж�Ӧ����**************/
        switch(Mark_Sign.Run_Task)
        {
        case NRF24L01_Task:
            /*******2.4G����********/
            NRF24L01_Task_APP();
            break;
        case Bluetooth_Task:
            /*******��������********/
            Bluetooth_Task_APP();
            break;
        case WIFI_Task:
            /*******WIFI����********/
            WIFI_Task_APP();
            break;
        case USB_Task:
            /*******USB����********/
            USB_Task_APP();
            break;
        case Set_Task:
            /*******��������********/
            Set_Task_APP();
            break;
        default :
            break;
        }
    }

}


/************************
 ->void Rocker_Display()
 ->��ʾҡ��ֵ
 ->������� : ��
 ->������� : ��
***********************/
void Rocker_Display_Drive(void)//��ʾҡ��ֵ
{
    int count = 0, Data[4] = {0, 0, 0, 0}, Average[4] = {0, 0, 0, 0};
    /************************************��ʾADֵ��ҡ��***************************/
    OLED_Clear();
    OLED_DrawBMP(0, 0, 128, 8, M2);

    //��ʾ���� ҡ������
    OLED_P16x16Ch(2 * 16, 1, 79, 1);
    OLED_P16x16Ch(3 * 16, 1, 80, 1);
    OLED_P16x16Ch(4 * 16, 1, 81, 1);
    OLED_P16x16Ch(5 * 16, 1, 82, 1);

    OLED_P16x16Ch(0 * 16, 6, 84, 1); //��ʾ�˵�ͼ��
    OLED_P16x16Ch(112, 6, 83, 1); //��ʾ����ͼ��
    while(1)
    {
        count++;
        //---��ȡ���� ��ƽ��ֵ
        Data[0] += Get_Adc(Left_Rocker_X);
        Data[1] += Get_Adc(Left_Rocker_Y);
        Data[2] += Get_Adc(Right_Rocker_X);
        Data[3] += Get_Adc(Right_Rocker_Y);
        //---�ж��Ƿ񵽴���
        if(count == 40)
        {
            //---���ƽ��ֵ
            Average[0] = Data[0] / 40;
            Average[1] = Data[1] / 40;
            Average[2] = Data[2] / 40;
            Average[3] = Data[3] / 40;
            //---��0
            Data[0] = Data[1] = Data[2] = Data[3] = 0;
            count = 0;
            //---��ʾ�������
            OLED_ShowString(4.5 * 8, 3, "CH1:", SIZE_6X8, 1);
            OLED_ShowNum(8.5 * 8, 3, Average[0] , 4, SIZE_6X8, 1);
            OLED_ShowString(4.5 * 8, 4, "CH2:", SIZE_6X8, 1);
            OLED_ShowNum(8.5 * 8, 4, Average[1], 4, SIZE_6X8, 1);
            OLED_ShowString(4.5 * 8, 5, "CH3:", SIZE_6X8, 1);
            OLED_ShowNum(8.5 * 8, 5, Average[2], 4, SIZE_6X8, 1);
            OLED_ShowString(4.5 * 8, 6, "CH4:", SIZE_6X8, 1);
            OLED_ShowNum(8.5 * 8, 6, Average[3], 4, SIZE_6X8, 1);

            /*OLED_ShowString(4.5 * 8, 3, "3V3:", SIZE_6X8, 1);
            OLED_ShowNum(8.5 * 8, 3, Get_Adc_Average(Get_battery_volt(_3V3_), 20) / 100, 1, SIZE_6X8, 1);
            OLED_ShowString(9.3 * 8, 3, ".", SIZE_6X8, 1);
            OLED_ShowNum(10 * 8, 3, Get_Adc_Average(Get_battery_volt(_3V3_), 20) % 100, 2, SIZE_6X8, 1);

            OLED_ShowString(4.5 * 8, 4, "5V:", SIZE_6X8, 1);
            OLED_ShowNum(8.5 * 8, 4, Get_Adc_Average(Get_Adc(_5V_), 20), 3, SIZE_6X8, 1);*/
        }
    }
}



/************************
 ->void NRF24L01_Task_APP()
 ->2.4G����
 ->������� : ��
 ->������� : ��
***********************/
void NRF24L01_Task_APP(void)//2.4G����
{

    /**
      * @{ NRF24L01_Menu_sign �����жϵ�ǰѡ�����
      * @{ NRF24L01_Menu_Mark �����ж�ҡ�˵�λ��
      */
    int NRF24L01_Menu_sign = 0,  NRF24L01_Menu_Mark = 0;
    /**
      * @{ ÿ�ν��뺯����������Щ����������
      * @{ ��ʼ��ʾ����Ҫ��ʾ������
      */
    OLED_Clear();
    /*****************************************NRF24L01_Task*************************************************/
    /**
      * @{ �жϵ�ǰ�������е�����
      * @{ ����� NRF24L01_Task
      * @{ ��һֱ��ѭ����������
      * @{ Mark_Sign.Run_Task��ֵ���ⲿ�ж� ��������
      * @{ �ı�Mark_Sign.Run_Task��ֵ���Ϳ��Ըı���������
      */
    while(NRF24L01_Task == Mark_Sign.Run_Task)//����״̬ ��������2.4G����
    {
        /**
          * @{ ��ʾ��ǰѡ��ͼ��
          * @{ ͼ����ݱ�־λ�Զ��ı�
          */
        OLED_P16x16Ch(0, NRF24L01_Menu_sign, Choose_Icon, Normal_Display); //��ʾѡ��ͼ��

        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����ϻ���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == NRF24L01_Menu_Mark)
        {
            /**
            	* @{ ���֮ǰ��ʾ��ͼ��
              * @{ NRF24L01_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, NRF24L01_Menu_sign, Remove, Normal_Display);


            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            NRF24L01_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            NRF24L01_Menu_sign -= 2;
            /**
              * @{ ��־λС��6
              * @{ ˵���Ѿ�������Ļ��ʾ�ķ�Χ����
              * @{ ���ǽ���־λ��6����ʾ������
              */
            if(NRF24L01_Menu_sign < 0)
                NRF24L01_Menu_sign = 6;
        }
        /**
          * @{ �ж�ҡ���Ƿ����»���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
          */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == NRF24L01_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ NRF24L01_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, NRF24L01_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ

            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            NRF24L01_Menu_Mark = 1;

            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            NRF24L01_Menu_sign += 2;
            /**
              * @{ ��־λ����6
              * @{ ˵���Ѿ���������Ļ��ʾ�����Χ
              * @{ ���ǽ���־λ��0����ʾ��һ��
              */
            if(NRF24L01_Menu_sign > 6)
                NRF24L01_Menu_sign = 0;
        }
        /**
          *  @{ �ж�ҡ�˵�ǰ�Ƿ�������λ��
          *  @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == NRF24L01_Menu_Mark)
        {
            //��־λ��0��˵��ҡ���Ѿ��ص�����λ��
            NRF24L01_Menu_Mark = 0;
        }
        /**
          *  @{ ����ת��
          *  @{ ��0 2 4 6 ת��Ϊ1 2 3 4
        	*  @{ ͬʱ��1 2 3 4�ĸ�ʽ���浽�ṹ�� Module_Mark.NRF24L01_Mark��
        	*  @{ ����Module_Mark.NRF24L01_Mark ��ֵ�Ϳ����ж�ѡ�����
          */
        Module_Mark.NRF24L01_Mark = Page(NRF24L01_Menu_sign);
        /*****************************��ʾ��Ӧ����*************************************/
        if(1 == Module_Mark.NRF24L01_Mark)
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, Normal_Display);
        }

        if(2 == Module_Mark.NRF24L01_Mark)
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, Normal_Display);
        }
        if(3 == Module_Mark.NRF24L01_Mark)
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, Normal_Display);
        }
        if(4 == Module_Mark.NRF24L01_Mark)
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, Normal_Display);
        }

        OLED_ShowNum(16 * 6, 6, Module_Mark.NRF24L01_Mark, 1, SIZE_6X8, Normal_Display);
        OLED_ShowString(17 * 6, 6, "/", SIZE_6X8, Normal_Display);
        OLED_ShowString(18 * 6, 6, "4", SIZE_6X8, Normal_Display);
        /******************************************************************************/
    }
}


/************************
 ->void Bluetooth_Task_APP()
 ->��������
 ->������� : ��
 ->������� : ��
***********************/
void Bluetooth_Task_APP(void)//��������
{
    /**
      * @{ Bluetooth_Menu_sign �����жϵ�ǰѡ�����
      * @{ Bluetooth_Menu_Mark �����ж�ҡ�˵�λ��
      */
    int Bluetooth_Menu_sign = 0,  Bluetooth_Menu_Mark = 0;
    /**
      * @{ ÿ�ν��뺯����������Щ����������
      * @{ ��ʼ��ʾ����Ҫ��ʾ������
      */
    OLED_Clear();

    /*****************************************Bluetooth_Task*************************************************/
    /**
      * @{ �жϵ�ǰ�������е�����
      * @{ ����� Bluetooth_Task
      * @{ ��һֱ��ѭ����������
      * @{ Mark_Sign.Run_Task��ֵ���ⲿ�ж� ��������
      * @{ �ı�Mark_Sign.Run_Task��ֵ���Ϳ��Ըı���������
      */
    while(Bluetooth_Task == Mark_Sign.Run_Task)//����״̬ ����������������
    {
        /**
          * @{ ��ʾ��ǰѡ��ͼ��
          * @{ ͼ����ݱ�־λ�Զ��ı�
          */
        OLED_P16x16Ch(0, Bluetooth_Menu_sign, Choose_Icon, Normal_Display); //��ʾѡ��ͼ��
        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����ϻ���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Bluetooth_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ Bluetooth_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, Bluetooth_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ

            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            Bluetooth_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            Bluetooth_Menu_sign -= 2;
            /**
              * @{ ��־λС��6
              * @{ ˵���Ѿ�������Ļ��ʾ�ķ�Χ����
              * @{ ���ǽ���־λ��6����ʾ������
              */
            if(Bluetooth_Menu_sign < 0)
                Bluetooth_Menu_sign = 6;
        }
        //�ж�ҡ�����»���
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Bluetooth_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ Bluetooth_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, Bluetooth_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ
            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            Bluetooth_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            Bluetooth_Menu_sign += 2;
            /**
              * @{ ��־λ����6
              * @{ ˵���Ѿ���������Ļ��ʾ�����Χ
              * @{ ���ǽ���־λ��0����ʾ��һ��
              */
            if(Bluetooth_Menu_sign > 6)
                Bluetooth_Menu_sign = 0;
        }
        /**
          *  @{ �ж�ҡ�˵�ǰ�Ƿ�������λ��
          *  @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == Bluetooth_Menu_Mark)
        {
            //��־λ��0��˵��ҡ���Ѿ��ص�����λ��
            Bluetooth_Menu_Mark = 0;
        }
        /**
          *  @{ ����ת��
          *  @{ ��0 2 4 6 ת��Ϊ1 2 3 4
          *  @{ ͬʱ��1 2 3 4�ĸ�ʽ���浽�ṹ�� Module_Mark.Bluetooth_Mark��
          *  @{ ����Module_Mark.Bluetooth_Mark ��ֵ�Ϳ����ж�ѡ�����
          */
        Module_Mark.Bluetooth_Mark = Page(Bluetooth_Menu_sign);
        /*****************************��ʾ��Ӧ����*************************************/

        if(1 == Module_Mark.Bluetooth_Mark)
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, Normal_Display);
        }
        if(2 == Module_Mark.Bluetooth_Mark)
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, Normal_Display);
        }
        if(3 == Module_Mark.Bluetooth_Mark)
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, Normal_Display);
        }
        if(4 == Module_Mark.Bluetooth_Mark)
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, Normal_Display);
        }



        OLED_ShowNum(16 * 6, 6, Module_Mark.Bluetooth_Mark , 1, SIZE_6X8, Normal_Display);
        OLED_ShowString(17 * 6, 6, "/", SIZE_6X8, Normal_Display);
        OLED_ShowString(18 * 6, 6, "4", SIZE_6X8, Normal_Display);

        /******************************************************************************/
    }
}


/************************
 ->void WIFI_Task_APP()
 ->WIFI����
 ->������� : ��
 ->������� : ��
***********************/
void WIFI_Task_APP(void)//WIFI����
{
    /**
      * @{ WIFI_Menu_sign �����жϵ�ǰѡ�����
      * @{ WIFI_Menu_Mark �����ж�ҡ�˵�λ��
      */
    int WIFI_Menu_sign = 0,  WIFI_Menu_Mark = 0;
    /**
      * @{ ÿ�ν��뺯����������Щ����������
      * @{ ��ʼ��ʾ����Ҫ��ʾ������
      */
    OLED_Clear();

    /*****************************************WIFI_Task*************************************************/
    /**
      * @{ �жϵ�ǰ�������е�����
      * @{ ����� WIFI_Task
      * @{ ��һֱ��ѭ����������
      * @{ Mark_Sign.Run_Task��ֵ���ⲿ�ж� ��������
      * @{ �ı�Mark_Sign.Run_Task��ֵ���Ϳ��Ըı���������
      */
    while(WIFI_Task == Mark_Sign.Run_Task)//����״̬ ��������WIFI����
    {
        /**
          * @{ ��ʾ��ǰѡ��ͼ��
          * @{ ͼ����ݱ�־λ�Զ��ı�
          */
        OLED_P16x16Ch(0, WIFI_Menu_sign, Choose_Icon, Normal_Display); //��ʾѡ��ͼ��
        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����ϻ���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == WIFI_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ WIFI_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, WIFI_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ
            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            WIFI_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            WIFI_Menu_sign -= 2;
            /**
              * @{ ��־λС��6
              * @{ ˵���Ѿ�������Ļ��ʾ�ķ�Χ����
              * @{ ���ǽ���־λ��6����ʾ������
              */
            if(WIFI_Menu_sign < 0)
                WIFI_Menu_sign = 6;
        }
        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����»���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
          */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == WIFI_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ NRF24L01_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, WIFI_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ
            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            WIFI_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            WIFI_Menu_sign += 2;
            /**
              * @{ ��־λ����6
              * @{ ˵���Ѿ���������Ļ��ʾ�����Χ
              * @{ ���ǽ���־λ��0����ʾ��һ��
              */
            if(WIFI_Menu_sign > 6)
                WIFI_Menu_sign = 0;
        }
        /**
          *  @{ �ж�ҡ�˵�ǰ�Ƿ�������λ��
          *  @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == WIFI_Menu_Mark)
        {
            //��־λ��0��˵��ҡ���Ѿ��ص�����λ��
            WIFI_Menu_Mark = 0;
        }
        /**
          *  @{ ����ת��
          *  @{ ��0 2 4 6 ת��Ϊ1 2 3 4
          *  @{ ͬʱ��1 2 3 4�ĸ�ʽ���浽�ṹ�� Module_Mark.WIFI_Mark��
          *  @{ Module_Mark.WIFI_Mark ��ֵ�Ϳ����ж�ѡ�����
          */
        Module_Mark.WIFI_Mark = Page(WIFI_Menu_sign);
        /*****************************��ʾ��Ӧ����*************************************/

        if(1 == Module_Mark.WIFI_Mark)
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, Normal_Display);
        }
        if(2 == Module_Mark.WIFI_Mark)
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, Normal_Display);
        }
        if(3 == Module_Mark.WIFI_Mark)
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, Normal_Display);
        }
        if(4 == Module_Mark.WIFI_Mark)
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, Normal_Display);
        }

        OLED_ShowNum(16 * 6, 6, Module_Mark.WIFI_Mark, 1, SIZE_6X8, Normal_Display);
        OLED_ShowString(17 * 6, 6, "/", SIZE_6X8, Normal_Display);
        OLED_ShowString(18 * 6, 6, "4", SIZE_6X8, Normal_Display);
        /******************************************************************************/
    }
}


/************************
 ->void USB_Task_APP()
 ->USB����
 ->������� : ��
 ->������� : ��
***********************/
void USB_Task_APP(void)//USB����
{
    /**
      * @{ USB_Menu_sign �����жϵ�ǰѡ�����
      * @{ USB_Menu_Mark �����ж�ҡ�˵�λ��
      */
    int USB_Menu_sign = 0,  USB_Menu_Mark = 0;
    /**
      * @{ ÿ�ν��뺯����������Щ����������
      * @{ ��ʼ��ʾ����Ҫ��ʾ������
      */
    OLED_Clear();

    /*****************************************USB_Task*************************************************/
    /**
      * @{ �жϵ�ǰ�������е�����
      * @{ ����� USB_Task
      * @{ ��һֱ��ѭ����������
      * @{ Mark_Sign.Run_Task��ֵ���ⲿ�ж� ��������
      * @{ �ı�Mark_Sign.Run_Task��ֵ���Ϳ��Ըı���������
      */
    while(USB_Task == Mark_Sign.Run_Task)//����״̬ ��������USB����
    {
        /**
          * @{ ��ʾ��ǰѡ��ͼ��
          * @{ ͼ����ݱ�־λ�Զ��ı�
          */
        OLED_P16x16Ch(0, USB_Menu_sign, Choose_Icon, Normal_Display); //��ʾѡ��ͼ��
        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����ϻ���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == USB_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ USB_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, USB_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ
            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            USB_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            USB_Menu_sign -= 2;
            /**
              * @{ ��־λС��6
              * @{ ˵���Ѿ�������Ļ��ʾ�ķ�Χ����
              * @{ ���ǽ���־λ��6����ʾ������
              */
            if(USB_Menu_sign < 0)
                USB_Menu_sign = 6;
        }
        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����»���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
        */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == USB_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ USB_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, USB_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ
            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            USB_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            USB_Menu_sign += 2;
            /**
              * @{ ��־λ����6
              * @{ ˵���Ѿ���������Ļ��ʾ�����Χ
              * @{ ���ǽ���־λ��0����ʾ��һ��
              */
            if(USB_Menu_sign > 6)
                USB_Menu_sign = 0;
        }
        /**
          *  @{ �ж�ҡ�˵�ǰ�Ƿ�������λ��
          *  @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == USB_Menu_Mark)
        {
            //��־λ��0��˵��ҡ���Ѿ��ص�����λ��
            USB_Menu_Mark = 0;
        }
        /**
          *  @{ ����ת��
          *  @{ ��0 2 4 6 ת��Ϊ1 2 3 4
          *  @{ ͬʱ��1 2 3 4�ĸ�ʽ���浽�ṹ�� Module_Mark.USB_Mark��
          *  @{ Module_Mark.USB_Mark ��ֵ�Ϳ����ж�ѡ�����
          */
        Module_Mark.USB_Mark = Page(USB_Menu_sign);
        /*****************************��ʾ��Ӧ����*************************************/

        if(1 == Module_Mark.USB_Mark)
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, Normal_Display);
        }
        if(2 == Module_Mark.USB_Mark)
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, Normal_Display);
        }
        if(3 == Module_Mark.USB_Mark)
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, Normal_Display);
        }
        if(4 == Module_Mark.USB_Mark)
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, White_Display);
        }
        else
        {
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, Normal_Display);
        }


        OLED_ShowNum(16 * 6, 6, Module_Mark.USB_Mark, 1, SIZE_6X8, Normal_Display);
        OLED_ShowString(17 * 6, 6, "/", SIZE_6X8, Normal_Display);
        OLED_ShowString(18 * 6, 6, "4", SIZE_6X8, Normal_Display);
        /******************************************************************************/
    }
}


/************************
 ->void Set_Task_APP()
 ->��������
 ->������� : ��
 ->������� : ��
***********************/
void Set_Task_APP(void)//��������
{
    /**
      * @{ Set_Menu_sign �����жϵ�ǰѡ�����
      * @{ Set_Menu_Mark �����ж�ҡ�˵�λ��
      */
    int  Set_Menu_sign = 0,  Set_Menu_Mark = 0;
    /**
      * @{ ÿ�ν��뺯����������Щ����������
      * @{ ��ʼ��ʾ����Ҫ��ʾ������
      */
    OLED_Clear();

    /*****************************************Set_Task*************************************************/
    /**
      * @{ �жϵ�ǰ�������е�����
      * @{ ����� Set_Task
      * @{ ��һֱ��ѭ����������
      * @{ Mark_Sign.Run_Task��ֵ���ⲿ�ж� ��������
      * @{ �ı�Mark_Sign.Run_Task��ֵ���Ϳ��Ըı���������
      */
    while(Set_Task == Mark_Sign.Run_Task)//����״̬ ����������������
    {
        /**
          * @{ ��ʾ��ǰѡ��ͼ��
          * @{ ͼ����ݱ�־λ�Զ��ı�
          */
        OLED_P16x16Ch(0, Set_Menu_sign, Choose_Icon, Normal_Display);


        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����ϻ���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
        */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Set_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ Set_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, Set_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ
            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            Set_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
              */
            Set_Menu_sign -= 2;
            /**
              * @{ ��־λС��6
              * @{ ˵���Ѿ�������Ļ��ʾ�ķ�Χ����
              * @{ ���ǽ���־λ��6����ʾ������
              */
            if(Set_Menu_sign < 0)
                Set_Menu_sign = 6;
        }
        /*****************************************ҡ�˿���*************************************************/
        /**
          * @{ �ж�ҡ���Ƿ����»���
          * @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          * @{ ���֮ǰ����������ô��Ҫ�ȴ�ҡ�˻ص�����λ�ú�����ٴλ���
        */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Set_Menu_Mark)
        {
            /**
              * @{ ���֮ǰ��ʾ��ͼ��
              * @{ Set_Menu_sign�������ϴ���ʾͼ���λ��
              */
            OLED_P16x16Ch(0, Set_Menu_sign, Remove, Normal_Display); //���֮ǰ����ʾ
            /**
              * @{ ��־λ��1��˵���Ѿ����»�����
              * @{ Ҫ�ȴ�ҡ�˻ص�����λ���־λ��0�����ٴλ���
              */
            Set_Menu_Mark = 1;
            /**
              *  @{ ��־λ��2����ΪOLED����ʾ��0-6
              *  @{ Ҳ����0�����һ��
              *  @{ 2����ڶ���
              *  @{ 4���������
              *  @{ 6���������
             */
            Set_Menu_sign += 2;
            /**
              * @{ ��־λ����6
              * @{ ˵���Ѿ���������Ļ��ʾ�����Χ
              * @{ ���ǽ���־λ��0����ʾ��һ��
             */
            if(Set_Menu_sign > 6)
                Set_Menu_sign = 0;
        }
        /**
          *  @{ �ж�ҡ�˵�ǰ�Ƿ�������λ��
          *  @{ �ж�֮ǰ�Ƿ񻬶���ҡ��
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == Set_Menu_Mark)
        {
            //��־λ��0��˵��ҡ���Ѿ��ص�����λ��
            Set_Menu_Mark = 0;
        }
        /**
          *  @{ ����ת��
          *  @{ ��0 2 4 6 ת��Ϊ1 2 3 4
          *  @{ ͬʱ��1 2 3 4�ĸ�ʽ���浽�ṹ�� Module_Mark.Set_Mark��
          *  @{ Module_Mark.Set_Mark ��ֵ�Ϳ����ж�ѡ�����
          */
        Module_Mark.Set_Mark = Page(Set_Menu_sign);
        /*****************************��ʾ��Ӧ����*************************************/
        if(1 == Module_Mark.Set_Mark)
        {
            /*//ʱ������
            OLED_P16x16Ch(1 * 16, 0, 52, 0);
            OLED_P16x16Ch(2 * 16, 0, 53, 0);
            OLED_P16x16Ch(3 * 16, 0, 50, 0);
            OLED_P16x16Ch(4 * 16, 0, 51, 0);*/
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, White_Display);
        }
        else
        {
            /*//ʱ������
            OLED_P16x16Ch(1 * 16, 0, 52, 1);
            OLED_P16x16Ch(2 * 16, 0, 53, 1);
            OLED_P16x16Ch(3 * 16, 0, 50, 1);
            OLED_P16x16Ch(4 * 16, 0, 51, 1);*/
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, Normal_Display);
        }

        if(2 == Module_Mark.Set_Mark)
        {
            /* //��ѹ����
             OLED_P16x16Ch(1 * 16, 2, 54, 0);
             OLED_P16x16Ch(2 * 16, 2, 55, 0);
             OLED_P16x16Ch(3 * 16, 2, 50, 0);
             OLED_P16x16Ch(4 * 16, 2, 51, 0);*/
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, White_Display);
        }

        else
        {
            /* //��ѹ����
             OLED_P16x16Ch(1 * 16, 2, 54, 1);
             OLED_P16x16Ch(2 * 16, 2, 55, 1);
             OLED_P16x16Ch(3 * 16, 2, 50, 1);
             OLED_P16x16Ch(4 * 16, 2, 51, 1);*/
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, Normal_Display);
        }

        if(3 == Module_Mark.Set_Mark)
        {
            /*//�ָ���������
            OLED_P16x16Ch(1 * 16, 4, 57, 0);
            OLED_P16x16Ch(2 * 16, 4, 58, 0);
            OLED_P16x16Ch(3 * 16, 4, 59, 0);
            OLED_P16x16Ch(4 * 16, 4, 60, 0);
            OLED_P16x16Ch(5 * 16, 4, 50, 0);
            OLED_P16x16Ch(6 * 16, 4, 51, 0);*/
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, White_Display);
        }

        else
        {
            /*//�ָ���������
            OLED_P16x16Ch(1 * 16, 4, 57, 1);
            OLED_P16x16Ch(2 * 16, 4, 58, 1);
            OLED_P16x16Ch(3 * 16, 4, 59, 1);
            OLED_P16x16Ch(4 * 16, 4, 60, 1);
            OLED_P16x16Ch(5 * 16, 4, 50, 1);
            OLED_P16x16Ch(6 * 16, 4, 51, 1);*/
            OLED_ShowString(1 * 16, 4, "3:", SIZE_8X16, Normal_Display);
        }

        if(4 == Module_Mark.Set_Mark)
        {
            /*//ϵͳ�汾
            OLED_P16x16Ch(1 * 16, 6, 61, 0);
            OLED_P16x16Ch(2 * 16, 6, 62, 0);
            OLED_P16x16Ch(3 * 16, 6, 63, 0);
            OLED_P16x16Ch(4 * 16, 6, 64, 0);*/
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, White_Display);
        }

        else
        {
            /*//ϵͳ�汾
            OLED_P16x16Ch(1 * 16, 6, 61, 1);
            OLED_P16x16Ch(2 * 16, 6, 62, 1);
            OLED_P16x16Ch(3 * 16, 6, 63, 1);
            OLED_P16x16Ch(4 * 16, 6, 64, 1);*/
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, Normal_Display);
        }

        OLED_ShowNum(16 * 6, 6, Module_Mark.Set_Mark , 1, SIZE_6X8, Normal_Display);
        OLED_ShowString(17 * 6, 6, "/", SIZE_6X8, Normal_Display);
        OLED_ShowString(18 * 6, 6, "4", SIZE_6X8, Normal_Display);
        /******************************************************************************/
    }
}


