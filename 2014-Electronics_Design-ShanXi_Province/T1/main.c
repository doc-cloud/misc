
#include <msp430x14x.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define XTOFF 0x40

#define DataDir     P4DIR
#define DataPort    P4OUT				
#define Busy	    0x80
#define CtrlDir     P3DIR

#define CLR_RS P3OUT&=~BIT0;    //RS = P3.0	
#define SET_RS P3OUT|=BIT0;	
#define CLR_RW P3OUT&=~BIT1;	//RW = P3.1
#define SET_RW P3OUT|=BIT1;	
#define CLR_EN P3OUT&=~BIT2;	//EN = P3.2	
#define SET_EN P3OUT|=BIT2;	

#define keyin (P2IN&0x0f)

uint high_level[19],dattmp[19];
uint low_level;
uchar month,day,year,hour,min,sec,weekday;
uchar tmp_month,tmp_day,tmp_year,tmp_hour,tmp_min,tmp_sec,tmp_weekday;
uchar flag;
uchar i;
uchar PP=0;
uchar cflag=0;

void main_test(void);
void Init_TimerA(void);
void Init_TimerB(void);
void Decode(void);
void Display(void);
void Delay10ms(void);
uchar Key4Scan(void);

void DispStr(uchar x,uchar y,uchar *ptr);
void DispNChar(uchar x,uchar y,uchar n,uchar *ptr);
void LocateXY(uchar x,uchar y);
void Disp1Char(uchar x,uchar y,uchar data);
void LcdReset(void);
void LcdWriteCommand(uchar cmd,uchar chk);
void LcdWriteData(uchar data);
void WaitForEnable(void);
void Delay5ms(void);

void main(void)
{
  main_test();
}

void main_test(void)
{    
    WDTCTL = WDTPW + WDTHOLD;   //关闭看门狗
    P2DIR = 0x80;
    P2OUT = 0x00;
    LcdReset();
    Init_TimerA();
    Init_TimerB();
    while(i<19)
      ;
    while(19<=i)
      Decode();
    Display();
    while(1)
    {
        if(!cflag)
        {
          Display();
        }
        switch(Key4Scan())
        {
        case 0x01:
          switch(PP++)      //确定游标地址
          {
          case 0:
            LocateXY(4,0);
            break;
          case 1:
            LocateXY(7,0);
            break;
          case 2:
            LocateXY(10,0);
            break;
          case 3:
            LocateXY(14,0);
            break;
          case 4: 
            LocateXY(4,1);
            break;
          case 5:
            LocateXY(7,1);
            break;
          case 6:
            LocateXY(10,1);
            break;
          default:
            break;
          }                  
          LcdWriteCommand(0x0f,1);
          if(7==PP)
            PP=0;
          cflag=1;          //标志置位
          break;
        case 0x02:
          if(cflag)
          {
            tmp_year=year;
            tmp_month=month;
            tmp_day=day;
            
            tmp_hour=hour;
            tmp_min=min;
            tmp_sec=sec;
            
            tmp_weekday=weekday;
            
            switch(PP)
            {
            case 0:         //年
              year++;
              if(99<year)
                year=0;
              Disp1Char(3,0,year/10+48);
              Disp1Char(4,0,year%10+48);
              LocateXY(4,0); 
              break;
            case 1:         //月
              month++;
              if(12<month)
                month=0;
              Disp1Char(6,0,month/10+48);
              Disp1Char(7,0,month%10+48);
              LocateXY(7,0);
              break;
            case 2:         //日
              day++;
              switch(month)
              {
              case 2:
                if(0==year%4)
                {
                  if(29<day)
                    day=1;
                }
                else
                  if(28<day)
                    day=1;
                break;
              case 4:
              case 6:
              case 9:
              case 11:
                if(30<day)
                  day=1;
                break;
              case 1:
              case 3:
              case 5:
              case 7:
              case 8:
              case 10:
              case 12:
                if(31<day)
                  day=1;
              default:
                break;
              }
              Disp1Char(9,0,day/10+48);
              Disp1Char(10,0,day%10+48);
              LocateXY(10,0);
              break;
            case 3:         //weekday
              weekday++;
              if(7<weekday)
                weekday=1;
                switch(weekday)
                {
                case 1:
                  Disp1Char(12,1,'M');
                  Disp1Char(13,1,'o');
                  Disp1Char(14,1,'n');
                  break;
                case 2:
                  Disp1Char(12,1,'T');
                  Disp1Char(13,1,'u');
                  Disp1Char(14,1,'e');
                  break;
                case 3:
                  Disp1Char(12,1,'W');
                  Disp1Char(13,1,'e');
                  Disp1Char(14,1,'d');
                  break;
                case 4:
                  Disp1Char(12,1,'T');
                  Disp1Char(13,1,'h');
                  Disp1Char(14,1,'u');
                  break;
                case 5:
                  Disp1Char(12,1,'F');
                  Disp1Char(13,1,'r');
                  Disp1Char(14,1,'i');
                  break;
                case 6:
                  Disp1Char(12,1,'S');
                  Disp1Char(13,1,'a');
                  Disp1Char(14,1,'t');
                  break;
                case 7:
                  Disp1Char(12,1,'S');
                  Disp1Char(13,1,'u');
                  Disp1Char(14,1,'n');
                  break;
                default:
                  break;
                }
              LocateXY(14,0);
              break;  
            case 4:         //时
              hour++;
              if(24<hour)
                hour=0;
              Disp1Char(3,1,hour/10+48);
              Disp1Char(4,1,hour%10+48);
              LocateXY(4,1);
              break;
            case 5:         //分
              min++;
              if(60<min)
                min=0;
              Disp1Char(6,1,min/10+48);
              Disp1Char(7,1,min%10+48);
              LocateXY(7,1);
              break;
            case 6:         //时
              sec++;
              if(60<sec)
                sec=0;
              Disp1Char(9,1,sec/10+48);
              Disp1Char(10,1,sec%10+48);
              LocateXY(10,1);
              break;
            default:
              break;                            
            }
          }
          break;
        case 0x03:
          if(cflag)
          {
            cflag = 0;
            PP = 0;
            
            year=tmp_year;
            month=tmp_month;
            day=tmp_day;
            
            hour=tmp_hour;
            min=tmp_min;
            sec=tmp_sec;
            
            weekday=tmp_weekday;
            
            Display();

            LcdWriteCommand(0x0c,1);
          }
          break;
        case 0x04:
          if(cflag)
          {
            cflag = 0;
            PP = 0;
            LcdWriteCommand(0x0c, 1);   //关闭游标
          }
        break; 
        default:
          break;                    
        }
    }
}

void Init_TimerA(void)
{
  P1SEL|=BIT2;                                  //set the port 1.2 to pulse-capture mode.
  TACTL=TASSEL0+MC1+TACLR+TAIE;                 //Timer A clock source:ACLK | continuous mode | clear the Timer A | enable the Timer A.
  CCTL1=CCIE+CM0+SCS+CAP;                       //enable the interrupt | capture mode | rising edge capture | synchronize capture source.
}

void Init_TimerB(void)
{
  /*
  BCSCTL1&=~XT2OFF;
  BCSCTL2=SELS+DIVS1+DIVS0;
  TBCTL=0x02d4;
  CCTL0=CCIE;
  CCR0=62500;
  _EINT();
  */
  TBCTL=TBSSEL0+TBCLR;
  CCR0=32767;
  TBCTL|=MC0;
  CCTL0=CCIE;
}

void Decode(void)
{
  uchar ii;
  //while(1)          //keep decoding.
  //{
    if(19<=i)       //decode the value if the array is filled.
    {
      i=0;
      for(ii=0;ii<19-flag;ii++)                    //set the former data number of high_level array.
        dattmp[ii]=high_level[flag+ii];      
      for(ii=0;ii<flag;ii++)                 //set the latter data number of high_level array.
        dattmp[19-flag+ii]=high_level[ii];
      for(ii=0;ii<19;ii++)                           //reset the value of the dattmp array.
      {
        if(1638<dattmp[ii]&&dattmp[ii]<4915)                        //5%--15%
          dattmp[ii]=0;
        else if(4915<dattmp[ii]&&dattmp[ii]<8192)                   //15%--25%
          dattmp[ii]=1;
        else if(8192<dattmp[ii]&&dattmp[ii]<11468)                  //25%--35%
          dattmp[ii]=2;
        else if(11468<dattmp[ii]&&dattmp[ii]<14765)                 //35%--45%
          dattmp[ii]=3;
      }
      
      year=dattmp[15]*16+dattmp[16]*4+dattmp[17];
      month=dattmp[13]*4+dattmp[14];
      day=dattmp[10]*16+dattmp[11]*4+dattmp[12];
        
      hour=dattmp[2]*4+dattmp[3];
      min=dattmp[4]*16+dattmp[5]*4+dattmp[6];
      sec=dattmp[0]*20+20-flag;
        
      weekday=dattmp[7]*4+dattmp[8];
      
      flag=0;
        
      if(2==dattmp[9]||3==dattmp[9])
        hour+=12;
      if(59<sec)
      {
        sec=0;
        min++;
        if(59<min)
        {      
          min=0;
          hour++;
          if(11<hour)
            hour=0;
        }
      }
    }
  //}
}

//type:     Timer A interrupt service routine.
//purpose:  get the high level pulse width,provide frame information for the function Decode.
//version:  1.0 by chen on 9/4/2014.
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_ISR(void)
{      
  switch(TAIV)                                
  {
  case 2:                                       //use 0x01==TAIV here for the consideration of the low frequency of watch oscillator.
    if(CCTL1&CM0)                               //rising edge capture.
    {
      low_level=TAR;                            //get the low level width to judge the frame flag.
      TACTL|=TACLR;                             //restart the counter to provide a pure origin for the high level width recording.
      CCTL1=(CCTL1&(~CM0))|CM1;                 //switch the capture mode to falling edge capture.
    }
    else
      if(CCTL1&CM1)                             //falling edge capture.
      {
        high_level[i]=TAR;                    //record the value of the high level width.
        i++;
        TACTL|=TACLR;                           //restart the counter to provide a pure origin for the low level width recording.
        CCTL1=(CCTL1&(~CM1))|CM0;               //switch the capture mode to rising edge capture.
      }
    break;
  default:
    break;
  }
  if(4915<low_level)                               //resort the high_level array by the frame flag.
    flag=i;                                //locate the frame flag position.
}

//type:     Timer B interrupt service routine.
//purpose:  provide a pulse for the main clock frequency per second.
//version:  1.0 by chen on 9/4/2014.
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B(void)
{
    sec++;
    if(59<sec) 
    {
      sec=0;
      min++;
      if(59<min)
      {
        min=0;
        hour++; 
        if(23<hour)
          hour=0;
      }
    }
    if(cflag)
    {
      tmp_sec++;
      if(59<sec)
      {
        tmp_sec=0;
        tmp_min++;
        if(59<tmp_min)
        {
          tmp_min=0;
          tmp_hour++;
          if(23<tmp_hour)
            tmp_hour=0;
        }
      }
    }
}

void Display(void)
{
  Disp1Char(1,0,'2');
  Disp1Char(2,0,'0');
  Disp1Char(3,0,year/10+48);
  Disp1Char(4,0,year%10+48);
  Disp1Char(5,0,'-');
  Disp1Char(6,0,month/10+48);
  Disp1Char(7,0,month%10+48);
  Disp1Char(8,0,'-');
  Disp1Char(9,0,day/10+48);
  Disp1Char(10,0,day%10+48);
  
  Disp1Char(3,1,hour/10+48);
  Disp1Char(4,1,hour%10+48);
  Disp1Char(5,1,'-');
  Disp1Char(6,1,min/10+48);
  Disp1Char(7,1,min%10+48);
  Disp1Char(8,1,'-');
  Disp1Char(9,1,sec/10+48);
  Disp1Char(10,1,sec%10+48);
  switch(weekday)
  {
  case 1:
    Disp1Char(12,1,'M');
    Disp1Char(13,1,'o');
    Disp1Char(14,1,'n');
    break;
  case 2:
    Disp1Char(12,1,'T');
    Disp1Char(13,1,'u');
    Disp1Char(14,1,'e');
    break;
  case 3:
    Disp1Char(12,1,'W');
    Disp1Char(13,1,'e');
    Disp1Char(14,1,'d');
    break;
  case 4:
    Disp1Char(12,1,'T');
    Disp1Char(13,1,'h');
    Disp1Char(14,1,'u');
    break;
  case 5:
    Disp1Char(12,1,'F');
    Disp1Char(13,1,'r');
    Disp1Char(14,1,'i');
    break;
  case 6:
    Disp1Char(12,1,'S');
    Disp1Char(13,1,'a');
    Disp1Char(14,1,'t');
    break;
  case 7:
    Disp1Char(12,1,'S');
    Disp1Char(13,1,'u');
    Disp1Char(14,1,'n');
    break;
  default:
    break;
  }
}

//explanation:  following functions are the display effect function for the LCD 1602.
void DispStr(uchar x,uchar y,uchar *ptr) 
{
    uchar *temp;
    uchar i,n=0;  
    temp=ptr;
    while(*ptr++ != '\0')
      n++;                          //计算字符串有效字符的个数
    for (i=0;i<n;i++)
    {
        Disp1Char(x++,y,temp[i]);
        if (x == 0x0f)
        {
           x  = 0; 
           y ^= 1;
        }
    }
}

void DispNChar(uchar x,uchar y,uchar n,uchar *ptr) 
{
    uchar i;
    for (i=0;i<n;i++)
    {
        Disp1Char(x++,y,ptr[i]);
        if (x==0x0f)
        {
           x=0; 
           y^=1;
        }
    }
}

void LocateXY(uchar x,uchar y) 
{
    uchar temp;
    temp=x&0x0f;
    y&=0x01;
    if(y)
      temp|=0x40;  //如果在第2行
    temp|=0x80;
    LcdWriteCommand(temp,1);
}

void Disp1Char(uchar x,uchar y,uchar data) 
{
    LocateXY(x,y);			
    LcdWriteData(data);		
}

void LcdReset(void) 
{
    CtrlDir|=0x07;                 //控制线端口设为输出状态 
    DataDir=0xFF;                 //数据端口设为输出状态
    LcdWriteCommand(0x38, 0);	    //规定的复位操作
    Delay5ms();
    LcdWriteCommand(0x38, 0);		
    Delay5ms();
    LcdWriteCommand(0x38, 0);
    Delay5ms();

    LcdWriteCommand(0x38, 1);		//显示模式设置
    LcdWriteCommand(0x08, 1);		//显示关闭
    LcdWriteCommand(0x01, 1);	    //显示清屏
    LcdWriteCommand(0x06, 1);		//写字符时整体不移动
    LcdWriteCommand(0x0c, 1);		//显示开，不开游标，不闪烁
}

void LcdWriteCommand(uchar cmd,uchar chk) 
{
    if(chk)
      WaitForEnable();   // 检测忙信号?
    CLR_RS;	
    CLR_RW; 
    _NOP();
    DataPort=cmd;             //将命令字写入数据端口 
    _NOP();					
    SET_EN;                     //产生使能脉冲信号
    _NOP();
    _NOP();
    CLR_EN;			
}

void LcdWriteData(uchar data) 
{
    WaitForEnable();        //等待液晶不忙
    SET_RS;
    CLR_RW; 
    _NOP();
    DataPort = data;        //将显示数据写入数据端口
    _NOP();
    SET_EN;                 //产生使能脉冲信号
    _NOP(); 
    _NOP(); 
    CLR_EN;		
}

void WaitForEnable(void) 
{
    P4DIR&=0x00;  //将P4口切换为输入状态
    CLR_RS;
    SET_RW;
    _NOP();
    SET_EN; 
    _NOP();
    _NOP();
    while((P4IN&Busy)!=0);  //检测忙标志
    CLR_EN;
    P4DIR |= 0xFF;  //将P4口切换为输出状态
}	
                       
void Delay5ms(void)
{ 
    uint tmp=40000;
    while (tmp!=0)
    {
        tmp--;
    }
}

void Delay10ms(void)
{
    uint tmp;   
    for(tmp=0x3fff;tmp>0;tmp--)
      ;
}

uchar Key4Scan(void)
{
    uchar temp,keyval;
    if(keyin!=0x0f)
    {
        Delay10ms();
        keyval=0;
        if(keyin!=0x0f)
        {
            temp=keyin;
            while(keyin!=0x0f)
              ;
            switch(temp)
            {
            case 0x0e:
              keyval=1;
              break;
            case 0x0d:
              keyval=2;
              break;
            case 0x0b:
              keyval=3;
              break;
            case 0x07:
              keyval=4;
              break;
            default:
              keyval=0;
              break;
            }
        }
    }
    else
      keyval = 0;
    return keyval;
}
