#include "24l01.h"
#include "delay.h"
#include "spi.h"

const u8 TX_ADDRESS[TX_ADR_WIDTH] = {'E', 'T', 'A', 'X', 'X'}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH] = {'E', 'T', 'A', 'X', 'X'}; //���͵�ַ

//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_4);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;   //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    SPIx_Init();    //��ʼ��SPI 
		

    Clr_NRF24L01_CE;	 //ʹ��24L01  NRF24L01_CE
    Set_NRF24L01_CSN;    //SPIƬѡȡ�� NRF24L01_CSN
}

//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��
u8 NRF24L01_Check(void)
{
    u8 buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    u8 i;
    SPIx_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + TX_ADDR, buf, 5); //д��5���ֽڵĵ�ַ.
    NRF24L01_Read_Buf(TX_ADDR, buf, 5); //����д��ĵ�ַ
    for(i = 0; i < 5; i++)if(buf[i] != 0XA5)break;
    if(i != 5)return 1; //���24L01����
    return 0;		 //��⵽24L01
}

//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 NRF24L01_Write_Reg(u8 reg, u8 value)
{
    u8 status;
    Clr_NRF24L01_CSN;                 //ʹ��SPI����
    status = SPIx_ReadWriteByte(reg); //���ͼĴ�����
    SPIx_ReadWriteByte(value);      //д��Ĵ�����ֵ
    Set_NRF24L01_CSN;                 //��ֹSPI����
    return(status);       			//����״ֵ̬
}

//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 reg)
{
    u8 reg_val;
    Clr_NRF24L01_CSN;          //ʹ��SPI����
    SPIx_ReadWriteByte(reg);   //���ͼĴ�����
    reg_val = SPIx_ReadWriteByte(0XFF); //��ȡ�Ĵ�������
    Set_NRF24L01_CSN;          //��ֹSPI����
    return(reg_val);           //����״ֵ̬
}

//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
{
    u8 status, u8_ctr;
    Clr_NRF24L01_CSN;           //ʹ��SPI����
    status = SPIx_ReadWriteByte(reg); //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for(u8_ctr = 0; u8_ctr < len; u8_ctr++)pBuf[u8_ctr] = SPIx_ReadWriteByte(0XFF); //��������
    Set_NRF24L01_CSN;       //�ر�SPI����
    return status;        //���ض�����״ֵ̬
}

//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
    u8 status, u8_ctr;
    Clr_NRF24L01_CSN;          //ʹ��SPI����
    status = SPIx_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for(u8_ctr = 0; u8_ctr < len; u8_ctr++)SPIx_ReadWriteByte(*pBuf++); //д������
    Set_NRF24L01_CSN;       //�ر�SPI����
    return status;          //���ض�����״ֵ̬
}

//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
u8 NRF24L01_TxPacket(u8 *txbuf)
{
    u8 sta;
    SPIx_SetSpeed(SPI_BaudRatePrescaler_8);//spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(NRF24L01_WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH); //д���ݵ�TX BUF  32���ֽ�
    Set_NRF24L01_CE;//��������
    //delay_us(10);
    //while(NRF24L01_IRQ != 0); //�ȴ��������
    sta = NRF24L01_Read_Reg(STATUS); //��ȡ״̬�Ĵ�����ֵ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + STATUS, sta); //���TX_DS��MAX_RT�жϱ�־
    if(sta & MAX_TX) //�ﵽ����ط�����
    {
        NRF24L01_Write_Reg(NRF24L01_FLUSH_TX, 0xff); //���TX FIFO�Ĵ���
        return MAX_TX;
    }
    if(sta & TX_OK) //�������
    {
        return TX_OK;
    }
    return 0xff;//����ԭ����ʧ��
}

//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
    u8 sta;
    SPIx_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
    sta = NRF24L01_Read_Reg(STATUS); //��ȡ״̬�Ĵ�����ֵ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + STATUS, sta); //���TX_DS��MAX_RT�жϱ�־
    if(sta & RX_OK) //���յ�����
    {
        NRF24L01_Read_Buf(NRF24L01_RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH); //��ȡ����
        NRF24L01_Write_Reg(NRF24L01_FLUSH_RX, 0xff); //���RX FIFO�Ĵ���
        return 0;
    }
    return 1;//û�յ��κ�����
}

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������
void RX_Mode(void)
{
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + RX_ADDR_P0, (u8 *)RX_ADDRESS, RX_ADR_WIDTH); //дRX�ڵ��ַ

    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_AA, 0x01); //ʹ��ͨ��0���Զ�Ӧ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_CH, 40);	  //����RFͨ��Ƶ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //ѡ��ͨ��0����Ч���ݿ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_SETUP, 0x0f); //����TX�������,0db����,2Mbps,���������濪��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + CONFIG, 0x0f); //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ
    Set_NRF24L01_CE; //CEΪ��,�������ģʽ
    delay_us(10);
}

//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������
//CEΪ�ߴ���10us,����������.
void TX_Mode(void)
{
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + TX_ADDR, (u8 *)TX_ADDRESS, TX_ADR_WIDTH); //дTX�ڵ��ַ
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + RX_ADDR_P0, (u8 *)RX_ADDRESS, RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK

    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_AA, 0x01);  //ʹ��ͨ��0���Զ�Ӧ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + SETUP_RETR, 0x1a); //�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_CH, 40);    //����RFͨ��Ϊ40
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_SETUP, 0x0f); //����TX�������,0db����,2Mbps,���������濪��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + CONFIG, 0x0e); //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
    Set_NRF24L01_CE;//CEΪ��,10us����������
    delay_us(10);
}


void NRF24L01(void)
{
    u8 mode = 1;	//����ģʽ
    u8 tmp_buf[32];
    u8 rxbuf[32];	 //���ջ���
    if(mode == 0) //RXģʽ
    {
        RX_Mode();
        while(1)
        {
            OLED_ShowString(0, 2, "2.4G RX_Mode", 16, 1);

            if(NRF24L01_RxPacket(rxbuf) == 0) //һ�����յ���Ϣ,����ʾ����.
            {
                printf("\r\n ��ʼ����\r\n");
                printf("\r\n��������Ϊ: %d %d %d %d %d %d %d %d\r\n", rxbuf[0], rxbuf[1], rxbuf[2], rxbuf[3], rxbuf[4], rxbuf[5], rxbuf[6], rxbuf[7]);
                printf("\r\n �������\r\n");
            }
        }
    }
    else //TXģʽ
    {
        TX_Mode();

        tmp_buf[0] = 5;
        tmp_buf[1] = 6;
        tmp_buf[31] = 8;
        
        while(1)
        {

            LED1 = !LED1;
            delay_ms(10);
            switch(NRF24L01_TxPacket(tmp_buf))
            {
            case MAX_TX:
                printf("\r\n ������ û���յ�Ӧ���źţ����ʹ��������޶�ֵ������ʧ�ܡ� \r\n");
                break;

            case 0xff:
                printf("\r\n δ֪ԭ���·���ʧ�ܡ� \r\n");
                break;

            case TX_OK:
                printf("\r\n ������ ���յ� �ӻ��� ��Ӧ���źţ����ͳɹ��� \r\n");
                break;
            }
            OLED_ShowString(0, 2, "2.4G TX_Mode", 12, 1);

            if(NRF24L01_TxPacket(tmp_buf) == TX_OK)
            {
                //printf("%d\r\n", tmp_buf[1]);
            }
            else
                delay_ms(10);
        }
    }
}

