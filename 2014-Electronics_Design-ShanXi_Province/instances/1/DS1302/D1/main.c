/********************************************************
�����ܣ���DS1302�ж���ʱ��������1602Һ��ģ������ʾ
---------------------------------------------------------
����˵�����û����Ը���"gdata.h"��wdata��bwdata��rwdata
          ���������е����ݣ�������ע�����ݸ�ʽ��
          ���ݳ�������ʾ�����öϵ�۲����ݡ�
*********************************************************/
#include <msp430x14x.h>
#include "BoardConfig.h"
#include "ds1302.h"
#include "cry1602.h"
#include "gdata.h"

void main(void)
{
    uchar disptemp[8]; 
    
    WDTCTL = WDTPW + WDTHOLD;   //�رտ��Ź�
    BoardConfig(0xf8);          //�ر�����ܡ���ˮ�ơ���ƽת��
    
    disptemp[2]=0x3a;   // ":"��Ӧ�ı���
    disptemp[5]=0x3a;   
    Reset_DS1302();
    
    
    
    /*****���Ը��ĺͶ���ʱ��*****/
    Set_DS1302(wdata);   
    Get_DS1302(rdata);
    
    _NOP();         //�ڴ˴����öϵ㣬�۲�rdata�Ƿ���wdataһ��
    
    /*****����������дʱ��Ĵ���*****/
    BurstWrite1302(bwdata);
    BurstRead1302(brdata);
    
    _NOP();         //�ڴ˴����öϵ㣬�۲�brdata�Ƿ���bwdataһ��
    
    /*****����������дRAM*****/
    BurstWriteRAM(rwdata);
    BurstReadRAM(rrdata);
    
    _NOP();         //�ڴ˴����öϵ㣬�۲�rrdata�Ƿ���rwdataһ��

    /*************************************************
    ע�ͣ��û�������27~43�еĳ�����ɲ����Ժ������ú�
    ��ȷ�ĵ�ǰʱ��Ȼ����˳������ε�������make�Ժ�д��
    CPU�У��������ܱ�֤ÿ���ϵ�ʱCPU����DS1302�ж�����ȷ
    �ĵ�ǰʱ���͵�Һ����ȥ��ʾ�������ᷢ��ÿ�ζ����¸�д
    DS1302�ڲ�ʱ������⡣
    *************************************************/
    //��ʼ��Һ��
    LcdReset();
    DispNchar(1,0,14,tishi);
    //��ȡʱ��ת����ֵ��ʾ
    while(1)
    {
        BurstRead1302(rdata);
        disptemp[6] = shuzi[(rdata[0]&0xf0)>>4];
        disptemp[7] = shuzi[rdata[0]&0x0f];
        disptemp[3] = shuzi[(rdata[1]&0xf0)>>4];
        disptemp[4] = shuzi[rdata[1]&0x0f];
        disptemp[0] = shuzi[(rdata[2]&0xf0)>>4];
        disptemp[1] = shuzi[rdata[2]&0x0f];
        DispNchar(4,1,8,disptemp);
        delay(50000);
    }
}
