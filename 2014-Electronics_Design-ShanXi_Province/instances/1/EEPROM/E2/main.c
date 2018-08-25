/*********************************************************
�����ܣ�PC��ͨ�����ڿ��Կ��ƴ�EEPROM��ָ����ַ�ж���һ��
          �ֽڵ����ݣ�������ָ����ַд��һ���ֽڵ�����
�ر�˵������PC������EEPROM�ڵĴ洢��ַ������д������ʱ������
          ʹ��ʮ�����Ʒ��ͣ����ڷ��Ͷ�д��������ʱҪʹ��Ĭ��
          �ķ���ASCII������ã����Ҫע�⣬��������޷����
-----------------------------------------------------------
ͨ�Ÿ�ʽ��N.8.1,  9600
-----------------------------------------------------------
����˵�����򿪴��ڵ��Ծ��飬��ȷ����ͨ�Ÿ�ʽ��������Ļ��ʾ��
          ��ʾ��Ϣ���Ϳ������ݽ��в���
**********************************************************/
#include <msp430.h>
#include "BoardConfig.h"
#include "uart0.h"

uchar step = 0xff;

void main( void )
{
    uchar i;
    
    WDTCTL = WDTPW + WDTHOLD;           //�ع�
    BoardConfig(0xb8);                  //������ܡ���ˮ�ƺ͵�ƽת�� 
    
    P1DIR |= BIT3 + BIT2;               //������Ӧ�˿�Ϊ���״̬
    P1OUT |= BIT3 + BIT2;
    InitUART();                         //��ʼ��UART�˿�
    
    DisplayConfigMenu();
    while(1)
    {
        Send1Char('>');
        Send1Char('\n');
        i=Get1Char();
        HandleConfigMenu(i);
    }
    
}