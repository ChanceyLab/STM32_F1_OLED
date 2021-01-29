#include "sys.h"

int main(void)
{
    delay_init();	    //��ʱ������ʼ��
    JTAG_Set(JTAG_SWD_DISABLE);
    JTAG_Set(SWD_ENABLE);

    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(9600);
    LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
    OLED_Init();
    NRF24L01_Init();
    Adc_Init();
    KEY_EXTIX_Init();
    TIM3_Int_Init(9999, 7199); //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms

    Detection_Hardware_Drive();//�ж�Ӳ��״̬
    //Ӳ�������ɣ�����������
    Mark_Sign.Interface_Mark = Main_Interface;

    while(1)
    {
        //״̬��־λ
        switch(Mark_Sign.Interface_Mark)
        {
        //״̬��־λ ������
        case Main_Interface:
            Main_Interface_APP();//��ʾ������
            break;

        //״̬��־λ �˵�����
        case Menu_Interface:
            Menu_Interface_APP();//��ʾ�˵�����
            break;

        //״̬��־λ �������
        case Task_Interface:
            Function_Menu_APP();//��ʾ���ܽ���
            break;
        default:
            break;
        }
    }
}


