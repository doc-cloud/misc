#include <msp430.h>
#include <ctype.h> 
typedef unsigned char uchar;

/*******************************************
�������ƣ�InitUART
��    �ܣ���ʼ��UART�˿�
��    ������
����ֵ  ����
********************************************/
void InitUART(void)
{
    P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
    ME1 |= URXE0 + UTXE0;                             // Enable USART0 T/RXD
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x1B;                             // 32k/1200
    UBR10 = 0x00;                             //
    UMCTL0 = 0x03;                            // Modulation
    UCTL0 &= ~SWRST;                          // Initialize USART state machine
    IE1 |= URXIE0;                            //ʹ�ܽ����ж�
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
      TXBUF0 = '\n';                              //���ͻ���ָ��
}
/*******************************************
�������ƣ�Get1Char
��    �ܣ�����һ������PC�����ַ�
��    ������
����ֵ  �����յ����ַ�
********************************************/
uchar Get1Char(void)
{
    while (!(IFG1 & URXIFG0));    //�ȴ����յ��ַ�        
    return  RXBUF0;
}
