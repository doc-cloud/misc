#ifndef __COMPASS_H
#define __COMPASS_H
#include "sys.h"
#include "delay.h" 
  	   		   
//指南针 IO方向设置
#define SDA_IN()  {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=0X00800000;}
#define SDA_OUT() {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=0X00300000;}

//指南针 IO操作函数	 
#define SCL    PEout(6) //SCL
#define SDA    PCout(13) //SDA	 
#define READ_SDA  PCin(13)  //输入SDA   

//指南针函数

//void SetDegree(u16 degree);	 //设置当前指南针方向的值 参数degree: 0至359
//void ShowDegree(void);		 //显示当前指南针方向的值

void Compass_Init(void);	//指南针初始化
void cal_on(void);	//校准
void CMP_OFFS(void);//修改指南针磁偏角值
void cal_off(void); //关闭校准
u16 read_cmp(void);	 //获取角度值


void recovery_factory(void); //恢复出厂设置	


#endif
