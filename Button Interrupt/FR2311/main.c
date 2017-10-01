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

    TB0SET(10);


    _BIS_SR(GIE); // Enable interrupt
    while(1)
    {
    }

}

 //Timer interrupt function
#pragma vector=TIMER0_B0_VECTOR
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
#pragma vector=PORT1_VECTOR
__interrupt void BTNs(void)
{
	    if(count==6)
	    {
	        count=0;
	        color^=1;
	    }
	    else
	        count++;

	    TB0CCR0=2500+(1250*count);

	    if(BTN1UP)
	    {
	    	TB0CTL  = TBSSEL_2 + MC_1 + ID_3; // SMCLK/8, upmode
	    }
	    else
	    {
	        TB0CTL=MC_0;
	        LED1OFF;
			LED2OFF;
	    }

	    BTN1SWAP;  // swaps Hi/lo edge
	    BTN1CLR;// IFG cleared
}

