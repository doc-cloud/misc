#include <msp430x14x.h>
typedef unsigned char uchar;
typedef unsigned int  uint;

#define SCL_H P1OUT |= BIT2
#define SCL_L P1OUT &= ~BIT2
#define SDA_H P1OUT |= BIT3
#define SDA_L P1OUT &= ~BIT3

#define SDA_in  P1DIR &= ~BIT3   //SDA改成输入模式
#define SDA_out P1DIR |= BIT3    //SDA变回输出模式
#define SDA_val P1IN&BIT3        //SDA的位值
 
#define TRUE    1
#define FALSE   0

/*******************************************
函数名称：delay
功    能：延时约15us的时间
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
	SDA_L;
	delay();
	SCL_H;
	delay();
	SDA_H;
	delay();	   
}
/*******************************************
函数名称：mack
功    能：完成IIC的主机应答操作
参    数：无
返回值  ：无
********************************************/
void mack(void)
{
	SDA_L;
	_NOP(); _NOP();
	SCL_H;
	delay();
	SCL_L;
	_NOP();_NOP();
	SDA_H;     
	delay();
}
/*******************************************
函数名称：mnack
功    能：完成IIC的主机无应答操作
参    数：无
返回值  ：无
********************************************/
void mnack(void)
{
	SDA_H;
	_NOP(); _NOP();
	SCL_H;
	delay();
	SCL_L;
	_NOP(); _NOP();
	SDA_L;   
	delay();       
}

/**********检查应答信号函数******************/
/*如果返回值为1则证明有应答信号，反之没有*/
/*******************************************
函数名称：check
功    能：检查从机的应答操作
参    数：无
返回值  ：从机是否有应答：1--有，0--无
********************************************/
uchar check(void)
{
	uchar slaveack;
    
	SDA_H;
	_NOP(); _NOP();
	SCL_H;
	_NOP(); _NOP();
        SDA_in;
        _NOP(); _NOP();
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
		else 			    write0();
		wdata <<= 1;
	}                  
	
	SDA_H;
	_NOP();   
}
/*******************************************
函数名称：writeNbyte
功    能：向IIC总线发送N个字节的数据
参    数：outbuffer--指向发送数据存放首地址
          的指针
          n--数据的个数
返回值  ：发送是否成功的标志：1--成功，0--失败
********************************************/
uchar writeNbyte(uchar * outbuffer,uchar n)
{
	uchar i;
    
	for(i = 0;i < n;i++)
	{
		write1byte(* outbuffer);
		if(check())      
		{
			outbuffer++;			
		}
		else 
		{
			stop();
			return FALSE;
		}
	}

	stop();
	return TRUE;			
}
/*******************************************
函数名称：read1byte
功    能：从IIC总线读取一个字节
参    数：无
返回值  ：读取的数据
********************************************/
uchar read1byte(void)
{
	uchar  rdata = 0x00,i;
    uchar flag;
    
	for(i = 0;i < 8;i++)
	{
		SDA_H;
		delay();
		SCL_H;
        SDA_in;
		delay();
		flag = SDA_val;
		rdata <<= 1;
		if(flag)	rdata |= 0x01;
        SDA_out;
		SCL_L;
		delay();
	}

	return rdata;
}
/*******************************************
函数名称：readNbyte
功    能：从IIC总线读取N个字节的数据
参    数：inbuffer--读取后数据存放的首地址
          n--数据的个数
返回值  ：无
********************************************/
void readNbyte(uchar * inbuffer,uchar n)
{
	uchar i;
    
	for(i = 0;i < n;i++)
	{
		inbuffer[i] = read1byte();
		if(i < (n-1))	mack();
		else            mnack();
	}
	 
	stop();
}
