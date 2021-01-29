#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "sys.h"

#define Remove     (37)             //清除
///mode:0,反白显示;1,正常显示
#define Normal_Display (1) //正常显示
#define White_Display  (0) //反白显示

#define Choose_Icon  (44) //选择图标

#define Determine_Double (Determine)         //确定
#define Menu_Double      (Menu)              //菜单
#define Return_Double    (Return)            //返回
#define Left_Double      (Left)              //左翻
#define Right_Double     (Right)             //右翻
#define On_Double        (On)                //上翻
#define Under_Double     (Under)             //下翻


/*********************************************
 * 创建一个枚举
 * 存放按下状态
*/
enum
{
    Determine = 1,   /****确定***/
    Menu      = 2,   /****菜单***/
    Return    = 3,   /****返回***/
    Left      = 4,   /****左翻***/
    Right     = 5,   /****右翻***/
    On        = 6,   /****上翻***/
    Under     = 7,   /****下翻***/
};
/*******************************************/

// 左摇杆X居中
#define Left_Rocker_X_Center  (Get_Adc(Left_Rocker_X) > 1900 &&  Get_Adc(Left_Rocker_X) < 2100)
// 左摇杆Y居中
#define Left_Rocker_Y_Center  (Get_Adc(Left_Rocker_Y) > 1900 &&  Get_Adc(Left_Rocker_Y) < 2100)
// 左摇杆在中心位置
#define Left_Rocker_Center    (Left_Rocker_X_Center && Left_Rocker_Y_Center)


// 右摇杆X居中
#define Right_Rocker_X_Center  (Get_Adc(Right_Rocker_X) > 1900 &&  Get_Adc(Right_Rocker_X) < 2100)
// 右摇杆Y居中
#define Right_Rocker_Y_Center  (Get_Adc(Right_Rocker_Y) > 1900 &&  Get_Adc(Right_Rocker_Y) < 2100)
// 右摇杆在中心位置
#define Right_Rocker_Center    (Right_Rocker_X_Center && Right_Rocker_Y_Center)

#define Page(ARE) (ARE/2+1)

/*********************************************
 * 创建一个枚举
 * 存放任务变量
*/	
enum
{
    NRF24L01_Task   = 0,   /****2.4G任务***/
    Bluetooth_Task  = 1,   /****蓝牙任务***/
    WIFI_Task       = 2,   /****WIFI任务***/
    USB_Task        = 3,   /****USB任务***/
    Set_Task        = 4,   /****设置任务***/
};
/*******************************************/


/*********************************************
 * 创建一个枚举
 * 存放图片变量
*/
enum
{ 
    NRF24L01_Picture  = 0,  /****2.4G图片***/
    Bluetooth_Picture = 1,  /****蓝牙图片***/
    WIFI_Picture      = 2,  /****WIFI图片***/
    USB_Picture       = 3,  /****USB图片****/
    Set_Picture       = 4,  /****设置图片***/
};
/*******************************************/

//菜单栏 任务个数
#define number 4
/*********************************************
 * 创建一个枚举
 * 存放界面变量
*/
enum
{
    Main_Interface = 0x10, /****主界面*****/
    Menu_Interface = 0x20, /****菜单界面***/
    Task_Interface = 0x30, /****任务界面***/
};
/*******************************************/


enum { _Left_Rocker_   =  0, /*****左摇杆******/  _Right_Rocker_  =  1  /*****右摇杆******/};
enum { Run   =  0xff, /*****运行******/  Stop  =  0xf0  /*****停止******/};




typedef struct
{
    u8 Interface_Mark;     //界面状态
    u8 Task_Mark;          //任务状态
    u8 Run_Task;           //开始运行任务
} Mark;
extern Mark Mark_Sign;//状态标志位

#define teme_size 59   //时间大小
typedef struct
{
    u8 When;      //时
    u8 Points;    //分
    u8 Seconds;   //秒
    u8 Point;     //中间的小点
} teme;
extern teme Teme;

typedef struct
{
    u8 Bluetooth_Mark;     //蓝牙状态
    u8 WIFI_Mark;          //WIFI状态
    u8 NRF24L01_Mark;      //2.4G状态
    u8 USB_Mark;           // USB状态
    u8 Set_Mark;           //设置状态
} Module_mark;
extern Module_mark Module_Mark;//模块状态

/*********************************************
 * 创建一个枚举
 * 存放选择个数变量
*/
enum
{
    NRF24L01_Choose_N  = 4,      //2.4G选择个数
    Bluetooth_Choose_N = 4,      //蓝牙选择个数
    WIFI_Choose_N      = 4,      //WIFI选择个数
    USB_Choose_N       = 4,      // USB选择个数
    Set_Choose_N       = 4       //设置选择个数
} ;
#define ALL_Task_Stop 0
typedef struct
{
    u8 Bluetooth_Choose;     //蓝牙选择
    u8 WIFI_Choose;          //WIFI选择
    u8 NRF24L01_Choose;      //2.4G选择
    u8 USB_Choose;           // USB选择
    u8 Set_Choose;           //设置选择
} Module_choose;
extern Module_choose Module_Choose;//选择


void Picture(u8 picture);          //显示对应图片
u8 Detection_Hardware_Drive(void); //判断硬件状态
void Main_Interface_APP(void);     //显示主界面
void Menu_Interface_APP(void);     //显示菜单界面
void Function_Menu_APP(void);      //显示功能界面
void Rocker_Display_Drive(void);   //显示摇杆数据
void NRF24L01_Task_APP(void);      //2.4G任务
void Bluetooth_Task_APP(void);     //蓝牙任务
void WIFI_Task_APP(void);          //WIFI任务
void USB_Task_APP(void);           //USB任务
void Set_Task_APP(void);           //设置任务

#endif

