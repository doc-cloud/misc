/**************************************************************
�����ܣ�ѧϰ����Ϊ�����м̣���USB�ڽ��յ�������ͨ������ת��
          ��ȥ
---------------------------------------------------------------
����˵������1��PC��ÿ����ѧϰ��ͨ��USB�˿ڷ������ݵĵ�1���ֽڱ�
           ���Ǳ���Ҫ�������ֽڵĳ��ȶ������ֽڳ��Ȳ����Գ���15��
          ��2��PC�����͵����ݸ�ʽ��16���ƣ��ڴ��ڵ��Ծ�����ҲҪ
           ������ʾ����ҲҪ����Ϊ16������ʾ��
---------------------------------------------------------------
��������:��������J3�ϵĶ�·ñ��á�
---------------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1, 9600
---------------------------------------------------------------
����˵�������ô��������߽�ѧϰ��Ĵ�����PC���������Ӻã��򿪴�
          �ڵ��Ծ��飬��ȷ����ͨ�Ÿ�ʽ�����������ص�MCU�У�
          Ȼ���˳�IAR����USB���¸�ѧϰ�幩�磬��USB���ӳɹ��Ժ�
          ��WinDriverͨ����������ѧϰ������ȷ��ʽ������
         ����1���ֽ������ݳ��ȣ���������ݣ����۲촮�ڵ��Ծ���
          ���յ������ݡ�
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "uart0.h"
#include  "gdata.h"

/***************************������****************************/
void main(void)
{
    uchar i,j;
    
    WDTCTL = WDTPW + WDTHOLD;           //�رտ��Ź�
    BoardConfig(0xf8);                  //�ر�����ܡ���ˮ�ƺ�4245
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // ��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     // �ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             // ����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2;                  //��ʱ��ѡ���Ƶ����
    
    InitUART();                         //��ʼ���˿�
    PutString("UART is Ready......");    
    
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
           j = Ep1Buf[0];
           for(i = 1;i <= j;i++)
           {
                Send1Char(Ep1Buf[i]);
           }
           USB_FLAG.ep1_rxdone = 0;
           _EINT();
        } 
        else if(USB_FLAG.ep2_rxdone == 1) //�˵�2���յ�����
        {
           _DINT();
           USB_FLAG.ep2_rxdone = 0;
           _EINT();
        }
    }
}
