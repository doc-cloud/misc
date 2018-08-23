#include "SMG1602.h"
#include "msp430.h"

unsigned char b_Introduce=1;	//���ڹرս��ܡ�1--�������ܣ�0--�˳����ܡ�

extern unsigned char uca_CharBox[];
extern unsigned char uc_CharPointer;
extern unsigned char b_CapStatus;
extern unsigned char b_InputMode;

unsigned char  d0[]={"                "};
unsigned char d1[]={"Hello. Sir! I am"};
unsigned char d2[]={"clear!I can show"};
unsigned char d3[]={"what you press !"};
unsigned char d4[]={"       ^-^      "};

/*******************************************
�������ƣ�vIntroduce
��    �ܣ�������ʾ��������
��    ������
����ֵ  ����
********************************************/
void vIntroduce(void)
{
    unsigned int uiCount;	//ѭ��������ʾ:
    unsigned char ucCount;
    
    unsigned char *ucaIntroduce[5];
    
    ucaIntroduce[0] = d0;
    ucaIntroduce[1] = d1;
    ucaIntroduce[2] = d2;
    ucaIntroduce[3] = d3;
    ucaIntroduce[4] = d4;
      
    LcdWriteCommand(0x0c,1);	//�رչ����ʾ

    //ѭ����ʾ���ȴ��˳�
    for(ucCount=0;b_Introduce==1;ucCount++)
    {
        DispStr(0,0,ucaIntroduce[ucCount]);     //ˢ�µ�һ��     	
        if(ucCount==4)
        {
            ucCount=0;
        }
        DispStr(0,1,ucaIntroduce[ucCount+1]);   //ˢ�µڶ���
    
        for(uiCount=0;uiCount<65000;uiCount++)
        {
            _NOP();
            _NOP();
            _NOP();
            _NOP();
            _NOP();
        }
        
    }
/*<<<<<<<<<<<<<<<�������ܣ��ָ���Ļ>>>>>>>>>>>>>>>>*/
    LcdWriteCommand(0x01, 1);	        //��ʾ����					 
    DispStr(0,0,"Please Input: ");	//�ָ���ʾ��Ϣ��

    if(!b_InputMode)
    {									//�ָ�״̬��־��
        DispStr(14,0," N");
    }
    else
    {
        if(!b_CapStatus)
            DispStr(14,0,"BC");
        else
            DispStr(14,0,"SC");
    }

    DispStr(0,1,uca_CharBox);	//�ָ�����ǰ���ݡ�

    LocateXY(uc_CharPointer,1);	//�ָ�����ǰ���λ�á�

    LcdWriteCommand(0x0F,1);	//�ָ���ʾģʽ����ʾ��������꿪����˸����
}
