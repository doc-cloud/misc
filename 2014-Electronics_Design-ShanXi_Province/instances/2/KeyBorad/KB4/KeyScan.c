/* 
<功能>：当有外部中断时调用此函数，使用列扫描的方式获取键码，                                                                                                                                
        键码由2位数字组成：高位为行号,低位为列号 
*/	

#include <msp430.h>

#define SCAN_OUT P1OUT	 //4×4键盘扫描端口，低4位是行线，高4位是列线。
			 //采用逐列扫描的方法，无按键时，低4位输出1，高4位输出0。
			 //当有按键时，高4位输出扫描电位，低4位输入扫描结果。

#define SCAN_IN P1IN

const unsigned char uca_LineScan[4]={0xEF,0xDF,0xBF,0x7F};//列线扫描电压，分为第1，2，3，4根列线

/*******************************************
函数名称：ucKeyScan
功    能：扫描键盘得到键值
参    数：无
返回值  ：键值
********************************************/ 															//为低电平，其他为高电平。
unsigned char ucKeyScan(void)
{
    unsigned char ucTemp=0;		//扫描状态暂存。
    unsigned char ucRow=0,ucLine=0;	//行号，列号。

    P1IE=0;			 	//在键扫描处理时，关闭外部中断

    for(ucLine=0;ucLine<4;ucLine++)     //列扫描
    {
        SCAN_OUT = uca_LineScan[ucLine];//输出扫描电位。
        ucTemp = SCAN_IN&0x0F;		//输入扫描电位，并屏蔽高4位。
        if(ucTemp != 0x0F)		 
        {									  //判断该列是否有按键按下。
            switch(ucTemp)              //如果有，则判断行号。
            {
                case 0x0E: ucRow=10;break;
                case 0x0D: ucRow=20;break;
                case 0x0B: ucRow=30;break;
                case 0x07: ucRow=40;break;
                default:   ucRow=50;break;
            }
            break;
        }
    }
    while((SCAN_IN&0x0F) != 0x0f);      //等待按键放开
    SCAN_OUT = 0x0F;	  		//恢复P1口
    P1IE |= 0x0f;			//恢复按键中断
    return (ucRow+ucLine+1);		//返回按键编码。格式为2位数，高位为行号，低位为列号。
}
