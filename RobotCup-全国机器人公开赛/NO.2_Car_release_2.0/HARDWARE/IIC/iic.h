#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include "delay.h" 
  	   		   
//EEPROM IO��������	 test
#define SDA_IN2()  {GPIOE->CRL&=0XFF0FFFFF;GPIOE->CRL|=0X00800000;}
#define SDA_OUT2() {GPIOE->CRL&=0XFF0FFFFF;GPIOE->CRL|=0X00300000;}

//EEPROM IO��������	 
#define IIC_SCL2    PEout(4) //SCL
#define IIC_SDA2    PEout(5) //SDA	 
#define READ_SDA2   PEin(5)  //����SDA 

//EEPROM����
void IIC_Init(void);  
u16 EEPROM_Read(u8 ReadAddr);  //��AT24C02ָ����ַ����һ��16λ������ 				  ��ַ������ 0~127
void EEPROM_Write(u8 WriteAddr,u16 DataToWrite);//��AT24C02ָ����ַд��һ��16λ����	  ��ַ������0~127

#endif
