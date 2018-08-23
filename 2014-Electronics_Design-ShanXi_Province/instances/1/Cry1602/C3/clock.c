#include <msp430x44x.h>
#include "cry1602.h"
typedef unsigned char uchar;
typedef unsigned int  uint;

/**************ȫ�ֱ���****************/
uchar second,minute,hour,hour0;  //�롢�֡�ʱ����
uchar pmin,phour,ps1;            //�����������          

/*******************************************
�������ƣ�Clock
��    �ܣ����㵱ǰʱ��
��    ������
����ֵ  ����
˵��    ���������Ա��ļ���ͷ�����second,minute,
          hour,hour0�ĸ�ȫ�ֱ������в���
********************************************/
void Clock(void)
{
    second += 1;
    if(second == 60) 
    {
        second = 0;
        minute += 1;
		if(minute == 60)
		{
		    minute = 0;
		    hour += 1; hour0 += 1;
		    if(hour == 24)   hour = 0;
		}
    }
}
/*******************************************
�������ƣ�Display
��    �ܣ���1602Һ������ʾʱ��
��    ������
����ֵ  ����
˵��    ���������Ա��ļ���ͷ�����ȫ�ֱ�������
          ����
********************************************/
void Display(void)
{
    uchar s0,s1;
    uchar m0,m1;
    uchar h0,h1;

    s1 = second / 10;           //ʮλ
    s0 = second - (s1 * 10);    //��λ
    s1 += 48;                   //����48�������Ӧ��ASCII��
    s0 += 48; 
    
    Disp1Char(11,1,s0);
  	if(ps1 != s1)
    {
		ps1 = s1;
  		Disp1Char(10,1,s1);                         
    }
  
    if(pmin != minute)
	{
	    pmin = minute;
	    m1 = minute / 10;
	    m0 = minute - (m1 * 10);
	    m1 += 48;
        m0 += 48;
	    Disp1Char(7,1,m1);
        Disp1Char(8,1,m0);
	}
	if(phour != hour)
	{
	    phour = hour;
	    h1 = hour / 10;
	    h0 = hour - (h1 * 10);
	    h1 += 48;
        h0 += 48;
	    Disp1Char(4,1,h1);
        Disp1Char(5,1,h0); 
	}
}


  
	   
