#include <msp430x14x.h>
#include "USBvariables.h"
#include "USBfunctions.h"
typedef unsigned char uchar;
typedef unsigned int  uint;

//外部变量声明
extern unsigned char KeyChar;            //按键输入数值
extern unsigned char SendFlag;           //是否发送数据标志

void (*StandardDeviceRequest[])(void)=
{
	Get_status,
	Clr_feature,
	Reserved,
	Set_feature,
	Reserved,
	Set_addr,
	Get_descriptor,
	Reserved,
	Get_config,
	Set_config,
	Get_interface,
	Set_interface,
	Reserved,
	Reserved,
	Reserved,
	Reserved
};
/*******************************************
函数名称: Delayus
功    能: 延时指定微秒（8M晶振）
参    数: US--延时的微秒数(大约，不是很精确)
返回值  : 无
********************************************/
void Delayus(uint US)		  
{
    uint i;
    
    US=US*5/4;		 // 5/4是在8MHz晶振下，通过软件仿真反复实验得到的数值
    for( i=0;i<US;i++); 
}
/*******************************************
函数名称: Delayms
功    能: 延时指定毫秒（8M晶振）
参    数: MS--延时的毫秒数
返回值  : 无
********************************************/
void Delayms(uint MS)		  
{
     uint i,j;
     
     for(i=0;i<MS;i++)
     for(j=0;j<1141;j++);	// 1141是在8MHz晶振下，通过软件仿真反复实验得到的数值
}
/*******************************************
函数名称: D12_init
功    能: 初始化D12接口（包括数据接口和控制接口）
参    数: 无
返回值  : 无
********************************************/
void D12_init(void)
{
     USBDAT_DDR|=0xFF;				    //数据端口设置为输出
     USBCTL_DDR|=BIT(WR_N)|BIT(RD_N)|BIT(C_D)|BIT(D12_CS);//控制引脚设置为输出
     USBINT_DDR&=~BIT(D12_INT);	        //中断引脚设置为输入						  //中断引脚设置为输入				  
     USBINT_IES|=BIT(D12_INT);          //选择下降沿中断
     USBINT_SEL&=~BIT(D12_INT);         //选择IO端口
     USBINT_IE|=BIT(D12_INT);           //使能端口中断
     USBCTL_PORT|=BIT(WR_N)|BIT(RD_N)|BIT(D12_CS);		  //控制引脚无效
     
     EN_GINT();                         //使能全局中断    
     USBCTL_PORT&=~BIT(D12_CS);        //给出片选信号
}
/*******************************************
函数名称: OutB
功    能: 向D12写入一个字节数据或者命令
参    数: cmd--命令标识（为CMD是命令，为DAT是数据）
	  	  dat--要写入的字节数据
返回值  : 无
********************************************/
void OutB(uchar cmd,uchar dat)
{
     if(cmd==CMD)
     {
          USBCTL_PORT|=BIT(C_D); 
          Delayus(5);
          USBCTL_PORT&=~BIT(WR_N);
          Delayus(5);
          USBDAT_PORT=dat;  
          Delayus(5);
          USBCTL_PORT|=BIT(WR_N);
     }
     else
     {
          USBCTL_PORT&=~BIT(C_D);
          Delayus(1);
          USBCTL_PORT&=~BIT(WR_N);
          Delayus(1);
          USBDAT_PORT=dat;  
          Delayus(1);
          USBCTL_PORT|=BIT(WR_N);
     }
}
/*******************************************
函数名称: InB
功    能: 从D12读出一个字节数据
参    数: 无
返回值  : dat--读出的字节数据
********************************************/
uchar InB(void)
{ 
      uchar dat;
      
      USBDAT_DDR=0x00;
      USBDAT_PORT=0xFF;
      USBCTL_PORT&=~BIT(C_D);
      Delayus(1);
      USBCTL_PORT&=~BIT(RD_N);
      Delayus(1);
      dat=USBDAT_PIN;
      Delayus(1);
      USBCTL_PORT|=BIT(RD_N);
      USBDAT_DDR=0xFF;
      return dat;
}
/*******************************************
函数名称: Set_addren
功    能: 设置地址/使能
参    数: addr--设置的地址
	  enable--使能标志（为1使能，为0禁止）
返回值  : 无
********************************************/
void Set_addren(uchar addr, uchar enable)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD, 0xD0);	//输出设置地址/使能指令
	Delayus(1);
	if(enable)
	{
		addr|=0x80;		//bit7置1,使能
	}
	Delayus(1);
	OutB(DAT,addr);		//输出设置值

	if(USB_FLAG.in_isr == 0)
		EN_GINT();
}
/*******************************************
函数名称: Set_EPen
功    能: 设置端点使能
参    数: enable--使能标志（为1使能，为0禁止）
返回值  : 无
********************************************/
void Set_EPen(uchar enable)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0xD8);	        //输出设置端点使能指令
	Delayus(1);
	if(enable)
		OutB(DAT,1);		//设置端点允许
	else
		OutB(DAT,0);		//设置端点禁止

	if(USB_FLAG.in_isr == 0)
		EN_GINT();
}
/*******************************************
函数名称: Set_mode
功    能: 设置模式
参    数: config--配置字节信息
	  	  clkdiv--分频因子
返回值  : 无
********************************************/
void Set_mode(uchar config,uchar clkdiv)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0xF3);		//输出设置模式指令
	Delayus(1);
	OutB(DAT,config);	//输出配置字节信息
	OutB(DAT,clkdiv);	//输出时钟分频因数字节

	if(USB_FLAG.in_isr == 0)
		EN_GINT();	
}
/*******************************************
函数名称: Set_DMA
功    能: 设置DMA工作方式设置
参    数: bMode--设置值
返回值  : 无
********************************************/
void Set_DMA(uchar bMode)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD, 0xFB);	//设置DMA工作方命令
	Delayus(1);
	OutB(DAT, bMode);	//输出设置值

	if(USB_FLAG.in_isr == 0)
		EN_GINT();			
}

/*******************************************
函数名称: Read_IntR
功    能: 读取中断寄存器值
参    数: 无
返回值  : intreg--16位中断寄存器值
********************************************/
uint Read_IntR(void)
{
	uchar regl;
	uint  intreg;

	OutB(CMD,0xF4);	        //读取中断寄存器命令
	Delayus(5);
	regl=InB( );			//读取低8位字节
	intreg=InB( );			//读取高8位字节

	intreg<<=8;
	intreg+=regl;			//组合为16位

	return intreg;
}
/*******************************************
函数名称: Sel_EP
功    能: 端点选择,将内部指针初始化到选择的缓冲区起始位置
参    数: endp--端点索引号,取值0 ~ 5
返回值  : byte--一个字节的返回数据
********************************************/
uchar Sel_EP(uchar endp)
{
	uchar byte;
    
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,endp);	//端点选择
	Delayus(1);
	byte=InB( );	//读出一个字节

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return byte;
}
/*******************************************
函数名称: Sel_EP
功    能: 读取端点状态
参    数: endp--端点索引号,取值0 ~ 5
返回值  : status--端点状态
********************************************/
uchar Read_EPsta(uchar endp)//-----------------
{
	uchar status;

	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0x80+endp);	//读取端点状态命令
	status=InB( );		    //读取端点状态

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return status;
}
/*******************************************
函数名称: Read_LttransSta
功    能: 读取最后处理状态寄存器
参    数: endp--端点索引号,取值0 ~ 5
返回值  : status--端点最后处理的状态
********************************************/
uchar Read_LttransSta(uchar endp)
{
 	uchar status;
    
	OutB(CMD,0x40+endp);	//输出读取最后处理状态寄存器命令
	Delayus(5);
	status=InB( );
	return status;		    //读取状态
}
/*******************************************
函数名称: Set_EPsta
功    能: 设置端点状态
参    数: endp--端点索引号,取值0 ~ 5
	  	  stall--设置状态值
返回值  : 无
********************************************/
void Set_EPsta(uchar endp,uchar stall)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0x40+endp);	//发送设置端点状态命令
	Delayus(1);
	OutB(CMD,stall);	    //设置端点状态

	if(USB_FLAG.in_isr == 0)
		EN_GINT();
}
/*******************************************
函数名称: Set_Sresume
功    能: 设置发送恢复
参    数: 无
返回值  : 无
********************************************/
void Set_Sresume(void)
{
	OutB(CMD,0xF6);		//设置发送恢复
}
/*******************************************
函数名称: Read_EP
功    能: 读取端点数据
参    数: endp--端点索引号,取值 0 ~ 5 
	  	  len--要读取的数据长度
		  buf--接收数据指针					   
返回值  : num--实际读到的字节数
********************************************/
uchar Read_EP(uchar endp,uchar len,uchar * buf)
{
	uchar i,num;

	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,endp);				//发送选择端点命令
	Delayus(1);
	if((InB( )&FULLEMPTY)==0)   //如果缓冲区为空 
	{	
		if(USB_FLAG.in_isr == 0)
		EN_GINT();
		return 0;			    //则返回读到0字节
	}

	OutB(CMD,0xF0);			    //发送读缓冲区命令
	Delayus(1);
	num=InB( );				    //读取保留字节
	num=InB( );				    //读取数据字节的数目/长度

	if(num>len)				    //如果大于要求读的字节数目
	{
		num=len;			    //则只读取要求的字节长度
	}
	for(i=0; i<num; i++)
		*(buf+i)=InB( );		//读取要求的字节数目/长度

	OutB(CMD,0xF2);				//清缓冲区,新的信息包才可以重新被接受

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return num;				    //返回读到的字节数
}
/*******************************************
函数名称: Write_EP
功    能: 将数据写入端点
参    数: endp--端点索引号,取值 0 ~ 5 
	  	  len--要写入的数据长度
		  buf--发送数据指针					   
返回值  : num--实际写入的字节数
********************************************/
uchar Write_EP(uchar endp,uchar len,uchar * buf)
{
	uchar i;

	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,endp);			//发送选择端点命令
	Delayus(1);
	i=InB( );			    //可选地读取一个字节

	OutB(CMD,0xF0);			//发送写缓冲区命令	
	Delayus(1);
	OutB(DAT,0);			//写入一个保留字节
	Delayus(1);
	OutB(DAT,len);			//写入即将写入的字节数目
	Delayus(1);

	for(i=0; i<len; i++)
	{
		OutB(DAT,*(buf+i));	//写入指定的字节
	}
	Delayus(1);
	OutB(CMD,0xFA);			//使缓冲区有效

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return len;				//返回写入的字节数
}
/*******************************************
函数名称: Ack_EP
功    能: 应答Setup
参    数: endp--端点索引号,取值 0 ~ 5 	   
返回值  : 无
********************************************/
void Ack_EP(uchar endp)
{
	OutB(CMD,endp);			//选择端点
	Delayus(1);
	OutB(CMD,0xF1);			//应答Setup指令
	Delayus(1);
	if(endp==0)	
	{	
		OutB(CMD,0xF2);		//清空该端点缓冲区
	}
}
/*******************************************
函数名称: Clear_buf
功    能: 清指定端点的缓冲区(包括双缓冲区)
参    数: endp--端点索引号,取值 0 ~ 5 	   
返回值  : 无
********************************************/
void Clear_buf(uchar endp)
{	
   	OutB(CMD,endp);			//选择端点
	Delayus(1);
	OutB(CMD,0xF2);			//清空第1个缓冲区	
	
	if (endp>=4)
	{
   		OutB(CMD,endp);		//选择端点
		Delayus(1);
		OutB(CMD,0xF2);		//清空第2个缓冲区	
	}
}
/*******************************************
函数名称: Stall_ep0
功    能: 使控制端点处于停止状态
参    数: 无   
返回值  : 无
********************************************/
void Stall_ep0(void)
{
	Set_EPsta(0,1);
	Set_EPsta(1,1);
}
/*******************************************
函数名称: S_trans
功    能: 通过端点索引 1 发送数据(DATA 类型)
参    数: buf--发送数据指针
		  len--发送数据长度   
返回值  : 无
********************************************/
void S_trans(uchar * buf, uchar len)
{
	if(len<=EP0_PACKET_SIZE) //长度小于EP0最大信息包大小才允许发送
	{			
		Write_EP(1,len,buf);
	}
}
/*******************************************
函数名称: Code_trans
功    能: 通过端点索引 1 发送数据(CODE类型)
参    数: buf--发送数据指针
		  len--发送数据长度   
返回值  : 无
********************************************/
void Code_trans(uchar *pRomData, uint len)
{
	ControlData.wCount = 0;								//传输字节数计数器清0
	if(ControlData.wLength > len)
		ControlData.wLength = len;						//传输数据总字节数不得超过len

	ControlData.pData = pRomData;						//传输数据指针指向pRomData
	if( ControlData.wLength >= EP0_PACKET_SIZE)         //传输数据总字节数大于端点0最大信息包大小
	{		
		Write_EP(1, EP0_PACKET_SIZE, ControlData.pData);//发送端点0最大信息包大小个字节
		ControlData.wCount += EP0_PACKET_SIZE;			//统计已发送字节数

		UEN_GINT();
		USB_FLAG.control_state = USB_TRANSMIT;	        //标志数据发送状态			
		EN_GINT();
	}
	else 
	{
		Write_EP(1, ControlData.wLength, pRomData);	    //写入传输数据总字节数
		ControlData.wCount += ControlData.wLength;	    //统计已发送字节数
		UEN_GINT();
		USB_FLAG.control_state = USB_IDLE;		        //标志空闲状态
		EN_GINT();
	}
}
/*******************************************
函数名称: USB_INT1
功    能: D12中断服务函数
参    数: 无   
返回值  : 无
********************************************/
#pragma vector=PORT1_VECTOR 
__interrupt void USB_INT1(void)
{
    uint int_sta;
   
    if((USBINT_IFG & BIT(D12_INT))==BIT(D12_INT))
    {
            USBINT_IFG&=~BIT(D12_INT);  //清除中断标志
    
            USB_FLAG.in_isr = 1;
            int_sta=Read_IntR();	    //读取PDIUSBD12中断寄存器值
          
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
    }
}
/*******************************************
函数名称: Ep0_rxdone
功    能: 通过端点索引 0 接收数据
参    数: 无   
返回值  : 无
********************************************/
void Ep0_rxdone(void)
{
	uchar ep_last,i;
	ep_last=Read_LttransSta(0);     //清除中断寄存器状态,取得最后处理状态
	if (ep_last&SETUPPACKET) 
	{				                //如果收到了建立包(Setup包)
		ControlData.wLength=0;	    //传输字节总数清0
		ControlData.wCount=0;	    //传输字节计数器清0
		if(Read_EP(0,sizeof(ControlData.DeviceRequest),(uchar * )(&(ControlData.DeviceRequest)))!= sizeof(DEVICE_REQUEST))//从端点0读8个字节失败 
		{												 		 
			Set_EPsta(0,1);			//停止控制端点0
			Set_EPsta(1,1);			//停止控制端点1
			USB_FLAG.control_state = USB_IDLE;	 //设置为等待状态
			return;
		}		
		/********  接收建立包成功 **********/
		Ack_EP(0);						 //对控制端点0进行建立包应答
		Ack_EP(1);						 //对控制端点1进行建立包应答
		ControlData.wLength=ControlData.DeviceRequest.wLength; 	 //取出要传输数据的总字节数
		ControlData.wCount = 0;
        
		//如果控制传输是控制读取
		if(ControlData.DeviceRequest.bmRequestType&(uchar)USB_ENDPOINT_DIRECTION_MASK) 
		{

			 USB_FLAG.setup_packet=1;		        //通知control_handler()处理Setup包
			 USB_FLAG.control_state=USB_TRANSMIT;	//设置为发送状态
		}
		else    //如果控制传输是控制写入
		{						
			  if(ControlData.DeviceRequest.wLength==0) 
			  {
				  USB_FLAG.setup_packet=1;		    //通知control_handler()处理Setup包				  
				  USB_FLAG.control_state=USB_IDLE;	//设置为等待状态
			  }
			  else 
			  {     //如果数据长度出错
				    if(ControlData.DeviceRequest.wLength>MAX_CTLDAT_SIZE) 
				    {				         
					     USB_FLAG.control_state=USB_IDLE;	//设置为等待状态	
					     Set_EPsta(0,1);			        //停止控制端点0
				 	     Set_EPsta(1,1);			        //停止控制端点1
				    }
				    else
				    {
					    USB_FLAG.control_state=USB_RECEIVE;  //设置为接收状态
				    }
			  }// set command with data
		 }// else set command
	}// if setup packet

/*************　下面为控制写入的数据阶段  ***************/
	else if(USB_FLAG.control_state==USB_RECEIVE)     //如果为接收状态
	{	  	    
			 i=Read_EP(0,EP0_PACKET_SIZE,ControlData.dataBuffer+ControlData.wCount);	//从端点0接收数据
			 ControlData.wCount+=i;					 //统计已接收的字节数
			 if(i!=EP0_PACKET_SIZE||ControlData.wCount>=ControlData.wLength) //数据接收完毕
			 {  		                                  
				 USB_FLAG.setup_packet=1;		    //通知control_handler()处理Setup包				  
				 USB_FLAG.control_state=USB_IDLE;	//设置为等待状态
			 }
	}
	else 
	{
		 	 USB_FLAG.control_state = USB_IDLE;		//设置等待状态
	}
}
/*******************************************
函数名称: Ep0_txdone
功    能: 通过端点索引 0 发送数据
参    数: 无   
返回值  : 无
********************************************/
void Ep0_txdone(void)
{
	uint i=ControlData.wLength-ControlData.wCount;	  //计算未发送的字节数

	Read_LttransSta(1); 					          //清除中断寄存器标志位

	if (USB_FLAG.control_state!=USB_TRANSMIT)         //非发送状态	
	{	
		return;						//返回
	}	
	if(i>=EP0_PACKET_SIZE)  //未发送字节数大于16,发送16个字节
	{							
		Write_EP(1,EP0_PACKET_SIZE,ControlData.pData+ControlData.wCount);
		ControlData.wCount+= EP0_PACKET_SIZE;
		USB_FLAG.control_state=USB_TRANSMIT;	
	}
	else if(i!=0)           //发送所有未发送的字节
	{							
		Write_EP(1,i,ControlData.pData+ControlData.wCount);
		ControlData.wCount+=i;
		USB_FLAG.control_state=USB_IDLE;		//置状态为等待状态
	}
	else if (i == 0)
	{
		Write_EP(1, 0, 0); 				        //发送完毕,发0个字节
		USB_FLAG.control_state = USB_IDLE;
	}
}
/*******************************************
函数名称: Ep1_txdone
功    能: 端点1发送处理函数
参    数: 无   
返回值  : 无
********************************************/
void Ep1_txdone(void)
{
	Read_LttransSta(3);		//清中断标志位
}
/*******************************************
函数名称: Ep1_rxdone
功    能: 端点1接收处理函数
参    数: 无   
返回值  : 无
********************************************/
void Ep1_rxdone(void)
{
	uchar len;

	Read_LttransSta(2);		                //清中断标志位
	len=Read_EP(2,sizeof(Ep1Buf),Ep1Buf);	//读取数据
	if(len!=0)
		USB_FLAG.ep1_rxdone = 1;		    //标志接收到数据
}
/*******************************************
函数名称: Ep2_txdone
功    能: 端点2发送处理函数
参    数: 无   
返回值  : 无
********************************************/
void Ep2_txdone(void)
{
	Read_LttransSta(5);		//清中断标志位
}
/*******************************************
函数名称: Ep2_rxdone
功    能: 端点2接收处理函数
参    数: 无   
返回值  : 无
********************************************/
void Ep2_rxdone(void)
{
	uchar len;
	
	Read_LttransSta(4); 			        //清中断标志位
	len=Read_EP(4,EP2_PACKET_SIZE,Ep2Buf);	//读取缓冲区中的数据
	if (len!=0)
		USB_FLAG.ep2_rxdone = 1;
}
/*******************************************
函数名称: Control_handler
功    能: 控制传输
参    数: 无   
返回值  : 无
********************************************/
void Control_handler(void)
{
	uchar type,req; 
	
	type=ControlData.DeviceRequest.bmRequestType&USB_REQUEST_TYPE_MASK;
											//读取请求代码													
	req=ControlData.DeviceRequest.bRequest&USB_REQUEST_MASK;
	if(type==USB_STANDARD_REQUEST)
		(*StandardDeviceRequest[req])();	//标准请求处理
	else
		Stall_ep0();				        //无效请求,返回STALL				
}
/*******************************************
函数名称: Reserved
功    能: 保留子程序
参    数: 无   
返回值  : 无
********************************************/
void Reserved(void)
{
	Stall_ep0();				//返回STALL
}
/*******************************************
函数名称: Init_unconfig
功    能: 进入地址状态,禁止0除外的所有端点
参    数: 无   
返回值  : 无
********************************************/
void Init_unconfig(void)
{
	Set_EPen(0);	//禁止0除外的所有端点
}
/*******************************************
函数名称: Init_config
功    能: 配置处理,允许端点收发
参    数: 无   
返回值  : 无
********************************************/
void Init_config(void)
{
	Set_EPen(1);	//使能普通/同步端点使能
}
/*******************************************
函数名称: Get_status
功    能: 主机要求获取状态,设备返回16位的状态描述给主机
参    数: 无   
返回值  : 无
********************************************/
void Get_status(void)
{
	uchar endp,txdat[2],c;
	uchar bRecipient=ControlData.DeviceRequest.bmRequestType&USB_RECIPIENT;	//取得设备请求类型	
						
	if (bRecipient==USB_RECIPIENT_DEVICE)//对设备请求 
	{					
		if(USB_FLAG.remote_wakeup==1)			
		{
			txdat[0]=3;		//支持远程唤醒、自供电
		}
		else
		{
			txdat[0]=1;		//不支持远程唤醒、自供电
		}
		txdat[1]=0;			//高8位为0
		S_trans(txdat,2);	//发送16位的状态到主机
		
	} 
	else if (bRecipient == USB_RECIPIENT_INTERFACE) //对接口请求
	{			
		txdat[0]=0;
		txdat[1]=0;
		S_trans(txdat, 2);	//发送16位的状态到主机
						
	} 
	else if (bRecipient == USB_RECIPIENT_ENDPOINT) //对端点请求
	{			
		endp = (uchar)(ControlData.DeviceRequest.wIndex & MAX_ENDPOINTS);
		if (ControlData.DeviceRequest.wIndex & (uchar)USB_ENDPOINT_DIRECTION_MASK)
		{
			c = Sel_EP(endp*2+1);	//读取输入端点状态
		}
		else
		{
			c = Sel_EP(endp*2);		//读取输出端点状态
		}
		if(c & STALL)
		{
			txdat[0] = 1;			//端点禁止
		}
		else
		{
			txdat[0] = 0;			//端点有效
		}
		txdat[1] = 0;
		S_trans(txdat, 2);			//发送16位的状态到主机

	} 
	else
	{
		Stall_ep0();				//非标准请求,发STALL
	}
}
/*******************************************
函数名称: Clr_feature
功    能: 清除特性
参    数: 无   
返回值  : 无
********************************************/
void Clr_feature(void)
{
	uchar endp;					//读取请求类型中的接收方
	uchar bRecipient = ControlData.DeviceRequest.bmRequestType & USB_RECIPIENT; //读取请求类型
										
	if (bRecipient == USB_RECIPIENT_DEVICE  //对设备请求
	&&ControlData.DeviceRequest.wValue==USB_FEATURE_REMOTE_WAKEUP) //清除远程唤醒特性	
	{
		UEN_GINT();								
		USB_FLAG.remote_wakeup = 0;			//清0远程唤醒标志
		EN_GINT();
		S_trans(0,0);						//返回一个空的数据表示执行完毕
	}
	
	else if (bRecipient == USB_RECIPIENT_ENDPOINT   //对端点请求
		&& ControlData.DeviceRequest.wValue == USB_FEATURE_ENDPOINT_STALL) //清除端点禁止特性,恢复其使用
	{
		
		endp = (uchar)(ControlData.DeviceRequest.wIndex & MAX_ENDPOINTS);
		if (ControlData.DeviceRequest.wIndex & (uchar)USB_ENDPOINT_DIRECTION_MASK)
		{
			Set_EPsta(endp*2 + 1, 0);			    //清除控制输入端点STALL特性
		}
		else
		{
			Set_EPsta(endp*2, 0);				    //清除控制输出端点STALL特性
		}
		S_trans(0, 0);						        //返回一个空的数据表示执行完毕
	} 
	else
	{
		Stall_ep0();					            //没有该请求,返回STALL	
	}						
}
/*******************************************
函数名称: Set_feature
功    能: 设置特性
参    数: 无   
返回值  : 无
********************************************/
void Set_feature(void)
{
	uchar endp;		//读取请求类型中的接收方							
	uchar bRecipient = ControlData.DeviceRequest.bmRequestType & USB_RECIPIENT;//读取请求类型
											
	if (bRecipient == USB_RECIPIENT_DEVICE  //对设备请求
		&& ControlData.DeviceRequest.wValue == USB_FEATURE_REMOTE_WAKEUP) //设置远程唤醒特性
	{														
		UEN_GINT();
		USB_FLAG.remote_wakeup = 1;				//置1远程唤醒标志
		EN_GINT();
		S_trans(0, 0);						    //返回一个空的数据表示执行完毕
	}		
	else if (bRecipient == USB_RECIPIENT_ENDPOINT //对端点请求
		&& ControlData.DeviceRequest.wValue == USB_FEATURE_ENDPOINT_STALL) //禁止端点
	{		
		endp = (uchar)(ControlData.DeviceRequest.wIndex & MAX_ENDPOINTS);
		if (ControlData.DeviceRequest.wIndex & (uchar)USB_ENDPOINT_DIRECTION_MASK)
		{
			Set_EPsta(endp*2 + 1, 1);		//设置输入端点禁止
		}
		else
		{
			Set_EPsta(endp*2, 1);			//设置输出端点禁止
		}
		S_trans(0, 0);					    //返回一个空的数据表示执行完毕
	} 
	else
	{
		Stall_ep0();					    //没有该请求,返回STALL
	}
}
/*******************************************
函数名称: Set_addr
功    能: 设置地址
参    数: 无   
返回值  : 无
********************************************/
void Set_addr(void)
{
	Set_addren((uchar)(ControlData.DeviceRequest.wValue&DEVICE_ADDRESS_MASK), 1);
	S_trans(0, 0);				//发送一个空的数据响应
}
/*******************************************
函数名称: Get_descriptor
功    能: 获取描述符
参    数: 无   
返回值  : 无
********************************************/
void Get_descriptor(void)
{
	uchar bDescriptor = MSB(ControlData.DeviceRequest.wValue); //读取请求的描述符类型

	if (bDescriptor == USB_DEVICE_DESCRIPTOR_TYPE) //获取设备描述符
	{						
		Code_trans((uchar *)&DeviceDescr, sizeof(USB_DEVICE_DESCRIPTOR));
	
	}
	else if (bDescriptor == USB_CONFIGURATION_DESCRIPTOR_TYPE) //获取其它描述符
	{		
		  		if (ControlData.DeviceRequest.wLength > CONFIG_DESCRIPTOR_LENGTH)
				{ 
					 ControlData.DeviceRequest.wLength = CONFIG_DESCRIPTOR_LENGTH;
				}   //发送描述符内容
			    Code_trans((uchar *)&(usb_descr.ConfigDescr), ControlData.DeviceRequest.wLength);
			    				
	}
	else
	{
			Stall_ep0();			//没有该请求,返回STALL
	}
	 
}
/*******************************************
函数名称: Get_config
功    能: 获取配置
参    数: 无   
返回值  : 无
********************************************/
void Get_config(void)
{
	uchar c = USB_FLAG.configuration;	//取出配置值
		
	S_trans(&c, 1);				        //发送配置值
}
/*******************************************
函数名称: Set_config
功    能: 设置配置
参    数: 无   
返回值  : 无
********************************************/
void Set_config(void)
{
	if (ControlData.DeviceRequest.wValue == 0) //配置值不对,设备进入未配置状态
	{			
		S_trans(0, 0);			    //发向一个空包响应
		UEN_GINT();
		USB_FLAG.configuration = 0;	//标记未配置
		EN_GINT();
		Init_unconfig();			//进入地址状态,禁止0除外的所有端点
		
	} 
	else if (ControlData.DeviceRequest.wValue == 1) //配置设备
	{		
		S_trans(0, 0);			    //发向一个空包响应
		Init_unconfig();			//进入地址状态,禁止0除外的所有端点
		Init_config();				//配置处理,允许端点收发
		UEN_GINT();
		USB_FLAG.configuration = 1;	//标志已配置
		EN_GINT();
	} 
	else
	{
		Stall_ep0();			    //没有该请求,返回STALL
	}
}
/*******************************************
函数名称: Get_interface
功    能: 获取接口信息
参    数: 无   
返回值  : 无
********************************************/
void Get_interface(void)
{
	uchar txdat = 0;		        //本设备只有一个接口
	S_trans(&txdat, 1);		        //发送一个字节
}
/*******************************************
函数名称: Set_interface
功    能: 设置接口信息
参    数: 无   
返回值  : 无
********************************************/
void Set_interface(void)
{
	if (ControlData.DeviceRequest.wValue == 0 && ControlData.DeviceRequest.wIndex == 0)
	{
		S_trans(0, 0);		        //发送一个空的数据表示执行完毕
	}
	else		
	{
		Stall_ep0();		        //没有该请求,返回STALL	
	}				
}
/*******************************************
函数名称: USB_connect
功    能: 连接USB总线
参    数: 无   
返回值  : 无
********************************************/
void USB_connect(void)
{
    //SoftConnect 连接上,并设置为无LazyClock,模式为非同步模式
	Set_DMA(0x00);
	Set_mode(NOLAZYCLOCK|SOFTCONNECT, SETTOONE | CLOCK_12M);
}	

/*******************************************
函数名称: Set_interface
功    能: 设置接口信息
参    数: 无   
返回值  : 无
********************************************/
void USB_disconnect(void)
{
	//SoftConnect 断开
	Set_mode(NOLAZYCLOCK, SETTOONE | CLOCK_12M);
}	
/*******************************************
函数名称: USB_reconnect
功    能: 重新连接USB总线
参    数: 无   
返回值  : 无
********************************************/
void USB_reconnect(void)
{
	USB_disconnect();	//断开芯片与USB总线连接
	Delayms(200);
	Set_addren(0,1);
	Set_EPen(1);
    USB_connect();		//连接到USB总线
}
/*******************************************
函数名称: Read_chipID
功    能: 读取芯片的ID
参    数: 无   
返回值  : 无
********************************************/
uint Read_chipID(void)
{
	uint i,j;
    
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD, 0xFD);
	i=InB( );
	j=InB( );
	i += (j<<8);
    
	if(USB_FLAG.in_isr == 0)
		EN_GINT();
	return i;
}
