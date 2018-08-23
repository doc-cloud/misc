/**************************************************************
������:ʵ��ѧϰ��ͨ��USB�˿���PC��ͨ�ţ��û�����K1~K4�ļ�ֵ
         ����ͨ��USB���͵�PC������ʾ
---------------------------------------------------------------
��������:��������J3�ϵĶ�·ñ��á�
---------------------------------------------------------------
����˵�������������ص�MCU�Ժ󣬴�IAR������˳�����USB��������ѧ
          ϰ���PC��������USB��Դ���ذ����������ӽ����ɹ��Ժ�
          ��WinDriver����м����˵�1����������ѧϰ������ݡ�
          ����K1~K4�������۲���Ļ��ʾ�ļ�ֵ��
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "gdata.h"

/****************������****************/
void main(void)
{
    uchar i,ptr;
    
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
    
    P1DIR |= BIT7;                      //P1.7����͵�ƽ��ʹ���̹���       
    P1OUT &= ~BIT7;                     //�ڶ�������ģʽ 
    P1IES |= 0x0f;                      //P1.0~P1.4ѡ���½����ж�
    P1IE |= 0x0f;                       //ʹ��P1.0~P1.4���ж�
    P3DIR |= BIT4;
    P3OUT |= BIT4;
    
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
        else if(SendFlag == 1)  //�м��̰��£�ͨ���˵�1��������
        {
           ptr = KeyChar;
           Write_EP(3,1,&ptr);
           SendFlag = 0;
        }
    }
}
