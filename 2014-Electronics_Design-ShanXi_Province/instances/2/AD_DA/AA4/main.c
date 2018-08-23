/**************************************************************
�����ܣ�ʵ��ѧϰ��ͨ��USB�˿���PC��ͨ�ţ��û�ͨ���˵�1(EP1)��
          �Ϳ���DAC��������ݣ������������ѹ������LED���⣬Ҳ��
          ��ֱ���õ�ѹ�����DAC�����ѹ
---------------------------------------------------------------
�������ã���1����������J3�ϵĶ�·ñ��á�
          ��2����������J1��1�ź�2�ţ���������������̽�
---------------------------------------------------------------
����˵�������������ص�MCU�Ժ󣬴�IAR������˳�����USB��������ѧ
          ϰ���PC��������USB��Դ���ذ����������ӽ����ɹ��Ժ�
          ��WinDriver�����ͨ��EP1��ѧϰ�巢�Ϳ���DAC���ģ���
          ѹ�����ݣ��۲�LED���ȱ仯�����õ�ѹ�����DAC����˵�ѹ��
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "IIC.h"
#include  "gdata.h"

uchar Write_DAC(uchar wdata);
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
    
    Set_IO();                           //����DAC��Ӧ��IO
    
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
           //��1���ֽڵĿ�������д��DAC
           Write_DAC(Ep1Buf[0]);           
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
/*******************************************
�������ƣ�Write_DAC
��    �ܣ���DAC��д�������ѹ����
��    ������
����ֵ  ��д������1--�ɹ���0--ʧ��
********************************************/
uchar Write_DAC(uchar wdata)
{
    start();
    write1byte(0x98);   //DAC���豸��ַ
    if(check())   write1byte(wdata >> 4);   //д����ģʽ�͵�ѹ���ݵĸ���λ
    else          return 0;
    if(check())   write1byte(wdata << 4);  //д��ѹ���ݵĵ���λ
    else          return 0;
    if(check())	  stop();
    else          return 0;
    return 1;    
}


