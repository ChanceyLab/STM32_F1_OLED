#include "key.h"



//������ʼ������
void KEY_Init(void) //IO��ʼ��
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PORTCʱ��
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
//����������
//mode:0,��֧��������;1,֧��������;
//���ذ���ֵ //0��û���κΰ�������
//1��KEY1����//2��KEY2����//3��KEY3����//4��KEY4����
//ע��˺�������Ӧ���ȼ�,KEY1->KEY2->KEY3->KEY4!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //�������ɿ���־
    if(mode)key_up = 1; //֧������
    if((1 == key_up) && (0 == KEY1 || 0 == KEY2 || 0 == KEY3 || 0 == KEY4 ))
    {
        delay_ms(10);//ȥ����
        key_up = 0;
        if(0 == KEY1)return KEY1_PRES;
        else if(0 == KEY2) return KEY2_PRES;
        else if(0 == KEY3) return KEY3_PRES;
        else if(0 == KEY4) return KEY4_PRES;
    }
    else if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1)key_up = 1;
    return 0;// �ް�������
}
///**************************************************************************
//�������ܣ�����ɨ��
//��ڲ�����˫���ȴ�ʱ��
//����  ֵ������״̬ 0���޶��� 1������ 2��˫��
//**************************************************************************/
//u8 click_N_Double (u8 time)
//{
//    static	u8 flag_key, count_key, double_key;
//    static	u16 count_single, Forever_count;
//    if(KEY == 0)  Forever_count++; //������־λδ��1
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
//            return 2;//˫��ִ�е�ָ��
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
//            return 1;//����ִ�е�ָ��
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
//�������ܣ��������
//��ڲ�������
//����  ֵ������״̬ 0���޶��� 1������2s
//**************************************************************************/
//u8 Long_Press(void)
//{
//    static u16 Long_Press_count, Long_Press;
//    if(Long_Press == 0 && KEY == 0)  Long_Press_count++; //������־λδ��1
//    else                       Long_Press_count = 0;
//    if(Long_Press_count > 200)
//    {
//        Long_Press = 1;
//        Long_Press_count = 0;
//        return 1;
//    }
//    if(Long_Press == 1)   //������־λ��1
//    {
//        Long_Press = 0;
//    }
//    return 0;
//}
