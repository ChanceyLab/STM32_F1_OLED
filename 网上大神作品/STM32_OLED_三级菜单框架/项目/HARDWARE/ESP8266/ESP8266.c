#include "ESP8266.h"


void ESP8266_Cmd (char *cmd)
{
    printf("%s\r\n", cmd);
}

void ESP8266_Init(void)
{

    uint16_t ESP88266_count = 0; //ESP8266 ����
    uint16_t P64x6Ch_count = 0; //P64x6Ch ����
    uint16_t ESP88266_sign = 0; //ESP8266 ��־
    Picture(WIFI_Picture);      //��ʾWIFIͼƬ
    while(!ESP88266_sign && ESP88266_count < 4000) //�ж��Ƿ��������
    {
        switch(ESP88266_count)
        {
        case 0:
            ESP8266_Cmd("AT+CWMODE=2");  //��wifiģ�鷢��ATָ�� APģʽ
            /*��������ʾ0-15*/
            for(P64x6Ch_count = 0; P64x6Ch_count < 15; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(50);
            }
            break;
        case 1000:
            ESP8266_Cmd("AT+RST");      //��wifiģ�鷢��ATָ�� ��λģ��
            /*��������ʾ15-30*/
            for(P64x6Ch_count = 15; P64x6Ch_count < 30; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(40);
            }
            break;
        case 2000:

            ESP8266_Cmd("AT+CIPMUX=1");      //��wifiģ�鷢��ATָ�� ������͸ģʽ
            /*��������ʾ30-45*/
            for(P64x6Ch_count = 30; P64x6Ch_count < 45; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(30);
            }
            break;
        case 3000:
            ESP8266_Cmd("AT+CIPSERVER=1,8888");//��wifiģ�鷢��ATָ�� �˿ں�Ϊ 88888
            /*��������ʾ45-62*/
            for(P64x6Ch_count = 45; P64x6Ch_count < 63; P64x6Ch_count++)
            {
                OLED_P64x6Ch(2 * 16, 6, P64x6Ch_count);
                delay_ms(20);
            }
            ESP88266_sign = 1;   //ģ�� APģʽ������ɣ���־λ��1
            break;
        default:
            break;
        }
        ESP88266_count++;
        if(ESP88266_count > 4000)ESP88266_sign = 0;//�������ֵΪ4000
        if(P64x6Ch_count == 63)P64x6Ch_count = 0;//�������ֵΪ63
    }
}


