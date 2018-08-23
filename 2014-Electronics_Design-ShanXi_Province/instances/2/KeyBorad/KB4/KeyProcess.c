#include "InputNumber.h"
#include "InputChar.h"
#include "SMG1602.h"

//<<<<<<<<���뷨��־λ>>>>>>>>
unsigned char b_InputMode=0xff;	//0��ʾ���������뷨��1��ʾ����ĸ���뷨��
			        //Ĭ������ĸ���뷨��
//<<<<<<<<<��ʾ����>>>>>>>>>>>>
extern unsigned char b_Introduce;

void vIntroduce(void);
//<<<<<<<<������������>>>>>>>>>
unsigned char uc_KeyTemp=0;	//���������ݴ档

unsigned char uc_ClickCount=1;	//ͬһ�����������µĴ�����

extern unsigned char uc_CleanCount;//�����������ʱ�������

unsigned char b_CleanClick=0;	//Ϊ1ʱ���������


//<<<<<<<<��Сдģʽ>>>>>>>>>
extern unsigned char b_CapStatus;//0--��д��1--Сд��(Ĭ��Ϊ0:��д)


//<<<<<<<<<ˢ���ַ���ʾ>>>>>>>>>
unsigned char uca_CharBox[]={"                "};  //�洢ˢ���ַ���	 
							
unsigned char uc_CharPointer=0;	//ˢ���ַ�ĩλ������ָ���ַ����λ�á�


/*******************************************
�������ƣ�vCleanAll
��    �ܣ���������е������ַ�
��    ������
����ֵ  ����
********************************************/
void vCleanAll(void)
{
    unsigned char ucCount;

    for(ucCount=0;ucCount<uc_CharPointer;ucCount++)
        uca_CharBox[ucCount]=' ';

    uc_CharPointer=0;
    DispStr(0,1,"                ");
    LocateXY(0,1);
}
/*******************************************
�������ƣ�vCleanOne
��    �ܣ���ǰ��������е�һ���ַ�
��    ������
����ֵ  ����
********************************************/
void vCleanOne(void)
{
    if(uc_CharPointer>0)
    {
        uc_CharPointer--;
        uca_CharBox[uc_CharPointer]=' ';
        LocateXY(uc_CharPointer,1);
        LcdWriteData(' ');
        LocateXY(uc_CharPointer,1);
    }
}
/*******************************************
�������ƣ�vCharAdd
��    �ܣ��������е�ĩβ׷����ʾһ���ַ�
��    ����ucChar--Ҫ��ʾ���ַ���ASCII��
����ֵ  ����
********************************************/
void vCharAdd(unsigned char ucChar)						   //���յ���ASC�ַ���
{
    unsigned char ucCount;
    
    if(uc_CharPointer<16)
    {
        LocateXY(uc_CharPointer,1);
        LcdWriteData(ucChar);
        
        uca_CharBox[uc_CharPointer]=ucChar; //���ַ�д��uca_CharBox��	
        uc_CharPointer++;	            //ʹucCharPointָ����һ��λ�á�
        if(uc_CharPointer == 16)
        {
            LocateXY(0,1);    
        }
    }
    else
    {					    //���ַ�����16����ȫ��������ѹ���Ƶ�����ߡ�
        
        DispStr(0,1,"                ");
        Disp1Char(0,1,ucChar);		    //д�������ַ���
    
        for(ucCount=1;ucCount<16;ucCount++)
                uca_CharBox[ucCount]=' ';   //ͬʱ���uca_CharBox��
        uca_CharBox[0]=ucChar;
        uc_CharPointer=1;
    }

    b_CleanClick=1;
    uc_CleanCount=0;
}
/*******************************************
�������ƣ�ucGetChar
��    �ܣ���ȡ������Ӧ�����ֻ�����ĸ
��    ����ucChar--��ֵ
����ֵ  ����Ӧ��ASCII��
********************************************/
unsigned char ucGetChar(unsigned char ucChar)
{
    if(b_InputMode==0)
        return ucGetNum(ucChar);	//��ȡ�����ַ�
    else
        return ucGetLetter(ucChar);     //��ȡ��ĸ�ַ�
}
/*******************************************
�������ƣ�vCharProcess
��    �ܣ�����ĸ״̬����ĸ�ͷ��Ž��д���ĺ���
��    ����ucKeyCode--��ֵ
����ֵ  ����
********************************************/
void vCharProcess(unsigned ucKeyCode)	       
{
    if(!b_InputMode)								 //������������룬��ֱ�������
        vCharAdd(ucGetChar(ucKeyCode));
    else
    {
        if(ucKeyCode!=22)	//������Ǳ��'!'
        {
            if(uc_ClickCount == 0)
            {
                vCharAdd(ucGetChar(ucKeyCode));	//�����ֻ��������1�ξ�ֱ�������
            }
            else
            {
                uc_CharPointer--;		//������ǰ�ƣ�Ȼ���������
                vCharAdd(ucGetChar(ucKeyCode));
            }
        }
        else
        {
            vCharAdd('!');                      //׷����ʾ!
        }
    }
    b_CleanClick=1;
    uc_CleanCount=0;
}
/*******************************************
�������ƣ�vKeyProcess
��    �ܣ����������������
��    ����ucKeyCode--��ֵ
����ֵ  ����
********************************************/
void vKeyProcess(unsigned char ucKeyCode)
{
    if(uc_KeyTemp==ucKeyCode)	//�жϰ�������һ�������ļ��Ƿ���ͬ��
    {
        if(uc_ClickCount<255)	//ͬһ�����������µĴ���:1��255��
            uc_ClickCount++;
    }
    else
    {
        uc_KeyTemp=ucKeyCode;
        uc_ClickCount=0;
    }

    /*���ݼ�ֵ�ֱ���д���*/
    switch(ucKeyCode)
    {
    case 11:		//*****��ʾ����****
            b_Introduce=1;
            vIntroduce();
            break;

    case 32:		//****����հ�****
            vCharAdd(' ');				
            break;

    case 31:	        //****��Сд�л�****
            if(b_InputMode)
            {
                b_CapStatus=~b_CapStatus;
                if(!b_CapStatus)    //��д
                {
                    
                    Disp1Char(14,0,'B');
                    LocateXY(uc_CharPointer,1);
                }
                else                //Сд
                {
                    Disp1Char(14,0,'S');
                    LocateXY(uc_CharPointer,1);
                }
            }
            break;

    case 41:	    //****ɾ�������ַ�****
            vCleanAll();
            break;

    case 42:	    //****ɾ��1���ַ�****
            vCleanOne();
            break;

    case 21:	    //****���뷨�л�****
            b_InputMode=~b_InputMode;
            if(b_InputMode)
            {
                if(b_CapStatus==0)	          //�л����ַ����뷨ʱ�����Ͻ���ʾ��C��
                {
                    DispStr(14,0,"BC");		  //��д��ʾ��BC��
                    LocateXY(uc_CharPointer,1);
                }
                else
                {
                    DispStr(14,0,"SC");		 //Сд��ʾ��SC��
                    LocateXY(uc_CharPointer,1);
                }
            }
            else
            {
                	  
                DispStr(14,0," N"); //�л����������뷨ʱ�����Ͻ���ʾ��N��
                LocateXY(uc_CharPointer,1);
            }	
            break;
    case 12:	 //��ü���
    case 13:
    case 14:
    case 22:	 
    case 23:
    case 24:
    case 33:	 
    case 34:
    case 43: 
    case 44:
            vCharProcess(ucKeyCode);
            break;
    default:
            break;
    }
}
