#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include "delay.h" 
  	   		   
//EEPROM IO方向设置	 test
#define SDA_IN2()  {GPIOE->CRL&=0XFF0FFFFF;GPIOE->CRL|=0X00800000;}
#define SDA_OUT2() {GPIOE->CRL&=0XFF0FFFFF;GPIOE->CRL|=0X00300000;}

//EEPROM IO操作函数	 
#define IIC_SCL2    PEout(4) //SCL
#define IIC_SDA2    PEout(5) //SDA	 
#define READ_SDA2   PEin(5)  //输入SDA 

//EEPROM函数
void IIC_Init(void);  
u16 EEPROM_Read(u8 ReadAddr);  //在AT24C02指定地址读出一个16位的数据 				  地址参数： 0~127
void EEPROM_Write(u8 WriteAddr,u16 DataToWrite);//在AT24C02指定地址写入一个16位数据	  地址参数：0~127

#endif
