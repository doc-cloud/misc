//******************************************************************************
//  MSP-FET430P140 Demo - Timer_B, Toggle P3.4, CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P3.4 using software and TB_0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to CCR0. In this example, CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~800kHz
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

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BoardConfig(0xb8);
  P3DIR |= BIT4;                            // Set P3.4 to output direction
  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
  TBCCR0 = 20000;
  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, upmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P3OUT ^= BIT4;                            // Toggle P3.4 using exclusive-OR
}
