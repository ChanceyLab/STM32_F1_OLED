#include "exti.h"



void KEY_EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//ʹ�ܸ��ù���ʱ��

    //ӳ�� GBIOC6-GBIOC9 IO�ڵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
    //GPIO6-9 �ж����Լ��жϳ�ʼ������   �½��ش���
    EXTI_InitStructure.EXTI_Line = EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���KEY1-4���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
}

//�жϷ����� 6-9��
void EXTI9_5_IRQHandler(void)
{
    /*������������*/
    delay_ms(10);

    if(DISABLE == KEY_Return)
    {
        /***�˳��������е�����***/
        Mark_Sign.Run_Task = Stop;
        


        /*******���ص����������*****/
        Mark_Sign.Interface_Mark = Main_Interface;


    }

    else if(DISABLE == KEY_Menu_Determine)
    {

    }





    /*
     * 1,��⵱ǰ���µİ���Ϊȷ�ϼ�
     * 2,��⵱ǰ�Ľ���
     *                (1)����������棬�����˵�����
     *                (2)����ǲ˵����棬������������
     *                (3)�����������棬��ִ�б�ѡ�е�����
     */
    /***********************************��ҡ�˰���*****�˵� ȷ�ϰ���******************************/
    else if(DISABLE == KEY_Rocker_Left)
    {
        //�����²˵���ʱ���жϵ�ǰ����

        /************�жϵ�ǰ����Ϊ������***********************/
        if(Main_Interface == Mark_Sign.Interface_Mark)
        {
            /**************����˵�����*************/
            Mark_Sign.Interface_Mark = Menu_Interface;
        }

        /************�жϵ�ǰ����Ϊ�˵�����*******************/
        else if(Menu_Interface == Mark_Sign.Interface_Mark)
        {
            /***************�����������************/
            Mark_Sign.Interface_Mark = Task_Interface;

            /**************����ָ���Ĺ�������*******/
            switch(Mark_Sign.Task_Mark)
            {
            /**************��ʼ����2.4G����*******/
            case NRF24L01_Task:
                Mark_Sign.Run_Task = NRF24L01_Task;
                break;
            /**************��ʼ������������*******/
            case Bluetooth_Task:
                Mark_Sign.Run_Task = Bluetooth_Task;
                break;
            /**************��ʼ����WIFI����*******/
            case WIFI_Task:
                Mark_Sign.Run_Task = WIFI_Task;
                break;
            /**************��ʼ����USB����*******/
            case USB_Task:
                Mark_Sign.Run_Task = USB_Task;
                break;
            /**************��ʼ������������*******/
            case Set_Task:
                Mark_Sign.Run_Task = Set_Task;
                break;
            default:
                break;
            }
        }

        /************�жϵ�ǰ����Ϊ�������******************/
        else if(Task_Interface == Mark_Sign.Interface_Mark)
        {
            /*******�жϵ�ǰ�������е�����*******/
            switch(Mark_Sign.Run_Task)
            {
            /*��ǰ�������� 2.4G����*/
            case NRF24L01_Task:
                
                break;


            /*��ǰ�������� 2.4G����*/
            case Bluetooth_Task:

                break;


            /*��ǰ�������� 2.4G����*/
            case WIFI_Task:

                break;


            /*��ǰ�������� 2.4G����*/
            case USB_Task:

                break;


            /*��ǰ�������� 2.4G����*/
            case Set_Task:

                break;
            default:
                break;

            }
        }
    }

    /*
     * 1,��⵱ǰ���µİ���Ϊ���ؼ�
     * 2,��⵱ǰ�Ľ���
     *             (1)�����������棬��ֹͣ�������е����񣬷��ص��˵�����
     *             (2)����ǲ˵����棬�򷵻ص�������
     */
    /*************************************��ҡ�˰���****���ذ���*****************************/
    else if(DISABLE == KEY_Rocker_Right)
    {
        //�����·��ؼ�ʱ���жϵ�ǰ����

        /************�жϵ�ǰ����Ϊ�˵�����*******************/
        if(Menu_Interface == Mark_Sign.Interface_Mark)
        {
            /*******�˳��˵�����***����������**/
            Mark_Sign.Interface_Mark = Main_Interface;
        }

        /************�жϵ�ǰ����Ϊ���ܽ���******************/
        else if(Task_Interface == Mark_Sign.Interface_Mark)
        {
            
                /***�˳��������е�����***/
                Mark_Sign.Run_Task = Stop;
                /*******�˳����ܽ���*****/
                Mark_Sign.Interface_Mark = Menu_Interface;
            
            

        }


    }
    /*******************���LINE6-9�ϵ��жϱ�־λ************/
    EXTI_ClearITPendingBit(EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9);
}



