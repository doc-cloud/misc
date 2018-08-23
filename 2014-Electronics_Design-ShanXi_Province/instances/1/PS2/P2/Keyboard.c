#include <msp430x14x.h>
#include "code.h"
typedef unsigned char uchar;
typedef unsigned int  uint;

#define BufferSize  32
extern uchar kb_buffer[BufferSize];
extern uchar input;
extern uchar output;
extern uchar flag;
/*******************************************
�������ƣ�PushBuff
��    �ܣ���һ���ַ�ѹ����ʾ���棬���������
          ���򸲸�ǰ�������
��    ����c--Ҫ��ʾ���ַ�
����ֵ  ����
********************************************/
void PutChar(uchar c)
{
    kb_buffer[input] = c;
    if (input < (BufferSize-1))
        input++; 
    else
        input = 0;	 
}
/*******************************************
�������ƣ�PopChar
��    �ܣ�����ʾ������ȡ��һ���ַ�
��    ������
����ֵ  ��ȡ�����ַ�
********************************************/
uchar GetChar(void)
{
    uchar temp;
    
    if(output == input)
        return 0xff;
    else
    {
	    temp = kb_buffer[output];
	    if(output < (BufferSize-1))
	    {
	        output++;
        }
	    else
        {
	        output = 0;
        }
	    return temp;	  
    }	     
}
/*******************************************
�������ƣ�Init_KB
��    �ܣ���ʼ���������ص�IO
��    ������
����ֵ  ����
********************************************/
void Init_KB(void)
{
    P1DIR &=~ BIT7;     //Clock��P1.7������Ϊ����
    P5DIR &=~ BIT6;     //SID��P5.6������Ϊ����
    P1IES |= BIT7;      //�½����ж�
    P1IFG = 0x00;       //�жϱ�־����
    P1IE  |= BIT7;      //ʹ��ʱ�Ӷ˿��ж�
    P1SEL = 0x00;       //P1����ΪIOʹ��
}
/*******************************************
�������ƣ�Decode
��    �ܣ������Լ��̵���Ϣ���н��룬ת���ɶ�
          Ӧ��ASCII���벢ѹ�뻺��
��    ����sc--���̷��͹�������Ϣ
����ֵ  ���Ƿ��յ���Ч���ݣ�0--��1--��
˵��    ��������ֻ�ܶԻ�������������������ʱ��
          �������ֽڵ�ɨ����İ������������룬
          �������еĿ���ʾ�ַ�����Table��
          Back Space��Enter�������⹦�ܼ���
����������ɨ�����������ֽ���ɣ���1���ֽ�Ϊ��ͨ
�룬��2��3�ֽ�Ϊ�Ͽ��룻���е�1�ֽں͵�3�ֽ���
ͬ���м��ֽ�Ϊ�Ͽ���־0xf0��
********************************************/
uchar Decode(uchar sc)
{
      static uchar shift = 0; //Shift���Ƿ��±�־��1--���£�0--δ��
      static uchar up = 0;    //���ѷſ���־��       1--�ſ���0--����
      uchar i,flag = 0;
      
      if(sc == 0xf0)    //����յ�����ɨ����ĵ�2���ֽ�---0xf0�������Ͽ���־
      {
          up = 1;        
          return 0;
      }
      else if(up == 1)  //����յ�����ɨ����ĵ�3���ֽ�
      {
	      up = 0;         
          if((sc == 0x12) || ( sc==0x59))   shift = 0;
	      return 0;
      }	
      
      //����յ�����ɨ����ĵ�1���ֽ�
      if((sc == 0x12) || (sc == 0x59)) //���������shift��
      {      
	      shift = 1;	        //����Shift���±�־
          flag = 0;
      }		           	           
      else
      {
	      if(shift) //�԰���Shift�ļ����н���
		  {
		       for(i = 0;(shifted[i][0] != sc) && shifted[i][0];i++);
               if (shifted[i][0] == sc) 
               {
                    PutChar(shifted[i][1]);
                    flag = 1;
               }
		  }
		  else  //ֱ�Ӷ԰������н���
		  {
		       for(i = 0;(unshifted[i][0] != sc) && unshifted[i][0];i++);
               if(unshifted[i][0] == sc)  
               {
                    PutChar(unshifted[i][1]);
                    flag = 1;
               }
	      } 
      }
      if(flag)  return 1;
      else      return 0;
}
