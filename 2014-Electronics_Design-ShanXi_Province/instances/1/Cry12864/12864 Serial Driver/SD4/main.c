/*************************************************************
�����ܣ��ô������ݴ��䷽ʽ��Һ�����ۺ���ʾ�ַ������ֺ�ͼ��
--------------------------------------------------------------
����˵�����۲�Һ����ʾ
*************************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "cryfucns.h"
#include "displaydata.h"

uchar flag = 0;
/************************������***********************/
void main(void)
{
    uchar i,j;
    
    WDTCTL = WDTPW + WDTHOLD;            //�رտ��Ź�
    BoardConfig(0xba);                   //�ر�����ܡ���ˮ�ơ�4245
    TACTL = TASSEL_1 + MC_1;             //����ʱ��ACLK, ������ģʽ
    CCR0 = 32768 - 1;
    CCTL0 |= CCIE;                       //ʹ��CCR0�Ƚ��ж�
    _EINT(); 
    
    Ini_Lcd();
    Disp_HZ(0x81,line1,6);
    Disp_HZ(0x8a,line2,4);
    flag = 0;
    while(flag < 3);                    //�ȴ�������
    Send(0,0x01);                       //����
    CCR0 = (32768 - 1) / 5;
    flag = 0;
    for(i = 0; i < 4; i++)
    {
        Send(0, 0x0f);                  //���α�
        switch(i)
        {
        case 0: Send(0,0x81);break;
        case 1: Send(0,0x91);break;
        case 2: Send(0,0x89);break;
        case 3: Send(0,0x99);break;
        }
        for(j = 0; j < 12; j++)
        {
            Send(1, shige[i*12 + j]);
            if(j == 11)
                Send(0, 0x0c);                    //�ر��α�
            flag = 0;
            while(!flag);                         //�ȴ�1/5��         
        }   
    }
    CCR0 = 32768 - 1; 
    flag = 0;
    while(flag < 2);                    //�ȴ�2����
    Send(0,0x01);                       //����
    Draw_PM(school);                    //��ʾ�����ͻ���             
    flag = 0;
    while(flag < 3);                    //�ȴ�������
    Draw_PM(QQ);                        //��ʾQQ����
    flag = 0;
    while(flag < 3);                    //�ȴ�������
    Send(0,0x01);                       //����
    Disp_HZ(0x92,jieshu,4);             //��������   
    while(1);
}
/*******************************************
�������ƣ�TimerA_ISR
��    �ܣ���ʱ��A���жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
{
    flag++;    
}
