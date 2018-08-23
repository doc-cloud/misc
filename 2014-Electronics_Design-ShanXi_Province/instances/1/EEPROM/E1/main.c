/*************************************************************
程序功能：对EEPROM进行读写测试
--------------------------------------------------------------
说    明：AT24C02是256Byte存储容量的EEPROM，内部
          寻址时，要用32个页地址，每页有8Byte
--------------------------------------------------------------
测试说明：根据提示设置断点，观察相应数据
**************************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "EEPROM.h"


/****************主函数****************/
void main(void)
{ 
    uchar wbuffer[] = {1,2,3,4,5,6,7,8};
    uchar rbuffer[8];
    uchar flag = 0;
        
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    BoardConfig(0xb8);          //关闭数码管、流水灯和电平转换
    P1DIR |= 0x0c;              //设置相应端口为输出状态
    
    if(Write_1Byte(0x11,0x00))  
        flag = 1;
    
    _NOP();     //在此设置断点观察flag
    
    if(Read_1Byte_Randomaddress(0x00) == 0x11)
        flag = 2;
    
	_NOP();     //在此设置断点观察flag
    
    if(Write_NByte(wbuffer,8,0x08)) //从第1页的第0个字节起连续写8个数据
        flag = 3;
    
    _NOP();     //在此设置断点观察flag
    
    if(Read_NByte_Randomaddress(rbuffer,8,0x08))//从第1页的第0个字节起连续读8个数据
        flag = 4;
    
    _NOP();     //在此设置断点观察rbuffer的值
    
    flag = flag-1;  //此句是为了消除编译警告，无实际意义
    
    while(1);
}



