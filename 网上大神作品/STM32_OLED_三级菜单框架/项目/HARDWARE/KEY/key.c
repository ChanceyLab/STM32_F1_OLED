#include "key.h"



//按键初始化函数
void KEY_Init(void) //IO初始化
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PORTC时钟
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
//按键处理函数
//mode:0,不支持连续按;1,支持连续按;
//返回按键值 //0，没有任何按键按下
//1，KEY1按下//2，KEY2按下//3，KEY3按下//4，KEY4按下
//注意此函数有响应优先级,KEY1->KEY2->KEY3->KEY4!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //按键按松开标志
    if(mode)key_up = 1; //支持连按
    if((1 == key_up) && (0 == KEY1 || 0 == KEY2 || 0 == KEY3 || 0 == KEY4 ))
    {
        delay_ms(10);//去抖动
        key_up = 0;
        if(0 == KEY1)return KEY1_PRES;
        else if(0 == KEY2) return KEY2_PRES;
        else if(0 == KEY3) return KEY3_PRES;
        else if(0 == KEY4) return KEY4_PRES;
    }
    else if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1)key_up = 1;
    return 0;// 无按键按下
}
///**************************************************************************
//函数功能：按键扫描
//入口参数：双击等待时间
//返回  值：按键状态 0：无动作 1：单击 2：双击
//**************************************************************************/
//u8 click_N_Double (u8 time)
//{
//    static	u8 flag_key, count_key, double_key;
//    static	u16 count_single, Forever_count;
//    if(KEY == 0)  Forever_count++; //长按标志位未置1
//    else        Forever_count = 0;
//    if(0 == KEY && 0 == flag_key)		flag_key = 1;
//    if(0 == count_key)
//    {
//        if(flag_key == 1)
//        {
//            double_key++;
//            count_key = 1;
//        }
//        if(double_key == 2)
//        {
//            double_key = 0;
//            count_single = 0;
//            return 2;//双击执行的指令
//        }
//    }
//    if(1 == KEY)			flag_key = 0, count_key = 0;

//    if(1 == double_key)
//    {
//        count_single++;
//        if(count_single > time && Forever_count < time)
//        {
//            double_key = 0;
//            count_single = 0;
//            return 1;//单击执行的指令
//        }
//        if(Forever_count > time)
//        {
//            double_key = 0;
//            count_single = 0;
//        }
//    }
//    return 0;
//}

///**************************************************************************
//函数功能：长按检测
//入口参数：无
//返回  值：按键状态 0：无动作 1：长按2s
//**************************************************************************/
//u8 Long_Press(void)
//{
//    static u16 Long_Press_count, Long_Press;
//    if(Long_Press == 0 && KEY == 0)  Long_Press_count++; //长按标志位未置1
//    else                       Long_Press_count = 0;
//    if(Long_Press_count > 200)
//    {
//        Long_Press = 1;
//        Long_Press_count = 0;
//        return 1;
//    }
//    if(Long_Press == 1)   //长按标志位置1
//    {
//        Long_Press = 0;
//    }
//    return 0;
//}
