/*****************************************************
�����ܣ�MCU��ͣ��PC����������,����Ļ����ʾ0~127��Ӧ
          ��ASCII�ַ�
------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1, 2400
------------------------------------------------------
����˵�����򿪴��ڵ������֣���ȷ����ͨ�Ÿ�ʽ���۲���Ļ
******************************************************/

#include  <msp430x14x.h>
#include  "BoardConfig.h"

void Delays(void);
void PutString(uchar *ptr);
   unsigned char ch;
/********************������**********************/
void main(void)
{

  
    WDTCTL = WDTPW + WDTHOLD;                 // �ع�
    BoardConfig(0xb8);                        // ����ˮ�ơ��������������
    P3SEL |= 0x30;
    P3DIR = BIT4;                             // P3.4,5ѡ��ΪUART�շ��˿�
    ME1 |= UTXE0 + URXE0;                     // ʹ��USART0�շ�
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x0D;                             // 32k/2400 - 13.65
    UBR10 = 0x00;                             //
    UMCTL0 = 0x6B;                            // Modulation
    UCTL0 &= ~SWRST;                                            // ��ʼ��UART0״̬��
    IE1 |= URXIE0;   
  //  IE1 |= UTXIE0; 
    _EINT();
 
    TXBUF0='s';
    while(1)
    { 
 
    
    }
} 

#pragma vector=UART0RX_VECTOR
 __interrupt void uart(void)
 {
   while (!(IFG1 & UTXIFG0));  
   TXBUF0 = RXBUF0;   
  // TXBUF0 = RXBUF0;
 }   

