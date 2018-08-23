//******************************************************************************
//  MSP-FET430P140 Demo - ADC12, Sample A0, Set P3.4 if A0 > 0.5*AVcc
//
//  Description: A single sample is made on A0 with reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC12SC
//  automatically cleared at EOC. ADC12 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC12
//  conversion complete, ADC12_ISR will force exit from LPM0 in Mainloop on
//  reti. If A0 > 0.5*AVcc, P3.4 set, else reset.
//
//                MSP430F149
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//      Vin-->|P6.0/A0      P3.4|--> LED
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
  ADC12CTL0 = SHT0_2 + ADC12ON;             // Set sampling time, turn on ADC12
  ADC12CTL1 = SHP;                          // Use sampling timer
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ENC;                         // Conversion enabled
  P6SEL |= 0x01;                            // P6.0 ADC option select
  P3DIR |= BIT4;                            // P3.4 output

  for (;;)
  {
    ADC12CTL0 |= ADC12SC;                   // Sampling open
    _BIS_SR(CPUOFF + GIE);                  // LPM0, ADC12_ISR will force exit
  }
}

// ADC12 interrupt service routine
#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR (void)
{
    if (ADC12MEM0 < 0x7FF)
      P3OUT &= ~BIT4;                       // Clear P3.4 LED off
    else
      P3OUT |= BIT4;                        // Set P3.4 LED on
    _BIC_SR_IRQ(CPUOFF);                    // Clear CPUOFF bit from 0(SR)
}
