/************************************************************
程序功能：在液晶上用串行数据通信方式循环滚动显示汉字
-------------------------------------------------------------
测试说明：观察液晶显示
*************************************************************/
#include  <msp430x14x.h>
#include "BoardConfig.h"
#include "cryfucns.h"

const uchar h0[] = {"诚实以启人之信我"};
const uchar h1[] = {"乐善以使人之亲我"};
const uchar h2[] = {"虚心以听人之教我"};
const uchar h3[] = {"恭顺以取人之敬我"};
const uchar h4[] = {"自检以杜人之议我"};
const uchar h5[] = {"自反以杜人之罪我"};
const uchar h6[] = {"容忍以免人之欺我"};
const uchar h7[] = {"勤俭以补人之助我"};
const uchar h8[] = {"量力以济人之求我"};
const uchar h9[] = {"尽心以报人之任我"};

const uchar *ptr[10];

uchar d1=0,d2=1,d3=2,d4=3;
uchar tcnt=0;
/************************主函数*************************/
void main(void)
{
    WDTCTL = WDT_ADLY_1000;             // 定时时间1S
    IE1   |= WDTIE;
    BoardConfig(0xba);                   // 关闭数码管、流水灯、4245
    
    //初始化指针数组
    ptr[0] = h0;
    ptr[1] = h1;
    ptr[2] = h2;
    ptr[3] = h3;
    ptr[4] = h4;
    ptr[5] = h5;
    ptr[6] = h6;
    ptr[7] = h7;
    ptr[8] = h8;
    ptr[9] = h9;
    
    Ini_Lcd();                           // 初始化液晶
    
    _EINT();    
    LPM1;
}

/*******************************************
函数名称：watchdog_timer
功    能：看门狗中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{ 
    uchar tmp;
    
    tcnt++;
    
    if(tcnt == 0x02)
    {
        Disp_HZ(0x80,ptr[d1],8);
        Disp_HZ(0x90,ptr[d2],8);
        Disp_HZ(0x88,ptr[d3],8);
        Disp_HZ(0x98,ptr[d4],8);
        
   /*这段代码与视频教程中略有不同，修正了视频教程中出现的某些行重复
     显示的错误，现在这个程序就是完美无误的了！这段代码的工作原理与
     视频中所述是一致的，大家仍可按视频中的讲解来理解*/
        tmp = d4;
        d4++;
        if(d4 == 10)    
        {   
            d4 = 0; 
        }
        d1 = d2;
        d2 = d3;
        d3 = tmp;           
        tcnt = 0;
    }
}
    
