#include <msp430.h>
#ifdef _MSP430F5529_ 
	#define LED1INIT (P1SEL&=~BIT0; P1DIR|=BIT0)
	#define LED1ON (P1OUT |= BIT0)
	#define LED1OFF (P1OUT &=~BIT0)
	#define LED1SWITCH (P1OUT ^=BIT0)

	#define LED2INIT (P4SEL&=~BIT7; P4DIR|=BIT7)
	#define LED2ON (P4OUT |= BIT7)
	#define LED2OFF (P4OUT &=~BIT7)
	#define LED2SWITCH (P4OUT ^=BIT7) 

	#define BTN1INIT P2DIR &= 0xFD;P2REN |= 0x02;P2OUT |= 0x02;P2IE |= 0x02; P2IES |= 0x02;P2IFG &= 0xFD;             
	#define BTN2INIT P1DIR &= 0xFD;P1REN |= 0x02;P1OUT |= 0x02;P1IE |= 0x02; P1IES |= 0x02;P1IFG &= 0xFD;
#endif // _MSP430F5529_

#ifdef _MSP430G2553_ 
	#define LED1INIT (P1SEL&=~BIT0; P1DIR|=BIT0)
	#define LED1ON (P1OUT |= BIT0)
	#define LED1OFF (P1OUT &=~BIT0)
	#define LED1SWITCH (P1OUT ^=BIT0)

	#define LED2INIT (P1SEL&=~BIT6; P1DIR|=BIT6)
	#define LED2ON (P1OUT |= BIT6)
	#define LED2OFF (P1OUT &=~BIT6)
	#define LED2SWITCH (P1OUT ^=BIT6) 

	#define BTN1INIT P1DIR &= 0xFD;P1REN |= BIT3;P1OUT |= BIT3;P1IE |= BIT3; P1IES |= BIT3;P1IFG &= 0x~BIT3;             
#endif // _MSP430G2553_
