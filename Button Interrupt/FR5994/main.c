#include <msp430.h> 
#include <config.h>

int count=0;
int color=0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //disables high impedence mode

    LED1INIT;
    LED2INIT;

    BTN1INIT;
    BTN2INIT;

    TA0CCTL0= CCIE;                   // CCR0 interrupt enabled
    TA0CTL  = TASSEL_2 + MC_1 + ID_3; // SMCLK/8, upmode
    TA0CCR0 = 10000;                  //Sets to 12 Hz


    _BIS_SR(GIE); // Enable interrupt
    while(1)
    {
    }

}

 //Timer interrupt function
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    if(count==0)
    {
        LED1OFF;
    	LED2OFF;
    }
    else if(color==0)
    {
        LED1SWITCH;
        LED2OFF;
    }
    else
    {
        LED2SWITCH;
        LED1OFF;
    }
}

// Button interrupt function
#pragma vector=PORT5_VECTOR
__interrupt void BTNs(void)
{
	if ((P5IN&BIT5)!=BIT5)//BTN2 pressed
	{
	color ^=1;
	BTN2CLR;// IFG cleared
	return;
	}
	else //BTN1 pressed
	{
	    if(count==6)
	        count=0;
	    else
	        count++;

	    TA0CCR0=2500+(1250*count);

	    if(BTN1UP)
	    {
	    	TA0CTL  = TASSEL_2 + MC_1 + ID_3; // SMCLK/8, upmode
	    }
	    else
	    {
	        TA0CTL=MC_0;
	        LED1OFF;
			LED2OFF;
	    }

	    BTN1SWAP;  // swaps Hi/lo edge
	    BTN1CLR;// IFG cleared

	}
}

