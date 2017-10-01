#include <msp430.h> 
#include <config.h>

int frequency (int);

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED1INIT;
    LED2INIT;

    TA1SET(12);

    TA0SET(4);


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMER1_A0_VECTOR
   __interrupt void Timer_A1 (void)
   {
	   //_BIS_SR(LPM0_EXIT);
       LED1SWITCH;
   }

	#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer_A (void)
   {
	   LED2SWITCH;
   }

   int frequency(int Hz)
   {
	   //Returns the number for TAxCCRx when the clock is to SMCLK/8
	   return 125000/Hz;
   }
