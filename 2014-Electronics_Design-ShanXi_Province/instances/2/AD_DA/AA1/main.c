/**************************************************************
�����ܣ�ʵ��ѧϰ��ͨ��USB�˿���PC��ͨ�ţ��û�ͨ���˵�1(EP1)��
          ��0x11������ADCת�������������ͨ��EP1���͸�PC����
          �û�ͨ��EP1����0x99ֹͣADCת��
---------------------------------------------------------------
�������ã���������J3�ϵĶ�·ñ��á�
---------------------------------------------------------------
����˵�������������ص�MCU�Ժ󣬴�IAR������˳�����USB��������ѧ
          ϰ���PC��������USB��Դ���ذ����������ӽ����ɹ��Ժ�
          ��WinDriver�����ͨ��EP1��ѧϰ�巢������ADCת�����ź�
          (0x11)�۲���յ������ݽ�����ٷ���ֹͣADCת���ź�(0x99)
          �Ϳ���ֹͣADCת��
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
    
    P6SEL |= 0x01;                            // ʹ��ADCͨ��A0
    ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // ��ADC�����ò���ʱ��
    ADC12CTL1 = SHP+CONSEQ_2;                 // ʹ�ò�����ʱ��
    ADC12IE = 0x01;                           // ʹ��ADC�ж�
    
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
           if(Ep1Buf[0] == 0x11)     //����յ�����ת���ź�
           {
                ADC12CTL0 |= ENC;                         // ʹ��ת��
                ADC12CTL0 |= ADC12SC;                     // ��ʼת��     
           }
           else if(Ep1Buf[0] == 0x99)     //����յ�ֹͣת���ź�
           {
                ADC12CTL0 &= ~ENC;                         // ��ֹת��
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
        else if(SendFlag == 1)  //ͨ���˵�1����ADC��������
        {
           ptr = (Average&0xff00)>>8;
           Write_EP(3,1,&ptr);
           ptr = (Average&0x00ff);
           Write_EP(3,1,&ptr);
           SendFlag = 0;
        }
    }
}
/*******************************************
�������ƣ�ADC12ISR
��    �ܣ�ADC�жϷ��������������ö��ƽ����
          ����P6.0�ڵ�ģ���ѹ��ֵ
��    ������       
����ֵ  ����
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
  static uint index = 0;

  results[index++] = ADC12MEM0;               // Move results
  if(index == 32)
  {
        uchar i;
        unsigned long sum = 0;

        index = 0;
        for(i = 0; i < 32; i++)
        {
            sum += results[i];
        }
        sum >>= 5;                            //����32
        Average = (uint)sum;
        SendFlag = 1;
  }
}

