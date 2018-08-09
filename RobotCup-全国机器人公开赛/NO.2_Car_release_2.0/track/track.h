#ifndef _TRACK_H_
#define _TRACK_H_



void Track_steep_line(void);	//ǰ����ѭ��
void Track_steep_turn(void);	//���˵�ѭ��
void Track_wheel_left(void);	//ֱ����ת
void Track_wheel_right(void);	//ֱ����ת
void Track_straight_line(void);//��ֱ��
void Track_steep_low(void);		//������ֱ��
int intersection(int view);//�ж�ʶ��·��

int my_intersection(int view);

void mid_stop(int r1);		//·��ͣ��

void mid_stop_nottrack(void);//�޹켣·�η���·��ֹͣ

void Track_path_stop(unsigned char flag);//תֱ�Ǻ�ֹͣ���޹켣·�Σ�
//������void Track_before_stop(void);//תֱ��ǰֹͣ���޹켣·�Σ�
void Track_round_stop(unsigned char flag);	//��ԲȦ�߽�ֹͣ


void Track_crash_ward(void);	//��ײ

void Trcak_ranging_point(unsigned char flag);//������

void Track_rear_20cm(void);		//20cm�ٸ�
void Track_rear_50cm(void);		//50cm�ٸ�
void Track_rear_clamp(int flag);//�гֱ���
void Trcak_ranging_cup(void);	//�������Ɑ��

void Track_steep_cmp(unsigned char flag);		//ָ������ֱ��

void switch_car1(int enn);	//��ȫ��  �����1---3
void switch_car2(int enn);	//��ȫ��  �����1---2
void switch_car3(int enn);	//��ȫ��  �����2---3
void switch_car4(int enn);	//��ȫ��  �����3---1 ����---��S4����S1
void switch_car5(int enn);	//��ȫ��  �����2---1 ����---��S4����S2
void switch_car6(int enn);	//��ȫ��  �����3---2 ����---��S4����S3

#endif
