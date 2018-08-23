#include "CapProcess.h"
#include "SmallProcess.h"

/**************ȫ�ֱ���*****************/
extern unsigned char uc_ClickCount;

unsigned char b_CapStatus=0;//��Сдģʽ��0--��д��1--Сд��

/*******************************************
�������ƣ�ucCapProc
��    �ܣ����ݰ����Ĵ����ҵ���Ӧ�Ĵ�д��ĸ��
          ASCII��ֵ
��    ������ֵ
����ֵ  ����Ӧ�Ĵ�д��ĸ��ASCII��
********************************************/
unsigned char ucCapProc(unsigned char ucKeyCode)
{
    switch(uc_ClickCount%3)
    {
        case 0:return ucCapOne(ucKeyCode);
        case 1:return ucCapTwo(ucKeyCode);
        case 2:return ucCapThree(ucKeyCode);
        default:break;
    }
    return ' ';
}
/*******************************************
�������ƣ�ucSmallProc
��    �ܣ����ݰ����Ĵ����ҵ���Ӧ��Сд��ĸ��
          ASCII��ֵ
��    ������ֵ
����ֵ  ����Ӧ�Ĵ�д��ĸ��ASCII��
********************************************/
unsigned char ucSmallProc(unsigned char ucKeyCode)
{
    switch(uc_ClickCount%3)
    {
        case 0:return ucSmallOne(ucKeyCode);
        case 1:return ucSmallTwo(ucKeyCode);
        case 2:return ucSmallThree(ucKeyCode);
        default:break;
    }
    return ' ';
}
/*******************************************
�������ƣ�ucGetLetter
��    �ܣ���ȡ������Ӧ��ĸ��ASCII��ֵ
��    ������ֵ
����ֵ  ����Ӧ�Ĵ�д��ĸ��ASCII��
********************************************/
unsigned char ucGetLetter(unsigned char ucKeyCode)
{
    if(b_CapStatus==0)		//��д���뷽ʽ
    {
        return ucCapProc(ucKeyCode);
    }
    else                        //Сд���뷽ʽ
    {
        return ucSmallProc(ucKeyCode);	
    }
        
}
