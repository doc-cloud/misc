/***********************************************
�����ܣ�ʵ����ˮ��������������ʽ�����������ٶ�
          �Ĳ�ͬ��϶����е���"����"
------------------------------------------------
����˵�����۲���ˮ������˳����ٶȵı仯
************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"

uint i = 0,j = 0,dir = 0;
uint flag = 0,speed = 0;  //flag--�ƹ�������ʽ��speed--�ƹ������ٶ�

/****************������****************/
void main(void)
{
  
    WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
    BoardConfig(0xf0);
    
    CCTL0 = CCIE;                   //ʹ��CCR0�ж�
    CCR0 = 50000;
    TACTL = TASSEL_2 + ID_3 + MC_1; //��ʱ��A��ʱ��Դѡ��SMCLK��������ģʽ
    P2DIR = 0xff;                   //����P2�ڷ���Ϊ���
    P2OUT = 0xff;
 
    _EINT();                        //ʹ��ȫ���ж�
    LPM0;                           //CPU����LPM0ģʽ
}

/*******************************************
�������ƣ�Timer_A 
��    �ܣ���ʱ��A���жϷ�������������ͨ����־
          ������ˮ�Ƶ���������������ٶ�
��    ������
����ֵ  ����
********************************************/
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{  
    if(flag == 0)
    {
        P2OUT = ~(0x80>>(i++));    //�Ƶĵ���˳��D8 -> D1
    }
    else if(flag == 1)
    {
        P2OUT = ~(0x01<<(i++));    //�Ƶĵ���˳��D1 -> D8
    }
    else 
    {
        if(dir)                  //�Ƶĵ���˳��  D8 -> D1,D1 -> D8,ѭ����Ȧ                        
        {
            P2OUT = ~(0x80>>(i++));
        }
        else
        {
            P2OUT = ~(0x01<<(i++));
        }
    }
  
    if(i == 8) 
    {
        i = 0;
        dir = ~dir;
    }
  
    j++;
    if(j == 40) 
    {
        i = 0;
        j = 0;
        flag++;
        if(flag == 4) flag = 0;
        switch(speed)
        {
        case 0:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_3;
            break;
        case 1:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_2;
            break;
        case 2:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_1;
            break;
        case 3:
            TACTL &=~ (ID0 + ID1);
            TACTL |= ID_0;
            break;
        default:
            break;
        }
        if(flag != 3)   speed++;
        if(speed == 4) speed = 0;
    } 
}

