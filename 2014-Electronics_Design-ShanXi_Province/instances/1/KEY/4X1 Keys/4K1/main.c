/***************************************************
�����ܣ���ɨ�跽ʽ��ȡ�ĸ�����ʽ�����ļ�ֵ��ͬʱ��
          �����ļ�ֵ�����������ʾ����   
----------------------------------------------------
����˵��������K1~k4�ĸ��������۲��������ʾ
***************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"

#define keyin    (P1IN & 0x0f)

//�����7λ���룺0--f
uchar scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delay(void);

/********************������********************/
void main( void )
{
    uchar temp,keyval = 0;
    
    WDTCTL = WDTPW + WDTHOLD;   //�رտ��Ź�
    BoardConfig(0x88);          //������ܣ��ر���ˮ�ƺ͵�ƽת��
    
    P1DIR = BIT7;               //����P1.0~P.3Ϊ����״̬��P.7Ϊ���
    P1OUT = 0;
    P3DIR |= BIT4;              //����P3.4Ϊ���״̬
    P3OUT |= BIT4;              //P3.4���1
    P4DIR = 0xff;
    P5DIR = 0xff;
    P4OUT = 0x3f;
    P5OUT = 0xf7;
    while(1)
    {
        if(keyin != 0x0f)       //����м�������
        {
            delay();            //��ʱ����
            if(keyin != 0x0f)   //�ٴμ�ⰴ��״̬
            {
                temp=keyin;
                while(keyin != 0x0f);   //�ȴ��������ſ�
                switch(temp)    //ת����ֵ    
                {
                case 0x0e:
                            keyval = 1;break;
                case 0x0d:
                            keyval = 2;break;
                case 0x0b:
                            keyval = 3;break;
                case 0x07:
                            keyval = 4;break;
                default:
                            keyval = 0;break;
                }
                P4OUT = scandata[keyval]; //��һλ�������ʾ
                P3OUT &= ~BIT4;           //P3.4���ӵ�LED��˸һ��
                delay();delay();
                P3OUT |= BIT4;
            }
        }
    }
}
/*******************************************
�������ƣ�delay
��    �ܣ�������������ʱ
��    ������
����ֵ  ����
********************************************/
void delay(void)
{
    uint tmp;
    
    for(tmp = 12000;tmp > 0;tmp--);
}
