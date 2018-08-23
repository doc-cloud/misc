//******************************************************************************
//  MSP-FET430P140 Demo - WDT, Toggle P3.4, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P3.4 using software timed by the WDT ISR. Toggle rate
//  is approximately 30ms based on default ~ 800khz DCO/SMCLK clock source
//  used in this example for the WDT.
//  ACLK= n/a, MCLK= SMCLK= default DCO~ 800k
//
//		  MSP430F149
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P3.4|-->LED
//
//  Dasheng
//  LiTian Electronic Inc.
//  Feb 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x14x.h>
#include  "BoardConfig.h"

void main(void)
{
  BoardConfig(0xbf);                        //关闭数码管、流水灯和电平转换
  WDTCTL = WDT_ADLY_1000;                     // Set Watchdog Timer interval to ~30ms
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P3DIR |= BIT4;                            // Set P3.4 to output direction
  _EINT();
 
  LPM3;
  
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog(void)
{
  P3OUT ^= BIT4;                            // Toggle P3.4 using exclusive-OR
}
