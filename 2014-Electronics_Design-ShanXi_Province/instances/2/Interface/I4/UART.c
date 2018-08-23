#include <msp430.h>
#include <ctype.h> 
typedef unsigned char uchar;

/*******************************************
�������ƣ�InitUART0
��    �ܣ���ʼ��UART0�˿�
��    ������
����ֵ  ����
********************************************/
void InitUART0(void)
{
    P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
    ME1 |=  UTXE0;                            // Enable USART0 TXD
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // 32k/9600
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4a;                            // Modulation
    UCTL0 &= ~SWRST;                          // Initialize USART state machine
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
/*******************************************
�������ƣ�InitUART1
��    �ܣ���ʼ��UART1�˿�
��    ������
����ֵ  ����
********************************************/
void InitUART1(void)
{
    P3SEL |= 0xC0;                            //��P3.6��P3.7ѡ��UART1��ͨ�Ŷ˿�
    ME2 |= URXE1;                             //ʹ��USART1��RXD
    UCTL1 |= CHAR;                            //ѡ��8-bit�ַ�
    UTCTL1 |= SSEL0;                          //����ʱ��ѡ��ACLK
    UBR01 = 0x03;                             //������9600
    UBR11 = 0x00;
    UMCTL1 = 0x4a;                            //����
    UCTL1 &= ~SWRST;                          //��ʼ��UART״̬��
    IE2 |= URXIE1;                            //ʹ�ܽ����ж�
}
