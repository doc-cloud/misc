#ifndef __REMOT_H
#define __REMOT_H 

#include "user.h"  

/***********************
162 098 226
034 002 194
224 168 144
104 152 176
048 024 122
016 056 090
066 074 082  
��ֵ
*************************/  
#define RDATA PEin(7)	 //�������������
//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      

extern u8 Remote_Cnt;    //��������,�˴ΰ��¼��Ĵ���
extern u8 Remote_Rdy;    //������յ����� 
extern u32 Remote_Odr;   //�����ݴ洦
void Remote_Init(void);    //���⴫��������ͷ���ų�ʼ��
u8 Remote_Process(void);   //������յ����ݴ���
u8 Pulse_Width_Check(void);//�������

//#define Key_stop 162     //�û��Զ���ֹͣ��ť��(1~20��		  
	
#endif

