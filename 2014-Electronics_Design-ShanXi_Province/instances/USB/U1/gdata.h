
//������USBfunctions.c�ж����ȫ�ֱ������ⲿ����
typedef struct flags
{
	unsigned char bus_reset;	    //���߸�λ��־
	unsigned char suspend;	            //����ı��־
	unsigned char setup_packet;	    //�յ�SETUP��
	unsigned char remote_wakeup;
	unsigned char in_isr;	            //USB�жϷ����־
	unsigned char control_state;	    //���ƶ˵㴦���־
													//0: IDLE	   ����״̬
													//1: TRANSMIT  ���ݷ���״̬
													//2: RECEIVE   ���ݽ���״̬
 	unsigned char configuration;	    //���ñ�־(0: δ����; 1: �Ѿ�����)		
	unsigned char ep1_rxdone;	    //�˵� 1 �յ����ݱ�־
	unsigned char ep2_rxdone;	    //�˵� 2 �յ����ݱ�־
	unsigned char ep2buf_full;	    //�˵� 2 ����˫����������־
} All_Usb_Flags;

extern All_Usb_Flags USB_FLAG;     
extern unsigned char Ep1Buf[16];	    //�˵�1���ջ�����
extern unsigned char Ep2Buf[64];	    //�˵�2���ջ�����

#define INT_ENDP0OUT		        0x01
#define INT_ENDP0IN			0x02
#define INT_ENDP1OUT	                0x04
#define INT_ENDP1IN			0x08
#define INT_ENDP2OUT		        0x10
#define INT_ENDP2IN			0x20
#define INT_BUSRESET		        0x40
#define INT_SUSPENDCHANGE	        0x80
