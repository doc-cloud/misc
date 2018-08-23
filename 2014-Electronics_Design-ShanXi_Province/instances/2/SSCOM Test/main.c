/******************************************************
�����ܣ���������PC�����ַ���Ȼ�����·��͸�PC��
-------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1,  9600
         ��У�飬8������λ��1��ֹͣλ��������9600
------------------------------------------------------
����˵������SSCOM����ȷ����ͨ�Ÿ�ʽ����ѧϰ�巢��һ��
          �ַ��������ַ������ַ����ַ�����β������ӽ���
          ��'\'�����۲�PC���Ƿ���ȷ�յ��ط����ַ�
*******************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

uchar  RecBuf[256];
uchar  Windex;
uchar  Rindex; 

void Send1Char(uchar sendchar);
void PutString(uchar *ptr);
/********************������********************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // �رտ��Ź�
    BoardConfig(0xb8);                        // �ر�����ܡ���ˮ�ƺ͵�ƽת��
    
    P3SEL |= 0x30;                            // ѡ��P3.4��P3.5��UARTͨ�Ŷ˿�
    ME1 |= UTXE0 + URXE0;                     // ʹ��USART0�ķ��ͺͽ���
    UCTL0 |= CHAR;                            // ѡ��8λ�ַ�
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // ������9600
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4A;                            // Modulation
    UCTL0 &= ~SWRST;                          // ��ʼ��UART״̬��
    IE1 |= URXIE0;                            // ʹ��USART0�Ľ����ж�
    _EINT();                                  //��ȫ���ж�
    
    Windex = 0;
    Rindex = 0;
    
    PutString("     ����һ�������ܹ���ʾ���ĵĴ��ڵ��Թ���SSCOM32��ʾ������");
    PutString("���ڷ��������뵥�������ַ���Ӣ����ĸ�����ֻ��ߺ��֣�����������ϣ���\
               �������ַ��Ľ�β������ӽ�������'\\'��������ͺ�۲�PC����Ļ��ʾ���ս��");
    while(1)
    {
        while(Rindex != Windex)
        {
            Send1Char(RecBuf[Rindex++]);             //���յ����ַ����ͳ�ȥ
            Rindex &= 0x3f;
        } 
        Send1Char(0x0d);   //˵��0x0d0a�����SSCOM32�Ļ���ָ��
        Send1Char(0x0a);
        LPM1;
    }
}
/*******************************************
�������ƣ�UART0_RXISR
��    �ܣ�UART0�Ľ����жϷ������������﻽��
          CPU��ʹ���˳��͹���ģʽ
��    ������
����ֵ  ����
********************************************/
#pragma vector = UART0RX_VECTOR
__interrupt void UART0_RXISR(void)
{
    if(RXBUF0 == '\\')   LPM1_EXIT;
    else
    {
        RecBuf[Windex++] = RXBUF0;
        Windex &= 0x3f;
    }
}
/*******************************************
�������ƣ�Send1Char
��    �ܣ���PC������һ���ַ�
��    ����sendchar--Ҫ���͵��ַ�
����ֵ  ����
********************************************/
void Send1Char(uchar sendchar)
{
      while (!(IFG1 & UTXIFG0));    //�ȴ����ͼĴ���Ϊ��         
      TXBUF0 = sendchar;  
}
/*******************************************
�������ƣ�PutSting
��    �ܣ���PC�������ַ���
��    ����ptr--ָ�����ַ�����ָ��
����ֵ  ����
********************************************/
void PutString(uchar *ptr)
{
      while(*ptr != '\0')
      {
            Send1Char(*ptr++);                     // ��������
      }
      while (!(IFG1 & UTXIFG0));
      TXBUF0 = 0x0d;  
      while (!(IFG1 & UTXIFG0));
      TXBUF0 = 0x0a;                              //���ͻ���ָ��
}
