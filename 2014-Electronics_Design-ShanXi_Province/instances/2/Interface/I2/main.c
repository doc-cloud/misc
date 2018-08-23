/**************************************************************
程序功能：学习板作为通信中继，将从串口接收到的数据通过USB端口
          转发出去。
---------------------------------------------------------------
跳线设置:将跳线座J3上的短路帽插好。
---------------------------------------------------------------
通信格式：N.8.1, 1200
---------------------------------------------------------------
特别提醒：在这个实验中，串口的波特率设置的很低，就是为了给MCU足
          够的时间处理向USB中发送数据的事务！如果串口波特率设置
          过高那么在连续发送多个字节时，将发生丢失数据的错误，这
          是因为在MCU执行Write_EP()这个函数时是关闭了全局中断使
          能位的，所以不能记性响应接收中断请求，造成了接收寄存器
          的溢出。此外，在串口调试精灵中发送数据格式必须设置为
          16进制，否则按ASCII码发送，这样在WinDriver中看到的数据就
          和在串口调试精灵中看到的不一样了。
---------------------------------------------------------------
测试说明：将程序下载到MCU中，连接好串口线和USB通信电缆，打开串口
          调试精灵，正确设置通信格式，待USB连接成功以后通过串口
          调试精灵发送数据，从WinDriver中查看EP1接收到的数据。
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "UART0.h"
#include  "gdata.h"

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
    
    InitUART();                         //初始化UART0控制寄存器
    
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
           USB_FLAG.ep1_rxdone = 0;
           _EINT();
        } 
        else if(USB_FLAG.ep2_rxdone == 1) //端点2接收到数据
        {
           _DINT();
           USB_FLAG.ep2_rxdone = 0;
           _EINT();
        }
        
        if(Rindex != Windex)  //如果缓存中有待发数据
        {
           Write_EP(3,1,&RecBuf[Windex++]);
           Windex &= 0x3f;           
        }
    }
}
/*******************************************
函数名称：UART0_RXISR
功    能：UART0的接收中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector = UART0RX_VECTOR
__interrupt void UART0_RXISR(void)
{    
    RecBuf[Rindex++] = RXBUF0;   //将接收到的数据存放到缓存中
    Rindex &= 0x3f;
}


