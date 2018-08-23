/**********************************************
程序功能：在六位数码管上显示六个数字012345
-----------------------------------------------
测试说明：观察数码管显示
***********************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

//数码管7位段码：0--f
uchar scandata[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f};
//记录显示位数的全局变量
uchar cnt = 0;
int num=0;

void delayus(i)
{
    i=i*100;
    for(;i>0;i--);
}
void init()
{
  P4OUT = 0x00;  
  P5OUT = 0xff;
}
void display(unsigned char data, unsigned char bit)
{
    P4OUT = scandata[data];
    P5OUT = (0xbf >> bit)|(0xbf << (8-bit));
}
void display_num()
{
     display(num%10,1);
     delayus(1);
     init();
     display(num/10%10,2);
     delayus(1);
     init();
     display(num/100,3);
     delayus(1);
     init();
     if(num == 1000)
        num=0;
}
/********************主函数********************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; 
    P1DIR |= 0x0c;  
    unsigned char readbuf[2];
  //  Write_1Byte(num,0x80);// 设置内部看门狗工作在定时器模式，1.9ms中断一次
    Read_NByte_Randomaddress(readbuf,2,0x80);
    num = readbuf[0]+readbuf[1]*256;
    num = num%1000;
    BoardConfig(0x88);
  
    P4DIR = 0xff;                 //设置P4，P5的IO方向为输出
    P5DIR = 0xff;                 
  
    P4OUT = 0x00;                 //设置P4，P5的输出初值
    P5OUT = 0xff;  
    CCR0 = 32768;
    CCTL0 = CCIE;
    TACTL = TASSEL_1+MC_1;
    _EINT();
    while(1)
    {
       display_num();
       if(num%10 == 5)
       Write_1Byte(num,0x80);
    }
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Time_A()
{
    num++;
}
