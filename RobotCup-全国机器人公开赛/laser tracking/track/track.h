#ifndef	_TRACK_H_
#define _TRACK_H_

#include "SuperSharkV1.0.h"

#define D(channel) DigitalIn(channel)  //���ֿں궨��


u8 An_to_Di(u8 channel,u16 num1,u16 num2);//ģ��ͨ��ֵת����ֵ
//4·���ͬʱ���ƺ���
void DMotor_Control(u8 D1,s8 DP1,u8 D2,s8 DP2,u8 D3,s8 DP3,u8 D4,s8 DP4);
void DMotor_Control_Par(s8 left,s8 right);//���˫�в��п���
void Track_steep_line(void);//ֱ��ǰ����ѭ�� --����
void Track_steep_Moderato(void);//ֱ�ߵ���ǰ������ѭ��
void Track_steep_Moderato_low(void);//ֱ�ߵ���ǰ��������ѭ��
void Track_steep_low(void);//ֱ�ߵ���ǰ������ѭ��
void Track_steep_turn(void);//ֱ�ߺ��˵�ѭ�� --����
void Track_steep_turn_Moderato(void);//ֱ�ߺ������ٵ�ѭ��
void Track_steep_turn_Moderato_low(void);//ֱ�ߺ��������ٵ�ѭ��
void Track_steep_turn_low(void);//ֱ�ߺ������ٵ�ѭ��
void Track_steep_WavyLine(unsigned char direction);//������ѭ��
void Track_round(unsigned char direction);//�ߴ�Բ

void Track_wheel_left(unsigned char num,unsigned char angle);//��ת��
void Track_wheel_right(unsigned char num,unsigned char angle);//��ת��
void Track_wheel_left180(void);//ƽ̨�;���180����ת

void Track_straight_line(unsigned char speed);//��ֱ��
//ָ������ֱ��
void Track_steep_cmp(unsigned char num,unsigned int floor,unsigned int upper_limit);

void Track_steep_Diaoyu_Islands(void);//���㵺����

int my_intersection(int view);//�ж�ʶ��·��
void mid_stop(int r1);//·��ֹͣ
void Track_crash_ward(void);//������ײ 
//ָ������ײ����
void Track_cmp_ward(unsigned char num,unsigned int floor,unsigned int upper_limit);
int Track_JudgeBarrier_Place(int flag);//�ж�С�����ϰ����λ��

void Fork_road_intersection(unsigned char flag);//����·�ڼ��

void Track_Triaxial_Uphill(unsigned int floor,unsigned int upper_limit);//����������




/*�������⴦��·�κ���*/  
//���ź���
//1.ȥ���ص��㵺
//2.ȥ����̫ƽ��
void Track_GapBridge(unsigned int floor,unsigned int upper_limit);
//ȥ��ƽ̨����  
//1.�ӵ��㵺����������---->�ӳ���������	0
//2.����5����ȥ������	0
//3.ȥ��ɽ			  0
//4.ȥ̫��			  1
//ȥ�޽���ƽ̨�;���
void Track_Speaicl_BridgeZM_to(unsigned char flag);
void Track_Taiping_To(void);	   
//���˹��ż�
void Track_Doorsill_Turn(void);	
//ǰ�����ż�
void Track_Doorsill_line(void);	
//�������ż�
void Track_Doorsill_WavyLine(void); 
//����������岢����
void Track_Qomolangma_To(void);	


#endif

