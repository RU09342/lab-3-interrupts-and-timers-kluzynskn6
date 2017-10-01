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

    TB1SET(100);

    TB0SET(10);


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMER1_B0_VECTOR
   __interrupt void Timer_A1 (void)
   {
	   LED2SWITCH;
	   cs++;
   }

	#pragma vector=TIMER0_B0_VECTOR
   __interrupt void Timer_A (void)
   {

	   LED1SWITCH;
   }

#pragma vector=PORT1_VECTOR
__interrupt void Btn1(void)
{

	if(BTN1UP) //When button released
	{
		TB1CTL=MC_0;//stops timer
		//Uses the amount of interrupts to determine time held
		if(cs>=30)//if it's a hold
		{
		//If hold, set TA0CCRO to frequency(time)
			TB0CCR0=125*cs;
			Hz=cs/100;
		}
		else //If it's a press
		{
			Hz++;
			TB0CCR0=125000/Hz;
		}
		//Clear registers for next press
		TB1R=0;
		cs=0;
	}
	else //When button is pressed
	{
		TB1R=0;
		cs=0;
		TB1CTL =  TBSSEL_2 + MC_1 + ID_3;//start timer again
	}

       BTN1SWAP;
       BTN1CLR;
}
