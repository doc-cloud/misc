/*********************************************************
�����ܣ���PC������SSCOM32��ʾDS18B20�����¶Ƚ��
-----------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1,  9600
-----------------------------------------------------------
����˵������SSCOM32��ȷ����ͨ�Ÿ�ʽ���۲���Ļ��ʾ�Ĳ���
          ���
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"
#include "uart0.h"
#include "DS18B20.h"

void Transfer(uint temper, uchar dN[6]);
/**************************������**************************/
void main( void )
{
    uint tmp;
    uchar i;
    uchar Dec[6];
    
    WDTCTL = WDTPW + WDTHOLD;           //�ع�
    BoardConfig(0xb8);                  //������ܣ���ˮ�ƺ͵�ƽת��
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     //�ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             //����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           //MCLK��SMCLKѡ���Ƶ����
    
    TACTL |= TASSEL_2 + ID_3;           //����ʱ��ѡ��SMLK=8MHz��1/8��Ƶ��Ϊ1MHz    
    
    InitUART();                         //��ʼ��UART�˿�
    
    PutString("������ʾDS18B20�����¶���ֵ��");
    while(1)
    {
        tmp = Do1Convert();
        Transfer(tmp,Dec);
        if(tmp & 0xf800)        //�������λ��1
        {
            Send1Char('-');     //��ʾ����
        }
        for(i = 0;i < 6;i++)
        {
            Send1Char(Dec[5-i]+0x30);
            if(i == 1)
            {
                Send1Char('.');
            }
        
        }
        PutString("��C"); 
        
    }
    
}
/*******************************************
�������ƣ�Transfer
��    �ܣ�����DS18B20��ȡ��11bit�¶�����ת��
          ��6λʮ�������ֱ�ʾ���¶�
��    ����temper--11bit�¶�����
����ֵ  ����
********************************************/
void Transfer(uint temper, uchar dN[6])
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
    if(temper & BIT1)     
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
