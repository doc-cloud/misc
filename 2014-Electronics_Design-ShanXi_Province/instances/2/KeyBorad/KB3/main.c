/**************************************************************
程序功能:实现学习板通过USB端口与PC机通信，用户按键K1~K4的键值
         可以通过USB发送到PC机上显示
---------------------------------------------------------------
跳线设置:将跳线座J3上的短路帽插好。
---------------------------------------------------------------
测试说明：将程序下载到MCU以后，从IAR软件中退出；用USB电缆连接学
          习板和PC机，按下USB电源开关按键，在连接建立成功以后。
          从WinDriver软件中监听端点1，接收来自学习板的数据。
          按动按键K1~K8和K13~K16，观察屏幕显示的键值。
----------------------------------------------------------------
特别提示：因为P1.5在USB电路中是作为外部中断输入端口使用的，因此
          在4X4键盘电路中K9~K12这四个按键将无法使用，只有其余12
          个按键有效。
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "Keypad.h"
#include  "gdata.h"

/****************主函数****************/
void main(void)
{
    uint i;
    
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
    
    P6DIR |= BIT7;                      //控制蜂鸣器引脚设置为输出
    P6OUT |= BIT7;
  
    Init_Keypad();                      //初始化键盘端口
    
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
        
        Key_Event();                     //扫描键盘
    
        if(key_Flag == 1)
        {
            key_Flag = 0;  
            
            Write_EP(3,1,&key_val);     //将键值发送给PC机
            
            P6OUT = 0;                      //蜂鸣器响一声
            for(i = 8000; i > 0; i--);
            P6OUT |= BIT7;            
        }
    }
}
