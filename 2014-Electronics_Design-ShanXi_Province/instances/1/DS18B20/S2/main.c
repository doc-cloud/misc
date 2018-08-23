/*************************************************************
程序功能：读取DS18B20进行温度测量以后的结果并在1602液晶上显示
---------------------------------------------------------------
测试说明：观察显示温度数值。
*************************************************************/

#include  "msp430.h"
#include  "BoardConfig.h"
#include  "cry1602.h"
#include "DS18B20.h"
 uchar scandata[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                          0x7f,0x6f};
//要显示的6位温度数字
 uchar dn[6]=""; 
double num=0;
int temp=0;

void Disp_Numb(uint temper);

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

/*************************主函数*************************/
void main( void )
{
 uchar dN[6]="";
    int high=0;
    unsigned char low;
    
    double c=0;

    int i;
  //  WDTCTL = WDTPW + WDTHOLD;
 
    WDTCTL = WDT_ADLY_1_9 ;  
    IE1 |= WDTIE;  
    BoardConfig(0x88);        
    P4DIR = 0xff;                 
    P5DIR = 0xff;                 
  
    P4OUT = 0x00;                
    P5OUT = 0xff; 

  
    BCSCTL1 &= ~XT2OFF;                
    do
    {
        IFG1 &= ~OFIFG;           
        for (i = 0xFF; i > 0; i--);     
    }
    while ((IFG1 & OFIFG));             
    BCSCTL2 |= SELM_2 + SELS;      
   
    TACTL |= TASSEL_2 + ID_3; 

    _EINT();
    
    while(1)
    {
       num = Do1Convert();
       num = num/16;
    }
             
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    display((int)num%10, 2);
    delayus(5);
    init();
    display((int)num/10%10,3);
    delayus(5);
    init();
    display((int)(num*10)%10,1);
    delayus(5);
    init();
}