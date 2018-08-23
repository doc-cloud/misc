//******************************************************************************
//  MSP-FET430P140 Demo - Timer_A, Toggle P3.4, CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P3.4 using software and TA_0 ISR. Timer_A is
//  configured for up mode, thus the timer overflows when TAR counts
//  to CCR0. In this example, CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~800kHz
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P3.4|-->LED
//
//  Dasheng
//  LiTian Electronic Inc.
//  Feb 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x14x.h>
#include  "BoardConfig.h"

int i=0;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BoardConfig(0xb8);
  P3DIR |= BIT4; 
  P3SEL |= BIT4;                          // P3.4 output
  //CCTL0 = CCIE; 
  CCTL0 = OUTMOD_7;                               // CCR0 interrupt enabled
  CCR0 = 5000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
   
  //_EINT();                                   // Enter LPM0 w/ interrupt
}
