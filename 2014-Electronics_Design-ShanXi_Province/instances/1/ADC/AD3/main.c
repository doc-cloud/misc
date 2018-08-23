/*********************************************************
�����ܣ���ADC��P6.0�˿ڵ�ѹ��ת�������ת�����ݺͶ�Ӧ��
          ģ���ѹ����ʽͨ�����ڷ��͵�PC����Ļ����ʾ
-----------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1, 9600
-----------------------------------------------------------
����˵�����򿪴��ڵ��Ծ��飬��ȷ����ͨ�Ÿ�ʽ���۲��������
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"
#include "allfunc.h"

#define   Num_of_Results   32
uint results[Num_of_Results];    //����ADCת�����������
uint average;
uchar tcnt = 0;

/***********************������***********************/
void main( void )
{
    uchar i;
    uchar buffer[5];
    
    WDTCTL = WDTPW + WDTHOLD;           //�ع�
    BoardConfig(0xb8);                  //������ܣ���ˮ�ƺ͵�ƽת��
    
    InitUART();
    Init_ADC();
    _EINT();
    
    buffer[4] = '\0';
    while(1)
    {
        LPM1;
        Hex2Dec(average,buffer);
        for(i = 0; i < 4; i++)
            buffer[i] += 0x30;
        PutString0("The digital value is: ");
        PutString(buffer);
        
        
        Trans_val(average,buffer);
        buffer[3] = buffer[2];
        buffer[2] = buffer[1];
        buffer[1] = 0x2e - 0x30;
        for(i = 0; i < 4; i++)
            buffer[i] += 0x30;
        PutString0("The analog value is: ");
        PutString(buffer);     
    }
    
}

/*******************************************
�������ƣ�ADC12ISR
��    �ܣ�ADC�жϷ��������������ö��ƽ����
          ����P6.0�ڵ�ģ���ѹ��ֵ
��    ������       
����ֵ  ����
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
    static uchar index = 0;
  
    results[index++] = ADC12MEM0;               // Move results
    if(index == Num_of_Results)
    {
        uchar i;

        average = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            average += results[i];
        }
        average >>= 5;                            //����32
        
        index = 0;
        tcnt++;
        if(tcnt == 250)      //��Ҫ�ǽ��ʹ��ڷ����ٶ�
        {
            LPM1_EXIT;
            tcnt = 0;
        }
    }
}
