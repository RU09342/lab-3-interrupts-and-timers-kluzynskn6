#include <msp430.h>
#include <config.h>
#include <stdlib.h>

       int count=0;
       int delay=0;
       int winner=0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    delay =rand() %5001 +5000;

    LED1INIT;
    LED1OFF;
    LED2INIT;
    LED2OFF;
    BTN1INIT;
    BTN2INIT;

   TA0SET(1000);
   TA1SET(6);


   _BIS_SR(LPM2_bits+ GIE); // Enable interrupt
   while(1)
   {
   }
}

    //Delayed LED
   #pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer_A0 (void)
   {
	   if (count==delay)
	   {
		   LED1ON;
		   LED2ON;
		   TA0STOP;
	   }
	   else
	   {
		   count++;
	   }
   }

   //Winner LED
  #pragma vector=TIMER1_A0_VECTOR
  __interrupt void Timer_A1 (void)
  {
	   if (winner==1)
	   {
		   TA0STOP;
		   LED1SWITCH;
		   LED2OFF;
	   }
	   if(winner==2)
	   {
		   TA0STOP;
		   LED2SWITCH;
		   LED1OFF;
	   }
  }
   // Button interrupt function
   #pragma vector=PORT1_VECTOR
   __interrupt void Port_1(void)
   {
          if(count<delay)
          {
        	  winner=1;
        	  P1IE&=BIT1;//Disables further inputs from this button
          }
          else
          {
        	  winner=2;
        	  P2IE&=BIT1;//Disables further inputs from other button
          }
          BTN2CLR;// IFG cleared
   }

   // Button interrupt function
   #pragma vector=PORT2_VECTOR
   __interrupt void Port_2(void)
   {
          if(count<delay)
          {
        	  winner=2;
        	  P2IE&=BIT1;//Disables further inputs from this button
          }
          else
          {
        	  winner=1;
        	  P1IE&=BIT1;//Disables further inputs from other button
          }
          BTN1CLR;// IFG cleared
   }
