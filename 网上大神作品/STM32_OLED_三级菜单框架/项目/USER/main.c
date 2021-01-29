#include "sys.h"

int main(void)
{
    delay_init();	    //延时函数初始化
    JTAG_Set(JTAG_SWD_DISABLE);
    JTAG_Set(SWD_ENABLE);

    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(9600);
    LED_Init();		  	//初始化与LED连接的硬件接口
    OLED_Init();
    NRF24L01_Init();
    Adc_Init();
    KEY_EXTIX_Init();
    TIM3_Int_Init(9999, 7199); //10Khz的计数频率，计数到5000为500ms

    Detection_Hardware_Drive();//判断硬件状态
    //硬件检测完成，进入主界面
    Mark_Sign.Interface_Mark = Main_Interface;

    while(1)
    {
        //状态标志位
        switch(Mark_Sign.Interface_Mark)
        {
        //状态标志位 主界面
        case Main_Interface:
            Main_Interface_APP();//显示主界面
            break;

        //状态标志位 菜单界面
        case Menu_Interface:
            Menu_Interface_APP();//显示菜单界面
            break;

        //状态标志位 任务界面
        case Task_Interface:
            Function_Menu_APP();//显示功能界面
            break;
        default:
            break;
        }
    }
}


