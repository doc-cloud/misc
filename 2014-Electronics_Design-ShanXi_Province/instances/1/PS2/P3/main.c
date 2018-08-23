/*****************************************************
�����ܣ����ղ��������Ա�׼���̵Ļ���������ɨ����
Ȼ����Ʒ�����������Ƶ�ʺ���ˮ�Ƶ�·����ʾ��

ʮ����������0~9��Ӧ10��Ƶ�ʣ�����S��ֹͣ����������

ע����ν�����������ǵ��˼�������ʱ��Ӧ���������ֽ�
��ɨ����İ�������������еġ��ڶ���ɨ���롷
-----------------------------------------------------
�������ã���������J4��1�ź�2�ţ��Ҳ���������̽�
*****************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "Keyboard.h"
#include "gdata.h"

#define SIDval  P5IN & BIT6

/****************������****************/
void main(void)
{
    uchar disptmp,i;
    
    WDTCTL = WDTPW + WDTHOLD;   //�رտ��Ź�
    BoardConfig(0x70);          // ��4245������5-->3.3,����ܺ͹ر���ˮ��
    
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // ��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 // �������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     // �ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             // ����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           // MCLK��SMCLKѡ���Ƶ����
    
    TACCTL0 |= CCIE;                    //ʹ�ܱȽ��ж�
    TACTL |= TASSEL_2 + ID_3 ;          //����ʱ��ѡ��SMLK=8MHz��1/8��Ƶ��Ϊ1MHz
    P6DIR = BIT7;                       //��������ӦIO����Ϊ���
    P6OUT = BIT7;
    P2DIR = 0xff;
    
    Init_KB();                  //��ʼ�����̶˿�
    _EINT();                    //��ȫ���ж�
  
    while(1)
    {
        LPM1;                   //����͹���ģʽ
        disptmp = GetChar();    //��ȡ��ֵ��Ӧ��ASCII��
        
        if((disptmp > 0x2f)&&(disptmp < 0x3a)) //������յ����ַ���0~9
        {
          //  uchar inputvalue;
            
          //  inputvalue = disptmp - 0x30;
            switch(disptmp) 
            {
              case '0':
                        TACCR0 = 5000;  
                        TACTL |= MC0;
                        P2OUT = ~1;
                        break;
              case '1':
                        TACCR0 = 2500;  
                        TACTL |= MC0;
                        P2OUT = ~2;
                        break;
              case '2':
                        TACCR0 = 1250;  
                        TACTL |= MC0;
                        P2OUT = ~3;
                        break;
              case '3':
                        TACCR0 = 625;  
                        TACTL |= MC0;
                        P2OUT = ~4;
                        break;
              case '4':
                        TACCR0 = 500;  
                        TACTL |= MC0;
                        P2OUT = ~5;
                        break;
              case '5':
                        TACCR0 = 250;  
                        TACTL |= MC0;
                        P2OUT = ~6;
                        break;
              case '6':
                        TACCR0 = 167;  
                        TACTL |= MC0;
                        P2OUT = ~7;
                        break;
              case '7':
                        TACCR0 = 125;  
                        TACTL |= MC0;
                        P2OUT = ~8;
                        break;
              case '8':
                        TACCR0 = 100;  
                        TACTL |= MC0;
                        P2OUT = ~9;
                        break;
              case '9':
                        TACCR0 = 83;  
                        TACTL |= MC0;
                        P2OUT = ~10;
                        break;
              default:
                        _NOP();
              }
          }
        else if(disptmp == 's')
        {
            TACTL &= ~MC0;  //ֹͣ����
            P6OUT = BIT7;
            P2OUT = 0xff;
        }
        
    }
} 
/*******************************************
�������ƣ�Timer_A
��    �ܣ���ʱ��A���жϷ�����������������
          ����������
��    ������
����ֵ  ����
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P6OUT ^= BIT7;                            // Toggle P6.7
}

/*******************************************
�������ƣ�PORT1_ISR 
��    �ܣ�P1�˿ڵ��жϷ������������������
          �Լ��̵��ַ�
��    ������
����ֵ  ����
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & BIT7)            //�����clock���ж�
    {
        P1IFG &=~ BIT7;         //����жϱ�־ 
        
        if(bitcount == 11)        //���յ�1λ
        {
            if(SIDval)          //���������ʼλ
                return;
            else  
                bitcount--;
        } 
        else if(bitcount == 2)    //������żУ��λ
        {   
            if(SIDval)          //���У��λ����1
                pebit = 1;
            else
                pebit = 0;
            bitcount--;
        }
        else if(bitcount == 1)    //����ֹͣλ
        {
            if(SIDval)          //��ֹͣλ��ȷ
            {
                bitcount = 11;    //��λλ��������
                if( Decode(recdata) )    //�����ô˼�ֵ��ASCIIֵ������
                    LPM3_EXIT;           //�˳��͹���ģʽ
                recdata = 0;          //�����������
            }
            else                //�������
            {
                bitcount = 11;
                recdata = 0;    
            }
        }
        else                    //����8������λ
        {
            recdata >>= 1;
            if(SIDval)  recdata |= 0x80;
            bitcount--;
        }
   }
}


