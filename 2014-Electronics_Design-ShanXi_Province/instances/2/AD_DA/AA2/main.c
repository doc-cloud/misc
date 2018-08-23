/****************************************************
�����ܣ���������������DAC�������ѹ����LED����
----------------------------------------------------
�������ã���������J1��1�ź�2�ţ���������������̽�
-----------------------------------------------------
����˵��������K3�����Լ�СDAC�������ѹ��
          ����K4����������DAC�������ѹ��
          �۲�LED���ȱ仯��
******************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "IIC.h"

uchar   DAC_Val;          //DAC�������

void delay20ms(void);
uchar Write_DAC(uchar wdata);
/****************������****************/
void main(void)
{
    uchar keyval;
    
    WDTCTL = WDTPW + WDTHOLD;   //ֹͣ���Ź�
    BoardConfig(0xb8);
    
    Set_IO();                   //����IIC�˿� 
    P1DIR |= BIT7;              //P1.7����͵�ƽ���Ƽ��̹����ڶ�������ģʽ
    P1OUT &= ~BIT7;
    DAC_Val = 0xff;
    Write_DAC(DAC_Val);
    while(1)
    {
        if((P1IN & 0x0c) != 0x0c)
        {
            delay20ms();
            if((P1IN & 0x0c) != 0x0c)
            {
                keyval = P1IN & 0x0c;
                while((P1IN & 0x0c) != 0x0c);       //�ȴ������ſ�
                if(keyval == 0x04)                  //�����K3������
                {
                     DAC_Val -= 20;                 //DAC���������20��ƫ����
                     Write_DAC(DAC_Val);            //д��DAC
                }
                else if(keyval == 0x08)             //�����K4������ 
                {
                     DAC_Val += 20;                 //DAC���������20��ƫ����
                     Write_DAC(DAC_Val);            //д��DAC   
                }
                else
                {
                     _NOP();
                }
            }
        }
    }
}
/*******************************************
�������ƣ�delay20ms
��    �ܣ�������������ʱ
��    ������
����ֵ  ����
********************************************/
void delay20ms(void)
{
    uint tmp;
    
    for(tmp = 12000;tmp > 0;tmp--);
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
