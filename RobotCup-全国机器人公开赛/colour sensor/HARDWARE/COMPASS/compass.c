#include "compass.h" 
//#include "lcd12864.h"

#define	WriteDeviceAddress   0xE0	  //定义器件在IIC总线中的地址
#define	ReadDviceAddress     0xE1     //器件在IIC总线中地址+1

void AT24C04_Start(void);
void AT24C04_Stop(void);
void AT24C04_SendACK(u8 ack);
u8  AT24C04_RecvACK(void);
void AT24C04_SendByte(u8 dat);
u8 AT24C04_RecvByte(void);
void AT24C04_ReadPage(void);
void AT24C04_WritePage(void);
u16 read_cmp(void);


//初始化IIC
void Compass_Init(void)
{	
	//指南针			     							 
	GPIOE->CRL&=0XF0FFFFFF;//PE6 推挽输出
	GPIOE->CRL|=0X03000000;	   
	GPIOE->ODR|=1<<6;     //PE6 输出高

	GPIOC->CRH&=0XFF0FFFFF;//PC13 推挽输出
	GPIOC->CRH|=0X00300000;	   
	GPIOC->ODR|=1<<13;     //PC13 输出高  
}

/*
**函数功能：读取指南针传感器测量角度值
**返回值  ：temp---返回角度值
*/
u16 read_cmp(void)
{   
	u16 temp = 0,temp1;

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0x31);                   //发送一次测量角度
    AT24C04_Stop();                           //停止信号

	delay_ms(100);

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
	AT24C04_SendByte(0x01);                   //发送存储单元地址，从0开始	
	delay_us(10);
	AT24C04_Start();						   //起始信号
	delay_us(10);                
    AT24C04_SendByte(WriteDeviceAddress+1);   //发送设备地址+读信号
	delay_us(8);
	temp = AT24C04_RecvByte();
	AT24C04_SendACK(0); 
	temp = temp << 8;
	delay_us(10);	
	temp1 = AT24C04_RecvByte();
	delay_us(10);
	temp = temp | temp1;	
    AT24C04_SendACK(1);                //最后一个数据需要回NOACK    
	delay_us(10);
	AT24C04_Stop();					  //停止信号                       
	return temp;
}  

/**************************************
起始信号
**************************************/
void AT24C04_Start()
{
	SDA_OUT();
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    delay_us(8);                 //延时
    SDA = 0;                    //产生下降沿
    delay_us(8);               //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void AT24C04_Stop()
{
	SDA_OUT();
	SDA = 0;
	SCL = 1; 
	delay_us(8);                    //拉低数据线                   //拉高时钟线                //延时
    SDA = 1;                    //产生上升沿
    delay_us(8);                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void AT24C04_SendACK(u8 ack)
{
	SDA_OUT();
	SCL = 0;                    //拉低时钟线
    delay_us(8);                 //延时
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    delay_us(8);                  //延时
    SCL = 0;                    //拉低时钟线
    delay_us(8);                 //延时
}

/**************************************
接收应答信号
**************************************/
u8 AT24C04_RecvACK()
{
	u8 ucErrTime=0;

 	SDA_IN();      //SDA设置为输入  
	SDA=1;delay_us(4);	   
	SCL=1;delay_us(4);
		 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			AT24C04_Stop();
			return 1;
		}
	}
	SCL=0;//时钟输出0 	   
	return 0;  
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void AT24C04_SendByte(u8 dat)
{
	u8 t; 
	SDA_OUT(); 	    
    SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        SDA=(dat&0x80)>>7;
        dat<<=1; 	  
		delay_us(5);   //对TEA5767这三个延时都是必须的
		SCL=1;
		delay_us(5); 
		SCL=0;	
		delay_us(5);
    }	
    AT24C04_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/	

u8 AT24C04_RecvByte()
{
	int i = 0;
	u8 byte = 0;
	SDA_IN();//SDA设置为输入
	for(i = 0;i < 8;i++)
	{
		SCL = 0;
		SDA = 1;
		delay_us(20);
		SCL = 1;
		delay_us(20);
		byte <<= 1;
		if(1 == READ_SDA)		
		{
			byte |= 0x01;
		}
		delay_us(20);
	}
	return byte;
}

//*********************************************************

/*
**函数功能：校准指南针传感器
*/
void cal_on(void)
{                                             
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC0);                   //发送校准命令
    AT24C04_Stop();                           //发送停止信号
}

/*
**函数功能：关闭指南针的校准
*/
void cal_off(void)                            
{
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC1);                   //发送停止校准命令
    AT24C04_Stop();                           //发送停止信号
}

/*
**函数功能：恢复出厂设置
*/
void recovery_factory(void)                   
{
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xA0);                   //发送数据0xA0
    AT24C04_Stop();                           //发送停止信号

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xAA);                   //发送数据0xAA
    AT24C04_Stop();                           //发送停止信号

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xA5);                   //发送数据0xA5
    AT24C04_Stop();                           //发送停止信号

	AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC5);                   //发送0xC5,恢复出厂命令
    AT24C04_Stop();                           //发送停止信号

}

/*
**函数功能：修改指南针磁偏角值
*/
void CMP_OFFS(void)                        
{
    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x03);                 //0表示命令 
    AT24C04_SendByte(0x00);                 //磁偏角高8位，写入0
    AT24C04_Stop();                         //发送停止信号

    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x04);                 //0表示命令 
    AT24C04_SendByte(0x73);                 //磁偏角低8位，写入100（实际是10.0度）
    AT24C04_Stop();                         //发送停止信号
}






