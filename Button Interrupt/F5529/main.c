#include <msp430.h> 
#include <config.h>

int count=0;
int color=0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

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
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	color ^=1;
	P1IFG &=0xFD;
}

// Button interrupt function
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if(count==6)
        count=0;
    else
        count++;

    TA0CCR0=2500+ (1250*count);

    if((P2IN & BIT1)==BIT1)
    {
    	TA0CTL  = TASSEL_2 + MC_1 + ID_3; // SMCLK/8, upmode
    }
    else
    {
        TA0CTL=MC_0;
        LED1OFF;
		LED2OFF;
    }

    P2IES ^= 0x02;  // swaps Hi/lo edge
    P2IFG &=0xFD;// IFG cleared
}
/*#include <msp430.h>
#include <config.h>

int count=0;
int color=0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1SEL &=0xFC; //Sets P1.1, and 1.0 to I/O
    P1DIR |=0x01; //Sets P1.0 to outputs
    P4SEL &=0x7F; //Sets P4.7 to I/O
    P4DIR |=0x80; //Sets P4.7 to output

    P1DIR &= 0xFD;  //Sets button 1 to an input
    P1REN |= 0x02;  //Enables resistor
    P1OUT |= 0x02;  // Sets resistor to pull up
    P1IE  |= 0x02;  // interrupt enabled
    P1IES |= 0x02;  // High edge
    P1IFG &= 0xFD;  // IFG cleared

    P2DIR &= 0xFD;  //Sets button 2 to an input
    P2REN |= 0x02;  //Enables resistor
    P2OUT |= 0x02;  // Sets resistor to pull up
    P2IE  |= 0x02;  // interrupt enabled
    P2IES |= 0x02;  // High edge
    P2IFG &= 0xFD;  // IFG cleared

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
        P1OUT&=0xFE; //Clears P1.0
        P4OUT&=0x7F; //Clears P4.7
    }
    else if(color==0)
    {
        P1OUT^=0x01;//Invert P1.0
        P4OUT&=0x7F;//Shuts off P4.7
    }
    else
    {
        P4OUT^=0x80;//Inverts P4.7
        P1OUT &=0xFE;//Shuts off P1.0
    }
}

// Button interrupt function
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	color ^=1;
	P1IFG &=0xFD;
}

// Button interrupt function
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if(count==6)
        count=0;
    else
        count++;

    TA0CCR0=2500+ (1250*count);

    P1DIR ^=0x01;
    P4DIR ^=0x80;

    P2IES ^= 0x02;  // swaps Hi/lo edge
    P2IFG &=0xFD;// IFG cleared
}
 *
 */
