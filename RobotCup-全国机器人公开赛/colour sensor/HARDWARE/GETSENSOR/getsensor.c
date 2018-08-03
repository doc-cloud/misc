#include <stm32f10x_lib.h>	   
#include "getsensor.h"

void GPIO_Configuration(void);	
void RCC_Configuration(void);
void ADC1_Configuration(void);
void DMA_Configuration(void);	  
void filter(u8 num);
	   
//ʹ����AB�ڵ�ʱ��		    
//IO��ʼ��
vu16  AD_Value[N];   //�������ADCת�������Ҳ��DMA��Ŀ���ַ
vu16  After_filter[M];    //���������ƽ��ֵ֮��Ľ��

void Sensor_Init(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	ADC1_Configuration();
	DMA_Configuration();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);	 //����DMAͨ��									 
}

/*
**�������ܣ�GPIO�ܽŵ�����
**GPIO���ţ�
**16·ģ��	GPIOA.0~7		   22·���ֿ�	GOIOA.8
**			GPIOB.0~1						GPIOB.10~15
**			GPIOC.0~5						GPIOC.7~9
**											GPIOD.8~15
**											GPIOE.8��10��12��15							
*/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//16·ģ���                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//22·���ֿ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//����������������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//����������������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//����������������
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//����������������
	GPIO_Init(GPIOD, &GPIO_InitStructure);
                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//����������������
	GPIO_Init(GPIOE, &GPIO_InitStructure);


}

/*����ϵͳʱ��,ʹ�ܸ�����ʱ��*/
void RCC_Configuration(void)
{
	 /*ʹ�ܸ�������ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	/* Configure ADCCLK such as ADCCLK = PCLK2/6 */ 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
}
 

/*����ADC1*/
void ADC1_Configuration(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode =ENABLE;	//ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ����ת���ر�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = M;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���	

	/* ADC1 regular channel11 configuration */ 
	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	//ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5 );		
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_239Cycles5 );		
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 14, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 15, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 16, ADC_SampleTime_239Cycles5 );	

	// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
    ADC_DMACmd(ADC1, ENABLE);	
	
	/* Enable ADC1 */
	 ADC_Cmd(ADC1, ENABLE);	   //ʹ��ָ����ADC1
	 /* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);	  //��λָ����ADC1��У׼�Ĵ���
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�
	
	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�	
}

/*����DMA*/
void DMA_Configuration(void)
{
	/* ADC1  DMA1 Channel Config */
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr =  (u32)&ADC1->DR;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = N*M;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
}


/*��ƽ��ֵ����*/
void filter(u8 num)
{
	int  sum = 0;
	u8  count;    

	for(count=0;count<N;count++)
	{
		sum += AD_Value[num];
	}
	After_filter[num]=sum/N;
	sum=0;
}

/*
**�������ܣ���ȡXͨ��ADֵ��0~1023��
**����    ��channel---ģ���ͨ����		  
**����ȡֵ��	1~16
*/
u16 analog(u8 channel)
{	
 	filter(channel - 1);
	return 	After_filter[channel-1];	  	
}

/*
**�������ܣ���ȡXͨ������ֵ��0��1��		  
**����	  ��channel---���ֿ�ͨ����
**����ȡֵ��	1~22
*/
u8 digtal(u8 channel)  	
{
	u8 value = 0;
	switch(channel) 
	{
		case 1:
			if(PEin(8) == 1) value = 1;
			else value = 0;  
			break;
		case 2:  
			if(PEin(10) == 1) value = 1;
			else value = 0;  
			break;  
		case 3: 
			if(PEin(12) == 1) value = 1;
			else value = 0;  
			break;  
		case 4: 
			if(PEin(15) == 1) value = 1;
			else value = 0;  
			break;   
		case 5:  
			if(PBin(10) == 1) value = 1;
			else value = 0;  
			break;   
		case 6: 
			if(PBin(11) == 1) value = 1;
			else value = 0;  
			break;   
		case 7:  
			if(PBin(12) == 1) value = 1;
			else value = 0;  
			break;   
		case 8:  
			if(PBin(13) == 1) value = 1;
			else value = 0;  
			break;  
		case 9: 
			if(PBin(14) == 1) value = 1;
			else value = 0;  
			break;  
		case 10:  
			if(PBin(15) == 1) value = 1;
			else value = 0;  
			break;  
		case 11: 
			if(PDin(8) == 1) value = 1;
			else value = 0;  
			break; 
		case 12:
			if(PDin(9) == 1) value = 1;
			else value = 0;  
			break;   
		case 13: 
			if(PDin(10) == 1) value = 1;
			else value = 0;  
			break;   
		case 14: 
			if(PDin(11) == 1) value = 1;
			else value = 0;  
			break;   
		case 15: 
			if(PDin(12) == 1) value = 1;
			else value = 0;  
			break;   
		case 16: 
			if(PDin(13) == 1) value = 1;
			else value = 0;  
			break;   
		case 17:  
			if(PDin(14) == 1) value = 1;
			else value = 0;  
			break;  
		case 18:  
			if(PDin(15) == 1) value = 1;
			else value = 0;  
			break;  
		case 19:  
			if(PCin(7) == 1) value = 1;
			else value = 0;  
			break; 
		case 20: 
			if(PCin(8) == 1) value = 1;
			else value = 0;  
			break;  
		case 21:  
			if(PCin(9) == 1) value = 1;
			else value = 0;  
			break; 
		case 22: 
			if(PAin(8) == 1) value = 1;
			else value = 0;  
			break;  
	}
	return value; 
}
