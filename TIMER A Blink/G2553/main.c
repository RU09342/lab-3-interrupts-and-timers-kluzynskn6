#include <msp430.h> 


int frequency (int);

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1SEL &=0xBA; //Sets P1.6, 1.1, and 1.3 to I/O
    P1DIR |=0x41; //Sets P1.6 and P1.1 to outputs


    TA1CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA1CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TA1CCR0 =  frequency(12);          //Sets to 12 Hz

    TA0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TA0CCR0 =  frequency(4);           //Sets to 4 Hz


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMER1_A0_VECTOR
   __interrupt void Timer_A1 (void)
   {
	   //_BIS_SR(LPM0_EXIT);
       P1OUT^=0x40;
   }

	#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer_A (void)
   {
	   P1OUT^=0x01;
   }

   int frequency(int Hz)
   {
	   //Returns the number for TAxCCRx when the clock is to SMCLK/8
	   return 125000/Hz;
   }
