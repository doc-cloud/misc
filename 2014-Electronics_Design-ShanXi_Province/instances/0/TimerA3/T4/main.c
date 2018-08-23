//******************************************************************************
//  MSP-FET430P140 Demo - Timer_A, Toggle P3.4, Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P3.4 using software and the Timer_A overflow ISR.
//  In this example an ISR triggers when TA overflows. Inside the ISR P3.4
//  is toggled. Toggle rate is exactly 0.5Hz. Proper use of the TAIV interrupt
//  vector generator is demonstrated.
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
#include  "BoardConfig.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BoardConfig(0xb8);
  P3DIR |= BIT4;                            // P3.4 output
  TACTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TAIV )
  {
    case  2:  break;                        // CCR1 not used
    case  4:  break;                        // CCR2 not used
    case 10:  P3OUT ^= BIT4;                // overflow
              break;
  }
}
