#ifndef __COMPASS_H
#define __COMPASS_H
#include "sys.h"
#include "delay.h" 
  	   		   
//ָ���� IO��������
#define SDA_IN()  {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=0X00800000;}
#define SDA_OUT() {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=0X00300000;}

//ָ���� IO��������	 
#define SCL    PEout(6) //SCL
#define SDA    PCout(13) //SDA	 
#define READ_SDA  PCin(13)  //����SDA   

//ָ���뺯��

//void SetDegree(u16 degree);	 //���õ�ǰָ���뷽���ֵ ����degree: 0��359
//void ShowDegree(void);		 //��ʾ��ǰָ���뷽���ֵ

void Compass_Init(void);	//ָ�����ʼ��
void cal_on(void);	//У׼
void CMP_OFFS(void);//�޸�ָ�����ƫ��ֵ
void cal_off(void); //�ر�У׼
u16 read_cmp(void);	 //��ȡ�Ƕ�ֵ


void recovery_factory(void); //�ָ���������	


#endif
