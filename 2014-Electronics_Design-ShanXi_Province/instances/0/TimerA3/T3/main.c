//******************************************************************************
//  MSP-FET430P140 Demo - Timer_A, Toggle P3.4, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P3.4 using software and Timer_A overflow ISR.
//  In this example an ISR triggers when TA overflows. Inside the TA
//  overflow ISR P3.4 is toggled. Toggle rate is approximatlely 12Hz.
//  Proper use of the TAIV interrupt vector generator is demonstrated.
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
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BoardConfig(0xb8);
  P3DIR |= BIT4;                            // P3.4 output
  TACTL = TASSEL_2 + MC_2 + TAIE;           // SMCLK, contmode, interrupt

   _EINT();
   while(1);
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
 switch( TAIV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 10: P3OUT ^= BIT4;                  // overflow
            break;
 }
}

