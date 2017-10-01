/*#include <msp430.h>

long int ms=0;
int Hz=10;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1SEL &=0xFE; //Sets P1.1 to I/O
    P1DIR |=0x41; //Sets P1.1 to output

    P1DIR &= 0xF7;  //Sets button 1 to an input
    P1REN |= 0x08;  //Enables resistor
    P1OUT |= 0x08;  // Sets resistor to pull up
    P1IE  |= 0x08;  // interrupt enabled
    P1IES |= 0x08;  // high edge interrupt
    P1IFG &= 0xF7;  // IFG cleared

    TA1CCTL0 = CCIE;            // CCR0 interrupt enabled
    TA1CTL = TASSEL_1 + MC_0;   // ACLK, stopped
    TA1CCR0=32;		 			//Sets to 1024 Hz, interrupt every ~1ms


    TA0CCTL0 = CCIE;          // CCR0 interrupt enabled
    TA0CTL = TASSEL_1 + MC_1; // ACLK, upmode
    TA0CCR0 =  3277;		  //Sets to 10 Hz


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMER1_A0_VECTOR
   __interrupt void Timer_A1 (void)
   {
	  // P1OUT^=0x40;
	   ms++;
   }

	#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer_A (void)
   {

	   P1OUT^=0x01;
   }

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

	if((P1IN & BIT3) == BIT3) //When button released
	{
		TA1CTL=MC_0;//stops timer
		//Uses the amount of interrupts + current timer value to determine time held
		if(ms>=500)//if it's a hold
		{
		//If hold, set TA0CCRO to frequency(time)
			TA0CCR0=32768/(ms>>10);
			Hz=ms>>10;
		}
		else //If it's a press
		{
			Hz++;
			TA0CCR0=32768/Hz;
		}
	}
	else //When button is down
	{
		TA1R=0;//clear timer register
		ms=0;//clear ms
		TA1CTL =  TASSEL_1 + MC_1;//start timer again
	}

       P1IES ^= 0x08;// swap Hi/lo edge
       P1IFG &=0xF7; // IFG cleared
}
*/

//Working code, but limited to 1 Hz LED blink
#include <msp430.h>


int getFrequency (int);
long int cs=0;
int Hz=10;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1SEL &=0xFE; //Sets P1.1 to I/O
    P1DIR |=0x41; //Sets P1.1 to output

    P1DIR &= 0xF7;  //Sets button 1 to an input
    P1REN |= 0x08;  //Enables resistor
    P1OUT |= 0x08;  // Sets resistor to pull up
    P1IE  |= 0x08;  // interrupt enabled
    P1IES |= 0x08;  // high edge interrupt
    P1IFG &= 0xF7;  // IFG cleared

    TA1CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA1CTL = TASSEL_2 + MC_0 + ID_3;   // SMCLK/8, stopped
    TA1CCR0=1250;		 			  //Sets to 100 Hz, interrupt every 1cs


    TA0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA0CTL = TASSEL_2 + MC_3 + ID_3;   // SMCLK/8, upmode
    TA0CCR0 =  getFrequency(Hz);           //Sets to 4 Hz


    _BIS_SR(LPM0_bits + GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMER1_A0_VECTOR
   __interrupt void Timer_A1 (void)
   {
	  // P1OUT^=0x40;
	   cs++;
   }

	#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer_A (void)
   {

	   P1OUT^=0x01;
   }

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

	if((P1IN & BIT3) == BIT3) //When button released
	{
		TA1CTL=MC_0;//stops timer
		//Uses the amount of interrupts to determine time held
		if(cs>=25)//if it's a hold
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
	}
	else //When button is down
	{
		TA1R=0;//clear timer register
		cs=0;//clear cs
		TA1CTL =  TASSEL_2 + MC_1 + ID_3;//start timer again
	}

       P1IES ^= 0x08;// swap Hi/lo edge
       P1IFG &=0xF7; // IFG cleared
}

   int getFrequency(int hz)
   {
	   //Returns the number for TAxCCRx when the clock is to SMCLK/8
	   return  125000/hz;
   }

