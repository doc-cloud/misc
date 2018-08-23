//*******************************************************************************
//  MSP-FET430P140 Demo - Software Toggle P3.4
//
//  Description: Toggle P3.4 by xor'ing P3.4 inside of a software loop.
//  ACLK= n/a, MCLK= SMCLK= default DCO ~800k
//
//                MSP430F149
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

#include  <msp430x16x.h>
#include  "BoardConfig.h"

void main(void)
{
//  BoardConfig(0xb8);
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P3DIR |= BIT3;                            // Set P3.4 to output direction

  for (;;)
  {
    volatile unsigned int i;                //get address from original place in memory

    P3OUT ^= BIT3;                          // Toggle P3.4 using exclusive-OR

    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
  }
}
