/****************************************************
�����ܣ���ADC����DAC�����ģ���ѹ���ݣ�
          ������ģ���ѹֵ��1602Һ������ʾ
----------------------------------------------------
�������ã���������J1��2�ź�3�ţ���������������̽�
-----------------------------------------------------
����˵��������S3�����Լ�СDAC�������ѹ��
          ����S4����������DAC�������ѹ��
          �۲�Һ����ʾ�仯��
******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "IIC.h"
#include "cry1602.h"

uint    ADC_tmp[16];      //���ADC��ֵ�Ļ�����
uchar   cnt = 0;          //��������
uint    ADC_Val = 0;      //һ��ADCת����ƽ��ֵ
uchar   DAC_Val;          //DAC�������

uchar shuzi[] = {"0123456789."};
uchar tishi1[] = {"DAC volt: "};
uchar tishi2[] = {"ADC volt: "};
void Init_ADC(void);
uchar Write_DAC(uchar wdata);
void Trans_val(uint Hex_Val,uchar n);

/****************������****************/
void main(void)
{
    
    WDTCTL = WDTPW + WDTHOLD;   //ֹͣ���Ź�
    BoardConfig(0xb8);
    P1DIR |= 0x03 + BIT7;       //����DAC�Ŀ���IOΪ���״̬
    P1OUT  = 0x03;
    P1IE  |= BIT2 + BIT3;       //����P1.2��P1.3�ж�
    
    LcdReset();
    DispNChar(0,0,10,tishi1);   //��ʾ��ʾ����
    Disp1Char(15,0,0x56);       //0x56���ַ�V��ASCII��ֵ       
    DispNChar(0,1,10,tishi2);
    Disp1Char(15,1,0x56);
    
    DAC_Val = 0;
    Write_DAC(DAC_Val);
    Trans_val(DAC_Val,8);
    
    Init_ADC();
    _EINT();
    while(1)
    {       
        ADC12CTL0 |= ADC12SC;           //��ʼһ��ת��
        LPM0;
        Trans_val(ADC_Val,12);          //��Һ������ʾ
    }
}
/*******************************************
�������ƣ�ADC12_ISR
��    �ܣ�ADC���жϷ�����
��    ������
����ֵ  ����
*******************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR(void)
{   
    ADC_tmp[cnt++] = ADC12MEM0;
    
    if(cnt == 16)
    {
        unsigned long ADC_sum = 0;
        uchar i;
        
        for(i = 0;i < 16;i++)           //��16�β����ľ�ֵ
            ADC_sum += ADC_tmp[i];
        
        ADC_Val = ADC_sum >> 4;        
        cnt = 0;
        LPM0_EXIT;
    }
    else
    {
        ADC12CTL0 |= ADC12SC;           //��ʼһ��ת��
    }
}
/*******************************************
�������ƣ�Port1_ISR
��    �ܣ��˿�P1���жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
    
    _DINT();
    
    if(P1IFG & BIT2)
    {
        P1IFG = 0x00;           //���жϱ�־ 
        DAC_Val -= 10;          //DAC���������10��ƫ����
        Write_DAC(DAC_Val);     //д��DAC
        Trans_val(DAC_Val,8);   //��Һ������ʾ
    }
    else if(P1IFG & BIT3)
    {
        P1IFG = 0x00;           //���жϱ�־
        DAC_Val += 10;          //DAC���������10��ƫ����
        Write_DAC(DAC_Val);     //д��DAC
        Trans_val(DAC_Val,8);   //��Һ������ʾ
    }
    else
        _NOP();
    
    P1IFG = 0x00;           //���жϱ�־
    _EINT();
}

/*******************************************
�������ƣ�Init_ADC
��    �ܣ���ʼ��ADC�Ĵ���
��    ������
����ֵ  ����
********************************************/
void Init_ADC(void)    
{
    P6SEL |= BIT1;                  //P6.1ѡ��ADC����˿�
    ADC12CTL0 = SHT0_2 + ADC12ON;   //���ò���ʱ�䣬��ADC
    ADC12CTL1 = SHP;                //ʹ�ò�����ʱ����ѡ��SMCLK
    ADC12IE = BIT0;                 //ʹ�ܲ����ж�
    ADC12MCTL0 = INCH_1;            //ѡ�����ͨ��1
    ADC12CTL0 |= ENC;               //��ת��ʹ��
}
/*******************************************
�������ƣ�Write_DAC
��    �ܣ���DAC��д�������ѹ����
��    ������
����ֵ  ��д������1--�ɹ���0--ʧ��
********************************************/
uchar Write_DAC(uchar wdata)
{
    start();
	write1byte(0x98);   //DAC���豸��ַ
	if(check())   write1byte(wdata >> 4);   //д����ģʽ�͵�ѹ���ݵĸ���λ
	else          return 0;
	if(check())   write1byte(wdata << 4);  //д��ѹ���ݵĵ���λ
	else          return 0;
	if(check())	  stop();
	else          return 0;
	return 1;    
}
/*******************************************
�������ƣ�Trans_val
��    �ܣ���16�������ݱ任����λ10�������ݣ�
          ����Һ������ʾ
��    ����Hex_Val--16��������
          n--�任ʱ�ķ�ĸ����2��n�η�       
����ֵ  ��д������1--�ɹ���0--ʧ��
********************************************/
void Trans_val(uint Hex_Val,uchar n)
{
    unsigned long caltmp;
    uint Curr_Volt;
    uchar t1,i;
    uchar ptr[4];
    
    caltmp = Hex_Val;
    caltmp = (caltmp << 5) + Hex_Val;           //caltmp = Hex_Val * 33
    caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
    Curr_Volt = caltmp >> n;                    //Curr_Volt = caltmp / 2^n
    ptr[0] = Curr_Volt / 100;                   //Hex->Dec�任
    t1 = Curr_Volt - (ptr[0] * 100);
    ptr[2] = t1 / 10;
    ptr[3] = t1 - (ptr[2] * 10);
    if(n == 8)          //�����DAC������
        t1 = 0;
    else                //�����ADC������
        t1 = 1;
    
    ptr[1] = 10;            //shuzi���е�10λ��Ӧ����"."
    _DINT();
    //��Һ������ʾ�任��Ľ��
    for(i = 0;i < 4;i++)
      Disp1Char((10 + i),t1,shuzi[ptr[i]]);
    _EINT();
}
