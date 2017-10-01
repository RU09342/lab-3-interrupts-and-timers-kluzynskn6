#include <msp430.h>
#include <config.h>

long int cs=0;
int Hz=10;
int getFrequency(int);

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED1INIT;
    LED2INIT;

    BTN1INIT;

    TA1CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA1CTL = TASSEL_2 + MC_0 + ID_3;   // SMCLK/8, stopped
    TA1CCR0=getFrequency(100);		   //Sets to 100 Hz, interrupt every 1cs


    TA0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TA0CCR0 =  getFrequency(Hz);           //Sets to 4 Hz


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

#pragma vector=PORT2_VECTOR
__interrupt void Btn1(void)
{

	if(BTN1UP) //When button released
	{
		TA1CTL=MC_0;//stops timer
		//Uses the amount of interrupts to determine time held
		if(cs>=30)//if it's a hold
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
		TA1CTL =  TASSEL_2 + MC_1 + ID_3;//start timer again
	}

       P2IES ^= 0x02;// swap Hi/lo edge
       P2IFG &=0xFD; // IFG cleared
}
int getFrequency(int hz)
{
	   //Returns the number for TAxCCRx when the clock is to SMCLK/8
	   return  125000/hz;
}

/*#include <msp430.h>
#include <config.h>


long int cs=0;
int Hz=10;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    LED1INIT;
    BTN1INIT;

    TA1SET(100);
    TA0SET(Hz);


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
	   LED1SWITCH;
   }

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

	if(BTN1UP) //When button released
	{
		TA1STOP;
		//Uses the amount of interrupts + current timer value to determine time held
		if(cs>=25)//if it's a hold
		{
		//If hold, set TA0CCRO to frequency(time)
			Hz=cs/100;
			TA0CCR0=125000.0/Hz;
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
		TA1START;//start timer again
	}

       P1IES ^= 0x08;// swap Hi/lo edge
       P1IFG &=0xF7; // IFG cleared
}
 *
 */
