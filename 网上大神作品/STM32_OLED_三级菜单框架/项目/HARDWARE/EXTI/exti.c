#include "exti.h"



void KEY_EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//使能复用功能时钟

    //映射 GBIOC6-GBIOC9 IO口到中断线
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
    //GPIO6-9 中断线以及中断初始化配置   下降沿触发
    EXTI_InitStructure.EXTI_Line = EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY1-4所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);
}

//中断服务函数 6-9线
void EXTI9_5_IRQHandler(void)
{
    /*消除机器抖动*/
    delay_ms(10);

    if(DISABLE == KEY_Return)
    {
        /***退出正在运行的任务***/
        Mark_Sign.Run_Task = Stop;
        


        /*******返回到主界面界面*****/
        Mark_Sign.Interface_Mark = Main_Interface;


    }

    else if(DISABLE == KEY_Menu_Determine)
    {

    }





    /*
     * 1,检测当前按下的按键为确认键
     * 2,检测当前的界面
     *                (1)如果是主界面，则进入菜单界面
     *                (2)如果是菜单界面，则进入任务界面
     *                (3)如果是任务界面，则开执行被选中的任务
     */
    /***********************************左摇杆按键*****菜单 确认按键******************************/
    else if(DISABLE == KEY_Rocker_Left)
    {
        //当按下菜单键时，判断当前界面

        /************判断当前界面为主界面***********************/
        if(Main_Interface == Mark_Sign.Interface_Mark)
        {
            /**************进入菜单界面*************/
            Mark_Sign.Interface_Mark = Menu_Interface;
        }

        /************判断当前界面为菜单界面*******************/
        else if(Menu_Interface == Mark_Sign.Interface_Mark)
        {
            /***************进入任务界面************/
            Mark_Sign.Interface_Mark = Task_Interface;

            /**************进入指定的功能任务*******/
            switch(Mark_Sign.Task_Mark)
            {
            /**************开始运行2.4G任务*******/
            case NRF24L01_Task:
                Mark_Sign.Run_Task = NRF24L01_Task;
                break;
            /**************开始运行蓝牙任务*******/
            case Bluetooth_Task:
                Mark_Sign.Run_Task = Bluetooth_Task;
                break;
            /**************开始运行WIFI任务*******/
            case WIFI_Task:
                Mark_Sign.Run_Task = WIFI_Task;
                break;
            /**************开始运行USB任务*******/
            case USB_Task:
                Mark_Sign.Run_Task = USB_Task;
                break;
            /**************开始运行设置任务*******/
            case Set_Task:
                Mark_Sign.Run_Task = Set_Task;
                break;
            default:
                break;
            }
        }

        /************判断当前界面为任务界面******************/
        else if(Task_Interface == Mark_Sign.Interface_Mark)
        {
            /*******判断当前正在运行的任务*******/
            switch(Mark_Sign.Run_Task)
            {
            /*当前正在运行 2.4G任务*/
            case NRF24L01_Task:
                
                break;


            /*当前正在运行 2.4G任务*/
            case Bluetooth_Task:

                break;


            /*当前正在运行 2.4G任务*/
            case WIFI_Task:

                break;


            /*当前正在运行 2.4G任务*/
            case USB_Task:

                break;


            /*当前正在运行 2.4G任务*/
            case Set_Task:

                break;
            default:
                break;

            }
        }
    }

    /*
     * 1,检测当前按下的按键为返回键
     * 2,检测当前的界面
     *             (1)如果是任务界面，则停止正在运行的任务，返回到菜单界面
     *             (2)如果是菜单界面，则返回到主界面
     */
    /*************************************右摇杆按键****返回按键*****************************/
    else if(DISABLE == KEY_Rocker_Right)
    {
        //当按下返回键时，判断当前界面

        /************判断当前界面为菜单界面*******************/
        if(Menu_Interface == Mark_Sign.Interface_Mark)
        {
            /*******退出菜单界面***进入主界面**/
            Mark_Sign.Interface_Mark = Main_Interface;
        }

        /************判断当前界面为功能界面******************/
        else if(Task_Interface == Mark_Sign.Interface_Mark)
        {
            
                /***退出正在运行的任务***/
                Mark_Sign.Run_Task = Stop;
                /*******退出功能界面*****/
                Mark_Sign.Interface_Mark = Menu_Interface;
            
            

        }


    }
    /*******************清除LINE6-9上的中断标志位************/
    EXTI_ClearITPendingBit(EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9);
}



