//*****************************************************************************
//  MSP-FET430P140 Demo - Timer_A, Toggle P3.4, CCR0 Up Mode ISR, 32kHz INCLK
//
//  Description: Toggle P3.4 using software and the TA_0 ISR. Timer_A is
//  configured for up mode, thus the timer overflows when TAR counts
//  to CCR0. In this example, CCR0 is loaded with 1000-1.
//  ACLK = TACLK = INCLK = 32768Hz, MCLK = SMCLK = default DCO ~800kHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |      P2.0/ACLK|---+
//        |               |   |
//        |     P2.1/INCLK|<--+
//        |               |
//        |           P3.4|-->LED (Toggle rate is ACLK/1000)
//
//  Dasheng
//  LiTian Electronic Inc.
//  Feb 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//*****************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= BIT4;                            // P3.4 output
  P2SEL |= 0x03;                            // Select P2.0,1 ACLK,INCLK options
  P2DIR |= 0x01;                            // Set P2.0 as output

  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 1000-1;
  TACTL = TASSEL_3 + MC_1;                  // INCLK, upmode

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P3OUT ^= BIT4;                            // Toggle P3.4
}
