/********************************************************
程序功能：从DS1302中读出时间数据在1602液晶模块上显示
---------------------------------------------------------
测试说明：用户可以更改"gdata.h"中wdata，bwdata，rwdata
          三个数组中的数据，但是请注意数据格式。
          根据程序中提示，设置断点观察数据。
*********************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "ds1302.h"
#include "cry1602.h"
#include "gdata.h"

void main(void)
{
    uchar disptemp[8]; 
    
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    BoardConfig(0xf8);          //关闭数码管、流水灯、电平转换
    
    disptemp[2]=0x3a;   // ":"对应的编码
    disptemp[5]=0x3a;   
    Reset_DS1302();
    
    
    
    /*****测试更改和读出时间*****/
    Set_DS1302(wdata);   
    Get_DS1302(rdata);
    
    _NOP();         //在此处设置断点，观察rdata是否与wdata一致
    
    /*****测试连续读写时间寄存器*****/
    BurstWrite1302(bwdata);
    BurstRead1302(brdata);
    
    _NOP();         //在此处设置断点，观察brdata是否与bwdata一致
    
    /*****测试连续读写RAM*****/
    BurstWriteRAM(rwdata);
    BurstReadRAM(rrdata);
    
    _NOP();         //在此处设置断点，观察rrdata是否与rwdata一致

    /*************************************************
    注释：用户在利用27~43行的程序完成测试以后，请设置好
    正确的当前时间然后将这端程序屏蔽掉，重新make以后写入
    CPU中，这样才能保证每次上电时CPU都从DS1302中读出正确
    的当前时间送到液晶中去显示，而不会发生每次都重新改写
    DS1302内部时间的问题。
    *************************************************/
    //初始化液晶
    LcdReset();
    DispNchar(1,0,14,tishi);
    //读取时间转换数值显示
    while(1)
    {
        BurstRead1302(rdata);
        disptemp[6] = shuzi[(rdata[0]&0xf0)>>4];
        disptemp[7] = shuzi[rdata[0]&0x0f];
        disptemp[3] = shuzi[(rdata[1]&0xf0)>>4];
        disptemp[4] = shuzi[rdata[1]&0x0f];
        disptemp[0] = shuzi[(rdata[2]&0xf0)>>4];
        disptemp[1] = shuzi[rdata[2]&0x0f];
        DispNchar(4,1,8,disptemp);
        delay(50000);
    }
}
