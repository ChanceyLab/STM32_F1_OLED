#include <DISPLAY.H>
#include "BMP.h"

Mark Mark_Sign;//状态标志位
Module_mark Module_Mark;//模块状态
Module_choose Module_Choose;//选择
/************************
 ->u8 Detection_Hardware_Drive()
 ->判断硬件状态
 ->输入参数 : 无
 ->输出参数 : 硬件状态
 ->
***********************/
u8 Detection_Hardware_Drive(void)//判断硬件状态
{
    static u8 sign = 0;
    //判断硬件是首次加载
    if(0 == sign)
    {
        if(0 == Module_Mark.NRF24L01_Mark) //检测不到24L01
        {
            OLED_P32x32Ch(3 * 16, 2, 7, 1); //显示2.4G模块加载失败
            //显示汉字  模块加载失败
            OLED_P16x16Ch(1 * 16, 6, 88, 1);
            OLED_P16x16Ch(2 * 16, 6, 89, 1);
            OLED_P16x16Ch(3 * 16, 6, 92, 1);
            OLED_P16x16Ch(4 * 16, 6, 93, 1);
            OLED_P16x16Ch(5 * 16, 6, 90, 1);
            OLED_P16x16Ch(6 * 16, 6, 91, 1);
            Module_Mark.NRF24L01_Mark = 0; //2.4G模块状态置0，说明模块加载失败
            delay_ms(1000);
        }
        else if(1 == Module_Mark.NRF24L01_Mark)//检测到24L01
        {
            OLED_P32x32Ch(3 * 16, 2, 8, 1); //显示2.4G模块加载成功
            //显示汉字  模块加载成功
            OLED_P16x16Ch(1 * 16, 6, 88, 1);
            OLED_P16x16Ch(2 * 16, 6, 89, 1);
            OLED_P16x16Ch(3 * 16, 6, 92, 1);
            OLED_P16x16Ch(4 * 16, 6, 93, 1);
            OLED_P16x16Ch(5 * 16, 6, 77, 1);
            OLED_P16x16Ch(6 * 16, 6, 78, 1);
            Module_Mark.NRF24L01_Mark = 1; //2.4G模块状态置1，说明模块加载成功
            delay_ms(1000);
        }
        OLED_Clear();
        sign = 1; //标志位置1，说明已经加载过一次
    }
    //检测硬件不是首次加载
    if(1 == sign)
    {
        if(Module_Mark.NRF24L01_Mark)
            OLED_P16x16Ch(0 * 16, 0, 38, 1);       //显示2.4G图标
        else
            OLED_P16x16Ch(0 * 16, 0, 37, 1);      //显示
    }


    //    OLED_P16x16Ch(3.4 * 16, 6, 87, 1);     //显示USB图标
    OLED_P16x16Ch(1 * 16, 0, 33, 1);       //显示WIFI图标
    OLED_P16x16Ch(2 * 16, 0, 5, 1);        //显示蓝牙图标
    OLED_P16x16Ch(111, 0, 86, 1);           //显示3V3
    return 0;
}


/************************
 ->void Picture(u8 picture)
 ->显示相关图片
 ->输入参数 : 图片号
 ->输出参数 : 无
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
        Draw_BMP(0, 0, 128, 8, WIFI);      //显示WIFI图片
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
 ->显示主界面
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void Main_Interface_APP(void)//显示主界面
{
    OLED_Clear();
    OLED_P128x32Ch(0, 3, 0);//显示ETA图标
    while(Main_Interface == Mark_Sign.Interface_Mark) //界面状态 主界面
    {
        OLED_P16x16Ch(0 * 16, 6, 84, 1);       //显示菜单图标
        Detection_Hardware_Drive();            //显示硬件状态
        OLED_P16x16Ch(112, 6, 87, 1);          //显示USB图标


        OLED_P8x16Ch(5.5 * 8, 2, Teme.Points / 10); //显示分钟高位
        OLED_P8x16Ch(6.5 * 8, 2, Teme.Points % 10); //显示分钟低位
        OLED_P8x16Ch(8.5 * 8, 2, Teme.Seconds / 10); //显示秒钟高位
        OLED_P8x16Ch(9.5 * 8, 2, Teme.Seconds % 10); //显示秒钟低位
        /**********中间的小数点一秒闪一次*************/
        if(Teme.Point)
            OLED_P8x16Ch(7.5 * 8, 2, 10);
        else
            OLED_P8x16Ch(7.5 * 8, 2, 11);
        /*********************************************/
    }
}


/************************
 ->void Menu_Interface_APP()
 ->显示菜单界面
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void Menu_Interface_APP(void)//显示菜单界面
{
    static int  Menu_Sign = 0, Menu_Mark = 0;
    OLED_Clear();
    while(Menu_Interface == Mark_Sign.Interface_Mark) //界面状态 菜单界面
    {
        OLED_P16x16Ch(0 * 16, 0, 38, 1);       //显示2.4G图标
        OLED_P16x16Ch(1 * 16, 0, 33, 1);       //显示WIFI图标
        OLED_P16x16Ch(2 * 16, 0, 5, 1);        //显示蓝牙图标
        OLED_P16x16Ch(111, 0, 4, 1);           //显示电量图标

        //显示确定
        OLED_P16x16Ch(0 * 16, 6, 31, 1);
        OLED_P16x16Ch(1 * 16, 6, 32, 1);
        //显示返回图标
        OLED_P16x16Ch(112, 6, 83, 1);

        OLED_P32x32Ch(0, 2, 5, 1); //显示向左箭头
        OLED_P32x32Ch(95, 2, 6, 1); //显示向右箭头

        /****************显示对应菜单栏*******************/
        switch(Menu_Sign)
        {
        case NRF24L01_Task:
            OLED_P32x32Ch(48, 2, 0, 1); //显示2.4G遥控器图标
            //显示2.4G字符
            OLED_ShowString(3 * 16, 6, "2.4G", 16, 1);
            break;
        case Bluetooth_Task:
            OLED_P32x32Ch(48, 2, 1, 1); //显示蓝牙图标
            //显示蓝牙汉字
            OLED_P16x16Ch(3 * 16, 6, 65, 1);
            OLED_P16x16Ch(4 * 16, 6, 66, 1);
            break;
        case WIFI_Task:
            OLED_P32x32Ch(48, 2, 2, 1); //显示WIFI图标
            //显示WIFI字符
            OLED_ShowString(3 * 16, 6, "WIFI", 16, 1);
            break;
        case USB_Task:
            OLED_P32x32Ch(48, 2, 3, 1); //显示USB图标
            //显示USB字符
            OLED_ShowString(2.8 * 16, 6, " USB ", 16, 1);
            break;
        case Set_Task:
            OLED_P32x32Ch(48, 2, 4, 1); //显示设置图标
            //显示设置汉字
            OLED_P16x16Ch(3 * 16, 6, 50, 1);
            OLED_P16x16Ch(4 * 16, 6, 51, 1);
            break;
        default:
            break;
        }
        /*****************************************摇杆控制*************************************************/
        //判断摇杆向右滑杆
        if(Right_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Menu_Mark)
        {
            Menu_Sign++;
            Menu_Mark = 1;
            if(Menu_Sign > number)
                Menu_Sign = 0;
        }
        //判断摇杆向左滑杆
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

        Mark_Sign.Task_Mark = Menu_Sign; //读取当前选择的任务
    }
    /***********************************************************************************************/
}


/************************
 ->void Function_Menu()
 ->显示功能界面
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void Function_Menu_APP(void)//显示功能界面
{
    while(Task_Interface == Mark_Sign.Interface_Mark) //界面状态 任务界面
    {
        /**********开始运行对应任务**************/
        switch(Mark_Sign.Run_Task)
        {
        case NRF24L01_Task:
            /*******2.4G任务********/
            NRF24L01_Task_APP();
            break;
        case Bluetooth_Task:
            /*******蓝牙任务********/
            Bluetooth_Task_APP();
            break;
        case WIFI_Task:
            /*******WIFI任务********/
            WIFI_Task_APP();
            break;
        case USB_Task:
            /*******USB任务********/
            USB_Task_APP();
            break;
        case Set_Task:
            /*******设置任务********/
            Set_Task_APP();
            break;
        default :
            break;
        }
    }

}


/************************
 ->void Rocker_Display()
 ->显示摇杆值
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void Rocker_Display_Drive(void)//显示摇杆值
{
    int count = 0, Data[4] = {0, 0, 0, 0}, Average[4] = {0, 0, 0, 0};
    /************************************显示AD值，摇杆***************************/
    OLED_Clear();
    OLED_DrawBMP(0, 0, 128, 8, M2);

    //显示汉字 摇杆数据
    OLED_P16x16Ch(2 * 16, 1, 79, 1);
    OLED_P16x16Ch(3 * 16, 1, 80, 1);
    OLED_P16x16Ch(4 * 16, 1, 81, 1);
    OLED_P16x16Ch(5 * 16, 1, 82, 1);

    OLED_P16x16Ch(0 * 16, 6, 84, 1); //显示菜单图标
    OLED_P16x16Ch(112, 6, 83, 1); //显示返回图标
    while(1)
    {
        count++;
        //---读取数据 求平均值
        Data[0] += Get_Adc(Left_Rocker_X);
        Data[1] += Get_Adc(Left_Rocker_Y);
        Data[2] += Get_Adc(Right_Rocker_X);
        Data[3] += Get_Adc(Right_Rocker_Y);
        //---判断是否到次数
        if(count == 40)
        {
            //---求出平均值
            Average[0] = Data[0] / 40;
            Average[1] = Data[1] / 40;
            Average[2] = Data[2] / 40;
            Average[3] = Data[3] / 40;
            //---置0
            Data[0] = Data[1] = Data[2] = Data[3] = 0;
            count = 0;
            //---显示相关数据
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
 ->2.4G任务
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void NRF24L01_Task_APP(void)//2.4G任务
{

    /**
      * @{ NRF24L01_Menu_sign 用于判断当前选择的行
      * @{ NRF24L01_Menu_Mark 用于判断摇杆的位置
      */
    int NRF24L01_Menu_sign = 0,  NRF24L01_Menu_Mark = 0;
    /**
      * @{ 每次进入函数，可能有些其它的数据
      * @{ 开始显示所需要显示的数据
      */
    OLED_Clear();
    /*****************************************NRF24L01_Task*************************************************/
    /**
      * @{ 判断当前正在运行的任务
      * @{ 如果是 NRF24L01_Task
      * @{ 则一直在循环里面运行
      * @{ Mark_Sign.Run_Task的值由外部中断 按键控制
      * @{ 改变Mark_Sign.Run_Task的值，就可以改变运行任务
      */
    while(NRF24L01_Task == Mark_Sign.Run_Task)//任务状态 正在运行2.4G任务
    {
        /**
          * @{ 显示当前选择图标
          * @{ 图标根据标志位自动改变
          */
        OLED_P16x16Ch(0, NRF24L01_Menu_sign, Choose_Icon, Normal_Display); //显示选择图标

        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向上滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == NRF24L01_Menu_Mark)
        {
            /**
            	* @{ 清除之前显示的图标
              * @{ NRF24L01_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, NRF24L01_Menu_sign, Remove, Normal_Display);


            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            NRF24L01_Menu_Mark = 1;
            /**
              *  @{ 标志位减2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            NRF24L01_Menu_sign -= 2;
            /**
              * @{ 标志位小于6
              * @{ 说明已经不在屏幕显示的范围以内
              * @{ 我们将标志位置6，显示第四行
              */
            if(NRF24L01_Menu_sign < 0)
                NRF24L01_Menu_sign = 6;
        }
        /**
          * @{ 判断摇杆是否向下滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
          */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == NRF24L01_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ NRF24L01_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, NRF24L01_Menu_sign, Remove, Normal_Display); //清除之前的显示

            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            NRF24L01_Menu_Mark = 1;

            /**
              *  @{ 标志位加2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            NRF24L01_Menu_sign += 2;
            /**
              * @{ 标志位大于6
              * @{ 说明已经超过了屏幕显示的最大范围
              * @{ 我们将标志位置0，显示第一行
              */
            if(NRF24L01_Menu_sign > 6)
                NRF24L01_Menu_sign = 0;
        }
        /**
          *  @{ 判断摇杆当前是否在中心位置
          *  @{ 判断之前是否滑动过摇杆
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == NRF24L01_Menu_Mark)
        {
            //标志位置0，说明摇杆已经回到中心位置
            NRF24L01_Menu_Mark = 0;
        }
        /**
          *  @{ 数据转换
          *  @{ 把0 2 4 6 转换为1 2 3 4
        	*  @{ 同时以1 2 3 4的格式保存到结构体 Module_Mark.NRF24L01_Mark中
        	*  @{ 根据Module_Mark.NRF24L01_Mark 的值就可以判断选择的项
          */
        Module_Mark.NRF24L01_Mark = Page(NRF24L01_Menu_sign);
        /*****************************显示对应数据*************************************/
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
 ->蓝牙任务
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void Bluetooth_Task_APP(void)//蓝牙任务
{
    /**
      * @{ Bluetooth_Menu_sign 用于判断当前选择的行
      * @{ Bluetooth_Menu_Mark 用于判断摇杆的位置
      */
    int Bluetooth_Menu_sign = 0,  Bluetooth_Menu_Mark = 0;
    /**
      * @{ 每次进入函数，可能有些其它的数据
      * @{ 开始显示所需要显示的数据
      */
    OLED_Clear();

    /*****************************************Bluetooth_Task*************************************************/
    /**
      * @{ 判断当前正在运行的任务
      * @{ 如果是 Bluetooth_Task
      * @{ 则一直在循环里面运行
      * @{ Mark_Sign.Run_Task的值由外部中断 按键控制
      * @{ 改变Mark_Sign.Run_Task的值，就可以改变运行任务
      */
    while(Bluetooth_Task == Mark_Sign.Run_Task)//任务状态 正在运行蓝牙任务
    {
        /**
          * @{ 显示当前选择图标
          * @{ 图标根据标志位自动改变
          */
        OLED_P16x16Ch(0, Bluetooth_Menu_sign, Choose_Icon, Normal_Display); //显示选择图标
        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向上滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Bluetooth_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ Bluetooth_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, Bluetooth_Menu_sign, Remove, Normal_Display); //清除之前的显示

            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            Bluetooth_Menu_Mark = 1;
            /**
              *  @{ 标志位减2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            Bluetooth_Menu_sign -= 2;
            /**
              * @{ 标志位小于6
              * @{ 说明已经不在屏幕显示的范围以内
              * @{ 我们将标志位置6，显示第四行
              */
            if(Bluetooth_Menu_sign < 0)
                Bluetooth_Menu_sign = 6;
        }
        //判断摇杆向下滑杆
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Bluetooth_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ Bluetooth_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, Bluetooth_Menu_sign, Remove, Normal_Display); //清除之前的显示
            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            Bluetooth_Menu_Mark = 1;
            /**
              *  @{ 标志位加2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            Bluetooth_Menu_sign += 2;
            /**
              * @{ 标志位大于6
              * @{ 说明已经超过了屏幕显示的最大范围
              * @{ 我们将标志位置0，显示第一行
              */
            if(Bluetooth_Menu_sign > 6)
                Bluetooth_Menu_sign = 0;
        }
        /**
          *  @{ 判断摇杆当前是否在中心位置
          *  @{ 判断之前是否滑动过摇杆
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == Bluetooth_Menu_Mark)
        {
            //标志位置0，说明摇杆已经回到中心位置
            Bluetooth_Menu_Mark = 0;
        }
        /**
          *  @{ 数据转换
          *  @{ 把0 2 4 6 转换为1 2 3 4
          *  @{ 同时以1 2 3 4的格式保存到结构体 Module_Mark.Bluetooth_Mark中
          *  @{ 根据Module_Mark.Bluetooth_Mark 的值就可以判断选择的项
          */
        Module_Mark.Bluetooth_Mark = Page(Bluetooth_Menu_sign);
        /*****************************显示对应数据*************************************/

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
 ->WIFI任务
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void WIFI_Task_APP(void)//WIFI任务
{
    /**
      * @{ WIFI_Menu_sign 用于判断当前选择的行
      * @{ WIFI_Menu_Mark 用于判断摇杆的位置
      */
    int WIFI_Menu_sign = 0,  WIFI_Menu_Mark = 0;
    /**
      * @{ 每次进入函数，可能有些其它的数据
      * @{ 开始显示所需要显示的数据
      */
    OLED_Clear();

    /*****************************************WIFI_Task*************************************************/
    /**
      * @{ 判断当前正在运行的任务
      * @{ 如果是 WIFI_Task
      * @{ 则一直在循环里面运行
      * @{ Mark_Sign.Run_Task的值由外部中断 按键控制
      * @{ 改变Mark_Sign.Run_Task的值，就可以改变运行任务
      */
    while(WIFI_Task == Mark_Sign.Run_Task)//任务状态 正在运行WIFI任务
    {
        /**
          * @{ 显示当前选择图标
          * @{ 图标根据标志位自动改变
          */
        OLED_P16x16Ch(0, WIFI_Menu_sign, Choose_Icon, Normal_Display); //显示选择图标
        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向上滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == WIFI_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ WIFI_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, WIFI_Menu_sign, Remove, Normal_Display); //清除之前的显示
            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            WIFI_Menu_Mark = 1;
            /**
              *  @{ 标志位减2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            WIFI_Menu_sign -= 2;
            /**
              * @{ 标志位小于6
              * @{ 说明已经不在屏幕显示的范围以内
              * @{ 我们将标志位置6，显示第四行
              */
            if(WIFI_Menu_sign < 0)
                WIFI_Menu_sign = 6;
        }
        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向下滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
          */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == WIFI_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ NRF24L01_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, WIFI_Menu_sign, Remove, Normal_Display); //清除之前的显示
            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            WIFI_Menu_Mark = 1;
            /**
              *  @{ 标志位加2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            WIFI_Menu_sign += 2;
            /**
              * @{ 标志位大于6
              * @{ 说明已经超过了屏幕显示的最大范围
              * @{ 我们将标志位置0，显示第一行
              */
            if(WIFI_Menu_sign > 6)
                WIFI_Menu_sign = 0;
        }
        /**
          *  @{ 判断摇杆当前是否在中心位置
          *  @{ 判断之前是否滑动过摇杆
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == WIFI_Menu_Mark)
        {
            //标志位置0，说明摇杆已经回到中心位置
            WIFI_Menu_Mark = 0;
        }
        /**
          *  @{ 数据转换
          *  @{ 把0 2 4 6 转换为1 2 3 4
          *  @{ 同时以1 2 3 4的格式保存到结构体 Module_Mark.WIFI_Mark中
          *  @{ Module_Mark.WIFI_Mark 的值就可以判断选择的项
          */
        Module_Mark.WIFI_Mark = Page(WIFI_Menu_sign);
        /*****************************显示对应数据*************************************/

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
 ->USB任务
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void USB_Task_APP(void)//USB任务
{
    /**
      * @{ USB_Menu_sign 用于判断当前选择的行
      * @{ USB_Menu_Mark 用于判断摇杆的位置
      */
    int USB_Menu_sign = 0,  USB_Menu_Mark = 0;
    /**
      * @{ 每次进入函数，可能有些其它的数据
      * @{ 开始显示所需要显示的数据
      */
    OLED_Clear();

    /*****************************************USB_Task*************************************************/
    /**
      * @{ 判断当前正在运行的任务
      * @{ 如果是 USB_Task
      * @{ 则一直在循环里面运行
      * @{ Mark_Sign.Run_Task的值由外部中断 按键控制
      * @{ 改变Mark_Sign.Run_Task的值，就可以改变运行任务
      */
    while(USB_Task == Mark_Sign.Run_Task)//任务状态 正在运行USB任务
    {
        /**
          * @{ 显示当前选择图标
          * @{ 图标根据标志位自动改变
          */
        OLED_P16x16Ch(0, USB_Menu_sign, Choose_Icon, Normal_Display); //显示选择图标
        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向上滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
          */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == USB_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ USB_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, USB_Menu_sign, Remove, Normal_Display); //清除之前的显示
            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            USB_Menu_Mark = 1;
            /**
              *  @{ 标志位减2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            USB_Menu_sign -= 2;
            /**
              * @{ 标志位小于6
              * @{ 说明已经不在屏幕显示的范围以内
              * @{ 我们将标志位置6，显示第四行
              */
            if(USB_Menu_sign < 0)
                USB_Menu_sign = 6;
        }
        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向下滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
        */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == USB_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ USB_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, USB_Menu_sign, Remove, Normal_Display); //清除之前的显示
            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            USB_Menu_Mark = 1;
            /**
              *  @{ 标志位加2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            USB_Menu_sign += 2;
            /**
              * @{ 标志位大于6
              * @{ 说明已经超过了屏幕显示的最大范围
              * @{ 我们将标志位置0，显示第一行
              */
            if(USB_Menu_sign > 6)
                USB_Menu_sign = 0;
        }
        /**
          *  @{ 判断摇杆当前是否在中心位置
          *  @{ 判断之前是否滑动过摇杆
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == USB_Menu_Mark)
        {
            //标志位置0，说明摇杆已经回到中心位置
            USB_Menu_Mark = 0;
        }
        /**
          *  @{ 数据转换
          *  @{ 把0 2 4 6 转换为1 2 3 4
          *  @{ 同时以1 2 3 4的格式保存到结构体 Module_Mark.USB_Mark中
          *  @{ Module_Mark.USB_Mark 的值就可以判断选择的项
          */
        Module_Mark.USB_Mark = Page(USB_Menu_sign);
        /*****************************显示对应数据*************************************/

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
 ->设置任务
 ->输入参数 : 无
 ->输出参数 : 无
***********************/
void Set_Task_APP(void)//设置任务
{
    /**
      * @{ Set_Menu_sign 用于判断当前选择的行
      * @{ Set_Menu_Mark 用于判断摇杆的位置
      */
    int  Set_Menu_sign = 0,  Set_Menu_Mark = 0;
    /**
      * @{ 每次进入函数，可能有些其它的数据
      * @{ 开始显示所需要显示的数据
      */
    OLED_Clear();

    /*****************************************Set_Task*************************************************/
    /**
      * @{ 判断当前正在运行的任务
      * @{ 如果是 Set_Task
      * @{ 则一直在循环里面运行
      * @{ Mark_Sign.Run_Task的值由外部中断 按键控制
      * @{ 改变Mark_Sign.Run_Task的值，就可以改变运行任务
      */
    while(Set_Task == Mark_Sign.Run_Task)//任务状态 正在运行设置任务
    {
        /**
          * @{ 显示当前选择图标
          * @{ 图标根据标志位自动改变
          */
        OLED_P16x16Ch(0, Set_Menu_sign, Choose_Icon, Normal_Display);


        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向上滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
        */
        if(On_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Set_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ Set_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, Set_Menu_sign, Remove, Normal_Display); //清除之前的显示
            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            Set_Menu_Mark = 1;
            /**
              *  @{ 标志位减2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
              */
            Set_Menu_sign -= 2;
            /**
              * @{ 标志位小于6
              * @{ 说明已经不在屏幕显示的范围以内
              * @{ 我们将标志位置6，显示第四行
              */
            if(Set_Menu_sign < 0)
                Set_Menu_sign = 6;
        }
        /*****************************************摇杆控制*************************************************/
        /**
          * @{ 判断摇杆是否向下滑动
          * @{ 判断之前是否滑动过摇杆
          * @{ 如果之前滑动过，那么就要等待摇杆回到中心位置后才能再次滑动
        */
        else if(Under_Double == Rocker_Detection_Drive(_Right_Rocker_) && 0 == Set_Menu_Mark)
        {
            /**
              * @{ 清除之前显示的图标
              * @{ Set_Menu_sign保存了上次显示图标的位置
              */
            OLED_P16x16Ch(0, Set_Menu_sign, Remove, Normal_Display); //清除之前的显示
            /**
              * @{ 标志位置1，说明已经向下滑动过
              * @{ 要等待摇杆回到中心位后标志位置0才能再次滑动
              */
            Set_Menu_Mark = 1;
            /**
              *  @{ 标志位加2，因为OLED屏显示从0-6
              *  @{ 也就是0代表第一行
              *  @{ 2代表第二行
              *  @{ 4代表的三行
              *  @{ 6代表第四行
             */
            Set_Menu_sign += 2;
            /**
              * @{ 标志位大于6
              * @{ 说明已经超过了屏幕显示的最大范围
              * @{ 我们将标志位置0，显示第一行
             */
            if(Set_Menu_sign > 6)
                Set_Menu_sign = 0;
        }
        /**
          *  @{ 判断摇杆当前是否在中心位置
          *  @{ 判断之前是否滑动过摇杆
          */
        else if(0 == Rocker_Detection_Drive(_Right_Rocker_) && 1 == Set_Menu_Mark)
        {
            //标志位置0，说明摇杆已经回到中心位置
            Set_Menu_Mark = 0;
        }
        /**
          *  @{ 数据转换
          *  @{ 把0 2 4 6 转换为1 2 3 4
          *  @{ 同时以1 2 3 4的格式保存到结构体 Module_Mark.Set_Mark中
          *  @{ Module_Mark.Set_Mark 的值就可以判断选择的项
          */
        Module_Mark.Set_Mark = Page(Set_Menu_sign);
        /*****************************显示对应数据*************************************/
        if(1 == Module_Mark.Set_Mark)
        {
            /*//时钟设置
            OLED_P16x16Ch(1 * 16, 0, 52, 0);
            OLED_P16x16Ch(2 * 16, 0, 53, 0);
            OLED_P16x16Ch(3 * 16, 0, 50, 0);
            OLED_P16x16Ch(4 * 16, 0, 51, 0);*/
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, White_Display);
        }
        else
        {
            /*//时钟设置
            OLED_P16x16Ch(1 * 16, 0, 52, 1);
            OLED_P16x16Ch(2 * 16, 0, 53, 1);
            OLED_P16x16Ch(3 * 16, 0, 50, 1);
            OLED_P16x16Ch(4 * 16, 0, 51, 1);*/
            OLED_ShowString(1 * 16, 0, "1:", SIZE_8X16, Normal_Display);
        }

        if(2 == Module_Mark.Set_Mark)
        {
            /* //电压设置
             OLED_P16x16Ch(1 * 16, 2, 54, 0);
             OLED_P16x16Ch(2 * 16, 2, 55, 0);
             OLED_P16x16Ch(3 * 16, 2, 50, 0);
             OLED_P16x16Ch(4 * 16, 2, 51, 0);*/
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, White_Display);
        }

        else
        {
            /* //电压设置
             OLED_P16x16Ch(1 * 16, 2, 54, 1);
             OLED_P16x16Ch(2 * 16, 2, 55, 1);
             OLED_P16x16Ch(3 * 16, 2, 50, 1);
             OLED_P16x16Ch(4 * 16, 2, 51, 1);*/
            OLED_ShowString(1 * 16, 2, "2:", SIZE_8X16, Normal_Display);
        }

        if(3 == Module_Mark.Set_Mark)
        {
            /*//恢复出厂设置
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
            /*//恢复出厂设置
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
            /*//系统版本
            OLED_P16x16Ch(1 * 16, 6, 61, 0);
            OLED_P16x16Ch(2 * 16, 6, 62, 0);
            OLED_P16x16Ch(3 * 16, 6, 63, 0);
            OLED_P16x16Ch(4 * 16, 6, 64, 0);*/
            OLED_ShowString(1 * 16, 6, "4:", SIZE_8X16, White_Display);
        }

        else
        {
            /*//系统版本
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


