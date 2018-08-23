/**********************************************
�����ܣ�����λ���������ʾһ���ƶ��Ĺ�Ȧ����
          Ȧ���ٶ����ɱ仯����-->��-->�죩
-----------------------------------------------
����˵�����۲��������ʾ
***********************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

#define NBIT(x)     ~(1 << x)

//�ƶ���Ȧ��Ӧ���ַ�
uchar scandata[16] = {0x01,0x01,0x01,0x01,0x01,0x01,0x20,0x10,
                      0x08,0x08,0x08,0x08,0x08,0x08,0x04,0x02};
//��ʾ�ַ��Ŀ��Ʊ���
uchar step = 0;
//�ƶ�Ȧ���ı���
uint circle = 0;

/********************������********************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�    
    BoardConfig(0x88);
  
    P4DIR = 0xff;                 //����P4��P5��IO����Ϊ���
    P5DIR = 0xff;                 
  
    P4OUT = 0x00;                 //����P4��P5�������ֵ
    P5OUT = 0xff;
    
    CCR0 = 164;
    TACCTL0 |= CCIE;              //ʹ�ܱȽ��ж�
    TACTL |= TASSEL_1 + MC_1;     //ACLK, up mode
  
    _BIS_SR(LPM3_bits + GIE);     //CPU����LPM3�͹���ģʽ��ͬʱ��ȫ���ж�
}

/*******************************************
�������ƣ�TimerA_ISR
��    �ܣ���ʱ��A�жϷ��������������������ܵ�
          ��ѡ��λѡ�ź�
��    ������
����ֵ  ����
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
{ 
    step++;
    if(step == 16)  
    {
        step = 0;
        circle++;
        if(circle == 10)        //����Ѿ��ƶ���10Ȧ
        {
            circle = CCR0;
            CCR0 += circle;     //�ٶȽ�Ϊԭ����һ��
            if(CCR0 > 32700)    //����ٶȵ�����ߣ����ͷ��ʼ
                CCR0 = 164;     
            circle = 0;
        }
    }
    switch(step)
    {
    case 0:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    case 1: 
            P5OUT = NBIT(4);
            P4OUT = scandata[step];
            break;
    case 2:
            P5OUT = NBIT(3);
            P4OUT = scandata[step];
            break;
    case 3: 
            P5OUT = NBIT(2);
            P4OUT = scandata[step];
            break;
    case 4:
            P5OUT = NBIT(1);
            P4OUT = scandata[step];
            break;
    case 5:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 6:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 7:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 8:
            P5OUT = NBIT(0);
            P4OUT = scandata[step];
            break;
    case 9:
            P5OUT = NBIT(1);
            P4OUT = scandata[step];
            break;
    case 10:
            P5OUT = NBIT(2);
            P4OUT = scandata[step];
            break;
    case 11:
            P5OUT = NBIT(3);
            P4OUT = scandata[step];
            break;
    case 12:
            P5OUT = NBIT(4);
            P4OUT = scandata[step];
            break;
    case 13:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    case 14:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    case 15:
            P5OUT = NBIT(5);
            P4OUT = scandata[step];
            break;
    }
}

