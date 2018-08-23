#include <msp430x14x.h>
#include "USBvariables.h"
#include "USBfunctions.h"
typedef unsigned char uchar;
typedef unsigned int  uint;

//�ⲿ��������
extern unsigned char KeyChar;            //����������ֵ
extern unsigned char SendFlag;           //�Ƿ������ݱ�־

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
��������: Delayus
��    ��: ��ʱָ��΢�루8M����
��    ��: US--��ʱ��΢����(��Լ�����Ǻܾ�ȷ)
����ֵ  : ��
********************************************/
void Delayus(uint US)		  
{
    uint i;
    
    US=US*5/4;		 // 5/4����8MHz�����£�ͨ��������淴��ʵ��õ�����ֵ
    for( i=0;i<US;i++); 
}
/*******************************************
��������: Delayms
��    ��: ��ʱָ�����루8M����
��    ��: MS--��ʱ�ĺ�����
����ֵ  : ��
********************************************/
void Delayms(uint MS)		  
{
     uint i,j;
     
     for(i=0;i<MS;i++)
     for(j=0;j<1141;j++);	// 1141����8MHz�����£�ͨ��������淴��ʵ��õ�����ֵ
}
/*******************************************
��������: D12_init
��    ��: ��ʼ��D12�ӿڣ��������ݽӿںͿ��ƽӿڣ�
��    ��: ��
����ֵ  : ��
********************************************/
void D12_init(void)
{
     USBDAT_DDR|=0xFF;				    //���ݶ˿�����Ϊ���
     USBCTL_DDR|=BIT(WR_N)|BIT(RD_N)|BIT(C_D)|BIT(D12_CS);//������������Ϊ���
     USBINT_DDR&=~BIT(D12_INT);	        //�ж���������Ϊ����						  //�ж���������Ϊ����				  
     USBINT_IES|=BIT(D12_INT);          //ѡ���½����ж�
     USBINT_SEL&=~BIT(D12_INT);         //ѡ��IO�˿�
     USBINT_IE|=BIT(D12_INT);           //ʹ�ܶ˿��ж�
     USBCTL_PORT|=BIT(WR_N)|BIT(RD_N)|BIT(D12_CS);		  //����������Ч
     
     EN_GINT();                         //ʹ��ȫ���ж�    
     USBCTL_PORT&=~BIT(D12_CS);        //����Ƭѡ�ź�
}
/*******************************************
��������: OutB
��    ��: ��D12д��һ���ֽ����ݻ�������
��    ��: cmd--�����ʶ��ΪCMD�����ΪDAT�����ݣ�
	  	  dat--Ҫд����ֽ�����
����ֵ  : ��
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
��������: InB
��    ��: ��D12����һ���ֽ�����
��    ��: ��
����ֵ  : dat--�������ֽ�����
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
��������: Set_addren
��    ��: ���õ�ַ/ʹ��
��    ��: addr--���õĵ�ַ
	  enable--ʹ�ܱ�־��Ϊ1ʹ�ܣ�Ϊ0��ֹ��
����ֵ  : ��
********************************************/
void Set_addren(uchar addr, uchar enable)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD, 0xD0);	//������õ�ַ/ʹ��ָ��
	Delayus(1);
	if(enable)
	{
		addr|=0x80;		//bit7��1,ʹ��
	}
	Delayus(1);
	OutB(DAT,addr);		//�������ֵ

	if(USB_FLAG.in_isr == 0)
		EN_GINT();
}
/*******************************************
��������: Set_EPen
��    ��: ���ö˵�ʹ��
��    ��: enable--ʹ�ܱ�־��Ϊ1ʹ�ܣ�Ϊ0��ֹ��
����ֵ  : ��
********************************************/
void Set_EPen(uchar enable)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0xD8);	        //������ö˵�ʹ��ָ��
	Delayus(1);
	if(enable)
		OutB(DAT,1);		//���ö˵�����
	else
		OutB(DAT,0);		//���ö˵��ֹ

	if(USB_FLAG.in_isr == 0)
		EN_GINT();
}
/*******************************************
��������: Set_mode
��    ��: ����ģʽ
��    ��: config--�����ֽ���Ϣ
	  	  clkdiv--��Ƶ����
����ֵ  : ��
********************************************/
void Set_mode(uchar config,uchar clkdiv)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0xF3);		//�������ģʽָ��
	Delayus(1);
	OutB(DAT,config);	//��������ֽ���Ϣ
	OutB(DAT,clkdiv);	//���ʱ�ӷ�Ƶ�����ֽ�

	if(USB_FLAG.in_isr == 0)
		EN_GINT();	
}
/*******************************************
��������: Set_DMA
��    ��: ����DMA������ʽ����
��    ��: bMode--����ֵ
����ֵ  : ��
********************************************/
void Set_DMA(uchar bMode)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD, 0xFB);	//����DMA����������
	Delayus(1);
	OutB(DAT, bMode);	//�������ֵ

	if(USB_FLAG.in_isr == 0)
		EN_GINT();			
}

/*******************************************
��������: Read_IntR
��    ��: ��ȡ�жϼĴ���ֵ
��    ��: ��
����ֵ  : intreg--16λ�жϼĴ���ֵ
********************************************/
uint Read_IntR(void)
{
	uchar regl;
	uint  intreg;

	OutB(CMD,0xF4);	        //��ȡ�жϼĴ�������
	Delayus(5);
	regl=InB( );			//��ȡ��8λ�ֽ�
	intreg=InB( );			//��ȡ��8λ�ֽ�

	intreg<<=8;
	intreg+=regl;			//���Ϊ16λ

	return intreg;
}
/*******************************************
��������: Sel_EP
��    ��: �˵�ѡ��,���ڲ�ָ���ʼ����ѡ��Ļ�������ʼλ��
��    ��: endp--�˵�������,ȡֵ0 ~ 5
����ֵ  : byte--һ���ֽڵķ�������
********************************************/
uchar Sel_EP(uchar endp)
{
	uchar byte;
    
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,endp);	//�˵�ѡ��
	Delayus(1);
	byte=InB( );	//����һ���ֽ�

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return byte;
}
/*******************************************
��������: Sel_EP
��    ��: ��ȡ�˵�״̬
��    ��: endp--�˵�������,ȡֵ0 ~ 5
����ֵ  : status--�˵�״̬
********************************************/
uchar Read_EPsta(uchar endp)//-----------------
{
	uchar status;

	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0x80+endp);	//��ȡ�˵�״̬����
	status=InB( );		    //��ȡ�˵�״̬

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return status;
}
/*******************************************
��������: Read_LttransSta
��    ��: ��ȡ�����״̬�Ĵ���
��    ��: endp--�˵�������,ȡֵ0 ~ 5
����ֵ  : status--�˵�������״̬
********************************************/
uchar Read_LttransSta(uchar endp)
{
 	uchar status;
    
	OutB(CMD,0x40+endp);	//�����ȡ�����״̬�Ĵ�������
	Delayus(5);
	status=InB( );
	return status;		    //��ȡ״̬
}
/*******************************************
��������: Set_EPsta
��    ��: ���ö˵�״̬
��    ��: endp--�˵�������,ȡֵ0 ~ 5
	  	  stall--����״ֵ̬
����ֵ  : ��
********************************************/
void Set_EPsta(uchar endp,uchar stall)
{
	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,0x40+endp);	//�������ö˵�״̬����
	Delayus(1);
	OutB(CMD,stall);	    //���ö˵�״̬

	if(USB_FLAG.in_isr == 0)
		EN_GINT();
}
/*******************************************
��������: Set_Sresume
��    ��: ���÷��ͻָ�
��    ��: ��
����ֵ  : ��
********************************************/
void Set_Sresume(void)
{
	OutB(CMD,0xF6);		//���÷��ͻָ�
}
/*******************************************
��������: Read_EP
��    ��: ��ȡ�˵�����
��    ��: endp--�˵�������,ȡֵ 0 ~ 5 
	  	  len--Ҫ��ȡ�����ݳ���
		  buf--��������ָ��					   
����ֵ  : num--ʵ�ʶ������ֽ���
********************************************/
uchar Read_EP(uchar endp,uchar len,uchar * buf)
{
	uchar i,num;

	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,endp);				//����ѡ��˵�����
	Delayus(1);
	if((InB( )&FULLEMPTY)==0)   //���������Ϊ�� 
	{	
		if(USB_FLAG.in_isr == 0)
		EN_GINT();
		return 0;			    //�򷵻ض���0�ֽ�
	}

	OutB(CMD,0xF0);			    //���Ͷ�����������
	Delayus(1);
	num=InB( );				    //��ȡ�����ֽ�
	num=InB( );				    //��ȡ�����ֽڵ���Ŀ/����

	if(num>len)				    //�������Ҫ������ֽ���Ŀ
	{
		num=len;			    //��ֻ��ȡҪ����ֽڳ���
	}
	for(i=0; i<num; i++)
		*(buf+i)=InB( );		//��ȡҪ����ֽ���Ŀ/����

	OutB(CMD,0xF2);				//�建����,�µ���Ϣ���ſ������±�����

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return num;				    //���ض������ֽ���
}
/*******************************************
��������: Write_EP
��    ��: ������д��˵�
��    ��: endp--�˵�������,ȡֵ 0 ~ 5 
	  	  len--Ҫд������ݳ���
		  buf--��������ָ��					   
����ֵ  : num--ʵ��д����ֽ���
********************************************/
uchar Write_EP(uchar endp,uchar len,uchar * buf)
{
	uchar i;

	if(USB_FLAG.in_isr == 0)
		UEN_GINT();

	OutB(CMD,endp);			//����ѡ��˵�����
	Delayus(1);
	i=InB( );			    //��ѡ�ض�ȡһ���ֽ�

	OutB(CMD,0xF0);			//����д����������	
	Delayus(1);
	OutB(DAT,0);			//д��һ�������ֽ�
	Delayus(1);
	OutB(DAT,len);			//д�뼴��д����ֽ���Ŀ
	Delayus(1);

	for(i=0; i<len; i++)
	{
		OutB(DAT,*(buf+i));	//д��ָ�����ֽ�
	}
	Delayus(1);
	OutB(CMD,0xFA);			//ʹ��������Ч

	if(USB_FLAG.in_isr == 0)
		EN_GINT();

	return len;				//����д����ֽ���
}
/*******************************************
��������: Ack_EP
��    ��: Ӧ��Setup
��    ��: endp--�˵�������,ȡֵ 0 ~ 5 	   
����ֵ  : ��
********************************************/
void Ack_EP(uchar endp)
{
	OutB(CMD,endp);			//ѡ��˵�
	Delayus(1);
	OutB(CMD,0xF1);			//Ӧ��Setupָ��
	Delayus(1);
	if(endp==0)	
	{	
		OutB(CMD,0xF2);		//��ոö˵㻺����
	}
}
/*******************************************
��������: Clear_buf
��    ��: ��ָ���˵�Ļ�����(����˫������)
��    ��: endp--�˵�������,ȡֵ 0 ~ 5 	   
����ֵ  : ��
********************************************/
void Clear_buf(uchar endp)
{	
   	OutB(CMD,endp);			//ѡ��˵�
	Delayus(1);
	OutB(CMD,0xF2);			//��յ�1��������	
	
	if (endp>=4)
	{
   		OutB(CMD,endp);		//ѡ��˵�
		Delayus(1);
		OutB(CMD,0xF2);		//��յ�2��������	
	}
}
/*******************************************
��������: Stall_ep0
��    ��: ʹ���ƶ˵㴦��ֹͣ״̬
��    ��: ��   
����ֵ  : ��
********************************************/
void Stall_ep0(void)
{
	Set_EPsta(0,1);
	Set_EPsta(1,1);
}
/*******************************************
��������: S_trans
��    ��: ͨ���˵����� 1 ��������(DATA ����)
��    ��: buf--��������ָ��
		  len--�������ݳ���   
����ֵ  : ��
********************************************/
void S_trans(uchar * buf, uchar len)
{
	if(len<=EP0_PACKET_SIZE) //����С��EP0�����Ϣ����С��������
	{			
		Write_EP(1,len,buf);
	}
}
/*******************************************
��������: Code_trans
��    ��: ͨ���˵����� 1 ��������(CODE����)
��    ��: buf--��������ָ��
		  len--�������ݳ���   
����ֵ  : ��
********************************************/
void Code_trans(uchar *pRomData, uint len)
{
	ControlData.wCount = 0;								//�����ֽ�����������0
	if(ControlData.wLength > len)
		ControlData.wLength = len;						//�����������ֽ������ó���len

	ControlData.pData = pRomData;						//��������ָ��ָ��pRomData
	if( ControlData.wLength >= EP0_PACKET_SIZE)         //�����������ֽ������ڶ˵�0�����Ϣ����С
	{		
		Write_EP(1, EP0_PACKET_SIZE, ControlData.pData);//���Ͷ˵�0�����Ϣ����С���ֽ�
		ControlData.wCount += EP0_PACKET_SIZE;			//ͳ���ѷ����ֽ���

		UEN_GINT();
		USB_FLAG.control_state = USB_TRANSMIT;	        //��־���ݷ���״̬			
		EN_GINT();
	}
	else 
	{
		Write_EP(1, ControlData.wLength, pRomData);	    //д�봫���������ֽ���
		ControlData.wCount += ControlData.wLength;	    //ͳ���ѷ����ֽ���
		UEN_GINT();
		USB_FLAG.control_state = USB_IDLE;		        //��־����״̬
		EN_GINT();
	}
}
/*******************************************
��������: USB_INT1
��    ��: D12�жϷ�����
��    ��: ��   
����ֵ  : ��
********************************************/
#pragma vector=PORT1_VECTOR 
__interrupt void USB_INT1(void)
{
    uint int_sta;
   
    if((USBINT_IFG & BIT(D12_INT))==BIT(D12_INT))
    {
            USBINT_IFG&=~BIT(D12_INT);  //����жϱ�־
    
            USB_FLAG.in_isr = 1;
            int_sta=Read_IntR();	    //��ȡPDIUSBD12�жϼĴ���ֵ
          
            if(int_sta!=0) 
            {
                    if(int_sta&INT_BUSRESET)
                            USB_FLAG.bus_reset=1;	//USB���߸�λ��־	
                    if(int_sta&INT_ENDP0IN)
                            Ep0_txdone();		//���ƶ˵㷢�����ݴ���
                    if(int_sta&INT_ENDP0OUT)
                            Ep0_rxdone();		//���ƶ˵�������ݴ���
                    if(int_sta&INT_ENDP1IN)
                            Ep1_txdone();		//�˵� 1�������ݴ���
                    if(int_sta&INT_ENDP1OUT)
                            Ep1_rxdone();		//�˵� 1�������ݴ���
                    if(int_sta&INT_ENDP2IN)
                            Ep2_txdone();		//�˵� 2�������ݴ���
                    if(int_sta&INT_ENDP2OUT)
                            Ep2_rxdone();		//�˵� 2�������ݴ���
            }
            USB_FLAG.in_isr = 0;
    }
}
/*******************************************
��������: Ep0_rxdone
��    ��: ͨ���˵����� 0 ��������
��    ��: ��   
����ֵ  : ��
********************************************/
void Ep0_rxdone(void)
{
	uchar ep_last,i;
	ep_last=Read_LttransSta(0);     //����жϼĴ���״̬,ȡ�������״̬
	if (ep_last&SETUPPACKET) 
	{				                //����յ��˽�����(Setup��)
		ControlData.wLength=0;	    //�����ֽ�������0
		ControlData.wCount=0;	    //�����ֽڼ�������0
		if(Read_EP(0,sizeof(ControlData.DeviceRequest),(uchar * )(&(ControlData.DeviceRequest)))!= sizeof(DEVICE_REQUEST))//�Ӷ˵�0��8���ֽ�ʧ�� 
		{												 		 
			Set_EPsta(0,1);			//ֹͣ���ƶ˵�0
			Set_EPsta(1,1);			//ֹͣ���ƶ˵�1
			USB_FLAG.control_state = USB_IDLE;	 //����Ϊ�ȴ�״̬
			return;
		}		
		/********  ���ս������ɹ� **********/
		Ack_EP(0);						 //�Կ��ƶ˵�0���н�����Ӧ��
		Ack_EP(1);						 //�Կ��ƶ˵�1���н�����Ӧ��
		ControlData.wLength=ControlData.DeviceRequest.wLength; 	 //ȡ��Ҫ�������ݵ����ֽ���
		ControlData.wCount = 0;
        
		//������ƴ����ǿ��ƶ�ȡ
		if(ControlData.DeviceRequest.bmRequestType&(uchar)USB_ENDPOINT_DIRECTION_MASK) 
		{

			 USB_FLAG.setup_packet=1;		        //֪ͨcontrol_handler()����Setup��
			 USB_FLAG.control_state=USB_TRANSMIT;	//����Ϊ����״̬
		}
		else    //������ƴ����ǿ���д��
		{						
			  if(ControlData.DeviceRequest.wLength==0) 
			  {
				  USB_FLAG.setup_packet=1;		    //֪ͨcontrol_handler()����Setup��				  
				  USB_FLAG.control_state=USB_IDLE;	//����Ϊ�ȴ�״̬
			  }
			  else 
			  {     //������ݳ��ȳ���
				    if(ControlData.DeviceRequest.wLength>MAX_CTLDAT_SIZE) 
				    {				         
					     USB_FLAG.control_state=USB_IDLE;	//����Ϊ�ȴ�״̬	
					     Set_EPsta(0,1);			        //ֹͣ���ƶ˵�0
				 	     Set_EPsta(1,1);			        //ֹͣ���ƶ˵�1
				    }
				    else
				    {
					    USB_FLAG.control_state=USB_RECEIVE;  //����Ϊ����״̬
				    }
			  }// set command with data
		 }// else set command
	}// if setup packet

/*************������Ϊ����д������ݽ׶�  ***************/
	else if(USB_FLAG.control_state==USB_RECEIVE)     //���Ϊ����״̬
	{	  	    
			 i=Read_EP(0,EP0_PACKET_SIZE,ControlData.dataBuffer+ControlData.wCount);	//�Ӷ˵�0��������
			 ControlData.wCount+=i;					 //ͳ���ѽ��յ��ֽ���
			 if(i!=EP0_PACKET_SIZE||ControlData.wCount>=ControlData.wLength) //���ݽ������
			 {  		                                  
				 USB_FLAG.setup_packet=1;		    //֪ͨcontrol_handler()����Setup��				  
				 USB_FLAG.control_state=USB_IDLE;	//����Ϊ�ȴ�״̬
			 }
	}
	else 
	{
		 	 USB_FLAG.control_state = USB_IDLE;		//���õȴ�״̬
	}
}
/*******************************************
��������: Ep0_txdone
��    ��: ͨ���˵����� 0 ��������
��    ��: ��   
����ֵ  : ��
********************************************/
void Ep0_txdone(void)
{
	uint i=ControlData.wLength-ControlData.wCount;	  //����δ���͵��ֽ���

	Read_LttransSta(1); 					          //����жϼĴ�����־λ

	if (USB_FLAG.control_state!=USB_TRANSMIT)         //�Ƿ���״̬	
	{	
		return;						//����
	}	
	if(i>=EP0_PACKET_SIZE)  //δ�����ֽ�������16,����16���ֽ�
	{							
		Write_EP(1,EP0_PACKET_SIZE,ControlData.pData+ControlData.wCount);
		ControlData.wCount+= EP0_PACKET_SIZE;
		USB_FLAG.control_state=USB_TRANSMIT;	
	}
	else if(i!=0)           //��������δ���͵��ֽ�
	{							
		Write_EP(1,i,ControlData.pData+ControlData.wCount);
		ControlData.wCount+=i;
		USB_FLAG.control_state=USB_IDLE;		//��״̬Ϊ�ȴ�״̬
	}
	else if (i == 0)
	{
		Write_EP(1, 0, 0); 				        //�������,��0���ֽ�
		USB_FLAG.control_state = USB_IDLE;
	}
}
/*******************************************
��������: Ep1_txdone
��    ��: �˵�1���ʹ�����
��    ��: ��   
����ֵ  : ��
********************************************/
void Ep1_txdone(void)
{
	Read_LttransSta(3);		//���жϱ�־λ
}
/*******************************************
��������: Ep1_rxdone
��    ��: �˵�1���մ�����
��    ��: ��   
����ֵ  : ��
********************************************/
void Ep1_rxdone(void)
{
	uchar len;

	Read_LttransSta(2);		                //���жϱ�־λ
	len=Read_EP(2,sizeof(Ep1Buf),Ep1Buf);	//��ȡ����
	if(len!=0)
		USB_FLAG.ep1_rxdone = 1;		    //��־���յ�����
}
/*******************************************
��������: Ep2_txdone
��    ��: �˵�2���ʹ�����
��    ��: ��   
����ֵ  : ��
********************************************/
void Ep2_txdone(void)
{
	Read_LttransSta(5);		//���жϱ�־λ
}
/*******************************************
��������: Ep2_rxdone
��    ��: �˵�2���մ�����
��    ��: ��   
����ֵ  : ��
********************************************/
void Ep2_rxdone(void)
{
	uchar len;
	
	Read_LttransSta(4); 			        //���жϱ�־λ
	len=Read_EP(4,EP2_PACKET_SIZE,Ep2Buf);	//��ȡ�������е�����
	if (len!=0)
		USB_FLAG.ep2_rxdone = 1;
}
/*******************************************
��������: Control_handler
��    ��: ���ƴ���
��    ��: ��   
����ֵ  : ��
********************************************/
void Control_handler(void)
{
	uchar type,req; 
	
	type=ControlData.DeviceRequest.bmRequestType&USB_REQUEST_TYPE_MASK;
											//��ȡ�������													
	req=ControlData.DeviceRequest.bRequest&USB_REQUEST_MASK;
	if(type==USB_STANDARD_REQUEST)
		(*StandardDeviceRequest[req])();	//��׼������
	else
		Stall_ep0();				        //��Ч����,����STALL				
}
/*******************************************
��������: Reserved
��    ��: �����ӳ���
��    ��: ��   
����ֵ  : ��
********************************************/
void Reserved(void)
{
	Stall_ep0();				//����STALL
}
/*******************************************
��������: Init_unconfig
��    ��: �����ַ״̬,��ֹ0��������ж˵�
��    ��: ��   
����ֵ  : ��
********************************************/
void Init_unconfig(void)
{
	Set_EPen(0);	//��ֹ0��������ж˵�
}
/*******************************************
��������: Init_config
��    ��: ���ô���,����˵��շ�
��    ��: ��   
����ֵ  : ��
********************************************/
void Init_config(void)
{
	Set_EPen(1);	//ʹ����ͨ/ͬ���˵�ʹ��
}
/*******************************************
��������: Get_status
��    ��: ����Ҫ���ȡ״̬,�豸����16λ��״̬����������
��    ��: ��   
����ֵ  : ��
********************************************/
void Get_status(void)
{
	uchar endp,txdat[2],c;
	uchar bRecipient=ControlData.DeviceRequest.bmRequestType&USB_RECIPIENT;	//ȡ���豸��������	
						
	if (bRecipient==USB_RECIPIENT_DEVICE)//���豸���� 
	{					
		if(USB_FLAG.remote_wakeup==1)			
		{
			txdat[0]=3;		//֧��Զ�̻��ѡ��Թ���
		}
		else
		{
			txdat[0]=1;		//��֧��Զ�̻��ѡ��Թ���
		}
		txdat[1]=0;			//��8λΪ0
		S_trans(txdat,2);	//����16λ��״̬������
		
	} 
	else if (bRecipient == USB_RECIPIENT_INTERFACE) //�Խӿ�����
	{			
		txdat[0]=0;
		txdat[1]=0;
		S_trans(txdat, 2);	//����16λ��״̬������
						
	} 
	else if (bRecipient == USB_RECIPIENT_ENDPOINT) //�Զ˵�����
	{			
		endp = (uchar)(ControlData.DeviceRequest.wIndex & MAX_ENDPOINTS);
		if (ControlData.DeviceRequest.wIndex & (uchar)USB_ENDPOINT_DIRECTION_MASK)
		{
			c = Sel_EP(endp*2+1);	//��ȡ����˵�״̬
		}
		else
		{
			c = Sel_EP(endp*2);		//��ȡ����˵�״̬
		}
		if(c & STALL)
		{
			txdat[0] = 1;			//�˵��ֹ
		}
		else
		{
			txdat[0] = 0;			//�˵���Ч
		}
		txdat[1] = 0;
		S_trans(txdat, 2);			//����16λ��״̬������

	} 
	else
	{
		Stall_ep0();				//�Ǳ�׼����,��STALL
	}
}
/*******************************************
��������: Clr_feature
��    ��: �������
��    ��: ��   
����ֵ  : ��
********************************************/
void Clr_feature(void)
{
	uchar endp;					//��ȡ���������еĽ��շ�
	uchar bRecipient = ControlData.DeviceRequest.bmRequestType & USB_RECIPIENT; //��ȡ��������
										
	if (bRecipient == USB_RECIPIENT_DEVICE  //���豸����
	&&ControlData.DeviceRequest.wValue==USB_FEATURE_REMOTE_WAKEUP) //���Զ�̻�������	
	{
		UEN_GINT();								
		USB_FLAG.remote_wakeup = 0;			//��0Զ�̻��ѱ�־
		EN_GINT();
		S_trans(0,0);						//����һ���յ����ݱ�ʾִ�����
	}
	
	else if (bRecipient == USB_RECIPIENT_ENDPOINT   //�Զ˵�����
		&& ControlData.DeviceRequest.wValue == USB_FEATURE_ENDPOINT_STALL) //����˵��ֹ����,�ָ���ʹ��
	{
		
		endp = (uchar)(ControlData.DeviceRequest.wIndex & MAX_ENDPOINTS);
		if (ControlData.DeviceRequest.wIndex & (uchar)USB_ENDPOINT_DIRECTION_MASK)
		{
			Set_EPsta(endp*2 + 1, 0);			    //�����������˵�STALL����
		}
		else
		{
			Set_EPsta(endp*2, 0);				    //�����������˵�STALL����
		}
		S_trans(0, 0);						        //����һ���յ����ݱ�ʾִ�����
	} 
	else
	{
		Stall_ep0();					            //û�и�����,����STALL	
	}						
}
/*******************************************
��������: Set_feature
��    ��: ��������
��    ��: ��   
����ֵ  : ��
********************************************/
void Set_feature(void)
{
	uchar endp;		//��ȡ���������еĽ��շ�							
	uchar bRecipient = ControlData.DeviceRequest.bmRequestType & USB_RECIPIENT;//��ȡ��������
											
	if (bRecipient == USB_RECIPIENT_DEVICE  //���豸����
		&& ControlData.DeviceRequest.wValue == USB_FEATURE_REMOTE_WAKEUP) //����Զ�̻�������
	{														
		UEN_GINT();
		USB_FLAG.remote_wakeup = 1;				//��1Զ�̻��ѱ�־
		EN_GINT();
		S_trans(0, 0);						    //����һ���յ����ݱ�ʾִ�����
	}		
	else if (bRecipient == USB_RECIPIENT_ENDPOINT //�Զ˵�����
		&& ControlData.DeviceRequest.wValue == USB_FEATURE_ENDPOINT_STALL) //��ֹ�˵�
	{		
		endp = (uchar)(ControlData.DeviceRequest.wIndex & MAX_ENDPOINTS);
		if (ControlData.DeviceRequest.wIndex & (uchar)USB_ENDPOINT_DIRECTION_MASK)
		{
			Set_EPsta(endp*2 + 1, 1);		//��������˵��ֹ
		}
		else
		{
			Set_EPsta(endp*2, 1);			//��������˵��ֹ
		}
		S_trans(0, 0);					    //����һ���յ����ݱ�ʾִ�����
	} 
	else
	{
		Stall_ep0();					    //û�и�����,����STALL
	}
}
/*******************************************
��������: Set_addr
��    ��: ���õ�ַ
��    ��: ��   
����ֵ  : ��
********************************************/
void Set_addr(void)
{
	Set_addren((uchar)(ControlData.DeviceRequest.wValue&DEVICE_ADDRESS_MASK), 1);
	S_trans(0, 0);				//����һ���յ�������Ӧ
}
/*******************************************
��������: Get_descriptor
��    ��: ��ȡ������
��    ��: ��   
����ֵ  : ��
********************************************/
void Get_descriptor(void)
{
	uchar bDescriptor = MSB(ControlData.DeviceRequest.wValue); //��ȡ���������������

	if (bDescriptor == USB_DEVICE_DESCRIPTOR_TYPE) //��ȡ�豸������
	{						
		Code_trans((uchar *)&DeviceDescr, sizeof(USB_DEVICE_DESCRIPTOR));
	
	}
	else if (bDescriptor == USB_CONFIGURATION_DESCRIPTOR_TYPE) //��ȡ����������
	{		
		  		if (ControlData.DeviceRequest.wLength > CONFIG_DESCRIPTOR_LENGTH)
				{ 
					 ControlData.DeviceRequest.wLength = CONFIG_DESCRIPTOR_LENGTH;
				}   //��������������
			    Code_trans((uchar *)&(usb_descr.ConfigDescr), ControlData.DeviceRequest.wLength);
			    				
	}
	else
	{
			Stall_ep0();			//û�и�����,����STALL
	}
	 
}
/*******************************************
��������: Get_config
��    ��: ��ȡ����
��    ��: ��   
����ֵ  : ��
********************************************/
void Get_config(void)
{
	uchar c = USB_FLAG.configuration;	//ȡ������ֵ
		
	S_trans(&c, 1);				        //��������ֵ
}
/*******************************************
��������: Set_config
��    ��: ��������
��    ��: ��   
����ֵ  : ��
********************************************/
void Set_config(void)
{
	if (ControlData.DeviceRequest.wValue == 0) //����ֵ����,�豸����δ����״̬
	{			
		S_trans(0, 0);			    //����һ���հ���Ӧ
		UEN_GINT();
		USB_FLAG.configuration = 0;	//���δ����
		EN_GINT();
		Init_unconfig();			//�����ַ״̬,��ֹ0��������ж˵�
		
	} 
	else if (ControlData.DeviceRequest.wValue == 1) //�����豸
	{		
		S_trans(0, 0);			    //����һ���հ���Ӧ
		Init_unconfig();			//�����ַ״̬,��ֹ0��������ж˵�
		Init_config();				//���ô���,����˵��շ�
		UEN_GINT();
		USB_FLAG.configuration = 1;	//��־������
		EN_GINT();
	} 
	else
	{
		Stall_ep0();			    //û�и�����,����STALL
	}
}
/*******************************************
��������: Get_interface
��    ��: ��ȡ�ӿ���Ϣ
��    ��: ��   
����ֵ  : ��
********************************************/
void Get_interface(void)
{
	uchar txdat = 0;		        //���豸ֻ��һ���ӿ�
	S_trans(&txdat, 1);		        //����һ���ֽ�
}
/*******************************************
��������: Set_interface
��    ��: ���ýӿ���Ϣ
��    ��: ��   
����ֵ  : ��
********************************************/
void Set_interface(void)
{
	if (ControlData.DeviceRequest.wValue == 0 && ControlData.DeviceRequest.wIndex == 0)
	{
		S_trans(0, 0);		        //����һ���յ����ݱ�ʾִ�����
	}
	else		
	{
		Stall_ep0();		        //û�и�����,����STALL	
	}				
}
/*******************************************
��������: USB_connect
��    ��: ����USB����
��    ��: ��   
����ֵ  : ��
********************************************/
void USB_connect(void)
{
    //SoftConnect ������,������Ϊ��LazyClock,ģʽΪ��ͬ��ģʽ
	Set_DMA(0x00);
	Set_mode(NOLAZYCLOCK|SOFTCONNECT, SETTOONE | CLOCK_12M);
}	

/*******************************************
��������: Set_interface
��    ��: ���ýӿ���Ϣ
��    ��: ��   
����ֵ  : ��
********************************************/
void USB_disconnect(void)
{
	//SoftConnect �Ͽ�
	Set_mode(NOLAZYCLOCK, SETTOONE | CLOCK_12M);
}	
/*******************************************
��������: USB_reconnect
��    ��: ��������USB����
��    ��: ��   
����ֵ  : ��
********************************************/
void USB_reconnect(void)
{
	USB_disconnect();	//�Ͽ�оƬ��USB��������
	Delayms(200);
	Set_addren(0,1);
	Set_EPen(1);
    USB_connect();		//���ӵ�USB����
}
/*******************************************
��������: Read_chipID
��    ��: ��ȡоƬ��ID
��    ��: ��   
����ֵ  : ��
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
