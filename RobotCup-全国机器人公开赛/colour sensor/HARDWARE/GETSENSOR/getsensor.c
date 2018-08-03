#include <stm32f10x_lib.h>	   
#include "getsensor.h"

void GPIO_Configuration(void);	
void RCC_Configuration(void);
void ADC1_Configuration(void);
void DMA_Configuration(void);	  
void filter(u8 num);
	   
//使能这AB口的时钟		    
//IO初始化
vu16  AD_Value[N];   //用来存放ADC转换结果，也是DMA的目标地址
vu16  After_filter[M];    //用来存放求平均值之后的结果

void Sensor_Init(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	ADC1_Configuration();
	DMA_Configuration();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);	 //启动DMA通道									 
}

/*
**函数功能：GPIO管脚的配置
**GPIO引脚：
**16路模拟	GPIOA.0~7		   22路数字口	GOIOA.8
**			GPIOB.0~1						GPIOB.10~15
**			GPIOC.0~5						GPIOC.7~9
**											GPIOD.8~15
**											GPIOE.8、10、12、15							
*/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//16路模拟口                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//22路数字口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//数字上拉输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//数字上拉输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//数字上拉输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//数字上拉输入引脚
	GPIO_Init(GPIOD, &GPIO_InitStructure);
                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//数字上拉输入引脚
	GPIO_Init(GPIOE, &GPIO_InitStructure);


}

/*配置系统时钟,使能各外设时钟*/
void RCC_Configuration(void)
{
	 /*使能各个外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
	/* Configure ADCCLK such as ADCCLK = PCLK2/6 */ 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC最大时间不能超过14M
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
}
 

/*配置ADC1*/
void ADC1_Configuration(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
	ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode =ENABLE;	//模数转换工作在扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//外部触发转换关闭
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = M;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器	

	/* ADC1 regular channel11 configuration */ 
	//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
	//ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期
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

	// 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
    ADC_DMACmd(ADC1, ENABLE);	
	
	/* Enable ADC1 */
	 ADC_Cmd(ADC1, ENABLE);	   //使能指定的ADC1
	 /* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);	  //复位指定的ADC1的校准寄存器
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1复位校准寄存器的状态,设置状态则等待
	
	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);		//开始指定ADC1的校准状态
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待	
}

/*配置DMA*/
void DMA_Configuration(void)
{
	/* ADC1  DMA1 Channel Config */
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);   //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr =  (u32)&ADC1->DR;  //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = N*M;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道
}


/*求平均值函数*/
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
**函数功能：获取X通道AD值（0~1023）
**参数    ：channel---模拟口通道号		  
**参数取值：	1~16
*/
u16 analog(u8 channel)
{	
 	filter(channel - 1);
	return 	After_filter[channel-1];	  	
}

/*
**函数功能：获取X通道数字值（0，1）		  
**参数	  ：channel---数字口通道号
**参数取值：	1~22
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
