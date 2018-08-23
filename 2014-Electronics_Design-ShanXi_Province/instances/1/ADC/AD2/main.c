/*********************************************************
�����ܣ�MCU��Ƭ��ADC��P6.0�˿ڵĵ�ѹ����ת��
          ��ģ���ѹֵ��ʾ��1602Һ���ϡ�
----------------------------------------------------------
����˵�������ڵ�λ��R7����ť�۲�Һ����ʾ���ֱ仯��
*********************************************************/
#include  <msp430x14x.h>
#include  "BoardConfig.h"
#include  "cry1602.h"

#define   Num_of_Results   32

uchar shuzi[] = {"0123456789."};
uchar tishi[] = {"The volt is:"};

static uint results[Num_of_Results];    //����ADCת�����������                                                     // is not used for anything.
void Trans_val(uint Hex_Val);           

/************************������****************************/
void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   //�رտ��Ź�
  BoardConfig(0xb8);                        //�ر�����ܡ���ˮ�ơ�4245
  LcdReset();                               //��λ1602Һ��
  DispNChar(2,0,12,tishi);                  //��ʾ��ʾ��Ϣ
  Disp1Char(11,1,'V');                      //��ʾ��ѹ��λ
  P6SEL |= 0x01;                            // ʹ��ADCͨ��
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // ��ADC�����ò���ʱ��
  ADC12CTL1 = SHP+CONSEQ_2;                 // ʹ�ò�����ʱ��
  ADC12IE = 0x01;                           // ʹ��ADC�ж�
  ADC12CTL0 |= ENC;                         // ʹ��ת��
  ADC12CTL0 |= ADC12SC;                     // ��ʼת��
  
  _EINT();
  LPM0;
}

/*******************************************
�������ƣ�ADC12ISR
��    �ܣ�ADC�жϷ��������������ö��ƽ����
          ����P6.0�ڵ�ģ���ѹ��ֵ
��    ������       
����ֵ  ����
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
  static uint index = 0;

  results[index++] = ADC12MEM0;               // Move results
  if(index == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

        index = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum += results[i];
        }
        sum >>= 5;                            //����32
        
        Trans_val(sum);
  }
}

/*******************************************
�������ƣ�Trans_val
��    �ܣ���16����ADCת�����ݱ任����λ10����
          ��ʵ��ģ���ѹ���ݣ�����Һ������ʾ
��    ����Hex_Val--16��������
          n--�任ʱ�ķ�ĸ����2��n�η�       
����ֵ  ����
********************************************/
void Trans_val(uint Hex_Val)
{
    unsigned long caltmp;
    uint Curr_Volt;
    uchar t1,i;
    uchar ptr[4];
    
    caltmp = Hex_Val;
    caltmp = (caltmp << 5) + Hex_Val;           //caltmp = Hex_Val * 33
    caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
    Curr_Volt = caltmp >> 12;                   //Curr_Volt = caltmp / 2^n
    ptr[0] = Curr_Volt / 100;                   //Hex->Dec�任
    t1 = Curr_Volt - (ptr[0] * 100);
    ptr[2] = t1 / 10;
    ptr[3] = t1 - (ptr[2] * 10);
    ptr[1] = 10;                                //shuzi���е�10λ��Ӧ����"."
    //��Һ������ʾ�任��Ľ��
    for(i = 0;i < 4;i++)
      Disp1Char((6 + i),1,shuzi[ptr[i]]);
}
