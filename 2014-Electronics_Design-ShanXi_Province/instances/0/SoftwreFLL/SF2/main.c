//******************************************************************************
//  MSP-FET430P140 Demo - Basic Clock, Implement Cont. SW FLL with Auto RSEL
//
//  Description: Set DCO clock to (Delta)*(4096) using software FLL. DCO clock
//  is output on P5.5 as SMCLK.  DCO clock, which is the selected SMCLK source
//  for timer_A is integrated over ACLK/8 (4096) continuously. CCR2 captures
//  ACLK/8.  To use this SW FLL, Timer_A must be operating in continous mode
//  with a watch crystal used for ACLK. Delta must be kept in a  range that
//  allows possible DCO speeds.  Minimum Delta must ensure
//  the AdjDCO ISR can complete. Maximum delta  can be calculated by
//  f(DCOx7) / 4096.  f(DCOx7) found in device specific datasheet.
//  ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = DCO = 4096xDelta
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.5|--> SMLCK = target DCO
//        |           P5.6|--> ALCK = 4096
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>
#include  "BoardConfig.h"

//#define DELTA 977                       // target DCO= DELTA*(4096) = 4Mhz
//#define DELTA 900                       // target DCO= DELTA*(4096) = 3686400
#define DELTA 250                           // target DCO= DELTA*(4096) = 1048576
//#define DELTA 70                        // target DCO= DELTA*(4096) = 286720

unsigned int Compare, Oldcapture;

void main(void)
{
  BoardConfig(0xb8);
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= DIVA_3;                        // ACLK= LFXT1CLK/8
  CCTL2 = CM_1 + CCIS_1 + CAP + CCIE;       // CAP, ACLK, interrupt
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear
  P5DIR |= 0x60;                            // P5.5,6 output
  P5SEL |= 0x60;                            // P5.5,6 SMCLK, ACLK output

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TAIV )
  {
    case  2: break;                         // CCR1 not used
    case  4:
    {
    Compare = CCR2;                         // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = CCR2;                      // Save current captured SMCLK
    if (DELTA == Compare) break;            // If equal, leave "While(1)"
    if (DELTA < Compare)
      {
        DCOCTL--;
        if (DCOCTL == 0xFF)                 // DCO is too fast, slow it down
        {
          if (!(BCSCTL1 == (XT2OFF + DIVA_3)))
          BCSCTL1--;                        // Did DCO roll under?, Sel lower RSEL
        }
      }
    else
      {
        DCOCTL++;                           // DCO is too slow, speed it down
        if (DCOCTL == 0x00)
        {
          if (!(BCSCTL1 == (XT2OFF + DIVA_3 + 0x07)))
          BCSCTL1++;                        // Did DCO roll over? Sel higher RSEL
        }
      }
    }
  case 10: break;                           // not used
  }
}

