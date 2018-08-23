/**************************************************************
�����ܣ�ѧϰ����Ϊͨ���м̣����Ӵ��ڽ��յ�������ͨ��USB�˿�
          ת����ȥ��
---------------------------------------------------------------
��������:��������J3�ϵĶ�·ñ��á�
---------------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1, 1200
---------------------------------------------------------------
�ر����ѣ������ʵ���У����ڵĲ��������õĺܵͣ�����Ϊ�˸�MCU��
          ����ʱ�䴦����USB�з������ݵ�����������ڲ���������
          ������ô���������Ͷ���ֽ�ʱ����������ʧ���ݵĴ�����
          ����Ϊ��MCUִ��Write_EP()�������ʱ�ǹر���ȫ���ж�ʹ
          ��λ�ģ����Բ��ܼ�����Ӧ�����ж���������˽��ռĴ���
          ����������⣬�ڴ��ڵ��Ծ����з������ݸ�ʽ��������Ϊ
          16���ƣ�����ASCII�뷢�ͣ�������WinDriver�п��������ݾ�
          ���ڴ��ڵ��Ծ����п����Ĳ�һ���ˡ�
---------------------------------------------------------------
����˵�������������ص�MCU�У����Ӻô����ߺ�USBͨ�ŵ��£��򿪴���
          ���Ծ��飬��ȷ����ͨ�Ÿ�ʽ����USB���ӳɹ��Ժ�ͨ������
          ���Ծ��鷢�����ݣ���WinDriver�в鿴EP1���յ������ݡ�
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "UART0.h"
#include  "gdata.h"

/****************������****************/
void main(void)
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //�رտ��Ź�
    BoardConfig(0xb8);                  //�ر�����ܡ���ˮ�ƺ�4245
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // ��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     // �ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             // ����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2;                  //��ʱ��ѡ���Ƶ����
    
    InitUART();                         //��ʼ��UART0���ƼĴ���
    
    D12_init();                         //��ʼ��D12
    USB_reconnect();                    //����USB����

    while(1)
    {
        
        if((!(P1IN&BIT5))&&(!(P1IFG&BIT5)))     //���P1.5�˿ڶ�ʧ���ж�
        {
            uint int_sta;
          
            _DINT();
            
            USB_FLAG.in_isr = 1;
            int_sta=Read_IntR();	        //��ȡPDIUSBD12�жϼĴ���ֵ
          
            if(int_sta!=0) 
            {
                if(int_sta&INT_BUSRESET)
                        USB_FLAG.bus_reset=1;	//USB���߸�λ��־	
                if(int_sta&INT_ENDP0IN)
                        Ep0_txdone();		//���ƶ˵㷢�����ݴ���
                if(int_sta&INT_ENDP0OUT)
                        Ep0_rxdone();		//���ƶ˵�������ݴ���
                if(int_sta&INT_ENDP1IN)
                        Ep1_txdone();		//�˵� 1�������ݴ���
                if(int_sta&INT_ENDP1OUT)
                        Ep1_rxdone();		//�˵� 1�������ݴ���
                if(int_sta&INT_ENDP2IN)
                        Ep2_txdone();		//�˵� 2�������ݴ���
                if(int_sta&INT_ENDP2OUT)
                        Ep2_rxdone();		//�˵� 2�������ݴ���
            }
            USB_FLAG.in_isr = 0;
            
            _EINT();
        }
      
        if (USB_FLAG.setup_packet)   //Setup������
        {		
            _DINT();
            USB_FLAG.setup_packet = 0;
            Control_handler();	     //�����������ӳ���
            _EINT();
        }
        
        if(USB_FLAG.ep1_rxdone == 1) //�˵�1���յ�����
        {
           _DINT();
           USB_FLAG.ep1_rxdone = 0;
           _EINT();
        } 
        else if(USB_FLAG.ep2_rxdone == 1) //�˵�2���յ�����
        {
           _DINT();
           USB_FLAG.ep2_rxdone = 0;
           _EINT();
        }
        
        if(Rindex != Windex)  //����������д�������
        {
           Write_EP(3,1,&RecBuf[Windex++]);
           Windex &= 0x3f;           
        }
    }
}
/*******************************************
�������ƣ�UART0_RXISR
��    �ܣ�UART0�Ľ����жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector = UART0RX_VECTOR
__interrupt void UART0_RXISR(void)
{    
    RecBuf[Rindex++] = RXBUF0;   //�����յ������ݴ�ŵ�������
    Rindex &= 0x3f;
}


