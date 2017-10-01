#include <msp430.h>
#include <msp430g2553.h>

       float count=0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

       P1SEL &=0xBA; //Sets P1.6, 1.1, and 1.3 to I/O
       P1DIR |=0x41; //Sets P1.6 and P1.1 to outputs

       P1DIR &= 0xF7;  //Sets button 1 to an input
       P1REN |= 0x08;  //Enables resistor
       P1OUT |= 0x08;  // Sets resistor to pull up
       P1IE  |= 0x08;  // interrupt enabled
       P1IES |= 0x08;  // Hi/lo edge
       P1IFG &= 0xF7;  // IFG cleared

       TA0CCTL0= CCIE;                   // CCR0 interrupt enabled
       TA0CTL  = TASSEL_2 + MC_1 + ID_3; // SMCLK/8, upmode
       TA0CCR0 = 10000;                  //Sets to 12 Hz


       _BIS_SR(GIE); // Enable interrupt
       while(1)
       {
           if(count==1||count==4)
           {
               TA0CCR0 = 2500; //Sets to 3 Hz
           }
           if(count==2||count==5)
           {
               TA0CCR0 = 5000; //Sets to 6 Hz
           }
           if(count==3||count==6)
           {
               TA0CCR0 = 10000;//Sets to 12 Hz
           }
       }

   }

    //Timer interrupt function
   #pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer_A (void)
   {
       if(count==0)
       {
           P1OUT&=0xBE; //Clears P1.6 and 1.0
       }
       else if(count<=3)
       {
           P1OUT^=0x01;//Invert P1.0
           P1OUT&=0xBF;//Shuts off P1.6
       }
       else
       {
           P1OUT^=0x40;//Inverts P1.6
           P1OUT &=0xFE;//Shuts off P1.0
       }
   }

   // Button interrupt function
   #pragma vector=PORT1_VECTOR
   __interrupt void Port_1(void)
   {
          if(count==6)
              count=0;
          else
              count+=.5;

          P1DIR ^=0x41;
          P1IES ^= 0x08;  // Hi/lo edge
          P1IFG &=0xF7;// IFG cleared
   }

