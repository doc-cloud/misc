/**************************************************************
程序功能：实现学习板通过USB端口与PC机通信，PC机向学习板发送字符
    	 并在1602液晶上显示
---------------------------------------------------------------
特殊说明：（1）PC机向学习板发送数据的第1个字节必须是本次要发送
          总字节的长度而且总字节长度不可以超过15
          （2）PC机发送的数据应该是可显示字符对应ASCII码值
          （第1个字节除外），否则1602液晶无法显示。
---------------------------------------------------------------
跳线设置:将跳线座J3上的短路帽插好。
---------------------------------------------------------------
测试说明：将程序下载到MCU以后，从IAR软件中退出；用USB电缆连接学
          习板和PC机，按下USB电源开关按键，在连接建立成功以后。
          从WinDriver软件中用端点1向学习板发送符合上述要求的数据，
          并观察1602液晶显示。
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "Cry1602.h"
#include  "gdata.h"

/***************************主函数****************************/
void main(void)
{
    uchar i;
    
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
    
    LcdReset();                         //复位液晶
    LocateXY(0,0);                      //确定显示的起始位置
    LcdWriteCommand(0x0f, 1);           //打开游标
    
    
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
           LcdWriteCommand(0x01, 1);                        //显示清屏
           DispNchar(0,0,Ep1Buf[0],&Ep1Buf[1]);             //在液晶上显示接收到的字符
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
