//���ﶨ����USBͨ�ų����õ������г�������


/******************�������ͺ궨��******************/
/*
typedef unsigned char unsigned char;
typedef unsigned int unsigned int;*/
/*************������λ�ĺ궨��**************/
#define BIT(x)	(1 << (x))
/******************USB����******************/
#define WR_N    0       //дʹ��,P2.0
#define RD_N    1       //��ʹ��,P2.1
#define C_D     2       //��������λ(1�����0������),P2.2
#define D12_CS  3       //USBƬѡλ,P2.3   
#define D12_INT 5       //USB�ж�,P2.5
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

#define UEN_GINT() _DINT()   //��ȫ���ж�
#define EN_GINT()  _EINT()   //�ر�ȫ���ж�

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

/* �豸������: �����豸���� */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE                    0xdc
/*****   D12 ��������������  ******/
#define CONFIG_DESCRIPTOR_LENGTH    sizeof(USB_CONFIGURATION_DESCRIPTOR) \
									+ sizeof(USB_INTERFACE_DESCRIPTOR) \
									+ (NUM_ENDPOINTS * sizeof(USB_ENDPOINT_DESCRIPTOR))
/*****   D12 �ӿ���������: ���˵�0�Ķ˵�������Ŀ  ******/
#define NUM_ENDPOINTS	4
/* �豸������: �����豸���� */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE                    0xdc

/* �ӿ�������: ������� */
#define USB_SUBCLASS_CODE_TEST_CLASS_D12                    0xA0

/* �ӿ�������: Э����� */
#define USB_PROTOCOL_CODE_TEST_CLASS_D12                    0xB0
/*******************************************************
	      USB �˵��������ṹ��: �˵�����
********************************************************/
#define USB_ENDPOINT_TYPE_MASK                    0x03

#define USB_ENDPOINT_TYPE_CONTROL                 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS             0x01
#define USB_ENDPOINT_TYPE_BULK                    0x02
#define USB_ENDPOINT_TYPE_INTERRUPT               0x03

//���ﶨ����USBͨ�ų����õ�������ȫ�ֱ���
typedef struct flags
{
	unsigned char bus_reset;	        //���߸�λ��־
	unsigned char suspend;	            //����ı��־
	unsigned char setup_packet;	        //�յ�SETUP��
	unsigned char remote_wakeup;
	unsigned char in_isr;	            //USB�жϷ����־
	unsigned char control_state;	    //���ƶ˵㴦���־
									    //0: IDLE	   ����״̬
										//1: TRANSMIT  ���ݷ���״̬
										//2: RECEIVE   ���ݽ���״̬
 	unsigned char configuration;	    //���ñ�־(0: δ����; 1: �Ѿ�����)		
	unsigned char ep1_rxdone;	        //�˵� 1 �յ����ݱ�־
	unsigned char ep2_rxdone;	        //�˵� 2 �յ����ݱ�־
	unsigned char ep2buf_full;	        //�˵� 2 ����˫����������־
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

/***********  USB  �ӿ��������ṹ��  ****************/
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

/***********  USB  �����������ṹ��  ****************/
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

/***********  USB  �˵��������ṹ��  ****************/
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

/***********  D12 USB �����������ṹ�� *********************/
typedef struct _USB_DESCRIPTOR 
{
	USB_CONFIGURATION_DESCRIPTOR ConfigDescr;		//����������
	USB_INTERFACE_DESCRIPTOR InterfaceDescr;		//�ӿ�������
	USB_ENDPOINT_DESCRIPTOR EP1_TXDescr;			//�˵�1����������
	USB_ENDPOINT_DESCRIPTOR EP1_RXDescr;			//�˵�1���������
	USB_ENDPOINT_DESCRIPTOR EP2_TXDescr;			//�˵�2����������
	USB_ENDPOINT_DESCRIPTOR EP2_RXDescr;			//�˵�2���������
} USB_DESCRIPTOR;

CONTROL_XFER ControlData;
unsigned char Ep1Buf[EP1_PACKET_SIZE];			        //�˵�1���ջ�����
unsigned char Ep2Buf[EP2_PACKET_SIZE];				//�˵�2���ջ�����

//�豸������
USB_DEVICE_DESCRIPTOR DeviceDescr =
{
	sizeof(USB_DEVICE_DESCRIPTOR),				//�豸����������,= 12H
	USB_DEVICE_DESCRIPTOR_TYPE,				//�豸����������,= 01H
	0x00,0x10,						//Э��汾,= 1.10
	USB_CLASS_CODE_TEST_CLASS_DEVICE,			//�����豸����, = 0DCH	
	0, 0,							//�豸����,�豸Э��
	EP0_PACKET_SIZE,					//�˵�0������ݰ���С,= 10H	
	0x71,0x04,						//PHILIPS��˾���豸ID	
	0x14,0x41,						//�豸�����̶��Ĳ�ƷID
	0x00,0x01,						//�豸ϵ�к�
	0, 0, 0,						//����
	1							//���ܵ�������
};

USB_DESCRIPTOR usb_descr =
{
//����������
{
	sizeof(USB_CONFIGURATION_DESCRIPTOR),		        //��������������,= 09H
	USB_CONFIGURATION_DESCRIPTOR_TYPE,			//��������������,= 02H
	CONFIG_DESCRIPTOR_LENGTH,0x00,				//�������ܳ���, = 002EH
	1,							//ֻ֧��1���ӿ�
	1,							//����ֵ
	0,							//�ַ���������ָ��(��)
	0xa0,							//�Թ���,֧��Զ�̻���
	0x32							//��󹦺�(100mA)
},
//�ӿ�������
{
	sizeof(USB_INTERFACE_DESCRIPTOR),			//�ӿ�����������,= 09H
	USB_INTERFACE_DESCRIPTOR_TYPE,				//�ӿ�����������,= 04H
	0,						        //�ӿ���,ֻ��1��
	0,							//��ѡ����,ֻ��1��
	NUM_ENDPOINTS,						//���˵�0�Ķ˵�������Ŀ,= 04H
	USB_CLASS_CODE_TEST_CLASS_DEVICE,			//�����豸����,= 0DCH
	USB_SUBCLASS_CODE_TEST_CLASS_D12,			//�������,= 0A0H	
	USB_PROTOCOL_CODE_TEST_CLASS_D12,			//Э�����,= 0B0H
	0							//�ַ�������������
},
//�˵����������˵�1����
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//�˵�����������,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//�˵�����������,= 05H
	0x81,							//�˵�1 IN
	USB_ENDPOINT_TYPE_INTERRUPT,				//�жϴ���, = 03H
	EP1_PACKET_SIZE,0x00,					//�˵������Ĵ�С,= 0010H
	1							//������ʱ��,= 1ms
},
//�˵����������˵�1���
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//�˵�����������,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//�˵�����������,= 05H
	0x01,							//�˵�1 OUT
	USB_ENDPOINT_TYPE_INTERRUPT,				//�жϴ���,= 03H
	EP1_PACKET_SIZE,0x00,					//�˵������Ĵ�С,= 0010H
	1						        //������ʱ��,= 1ms
},
//�˵�2����
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//�˵�����������,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//�˵�����������,= 05H
	0x82,							//�˵�2 OUT
	USB_ENDPOINT_TYPE_BULK,					//��������,= 02H
	EP2_PACKET_SIZE,0x00,					//�˵������Ĵ�С,= 0040H
	1							//��������ʱ��������Ч
},
//�˵�2���
{
	sizeof(USB_ENDPOINT_DESCRIPTOR),			//�˵�����������,= 07H
	USB_ENDPOINT_DESCRIPTOR_TYPE,				//�˵�����������,= 05H
	0x02,							//�˵�2 IN	
	USB_ENDPOINT_TYPE_BULK,					//��������,= 02H
	EP2_PACKET_SIZE,0x00,					//�˵������Ĵ�С,= 0040H
	1							//��������ʱ��������Ч
} 
};
