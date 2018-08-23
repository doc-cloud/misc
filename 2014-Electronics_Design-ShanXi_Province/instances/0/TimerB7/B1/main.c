//******************************************************************************
//  MSP-FET430P140 Demo - Timer_B, Toggle P3.4, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P3.4 using software and TB_0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TBCLK.
//  During the TB_0 ISR, P3.4 is toggled and 50000 clock cycles are added to
//  CCR0. TB_0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TB_ISR.
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
  P3DIR |= BIT4;                            // P3.4 output
  TBCCTL0 = CCIE;                           // CCR0 interrupt enabled
  TBCCR0 = 50000;
  TBCTL = TBSSEL_2 + MC_2;                  // SMCLK, contmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P3OUT ^= BIT4;                            // Toggle P3.4
//  TBCCR0 += 50000;                          // Add Offset to CCR0
}
