#include <msp430x44x.h>
#include "cry1602.h"
typedef unsigned char uchar;
typedef unsigned int  uint;

/**************全局变量****************/
uchar second,minute,hour,hour0;  //秒、分、时变量
uchar pmin,phour,ps1;            //辅助计算变量          

/*******************************************
函数名称：Clock
功    能：计算当前时间
参    数：无
返回值  ：无
说明    ：本函数对本文件开头定义的second,minute,
          hour,hour0四个全局变量进行操作
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
函数名称：Display
功    能：在1602液晶上显示时间
参    数：无
返回值  ：无
说明    ：本函数对本文件开头定义的全局变量进行
          操作
********************************************/
void Display(void)
{
    uchar s0,s1;
    uchar m0,m1;
    uchar h0,h1;

    s1 = second / 10;           //十位
    s0 = second - (s1 * 10);    //个位
    s1 += 48;                   //加上48等于其对应的ASCII码
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


  
	   
