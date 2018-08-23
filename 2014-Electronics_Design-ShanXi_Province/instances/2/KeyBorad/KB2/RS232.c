#include  <msp430x14x.h>

/*******************************************
�������ƣ�nit_UART0
��    �ܣ���ʼ��UART0�˿ڼĴ���
��    ������
����ֵ  ����
********************************************/
void Init_UART0(void)
{
    P3SEL |= 0x30;                            // ѡ��P3.4��P3.5��UARTͨ�Ŷ˿�
    ME1 |= UTXE0 + URXE0;                     // ʹ��USART0�ķ��ͺͽ���
    UCTL0 |= CHAR;                            // ѡ��8λ�ַ�
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x03;                             // ������9600
    UBR10 = 0x00;                             //
    UMCTL0 = 0x4A;                            // Modulation
    UCTL0 &= ~SWRST;                          // ��ʼ��UART״̬��
}

void Send_Char(unsigned char schar)
{   
    while(!(IFG1 & UTXIFG0));                 //�ȴ��ַ����ͽ���
    TXBUF0 = schar;
}
    
