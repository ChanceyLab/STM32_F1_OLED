#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "sys.h"

#define Remove     (37)             //���
///mode:0,������ʾ;1,������ʾ
#define Normal_Display (1) //������ʾ
#define White_Display  (0) //������ʾ

#define Choose_Icon  (44) //ѡ��ͼ��

#define Determine_Double (Determine)         //ȷ��
#define Menu_Double      (Menu)              //�˵�
#define Return_Double    (Return)            //����
#define Left_Double      (Left)              //��
#define Right_Double     (Right)             //�ҷ�
#define On_Double        (On)                //�Ϸ�
#define Under_Double     (Under)             //�·�


/*********************************************
 * ����һ��ö��
 * ��Ű���״̬
*/
enum
{
    Determine = 1,   /****ȷ��***/
    Menu      = 2,   /****�˵�***/
    Return    = 3,   /****����***/
    Left      = 4,   /****��***/
    Right     = 5,   /****�ҷ�***/
    On        = 6,   /****�Ϸ�***/
    Under     = 7,   /****�·�***/
};
/*******************************************/

// ��ҡ��X����
#define Left_Rocker_X_Center  (Get_Adc(Left_Rocker_X) > 1900 &&  Get_Adc(Left_Rocker_X) < 2100)
// ��ҡ��Y����
#define Left_Rocker_Y_Center  (Get_Adc(Left_Rocker_Y) > 1900 &&  Get_Adc(Left_Rocker_Y) < 2100)
// ��ҡ��������λ��
#define Left_Rocker_Center    (Left_Rocker_X_Center && Left_Rocker_Y_Center)


// ��ҡ��X����
#define Right_Rocker_X_Center  (Get_Adc(Right_Rocker_X) > 1900 &&  Get_Adc(Right_Rocker_X) < 2100)
// ��ҡ��Y����
#define Right_Rocker_Y_Center  (Get_Adc(Right_Rocker_Y) > 1900 &&  Get_Adc(Right_Rocker_Y) < 2100)
// ��ҡ��������λ��
#define Right_Rocker_Center    (Right_Rocker_X_Center && Right_Rocker_Y_Center)

#define Page(ARE) (ARE/2+1)

/*********************************************
 * ����һ��ö��
 * ����������
*/	
enum
{
    NRF24L01_Task   = 0,   /****2.4G����***/
    Bluetooth_Task  = 1,   /****��������***/
    WIFI_Task       = 2,   /****WIFI����***/
    USB_Task        = 3,   /****USB����***/
    Set_Task        = 4,   /****��������***/
};
/*******************************************/


/*********************************************
 * ����һ��ö��
 * ���ͼƬ����
*/
enum
{ 
    NRF24L01_Picture  = 0,  /****2.4GͼƬ***/
    Bluetooth_Picture = 1,  /****����ͼƬ***/
    WIFI_Picture      = 2,  /****WIFIͼƬ***/
    USB_Picture       = 3,  /****USBͼƬ****/
    Set_Picture       = 4,  /****����ͼƬ***/
};
/*******************************************/

//�˵��� �������
#define number 4
/*********************************************
 * ����һ��ö��
 * ��Ž������
*/
enum
{
    Main_Interface = 0x10, /****������*****/
    Menu_Interface = 0x20, /****�˵�����***/
    Task_Interface = 0x30, /****�������***/
};
/*******************************************/


enum { _Left_Rocker_   =  0, /*****��ҡ��******/  _Right_Rocker_  =  1  /*****��ҡ��******/};
enum { Run   =  0xff, /*****����******/  Stop  =  0xf0  /*****ֹͣ******/};




typedef struct
{
    u8 Interface_Mark;     //����״̬
    u8 Task_Mark;          //����״̬
    u8 Run_Task;           //��ʼ��������
} Mark;
extern Mark Mark_Sign;//״̬��־λ

#define teme_size 59   //ʱ���С
typedef struct
{
    u8 When;      //ʱ
    u8 Points;    //��
    u8 Seconds;   //��
    u8 Point;     //�м��С��
} teme;
extern teme Teme;

typedef struct
{
    u8 Bluetooth_Mark;     //����״̬
    u8 WIFI_Mark;          //WIFI״̬
    u8 NRF24L01_Mark;      //2.4G״̬
    u8 USB_Mark;           // USB״̬
    u8 Set_Mark;           //����״̬
} Module_mark;
extern Module_mark Module_Mark;//ģ��״̬

/*********************************************
 * ����һ��ö��
 * ���ѡ���������
*/
enum
{
    NRF24L01_Choose_N  = 4,      //2.4Gѡ�����
    Bluetooth_Choose_N = 4,      //����ѡ�����
    WIFI_Choose_N      = 4,      //WIFIѡ�����
    USB_Choose_N       = 4,      // USBѡ�����
    Set_Choose_N       = 4       //����ѡ�����
} ;
#define ALL_Task_Stop 0
typedef struct
{
    u8 Bluetooth_Choose;     //����ѡ��
    u8 WIFI_Choose;          //WIFIѡ��
    u8 NRF24L01_Choose;      //2.4Gѡ��
    u8 USB_Choose;           // USBѡ��
    u8 Set_Choose;           //����ѡ��
} Module_choose;
extern Module_choose Module_Choose;//ѡ��


void Picture(u8 picture);          //��ʾ��ӦͼƬ
u8 Detection_Hardware_Drive(void); //�ж�Ӳ��״̬
void Main_Interface_APP(void);     //��ʾ������
void Menu_Interface_APP(void);     //��ʾ�˵�����
void Function_Menu_APP(void);      //��ʾ���ܽ���
void Rocker_Display_Drive(void);   //��ʾҡ������
void NRF24L01_Task_APP(void);      //2.4G����
void Bluetooth_Task_APP(void);     //��������
void WIFI_Task_APP(void);          //WIFI����
void USB_Task_APP(void);           //USB����
void Set_Task_APP(void);           //��������

#endif

