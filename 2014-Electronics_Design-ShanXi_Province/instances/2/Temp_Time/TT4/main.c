/*************************************************
�����ܣ���DS18B20���½����DS1302��ʱ��һ����1602
          Һ������ʾ
-------------------------------------------------
����˵�����۲�Һ����ʾ��
*************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "DS18B20.h"
#include "DS1302.h"
#include "cry1602.h"

uchar dN[6];        //���ʮ���Ʋ��½��������

void Disp_Numb(uint temper);
void ShowTime(uchar *times);
/****************������****************/
void main(void)
{
    uchar i;
    //���õ���ʱ������飬��ʽΪBCD�룬˳���� �� ʱ �� �� ���� ��
    uchar CurrentTime[7] = {0x00,0x00,0x00,0x18,0x04,0x05,0x08};
    uchar ReadTime[7];
    
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
   
    BoardConfig(0xb8);                  //�ر�����ܡ���ˮ�ƺ͵�ƽת��
    LcdReset();                         //��ʼ��Һ��
    Reset_DS1302();                     //��ʼ��DS1302
    //���������������DS1302�ڲ�ʱ�䣬�������Ҫ�뽫��ע�͵�����ݼ���Ctrl+K��
    Set_DS1302(CurrentTime);                             
    //����ʱ��ѡ��SMLK=8MHz��1/8��Ƶ��Ϊ1MHz
    TACTL |= TASSEL_2 + ID_3; 
    //��Һ������ʾ��ʾ����    
    DispStr(0,0,"Temp:"); 
    DispStr(0,1,"Time:"); 
    //ѭ��������ʾ
    while(1)
    {
       Disp_Numb(Do1Convert());         //ִ��һ�β���
       Disp1Char(6,0,dN[5]+0x30);       //��ʾ���½��
       Disp1Char(7,0,dN[4]+0x30);
       Disp1Char(8,0,'.');
       Disp1Char(9,0,dN[3]+0x30);
       Disp1Char(10,0,dN[2]+0x30);
       Disp1Char(11,0,dN[1]+0x30);
       Disp1Char(12,0,dN[0]+0x30);
       
       Get_DS1302(ReadTime);            //��ȡ��ǰʱ��
       ShowTime(ReadTime);              //��ʾʱ������Ϣ
    }
}
/*******************************************
�������ƣ�Disp_Numb
��    �ܣ�����DS18B20��ȡ��11bit�¶�����ת��
          ��ʮ�����¶�����
��    ����temper--11bit�¶�����
����ֵ  ����
********************************************/
void Disp_Numb(uint temper)
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
/*******************************************
�������ƣ�ShowTime
��    �ܣ���DS1302��ʱ��ת����10������ʾ
��    ����times--��ȡ��ʱ������
����ֵ  ����
********************************************/    
void ShowTime(uchar *times)
{
    uchar h2[8];        //��2����ʾ����
    const uchar shuzi[] = {"0123456789"};
      
    h2[0] = shuzi[times[2]>>4];     //ʱ
    h2[1] = shuzi[times[2]&0x0f];
    h2[2] = 0x3a;       //":"
    h2[3] = shuzi[times[1]>>4];     //��
    h2[4] = shuzi[times[1]&0x0f];
    h2[5] = 0x3a;       //":"
    h2[6] = shuzi[times[0]>>4];     //��
    h2[7] = shuzi[times[0]&0x0f];
    DispNChar(6,1,8,h2);           //�ڵڶ�����ʾ
}

