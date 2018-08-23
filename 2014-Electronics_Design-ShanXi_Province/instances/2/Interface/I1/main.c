/**************************************************************
程序功能：学习板作为传输中继，将USB口接收到的数据通过串口转发
          出去
---------------------------------------------------------------
特殊说明：（1）PC机每次向学习板通过USB端口发送数据的第1个字节必
           须是本次要发送总字节的长度而且总字节长度不可以超过15。
          （2）PC机发送的数据格式是16进制，在串口调试精灵中也要
           接收显示部分也要设置为16进制显示。
---------------------------------------------------------------
跳线设置:将跳线座J3上的短路帽插好。
---------------------------------------------------------------
通信格式：N.8.1, 9600
---------------------------------------------------------------
测试说明：先用串口连接线将学习板的串口与PC机串口连接好，打开串
          口调试精灵，正确设置通信格式。将程序下载到MCU中，
          然后退出IAR，用USB电缆给学习板供电，待USB连接成功以后，
          打开WinDriver通过这个软件向学习发送正确格式的数据
         （第1个字节是数据长度，其后是数据），观察串口调试精灵
          接收到的数据。
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "uart0.h"
#include  "gdata.h"

/***************************主函数****************************/
void main(void)
{
    uchar i,j;
    
    WDTCTL = WDTPW + WDTHOLD;           //关闭看门狗
    BoardConfig(0xf8);                  //关闭数码管、流水灯和4245
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // 打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 //清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     // 等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             // 晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2;                  //主时钟选择高频晶振
    
    InitUART();                         //初始化端口
    PutString("UART is Ready......");    
    
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
           j = Ep1Buf[0];
           for(i = 1;i <= j;i++)
           {
                Send1Char(Ep1Buf[i]);
           }
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
