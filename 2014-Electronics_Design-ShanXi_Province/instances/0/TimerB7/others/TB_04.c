//******************************************************************************
//  MSP-FET430P140 Demo - Timer_B, Toggle P3.4, Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P3.4 using software and the Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows. Inside the ISR P3.4
//  is toggled. Toggle rate is exactly 0.5Hz. Proper use of the TBIV
//  interrupt vector generator is demonstrated.
//  ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~800kHz
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= BIT4;                            // Set P3.4 to output direction
  TBCTL = TBSSEL_1 + MC_2 + TBIE;           // ACLK, contmode, interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer_B7 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
 switch( TBIV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 14: P3OUT ^= BIT4;                  // overflow
           break;
  }
}

