//******************************************************************************
//  MSP-FET430P140 Demo - Timer_A, Toggle P3.4, CCR1 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P3.4 using software and TA_1 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//  During the TA_1 ISR, P3.4 is toggled and 50000 clock cycles are added to
//  CCR0. TA_1 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR. Proper use of the TAIV interrupt vector generator
//  is demonstrated.
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

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= BIT4;                            // P3.4 output
  CCTL1 = CCIE;                             // CCR1 interrupt enabled
  CCR1 = 50000;
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, Contmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TAIV )
  {
  case  2:                                  // CCR1
    {
    P3OUT ^= BIT4;                          // Toggle P3.4
    CCR1 += 50000;                          // Add Offset to CCR1
    }
           break;
  case  4: break;                           // CCR2 not used
  case 10: break;                           // overflow not used
 }
}

