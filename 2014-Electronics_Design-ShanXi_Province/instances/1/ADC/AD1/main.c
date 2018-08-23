/*************************************************************
�����ܣ���P6.0��Ӧ��ģ��ͨ�����ж��ת���󣬽�32��ƽ��ֵ
          �����������ʾ���������ʾ��ֻ��ADC��ת���������
          ����ʵ��ģ���ѹ��
--------------------------------------------------------------
�ر�˵�������������32��ƽ�������ǻῴ�����λ��ͣ�����䡣
--------------------------------------------------------------
����˵�������ڵ�λ��R7�ĵ�����ť���۲���ʾ���ֵı仯
*************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

uint Results[32];         //���ADC��ת�����
uint Average; 
//�����7λ���룺0--f
uchar scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar DispBuf[4] = {0,0,0,0};
                                                                                   
//��¼��ʾλ����ȫ�ֱ���
uchar cnt = 0;

void main(void)
{
    WDTCTL = WDT_ADLY_1_9;                    // �����ڲ����Ź������ڶ�ʱ��ģʽ��1.9ms�ж�һ��
    IE1 |= WDTIE;                             // ʹ�ܿ��Ź��ж�
    BoardConfig(0x88);                        // ������ܣ��ر���ˮ�ƺ͵�ƽת��
    P6SEL |= 0x01;                            // Enable A/D channel A0
    ADC12CTL0 = ADC12ON + SHT0_15 + MSC;      // Turn on ADC12, set sampling time
    ADC12CTL1 = SHP + CONSEQ_2;               // Use sampling timer, set mode
    ADC12IE = 0x01;                           // Enable ADC12IFG.0
    ADC12CTL0 |= ENC;                         // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    
    P4DIR = 0xff;
    P5DIR = 0xff;
    
    _EINT();
    while(1)
    {
        _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, Enable interrupts
        DispBuf[0] = Average / 1000;              //�����������ʾ
        DispBuf[1] = (Average - DispBuf[0]*1000)/100;
        DispBuf[2] = (Average - DispBuf[0]*1000 - DispBuf[1]*100)/10;
        DispBuf[3] = (Average - DispBuf[0]*1000 - DispBuf[1]*100 - DispBuf[2]*10);    
    }
}
/*******************************************
�������ƣ�ADC12ISR
��    �ܣ�ADC12���жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
    static uchar index = 0;
    float tmp;
    Results[index++] = ADC12MEM0;                      // Move results, IFG is cleared
    if(index == 31)
    {
         uchar i;
         
         Average = 0;
         for(i = 0; i < 32; i++)
            Average += Results[i];
         Average >>= 5; 
         tmp = Average;//����32��ƽ��ֵ
         tmp = tmp*3.6/4096;
         Average = tmp*1000;
         index = 0;
        _BIC_SR_IRQ(LPM0_bits);                   // Clear LPM0
    }
}
/*******************************************
�������ƣ�watchdog_timer
��    �ܣ����Ź��жϷ��������������������ܵ�
          ��ѡ��λѡ�ź�
��    ������
����ֵ  ����
********************************************/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{ 
    P5OUT = 0xff;
    P4OUT = scandata[DispBuf[cnt]];        //�����ѡ�ź�
    P5OUT &= ~(1 << cnt);           //���λѡ�ź�
  
    cnt++;                        //λ����������0~3֮��ѭ��
    if(cnt == 4) cnt = 0;
}
