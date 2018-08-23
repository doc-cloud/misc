/****************************************************************
�����ܣ���MCUƬ�ڵ�MCLK,SMCLK��ACLK�����ź�ת����5V��ƽ�ź�
-----------------------------------------------------------------
����˵�����û�������ʾ��������������P7�ĵ�6��7��8�������ŵ�
          ������Σ�P7���Ҳ����ǵ�1���ţ�
****************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

void main(void)
{
  BoardConfig(0x38);                        // �򿪵�ƽת�����ر���ˮ�ƺ������
  WDTCTL = WDTPW +WDTHOLD;                  // �ع�
  DCOCTL = DCO0 + DCO1 + DCO2;              // Max DCO
  BCSCTL1 = RSEL0 + RSEL1 + RSEL2;          // XT2on, max RSEL
  BCSCTL2 |= SELS;                          // SMCLK = XT2
  P5DIR |= 0x70;                            // P5.6,5,4 outputs
  P5SEL |= 0x70;                            // P5.6,5,5 options

  while(1);
}
