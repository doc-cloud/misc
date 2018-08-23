//这里定义了USB通信程序用到的所有常量数据


/******************数据类型宏定义******************/
/*
typedef unsigned char unsigned char;
typedef unsigned int unsigned int;*/
/*************数据移位的宏定义**************/
#define BIT(x)	(1 << (x))
/******************USB常量******************/
#define WR_N    0       //写使能,P2.0
#define RD_N    1       //读使能,P2.1
#define C_D     2       //命令数据位(1：命令，0：数据),P2.2
#define D12_CS  3       //USB片选位,P2.3   
#define D12_INT 5       //USB中断,P2.5
#define USBINT_IE     P1IE
#define USBINT_IES    P1IES
#define USBINT_IFG    P1IFG
#define USBINT_SEL    P1SEL
#define USBINT_DDR    P1DIR
#define USBCTL_DDR    P2DIR
#define USBCTL_PORT   P2OUT
#define USBDAT_DDR    P5DIR
#define USBDAT_PORT   P5OUT
#define USBDAT_PIN    P5IN

#define CMD     0x01
#define DAT     0x00

#define UEN_GINT() _DINT()   //打开全局中断
#define EN_GINT()  _EINT()   //关闭全局中断

#define MSB(x)    (((x) >> 8) & 0xFF)

#define MAX_ENDPOINTS      (unsigned char)0x3

#define NOLAZYCLOCK			0x02
#define CLOCKRUNNING                    0x04
#define INTERRUPTMODE		        0x08
#define SOFTCONNECT			0x10
#define ENDP_NONISO			0x00
#define ENDP_ISOOUT			0x40
#define ENDP_ISOIN			0x80
#define ENDP_ISOIO			0xC0

#define CLOCK_12M			0x03
#define CLOCK_4M			0x0b
#define SETTOONE                        0x40
#define SOFONLY				0x80

#define NORMALPLUSSOF		        0x20
#define ENDP4INTENABLE		        0x40
#define ENDP5INTENABLE		        0x80

#define INT_ENDP0OUT		        0x01
#define INT_ENDP0IN			0x02
#define INT_ENDP1OUT	                0x04
#define INT_ENDP1IN			0x08
#define INT_ENDP2OUT		        0x10
#define INT_ENDP2IN			0x20
#define INT_BUSRESET		        0x40
#define INT_SUSPENDCHANGE	        0x80

#define SETUPPACKET			0x20
#define BUFFER0FULL			0x20
#define BUFFER1FULL			0x40

#define FULLEMPTY			0x01
#define STALL				0x02

#define USB_IDLE            0
#define USB_TRANSMIT        1
#define USB_RECEIVE         2

#define MAX_CTLDAT_SIZE	    8

#define USB_ENDPOINT_DIRECTION_MASK     0x80
#define USB_REQUEST_MASK         (unsigned char)0x0F
#define USB_REQUEST_TYPE_MASK    (unsigned char)0x60
#define USB_STANDARD_REQUEST     (unsigned char)0x00

#define DEVICE_ADDRESS_MASK      0x7F

#define USB_FEATURE_ENDPOINT_STALL          (unsigned int)0x0000
#define USB_FEATURE_REMOTE_WAKEUP           (unsigned int)0x0001

#define EP0_PACKET_SIZE    16
#define EP1_PACKET_SIZE    16
#define EP2_PACKET_SIZE    64

#define USB_RECIPIENT            (unsigned char)0x1F
#define USB_RECIPIENT_DEVICE     (unsigned char)0x00
#define USB_RECIPIENT_INTERFACE  (unsigned char)0x01
#define USB_RECIPIENT_ENDPOINT   (unsigned char)0x02

#define USB_DEVICE_DESCRIPTOR_TYPE                0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE         0x02
#define USB_STRING_DESCRIPTOR_TYPE                0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE             0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE              0x05
#define USB_POWER_DESCRIPTOR_TYPE                 0x06

/* 设备描述符: 测试设备类型 */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE                    0xdc
/*****   D12 配置描述符长度  ******/
#define CONFIG_DESCRIPTOR_LENGTH    sizeof(USB_CONFIGURATION_DESCRIPTOR) \
									+ sizeof(USB_INTERFACE_DESCRIPTOR) \
									+ (NUM_ENDPOINTS * sizeof(USB_ENDPOINT_DESCRIPTOR))
/*****   D12 接口描述符中: 除端点0的端点索引数目  ******/
#define NUM_ENDPOINTS	4
/* 设备描述符: 测试设备类型 */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE                    0xdc

/* 接口描述符: 子类代码 */
#define USB_SUBCLASS_CODE_TEST_CLASS_D12                    0xA0

/* 接口描述符: 协议代码 */
#define USB_PROTOCOL_CODE_TEST_CLASS_D12                    0xB0
/*******************************************************
	      USB 端点描述符结构体: 端点属性
********************************************************/
#define USB_ENDPOINT_TYPE_MASK                    0x03

#define USB_ENDPOINT_TYPE_CONTROL                 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS             0x01
#define USB_ENDPOINT_TYPE_BULK                    0x02
#define USB_ENDPOINT_TYPE_INTERRUPT               0x03

//这里定义了USB通信程序用到的所有全局变量
typedef struct flags
{
	unsigned char bus_reset;	        //总线复位标志
	unsigned char suspend;	            //挂起改变标志
	unsigned char setup_packet;	        //收到SETUP包
	unsigned char remote_wakeup;
	unsigned char in_isr;	            //USB中断服务标志
	unsigned char control_state;	    //控制端点处理标志
									    //0: IDLE	   空闲状态
										//1: TRANSMIT  数据发送状态
										//2: RECEIVE   数据接收状态
 	unsigned char configuration;	    //配置标志(0: 未配置; 1: 已经配置)		
	unsigned char ep1_rxdone;	        //端点 1 收到数据标志
	unsigned char ep2_rxdone;	        //端点 2 收到数据标志
	unsigned char ep2buf_full;	        //端点 2 接收双缓冲区满标志
} All_Usb_Flags;
All_Usb_Flags USB_FLAG={0,0,0,0,0,0,0,0,0,0};

typedef struct request
{
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned int wValue;
	unsigned int wIndex;
	unsigned int wLength;
}DEVICE_REQUEST;

typedef struct xfer
{
	DEVICE_REQUEST DeviceRequest;
	unsigned int wLength;
	unsigned int wCount;
	unsigned char * pData;
	unsigned char dataBuffer[MAX_CTLDAT_SIZE];
}CONTROL_XFER;

typedef struct _USB_DEVICE_DESCRIPTOR 
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bcdUSB0;
    unsigned char bcdUSB1;
    unsigned char bDeviceClass;
    unsigned char bDeviceSubClass;
    unsigned char bDeviceProtocol;
    unsigned char bMaxPacketSize0;
    unsigned char idVendor0;
    unsigned char idVendor1;
    unsigned char idProduct0;
    unsigned char idProduct1;
    unsigned char bcdDevice0;
    unsigned char bcdDevice1;
    unsigned char iManufacturer;
    unsigned char iProduct;
    unsigned char iSerialNumber;
    unsigned char bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;

/***********  USB  接口描述符结构体  ****************/
typedef struct _USB_INTERFACE_DESCRIPTOR 
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bInterfaceNumber;
    unsigned char bAlternateSetting;
    unsigned char bNumEndpoints;
    unsigned char bInterfaceClass;
    unsigned char bInterfaceSubClass;
    unsigned char bInterfaceProtocol;
    unsigned char iInterface;
} USB_INTERFACE_DESCRIPTOR;

/***********  USB  配置描述符结构体  ****************/
typedef struct _USB_CONFIGURATION_DESCRIPTOR 
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char wTotalLength0;
    unsigned char wTotalLength1;
    unsigned char bNumInterfaces;
    unsigned char bConfigurationValue;
    unsigned char iConfiguration;
    unsigned char bmAttributes;
    unsigned char MaxPower;
} USB_CONFIGURATION_DESCRIPTOR;

/***********  USB  端点描述符结构体  ****************/
typedef struct _USB_ENDPOINT_DESCRIPTOR 
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bEndpointAddress;
    unsigned char bmAttributes;
    unsigned char wMaxPacketSize0;
    unsigned char wMaxPacketSize1;
    unsigned char bInterval;
} USB_ENDPOINT_DESCRIPTOR;

/***********  D12 USB 各种描述符结构体 *********************/
typedef struct _USB_DESCRIPTOR 
{
	USB_CONFIGURATION_DESCRIPTOR ConfigDescr;		//配置描述符
	USB_INTERFACE_DESCRIPTOR InterfaceDescr;		//接口描述符
	USB_ENDPOINT_DESCRIPTOR EP1_TXDescr;			//端点1输入描述符
	USB_ENDPOINT_DESCRIPTOR EP1_RXDescr;			//端点1输出描述符
	USB_ENDPOINT_DESCRIPTOR EP2_TXDescr;			//端点2输入描述符
	USB_ENDPOINT_DESCRIPTOR EP2_RXDescr;			//端点2输出描述符
} USB_DESCRIPTOR;

CONTROL_XFER ControlData;
unsigned char Ep1Buf[EP1_PACKET_SIZE];			        //端点1接收缓冲区
unsigned char Ep2Buf[EP2_PACKET_SIZE];				//端点2接收缓冲区

//设备描述符
USB_DEVICE_DESCRIPTOR DeviceDescr =
{
	sizeof(USB_DEVICE_DESCRIPTOR),				//设备描述符长度,= 12H
	USB_DEVICE_DESCRIPTOR_TYPE,				//设备描述符类型,= 01H
	0x00,0x10,						//协议版本,= 1.10
	USB_CLASS_CODE_TEST_CLASS_DEVICE,			//测试设备类型, = 0DCH	
	0, 0,							//设备子类,设备协议
	EP0_PACKET_SIZE,					//端点0最大数据包大小,= 10H	
	0x71,0x04,						//PHILIPS公司的设备ID	
	0x14,0x41,						//设备制造商定的产品ID
	0x00,0x01,						//设备系列号
	0, 0, 0,						//索引
	1							//可能的配置数
};

USB_DESCRIPTOR usb_descr =
{
//配置描述符
{
	sizeof(USB_CONFIGURATION_DESCRIPTOR),		        //配置描述符长度,= 09H
	USB_CONFIGURATION_DESCRIPTOR_TYPE,			//配置描述符类型,= 02H
	CONFIG_DESCRIPTOR_LENGTH,0x00,				//描述符总长度, = 002EH
	1,							//只支持1个接口
	1,							//配置值
	0,							//字符串描述符指针(无)
	0xa0,							//自供电,支持远程唤醒
	0x32							//最大功耗(100mA)
},
//接口描述符
{
	sizeof(USB_INTERFACE_DESCRIPTOR),			//接口描述符长度,= 09H
	USB_INTERFACE_DESCRIPTOR_TYPE,				//接口描述符类型,= 04H
	0,						        //接口数,只有1个
	0,							//可选配置,只有1个
	NUM_ENDPOINTS,						//除端点0的端点索引数目,= 04H
	USB_CLASS_CODE_TEST_CLASS_DEVICE,			//测试设备类型,= 0DCH
	USB_SUBCLASS_CODE_TEST_CLASS_D12,			//子类代码,= 0A0H	
	USB_PROTOCOL_CODE_TEST_CLASS_D12,			//协议代码,= 0B0H
	0							//字符串描述符索引
},
//端点描述符，端点1输入
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//端点描述符长度,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//端点描述符类型,= 05H
	0x81,							//端点1 IN
	USB_ENDPOINT_TYPE_INTERRUPT,				//中断传输, = 03H
	EP1_PACKET_SIZE,0x00,					//端点最大包的大小,= 0010H
	1							//传输间隔时间,= 1ms
},
//端点描述符，端点1输出
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//端点描述符长度,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//端点描述符类型,= 05H
	0x01,							//端点1 OUT
	USB_ENDPOINT_TYPE_INTERRUPT,				//中断传输,= 03H
	EP1_PACKET_SIZE,0x00,					//端点最大包的大小,= 0010H
	1						        //传输间隔时间,= 1ms
},
//端点2输入
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//端点描述符长度,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//端点描述符类型,= 05H
	0x82,							//端点2 OUT
	USB_ENDPOINT_TYPE_BULK,					//批量传输,= 02H
	EP2_PACKET_SIZE,0x00,					//端点最大包的大小,= 0040H
	1							//批量传输时该设置无效
},
//端点2输出
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//端点描述符长度,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//端点描述符类型,= 05H
	0x02,							//端点2 IN	
	USB_ENDPOINT_TYPE_BULK,					//批量传输,= 02H
	EP2_PACKET_SIZE,0x00,					//端点最大包的大小,= 0040H
	1							//批量传输时该设置无效
} 
};
