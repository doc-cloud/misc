#include <msp430x14x.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

#define SCL_H P1OUT |= BIT1
#define SCL_L P1OUT &= ~BIT1
#define SDA_H P1OUT |= BIT0
#define SDA_L P1OUT &= ~BIT0

#define SCL_out P1DIR |= BIT1    //SCL设置为输出模式
#define SDA_in  P1DIR &= ~BIT0   //SDA改成输入模式
#define SDA_out P1DIR |= BIT0    //SDA变回输出模式
#define SDA_val P1IN&BIT0        //SDA的位值
 
#define TRUE    1
#define FALSE   0

/*******************************************
函数名称：Set_IO
功    能：设置IIC对应IO为输出方向并输出高电平
参    数：无
返回值  ：无
********************************************/
void Set_IO(void)
{
    SCL_out;
    SDA_out;
    SCL_H;
    SDA_H;
}
/*******************************************
函数名称：delay
功    能：延时约100us的时间
参    数：无
返回值  ：无
********************************************/
void delay(void)
{
    uchar i;
    
    for(i = 0;i < 15;i++)
        _NOP();
}	
/*******************************************
函数名称：start
功    能：完成IIC的起始条件操作
参    数：无
返回值  ：无
********************************************/
void start(void)
{
    SCL_H;
    SDA_H;
    delay();
    SDA_L;
    delay();
    SCL_L;
    delay();
}
/*******************************************
函数名称：stop
功    能：完成IIC的终止条件操作
参    数：无
返回值  ：无
********************************************/
void stop(void)
{
    SCL_H;
    SDA_L;	
    delay();
    SDA_H;
    delay();	   
}
/*******************************************
函数名称：check
功    能：检查从机的应答操作
参    数：无
返回值  ：从机是否有应答：1--有，0--无
********************************************/
uchar check(void)
{
    uchar slaveack;

    SDA_in;
    SCL_H;
    delay();
    slaveack = SDA_val;   //读入SDA数值
    SCL_L;
    delay();
    SDA_out;
    if(slaveack)    return FALSE;
    else            return TRUE;
}
/*******************************************
函数名称：write1
功    能：向IIC总线发送一个1
参    数：无
返回值  ：无
********************************************/
void write1(void)
{
    SDA_H;
    delay();
    SCL_H;
    delay();
    SCL_L;				
    delay();
}
/*******************************************
函数名称：write0
功    能：向IIC总线发送一个0
参    数：无
返回值  ：无
********************************************/
void write0(void)
{
    SDA_L;
    delay();
    SCL_H;
    delay();			 
    SCL_L;				
    delay();
}
/*******************************************
函数名称：write1byte
功    能：向IIC总线发送一个字节的数据
参    数：wdata--发送的数据
返回值  ：无
********************************************/
void write1byte(uchar wdata)
{
    uchar i;

    for(i = 8;i > 0;i--)
    {
        if(wdata & 0x80)	write1();
        else 			write0();
        wdata <<= 1;
    }                    
}
