/**************************************************************
程序功能：实现学习板通过USB端口与PC机通信，用户通过端点1(EP1)发
          送控制DAC输出的数据，可以用这个电压来驱动LED发光，也可
          以直接用电压表测量DAC输出电压
---------------------------------------------------------------
跳线设置：（1）将跳线座J3上的短路帽插好。
          （2）将跳线座J1的1脚和2脚（靠上面的两个）短接
---------------------------------------------------------------
测试说明：将程序下载到MCU以后，从IAR软件中退出；用USB电缆连接学
          习板和PC机，按下USB电源开关按键，在连接建立成功以后。
          从WinDriver软件中通过EP1向学习板发送控制DAC输出模拟电
          压的数据，观察LED亮度变化或者用电压表测量DAC输出端电压。
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "IIC.h"
#include  "gdata.h"

uchar Write_DAC(uchar wdata);
/****************主函数****************/
void main(void)
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //关闭看门狗
    BoardConfig(0xb8);                  //关闭数码管、流水灯和4245
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // 打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     // 等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             // 晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2;                  //主时钟选择高频晶振
    
    Set_IO();                           //设置DAC对应的IO
    
    D12_init();                         //初始化D12
    USB_reconnect();                    //进行USB连接

    while(1)
    {
        
        if((!(P1IN&BIT5))&&(!(P1IFG&BIT5)))     //如果P1.5端口丢失了中断
        {
            uint int_sta;
          
            _DINT();
            
            USB_FLAG.in_isr = 1;
            int_sta=Read_IntR();	        //读取PDIUSBD12中断寄存器值
          
            if(int_sta!=0) 
            {
                if(int_sta&INT_BUSRESET)
                        USB_FLAG.bus_reset=1;	//USB总线复位标志	
                if(int_sta&INT_ENDP0IN)
                        Ep0_txdone();		//控制端点发送数据处理
                if(int_sta&INT_ENDP0OUT)
                        Ep0_rxdone();		//控制端点接收数据处理
                if(int_sta&INT_ENDP1IN)
                        Ep1_txdone();		//端点 1发送数据处理
                if(int_sta&INT_ENDP1OUT)
                        Ep1_rxdone();		//端点 1接收数据处理
                if(int_sta&INT_ENDP2IN)
                        Ep2_txdone();		//端点 2发送数据处理
                if(int_sta&INT_ENDP2OUT)
                        Ep2_rxdone();		//端点 2接收数据处理
            }
            USB_FLAG.in_isr = 0;
            
            _EINT();
        }
      
        if (USB_FLAG.setup_packet)   //Setup包处理
        {		
            _DINT();
            USB_FLAG.setup_packet = 0;
            Control_handler();	     //调用请求处理子程序
            _EINT();
        }
        
        if(USB_FLAG.ep1_rxdone == 1) //端点1接收到数据
        {
           _DINT();
           //将1个字节的控制数据写入DAC
           Write_DAC(Ep1Buf[0]);           
           USB_FLAG.ep1_rxdone = 0;
           _EINT();
        } 
        else if(USB_FLAG.ep2_rxdone == 1) //端点2接收到数据
        {
           _DINT();
           USB_FLAG.ep2_rxdone = 0;
           _EINT();
        }
    }
}
/*******************************************
函数名称：Write_DAC
功    能：向DAC中写入输出电压数据
参    数：无
返回值  ：写入结果：1--成功，0--失败
********************************************/
uchar Write_DAC(uchar wdata)
{
    start();
    write1byte(0x98);   //DAC的设备地址
    if(check())   write1byte(wdata >> 4);   //写控制模式和电压数据的高四位
    else          return 0;
    if(check())   write1byte(wdata << 4);  //写电压数据的低四位
    else          return 0;
    if(check())	  stop();
    else          return 0;
    return 1;    
}


