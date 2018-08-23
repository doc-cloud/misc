//******************************************************************************
//  MSP-FET430P140 Demo - Timer_A, Toggle P3.4, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P3.4 using software and the TA_0 ISR. Timer_A is
//  configured for up mode, thus the timer overflows when TAR counts
//  to CCR0. In this example, CCR0 is loaded with 1000-1.
//  Toggle rate = 32768/(2*1000) = 16.384
//  ACLK = TACLK = 32768Hz, MCLK = SMCLK = default DCO ~800kHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
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

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  P3DIR |= BIT4;                        // P3.4 output
  CCTL0 = CCIE;                         // CCR0 interrupt enabled
  CCR0 = 1000-1;
  TACTL = TASSEL_1 + MC_1;              // ACLK, upmode

  _BIS_SR(LPM3_bits + GIE);             // Enter LPM3 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P3OUT ^= BIT4;                        // Toggle P3.4
}

