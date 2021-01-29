#include "ESP8266.h"


void ESP8266_Cmd (char *cmd)
{
    printf("%s\r\n", cmd);
}

void ESP8266_Init(void)
{

    uint16_t ESP88266_count = 0; //ESP8266 计数
    uint16_t P64x6Ch_count = 0; //P64x6Ch 计数
    uint16_t ESP88266_sign = 0; //ESP8266 标志
    Picture(WIFI_Picture);      //显示WIFI图片
    while(!ESP88266_sign && ESP88266_count < 4000) //判断是否配置完毕
    {
        switch(ESP88266_count)
        {
        case 0:
            ESP8266_Cmd("AT+CWMODE=2");  //向wifi模块发送AT指令 AP模式
            /*进度条显示0-15*/
            for(P64x6Ch_count = 0; P64x6Ch_count < 15; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(50);
            }
            break;
        case 1000:
            ESP8266_Cmd("AT+RST");      //向wifi模块发送AT指令 复位模块
            /*进度条显示15-30*/
            for(P64x6Ch_count = 15; P64x6Ch_count < 30; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(40);
            }
            break;
        case 2000:

            ESP8266_Cmd("AT+CIPMUX=1");      //向wifi模块发送AT指令 开启穿透模式
            /*进度条显示30-45*/
            for(P64x6Ch_count = 30; P64x6Ch_count < 45; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(30);
            }
            break;
        case 3000:
            ESP8266_Cmd("AT+CIPSERVER=1,8888");//向wifi模块发送AT指令 端口号为 88888
            /*进度条显示45-62*/
            for(P64x6Ch_count = 45; P64x6Ch_count < 63; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(20);
            }
            ESP88266_sign = 1;   //模块 AP模式配置完成，标志位置1
            break;
        default:
            break;
        }
        ESP88266_count++;
        if(ESP88266_count > 4000)ESP88266_sign = 0;//限制最大值为4000
        if(P64x6Ch_count == 63)P64x6Ch_count = 0;//限制最大值为63
    }
}


