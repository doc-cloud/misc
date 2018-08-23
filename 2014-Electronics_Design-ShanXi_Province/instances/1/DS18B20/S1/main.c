/*************************************************
�����ܣ���DS18B20�������²������������ʾ��
-------------------------------------------------
����˵�����۲���ʾ�¶���ֵ��
*************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "DS18B20.h"

//Ҫ��ʾ��6λ�¶�����
uchar dN[6];        
//������߶��룻0--f
uchar scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//�����λѡ����
uchar cnt = 0;  

void Disp_Numb(uint temper);

/****************������****************/
void main(void)
{
    uchar i;
    
    WDTCTL=WDTPW+WDTHOLD; 
     
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     //�ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             //����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           //MCLK��SMCLKѡ���Ƶ����
   
    BoardConfig(0x88);                  //�������

    //���ÿ��Ź���ʱ������ʼ����������ܵ�IO
         
    IE1 |= WDTIE;                            
    P4DIR = 0xff;
    P5DIR = 0xff; 
    P4OUT = 0x00;
    P5OUT = 0xff;
    
    //����ʱ��ѡ��SMLK=8MHz��1/8��Ƶ��Ϊ1MHz
    TACTL |= TASSEL_2 + ID_3; 
    //��ȫ���ж�
    _EINT();
    //ѭ��������ʾ
    while(1)
    {
       Disp_Numb(Do1Convert());
    }
}

/*******************************************
�������ƣ�Disp_Numb
��    �ܣ�����DS18B20��ȡ��11bit�¶�����ת��
          ���������ʾ���¶�����
��    ����temper--11bit�¶�����
����ֵ  ����
********************************************/
/*void Disp_Numb(uint temper)
{
    uchar i;
    
    for(i = 0;i < 6;i++) dN[i] = 0; //��ʼ����ʾ����

    //��ֵת��
    if(temper & BIT0) 
    {
        dN[0] = 5;
        dN[1] = 2;
        dN[2] = 6;
    }
    if(temper&BIT1)     
    {
        dN[1] += 5;
        dN[2] += 2;
        dN[3] += 1;
    }
    if(temper & BIT2)     
    {
        dN[2] += 5;
        dN[3] += 2;
        if(dN[2] >= 10)
        {
            dN[2] -= 10;
            dN[3] += 1;
        }
    }
    if(temper&BIT3)     
    {
        dN[3] += 5;
    }
    if(temper & BIT4)
    {
        dN[4] += 1;
    }
    if(temper & BIT5)     
    {
        dN[4] += 2;
    }
    if(temper & BIT6)
    {
        dN[4] += 4;
    }
    if(temper & BIT7)     
    {
        dN[4] += 8;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT8)
    {
        dN[4] += 6;
        dN[5] += 1;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT9)
    {
        dN[4] += 2;
        dN[5] += 3;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BITA)
    {
        dN[4] += 4;
        dN[5] += 6;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
        if(dN[5] >= 10)
        {
            dN[5] -= 10;
        }
    }
}

/*