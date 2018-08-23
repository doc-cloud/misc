/**************************************************************
�����ܣ�ʵ��ѧϰ��ͨ��USB�˿���PC��ͨ�ţ�PC����ѧϰ�巢���ַ�
    	 ����1602Һ������ʾ
---------------------------------------------------------------
����˵������1��PC����ѧϰ�巢�����ݵĵ�1���ֽڱ����Ǳ���Ҫ����
          ���ֽڵĳ��ȶ������ֽڳ��Ȳ����Գ���15
          ��2��PC�����͵�����Ӧ���ǿ���ʾ�ַ���ӦASCII��ֵ
          ����1���ֽڳ��⣩������1602Һ���޷���ʾ��
---------------------------------------------------------------
��������:��������J3�ϵĶ�·ñ��á�
---------------------------------------------------------------
����˵�������������ص�MCU�Ժ󣬴�IAR������˳�����USB��������ѧ
          ϰ���PC��������USB��Դ���ذ����������ӽ����ɹ��Ժ�
          ��WinDriver������ö˵�1��ѧϰ�巢�ͷ�������Ҫ������ݣ�
          ���۲�1602Һ����ʾ��
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "Cry1602.h"
#include  "gdata.h"

/***************************������****************************/
void main(void)
{
    uchar i;
    
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
    
    LcdReset();                         //��λҺ��
    LocateXY(0,0);                      //ȷ����ʾ����ʼλ��
    LcdWriteCommand(0x0f, 1);           //���α�
    
    
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
           LcdWriteCommand(0x01, 1);                        //��ʾ����
           DispNchar(0,0,Ep1Buf[0],&Ep1Buf[1]);             //��Һ������ʾ���յ����ַ�
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
