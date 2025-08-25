// Program Name: Digital Output IR Sensor Code for MSP430FR5969
// Author: Fayyaz Nisar Shaikh
// Email: fayyaz.shaikh7862005@gmail.com
// LinkedIn: https://www.linkedin.com/in/fayyaz-shaikh-7646312a3/

#include <stdio.h>
#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;      

  // Configure GPIO
  P1OUT &= ~BIT0;                 
  P1DIR |= BIT0;                  

  P3DIR &= ~BIT4;
  P3REN |= BIT4;
  P3OUT |= BIT4;

  PM5CTL0 &= ~LOCKLPM5;           // disable gpio power on mode

  while(1)
  {
    if(!(P3IN & BIT4)){
          printf("object detected\n");
          P1OUT |= BIT0;
    }
    else{
          P1OUT &= ~BIT0;
    }
    __delay_cycles(1000); // for better sensitivity 
  }
}
