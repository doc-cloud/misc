/**************************************************************
程序功能：学习板通过USB端口将DS18B20转换结果的高3位数字发给PC机
---------------------------------------------------------------
跳线设置：将跳线座J3上的短路帽插好。
---------------------------------------------------------------
测试说明：将程序下载到MCU以后，从IAR软件中退出；用USB电缆连接学
          习板和PC机，按下USB电源开关按键，在连接建立成功以后。
          打开WinDriver软件，首先向EP1中写入数值0x88，然后再接收
          来自EP1的数据，就可以看到3位温度数值了。
***************************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "USBfunctions.h"
#include  "DS18B20.h"
#include  "gdata.h"

void Disp_Numb(uint temper);
/****************主函数****************/
void main(void)
{
    uchar i;
    uint tmp;
    uchar ConvertFlag=0;
    
    WDTCTL = WDTPW + WDTHOLD;           // 关闭看门狗
    BoardConfig(0xb8);                  // 关闭数码管、流水灯和4245
    
    /*------选择系统主时钟为8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 // 打开XT2高频晶体振荡器
    do
    {
        IFG1 &= ~OFIFG;                 // 清除晶振失败标志
        for (i = 0xFF; i > 0; i--);     // 等待8MHz晶体起振
    }
    while ((IFG1 & OFIFG));             // 晶振失效标志仍然存在？
    BCSCTL2 |= SELM_2 + SELS;           // MCLK和SMCLK选择高频晶振
    
    //计数时钟选择SMLK=8MHz，1/8分频后为1MHz
    TACTL |= TASSEL_2 + ID_3; 
    
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
           if(Ep1Buf[0] == 0x88)        //如果收到转换命令
           {
               ConvertFlag = 1; 
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
        if(ConvertFlag)
        {
            for(i = 0xff; i > 0; i--)  //延时一会
            {
                for(tmp = 0;tmp < 250; tmp++)
                    _NOP();                
            }
            
            tmp = Do1Convert();           //控制DS18B20发生一次转换
            Disp_Numb(tmp);
            //这里实际上只发送了转换后6位数值中的高三位,如果将参数表中
            //第二个3改成6，那么就是发送全部的6位温度数字了
            Write_EP(3,3,dN);             //将转换结果通过USB发送给PC机
        }

    }
}
/*******************************************
函数名称：Disp_Numb
功    能：将从DS18B20读取的11bit温度数据转换
          成10进制格式的温度数字
参    数：temper--11bit温度数据
返回值  ：无
********************************************/
void Disp_Numb(uint temper)
{
    uchar i;
    
    for(i = 0;i < 6;i++) dN[i] = 0; //初始化显示变量

    //数值转换
    if(temper & BIT0) 
    {
        dN[0] = 5;
        dN[1] = 2;
        dN[2] = 6;
    }
    if(temper&BIT1)     
    {
        dN[1] += 5;
        dN[2] += 2;
        dN[3] += 1;
    }
    if(temper & BIT2)     
    {
        dN[2] += 5;
        dN[3] += 2;
        if(dN[2] >= 10)
        {
            dN[2] -= 10;
            dN[3] += 1;
        }
    }
    if(temper&BIT3)     
    {
        dN[3] += 5;
    }
    if(temper & BIT4)
    {
        dN[4] += 1;
    }
    if(temper & BIT5)     
    {
        dN[4] += 2;
    }
    if(temper & BIT6)
    {
        dN[4] += 4;
    }
    if(temper & BIT7)     
    {
        dN[4] += 8;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT8)
    {
        dN[4] += 6;
        dN[5] += 1;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BIT9)
    {
        dN[4] += 2;
        dN[5] += 3;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
    }
    if(temper & BITA)
    {
        dN[4] += 4;
        dN[5] += 6;
        if(dN[4] >= 10)
        {
            dN[4] -= 10;
            dN[5] += 1;
        }
        if(dN[5] >= 10)
        {
            dN[5] -= 10;
        }
    }
    //交换位置
    i = dN[5];
    dN[5] = dN[0];
    dN[0] = i;
    
    i = dN[4];
    dN[4] = dN[1];
    dN[1] = i;
    
    i = dN[3];
    dN[3] = dN[2];
    dN[2] = i;
}
