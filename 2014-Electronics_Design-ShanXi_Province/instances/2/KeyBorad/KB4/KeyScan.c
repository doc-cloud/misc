/* 
<����>�������ⲿ�ж�ʱ���ô˺�����ʹ����ɨ��ķ�ʽ��ȡ���룬                                                                                                                                
        ������2λ������ɣ���λΪ�к�,��λΪ�к� 
*/	

#include <msp430.h>

#define SCAN_OUT P1OUT	 //4��4����ɨ��˿ڣ���4λ�����ߣ���4λ�����ߡ�
			 //��������ɨ��ķ������ް���ʱ����4λ���1����4λ���0��
			 //���а���ʱ����4λ���ɨ���λ����4λ����ɨ������

#define SCAN_IN P1IN

const unsigned char uca_LineScan[4]={0xEF,0xDF,0xBF,0x7F};//����ɨ���ѹ����Ϊ��1��2��3��4������

/*******************************************
�������ƣ�ucKeyScan
��    �ܣ�ɨ����̵õ���ֵ
��    ������
����ֵ  ����ֵ
********************************************/ 															//Ϊ�͵�ƽ������Ϊ�ߵ�ƽ��
unsigned char ucKeyScan(void)
{
    unsigned char ucTemp=0;		//ɨ��״̬�ݴ档
    unsigned char ucRow=0,ucLine=0;	//�кţ��кš�

    P1IE=0;			 	//�ڼ�ɨ�账��ʱ���ر��ⲿ�ж�

    for(ucLine=0;ucLine<4;ucLine++)     //��ɨ��
    {
        SCAN_OUT = uca_LineScan[ucLine];//���ɨ���λ��
        ucTemp = SCAN_IN&0x0F;		//����ɨ���λ�������θ�4λ��
        if(ucTemp != 0x0F)		 
        {									  //�жϸ����Ƿ��а������¡�
            switch(ucTemp)              //����У����ж��кš�
            {
                case 0x0E: ucRow=10;break;
                case 0x0D: ucRow=20;break;
                case 0x0B: ucRow=30;break;
                case 0x07: ucRow=40;break;
                default:   ucRow=50;break;
            }
            break;
        }
    }
    while((SCAN_IN&0x0F) != 0x0f);      //�ȴ������ſ�
    SCAN_OUT = 0x0F;	  		//�ָ�P1��
    P1IE |= 0x0f;			//�ָ������ж�
    return (ucRow+ucLine+1);		//���ذ������롣��ʽΪ2λ������λΪ�кţ���λΪ�кš�
}
