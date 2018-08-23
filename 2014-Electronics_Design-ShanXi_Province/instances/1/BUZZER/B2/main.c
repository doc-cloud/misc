/*********************************************
�����ܣ�MCU���Ʒ��������������ף��ƽ����
----------------------------------------------
����˵����������������������������
*********************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "music.h"

#define   Buzzer        BIT7
#define   Buzzer_Port   P6OUT
#define   Buzzer_DIR    P6DIR

uchar counter;
void Play_Song(void);

/***************������****************/
void main(void)
{
    uchar i;
     
    WDTCTL = WDTPW + WDTHOLD;                 //�رտ��Ź�
    /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                       // ��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                       //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);           // �ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));                   // ����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;                 //��ʱ�Ӻʹ�ʱ�Ӷ�ѡ���Ƶ����
    
    BoardConfig(0xf8);                        //�ر�����ܡ���ˮ�ơ���ƽת��
    
    //���ö�ʱ��Aÿ10ms�ж�һ��
    CCTL0 = CCIE;
    CCR0 = 10000;
    TACTL |= TASSEL_2 + ID_3; 
    //���ÿ��Ʒ�������IO����Ϊ���
    Buzzer_DIR |= Buzzer;
    //��ȫ���ж�
    _EINT();
    //ѭ���������
    while(1)
    {
        Play_Song();
    }
}

/*******************************************
�������ƣ�TimerA_ISR
��    �ܣ���ʱ��A���жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector = TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
{
    counter++;
}
/*******************************************
�������ƣ�Delay_Nms
��    �ܣ���ʱN��ms�ĺ���
��    ����n--��ʱ����
����ֵ  ����
********************************************/
void Delay_Nms(uchar n)
{
    uchar i,j;
    
    for( i = 0;i < n; i++ )
    {
        for( j = 0;j < 3;j++ )
          _NOP();
    }
}
/*******************************************
�������ƣ�Play_Song
��    �ܣ����š�ף��ƽ����������
��    ������
����ֵ  ����
********************************************/
void Play_Song(void)
{
    uchar Temp1,Temp2;
    uchar addr = 0;
    
    counter = 0; //�жϼ�������0
    while(1)
    {
        Temp1 = SONG[addr++];
        if ( Temp1 == 0xFF )        //��ֹ��
        {
            TACTL &=~MC_1;          //ֹͣ����
            Delay_Nms(100);
        }
        else if ( Temp1 == 0x00 )   //����������
        {
            return;
        }
        else
        {
            Temp2 = SONG[addr++];
            TACTL |=MC_1;           //��ʼ����
            while(1)
            {
                Buzzer_Port ^= Buzzer;
                Delay_Nms(Temp1);
                if ( Temp2 == counter )
                {
                    counter = 0;
                    break;
                }
            }
        }
    }
}
