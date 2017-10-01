#include <msp430.h> 
#include <config.h>

int frequency (int);

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //disables high impedence mode

    LED1INIT;
    LED2INIT;

    TB1SET(12);

    TB0SET(4);


    _BIS_SR(LPM1_bits+GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMER1_B0_VECTOR
   __interrupt void Timer_A1 (void)
   {
       LED1SWITCH;
   }

	#pragma vector=TIMER0_B0_VECTOR
   __interrupt void Timer_A (void)
   {
	   LED2SWITCH;
   }
