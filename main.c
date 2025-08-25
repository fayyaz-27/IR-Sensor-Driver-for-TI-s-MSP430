// Program Name: Digital Output IR Sensor 
// Author: Fayyaz Nisar Shaikh

#include <stdio.h>

#include <msp430.h>

void uart_init(void) {
    UCA0CTLW0 |= UCSWRST;           // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;     // Clock = SMCLK
    UCA0BR0 = 104;                  // 9600 baud at 1MHz clock
    UCA0BR1 = 0;
    UCA0MCTLW = 0x1100;             // Modulation
    UCA0CTLW0 &= ~UCSWRST;          // Release from reset
}

void uart_putc(char c) {
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = c;
}

void uart_puts(const char *s) {
    while (*s) uart_putc(*s++);
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

  // Configure GPIO
  P1OUT &= ~BIT0;                 // Clear P1.0 output latch for a defined power-on state
  P1DIR |= BIT0;                  // Set P1.0 to output direction

  P3DIR &= ~BIT4;
  P3REN |= BIT4;
  P3OUT |= BIT4;

  PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
                                  // to activate previously configured port settings

    uart_init();


  while(1)
  {
    if(!(P3IN & BIT4)){
       uart_puts("Object detected!\r\n");
      printf("object detected\n");
      P1OUT |= BIT0;
    }
    else{
          P1OUT &= ~BIT0;
    }
    __delay_cycles(1000);
  }
}
