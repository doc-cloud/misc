#include <msp430x14x.h>

void main(void)
{
WDTCTL = WDTPW + WDTHOLD;                       // Stop WDT
P3SEL |= 0x30;                                  // P3.4,5 = USART0 TXD/RXD
ME1 |= UTXE0 + URXE0;                           // Ena¡Á¡Áe USART0 TXD/RXD
UCTL0 |= CHAR;                                  // 8-bit character
UTCTL0 |= SSEL0;                                // UCLK = ACLK
UBR00 = 0x03; // 32k/9600 - 3.41
UBR10 = 0x00; //
UMCTL0 = 0x4A; // Modulation
UCTL0 &= ~SWRST; // Initialize USART state machine
IE1 |= URXIE0; // Ena¡Á¡Áe USART0 RX interrupt
_EINT();
while(1)
{
    ;
}
//_BIS_SR(LPM3_bits + GIE); // Enter LPM3 w/ interrupt
}

#pragma vector=UART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  
while (!(IFG1 & UTXIFG0)); // USART0 TX buffer ready?
TXBUF0 = RXBUF0; // RXBUF0 to TXBUF0
}