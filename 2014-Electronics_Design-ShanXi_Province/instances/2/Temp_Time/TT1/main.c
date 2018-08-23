/**************************************************************
�����ܣ�ѧϰ��ͨ��USB�˿ڽ�DS18B20ת������ĸ�3λ���ַ���PC��
---------------------------------------------------------------
�������ã���������J3�ϵĶ�·ñ��á�
---------------------------------------------------------------
����˵�������������ص�MCU�Ժ󣬴�IAR������˳�����USB��������ѧ
          ϰ���PC��������USB��Դ���ذ����������ӽ����ɹ��Ժ�
          ��WinDriver�����������EP1��д����ֵ0x88��Ȼ���ٽ���
          ����EP1�����ݣ��Ϳ��Կ���3λ�¶���ֵ�ˡ�
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "DS18B20.h"
#include  "gdata.h"

void Disp_Numb(uint temper);
/****************������****************/
void main(void)
{
    uchar i;
    uint tmp;
    uchar ConvertFlag=0;
    
    WDTCTL = WDTPW + WDTHOLD;           // �رտ��Ź�
    BoardConfig(0xb8);                  // �ر�����ܡ���ˮ�ƺ�4245
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // ��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 // �������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     // �ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             // ����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           // MCLK��SMCLKѡ���Ƶ����
    
    //����ʱ��ѡ��SMLK=8MHz��1/8��Ƶ��Ϊ1MHz
    TACTL |= TASSEL_2 + ID_3; 
    
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
           if(Ep1Buf[0] == 0x88)        //����յ�ת������
           {
               ConvertFlag = 1; 
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
        if(ConvertFlag)
        {
            for(i = 0xff; i > 0; i--)  //��ʱһ��
            {
                for(tmp = 0;tmp < 250; tmp++)
                    _NOP();                
            }
            
            tmp = Do1Convert();           //����DS18B20����һ��ת��
            Disp_Numb(tmp);
            //����ʵ����ֻ������ת����6λ��ֵ�еĸ���λ,�������������
            //�ڶ���3�ĳ�6����ô���Ƿ���ȫ����6λ�¶�������
            Write_EP(3,3,dN);             //��ת�����ͨ��USB���͸�PC��
        }

    }
}
/*******************************************
�������ƣ�Disp_Numb
��    �ܣ�����DS18B20��ȡ��11bit�¶�����ת��
          ��10���Ƹ�ʽ���¶�����
��    ����temper--11bit�¶�����
����ֵ  ����
********************************************/
void Disp_Numb(uint temper)
{
    uchar i;
    
    for(i = 0;i < 6;i++) dN[i] = 0; //��ʼ����ʾ����

    //��ֵת��
    if(temper & BIT0) 
    {
        dN[0] = 5;
        dN[1] = 2;
        dN[2] = 6;
    }
    if(temper&BIT1)     
    {
        dN[1] += 5;
        dN[2] += 2;
        dN[3] += 1;
    }
    if(temper & BIT2)     
    {
        dN[2] += 5;
        dN[3] += 2;
        if(dN[2] >= 10)
        {
            dN[2] -= 10;
            dN[3] += 1;
        }
    }
    if(temper&BIT3)     
    {
        dN[3] += 5;
    }
    if(temper & BIT4)
    {
        dN[4] += 1;
    }
    if(temper & BIT5)     
    {
        dN[4] += 2;
    }
    if(temper & BIT6)
    {
        dN[4] += 4;
    }
    if(temper & BIT7)     
    {
        dN[4] += 8;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT8)
    {
        dN[4] += 6;
        dN[5] += 1;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT9)
    {
        dN[4] += 2;
        dN[5] += 3;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BITA)
    {
        dN[4] += 4;
        dN[5] += 6;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
        if(dN[5] >= 10)
        {
            dN[5] -= 10;
        }
    }
    //����λ��
    i = dN[5];
    dN[5] = dN[0];
    dN[0] = i;
    
    i = dN[4];
    dN[4] = dN[1];
    dN[1] = i;
    
    i = dN[3];
    dN[3] = dN[2];
    dN[2] = i;
}
