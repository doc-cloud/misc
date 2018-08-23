//******************************************************************************
//  MSP-FET430P140 Demo - WDT, Toggle P3.4, Interval Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P3.4 using software timed by WDT ISR. Toggle rate is
//  exactly 250ms based on 32kHz ACLK WDT clock source.  In this example the
//  WDT is configured to divide 32768 watch-crystal(2^15) by 2^13 with an ISR
//  triggered @ 4Hz.
//  ACLK= LFXT1= 32768, MCLK= SMCLK= DCO~ 800kHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//		  MSP430F149
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
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
  BoardConfig(0xb8);                       
  WDTCTL = WDT_ADLY_250;                    // WDT 250ms, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P3DIR |= BIT4;                            // Set P3.4 to output direction

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P3OUT ^= BIT4;                            // Toggle P3.4 using exclusive-OR
}
