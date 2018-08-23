//******************************************************************************
//  MSP-FET430P140 Demo - ADC12, Repeated Single Channel Conversions
//
//  Description: This example shows how to perform repeated conversions on a
//  single channel using "repeat-single-channel" mode.  AVcc is used for the
//  reference and repeated conversions are performed on Channel A0. Each
//  conversion result is moved to an 8-element array called results[].  Test by
//  applying a voltage to channel A0, then running. To view the conversion results
//  open a watch window and view 'results.'
//  This can run even in LPM4 mode as ADC has its own clock
//
//               MSP430F149
//             ---------------
//            |               |
//     Vin -->|P6.0/A0        |
//            |               |
//
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

#define   Num_of_Results   8

static unsigned int results[Num_of_Results];  // Needs to be global in this
                                              // example. Otherwise, the
                                              // compiler removes it because it
                                              // is not used for anything.

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P6SEL |= 0x01;                            // Enable A/D channel A0
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // Turn on ADC12, set sampling time
  ADC12CTL1 = SHP+CONSEQ_2;                 // Use sampling timer, set mode
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ENC;                         // Enable conversions
  ADC12CTL0 |= ADC12SC;                     // Start conversion
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0,Enable interrupts
}


#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  results[index] = ADC12MEM0;               // Move results
  index = (index+1)%Num_of_Results;         // Increment results index, modulo
}
