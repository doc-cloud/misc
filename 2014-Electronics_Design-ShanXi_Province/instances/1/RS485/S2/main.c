/*************************************************
�����ܣ�ͨ��RS485�˿ڽ����ַ�����1602Һ������ʾ
--------------------------------------------------
���Է���������һ��RS485��������ͨ��RS485������ѧϰ��
          �������ݣ������ǿ���ʾ�ַ���Ӧ��ASCII�룩��
          �۲�Һ����ʾ
**************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "cry1602.h"

#define DRE_out     P3DIR |= BIT3     //����485оƬ��DE��RE�˿ڵ�IO����Ϊ���״̬
#define DE          P3OUT |= BIT3     //����485оƬ���ڷ���״̬ 
#define RE          P3OUT &= ~BIT3    //����485оƬ���ڽ���״̬

uchar pX = 0,pY = 0;

void Set_UART1(void);

/****************������****************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 //�رտ��Ź�
    BoardConfig(0xbf);
    
    DRE_out;
    RE;
    Set_UART1();  
    LcdReset();             //��ʾ��Һ��
    LPM3;
}
/*******************************************
�������ƣ�UART0_RX
��    �ܣ�UART0���жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=UART0RX_VECTOR
__interrupt void UART0_RX (void)
{
    Disp1Char(pX++,pY,RXBUF0);
    if(pX == 16)
    {
      pX = 0;
      pY ^= 1;
    }
}


/*******************************************
�������ƣ�Set_UART1
��    �ܣ�����MCU��UART1��Ӧ�ļĴ���
��    ������
����ֵ  ����
********************************************/
void Set_UART1(void)
{
    P3SEL |= 0xC0;                            //��P3.6��P3.7ѡ��UART1��ͨ�Ŷ˿�
    ME2 |= UTXE1 + URXE1;                     //ʹ��USART1��TXD��RXD
    UCTL1 |= CHAR;                            //ѡ��8-bit�ַ�
    UTCTL1 |= SSEL0;                          //����ʱ��ѡ��ACLK
    UBR01 = 0x0D;                             //������2400
    UBR11 = 0x00;
    UMCTL1 = 0x6B;                            //����
    UCTL1 &= ~SWRST;                          //��ʼ��UART״̬��
    IE2 |= URXIE1;                            //ʹ��UART1�����ж�
}
