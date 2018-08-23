/***********************************************************
程序功能：在12864液晶上显示一屏汉字
-----------------------------------------------------------
测试说明：观察液晶显示
***********************************************************/
#include  "msp430.h"
#include  "BoardConfig.h"
#include  "cry12864.h"

const uchar hang1[] = {"大工至善大学至真"};
const uchar hang2[] = {"自强不息厚德载物"};
const uchar hang3[] = {"博学笃志切问近思"};
const uchar hang4[] = {"诚朴雄伟励学敦行"};

/***************************主函数*************************/
void main( void )
{

    WDTCTL = WDTPW + WDTHOLD;    //关狗
    BoardConfig(0xbe);
    
    Ini_Lcd();                  //初始化液晶
    
    Disp_HZ(0x80,hang1,8);
    Disp_HZ(0x90,hang2,8);
    Disp_HZ(0x88,hang3,8);
    Disp_HZ(0x98,hang4,8);
    
    LPM4; 
}
