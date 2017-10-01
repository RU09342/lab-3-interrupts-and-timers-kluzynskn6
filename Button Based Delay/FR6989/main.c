#include <msp430.h>
#include <config.h>

long int cs=0;
int Hz=10;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //disables high impedence mode


    LED1INIT;
    LED2INIT;

    BTN1INIT;

    TA1SET(100);


    TA0SET(10);


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMER1_A0_VECTOR
   __interrupt void Timer_A1 (void)
   {
	   LED2SWITCH;
	   cs++;
   }

	#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer_A (void)
   {

	   LED1SWITCH;
   }

#pragma vector=PORT1_VECTOR
__interrupt void Btn1(void)
{

	if(BTN1UP) //When button released
	{
		LED2OFF;
		TA1CTL=MC_0;//stops timer
		//Uses the amount of interrupts to determine time held
		if(cs>=35)//if it's a hold
		{
		//If hold, set TA0CCRO to frequency(time)
			TA0CCR0=125*cs;
			Hz=cs/100;
		}
		else //If it's a press
		{
			Hz++;
			TA0CCR0=125000/Hz;
		}
		//Clear registers for next press
		TA1R=0;
		cs=0;
	}
	else //When button is pressed
	{
		TA1R=0;
		cs=0;
		TA1CTL =  TASSEL_2 + MC_1 + ID_3;//start timer again
	}

       BTN1SWAP;
       BTN1CLR; // IFG cleared
}
