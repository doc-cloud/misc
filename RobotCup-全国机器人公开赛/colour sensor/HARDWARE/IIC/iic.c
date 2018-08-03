#include "iic.h" 

void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);

//初始化IIC
void IIC_Init(void)
{	
	//EEPROM
	GPIOE->CRL&=0XFF00FFFF;//PE4/5 推挽输出
	GPIOE->CRL|=0X00330000;	   
	GPIOE->ODR|=1<<4;     //PE4/5 输出高
	GPIOE->ODR|=1<<5;
}
//产生IIC起始信号
void IIC_Start()
{
	SDA_OUT2();     //sda线输出
	IIC_SDA2=1;	  	  
	IIC_SCL2=1;
	delay_us(4);
 	IIC_SDA2=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL2=0;//钳住I2C总线，准备发送或接收数据 	
}	  
//产生IIC停止信号
void IIC_Stop()
{
	SDA_OUT2();//sda线输出
	IIC_SCL2=0;
	IIC_SDA2=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL2=1; 
	IIC_SDA2=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack()
{
	u8 ucErrTime=0;

	SDA_IN2();      //SDA设置为输入  
	IIC_SDA2=1;delay_us(1);	   
	IIC_SCL2=1;delay_us(1);	 
	while(READ_SDA2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL2=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack()
{
	IIC_SCL2=0;
	SDA_OUT2();
	IIC_SDA2=0;
	delay_us(2);
	IIC_SCL2=1;
	delay_us(2);
	IIC_SCL2=0;	
}
//不产生ACK应答		    
void IIC_NAck()
{	
	IIC_SCL2=0;
	SDA_OUT2();
	IIC_SDA2=1;
	delay_us(2);
	IIC_SCL2=1;
	delay_us(2);
	IIC_SCL2=0;
	
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t; 
	SDA_OUT2(); 	    
    IIC_SCL2=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA2=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL2=1;
		delay_us(2); 
		IIC_SCL2=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

	SDA_IN2();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL2=0; 
        delay_us(2);
		IIC_SCL2=1;
        receive<<=1;
        if(READ_SDA2)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK  	
    return receive;
}

//EEPROM函数

//在AT24C02指定地址读出一个16位的数据  0~127
u16 EEPROM_Read(u8 ReadAddr)
{				  
	u16 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0);   //发送器件地址0XA0,写数据 	   
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr*2);   //发送地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件
	
	IIC_Start();  
	IIC_Send_Byte(0XA0);   //发送器件地址0XA0,写数据 	   
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr*2+1);   //发送地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();
	temp = temp << 8;	 
    temp = temp | IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24C02指定地址写入一个16位数据
void EEPROM_Write(u8 WriteAddr,u16 DataToWrite)
{
	u8 temp;				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0);   //发送器件地址0XA0,写数据 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr*2);   //发送地址
	IIC_Wait_Ack(); 
	temp = (DataToWrite&0xff00) >> 8;	 										  		   
	IIC_Send_Byte(temp);     //发送低字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	
	
	IIC_Start();  
	IIC_Send_Byte(0XA0);   //发送器件地址0XA0,写数据 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr*2+1);   //发送地址
	IIC_Wait_Ack(); 
	temp = DataToWrite&0x00ff;										  		   
	IIC_Send_Byte(temp);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	  
}
