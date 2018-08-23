//主函数中用到的全局变量

//数码管段码；0--f
unsigned char scandata[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                              0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char cnt=0;
unsigned char Dispbuf[6]={0,0};     //数码管显示的数据缓冲区
unsigned char KeyChar=0;            //按键输入数值
unsigned char SendFlag=0;           //是否发送数据标志


//引用在USBfunctions.c中定义的全局变量的外部声明
typedef struct flags
{
	unsigned char bus_reset;	    //总线复位标志
	unsigned char suspend;	        //挂起改变标志
	unsigned char setup_packet;	    //收到SETUP包
	unsigned char remote_wakeup;
	unsigned char in_isr;	          //USB中断服务标志
	unsigned char control_state;	  //控制端点处理标志
													//0: IDLE	   空闲状态
													//1: TRANSMIT  数据发送状态
													//2: RECEIVE   数据接收状态
 	unsigned char configuration;	//配置标志(0: 未配置; 1: 已经配置)		
	unsigned char ep1_rxdone;	    //端点 1 收到数据标志
	unsigned char ep2_rxdone;	    //端点 2 收到数据标志
	unsigned char ep2buf_full;	    //端点 2 接收双缓冲区满标志
} All_Usb_Flags;

extern All_Usb_Flags USB_FLAG;     
extern unsigned char Ep1Buf[16];			    //端点1接收缓冲区
extern unsigned char Ep2Buf[64];				//端点2接收缓冲区

#define INT_ENDP0OUT		        0x01
#define INT_ENDP0IN			0x02
#define INT_ENDP1OUT	                0x04
#define INT_ENDP1IN			0x08
#define INT_ENDP2OUT		        0x10
#define INT_ENDP2IN			0x20
#define INT_BUSRESET		        0x40
#define INT_SUSPENDCHANGE	        0x80

//4X4键盘引用外部变量的声明
extern unsigned char key_Pressed;      
extern unsigned char key_val;         
extern unsigned char key_Flag; 
