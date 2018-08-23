/**************************************************************
程序功能：实现学习板通过USB端口与PC机通信，用户通过端点1(EP1)发
          送0x11将启动ADC转换并将采样结果通过EP1发送给PC机，
          用户通过EP1发送0x99停止ADC转换
---------------------------------------------------------------
跳线设置：将跳线座J3上的短路帽插好。
---------------------------------------------------------------
测试说明：将程序下载到MCU以后，从IAR软件中退出；用USB电缆连接学
          习板和PC机，按下USB电源开关按键，在连接建立成功以后。
          从WinDriver软件中通过EP1向学习板发送启动ADC转换的信号
          (0x11)观察接收到的数据结果，再发送停止ADC转换信号(0x99)
          就可以停止ADC转换
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "gdata.h"

/****************主函数****************/
void main(void)
{
    uchar i,ptr;
    
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
    
    P6SEL |= 0x01;                            // 使能ADC通道A0
    ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // 打开ADC，设置采样时间
    ADC12CTL1 = SHP+CONSEQ_2;                 // 使用采样定时器
    ADC12IE = 0x01;                           // 使能ADC中断
    
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
           if(Ep1Buf[0] == 0x11)     //如果收到启动转换信号
           {
                ADC12CTL0 |= ENC;                         // 使能转换
                ADC12CTL0 |= ADC12SC;                     // 开始转换     
           }
           else if(Ep1Buf[0] == 0x99)     //如果收到停止转换信号
           {
                ADC12CTL0 &= ~ENC;                         // 禁止转换
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
        else if(SendFlag == 1)  //通过端点1发送ADC采样数据
        {
           ptr = (Average&0xff00)>>8;
           Write_EP(3,1,&ptr);
           ptr = (Average&0x00ff);
           Write_EP(3,1,&ptr);
           SendFlag = 0;
        }
    }
}
/*******************************************
函数名称：ADC12ISR
功    能：ADC中断服务函数，在这里用多次平均的
          计算P6.0口的模拟电压数值
参    数：无       
返回值  ：无
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
  static uint index = 0;

  results[index++] = ADC12MEM0;               // Move results
  if(index == 32)
  {
        uchar i;
        unsigned long sum = 0;

        index = 0;
        for(i = 0; i < 32; i++)
        {
            sum += results[i];
        }
        sum >>= 5;                            //除以32
        Average = (uint)sum;
        SendFlag = 1;
  }
}

