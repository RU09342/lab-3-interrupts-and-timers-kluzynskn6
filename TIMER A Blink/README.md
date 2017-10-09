# TIMER A Blink

### Nick Kluzynski

One of the most common peripherals on the MSP430 is the timer. Using the timer, the CPU can be shut off and run with very little power consumption. Whenever the timer throws an interrupt flag, the CPU turns on, executes the code inside the Interrupt, and reenters sleep. By using the timer, precision timing is much easrier to acheive.

## Usage
This project can be used to execute code at precise timing intervals. In the current code, 2 LEDs are blinking at 2 different rates utilizing 2 different timers.



## Timer Module

The timer module available on the MSP430 has various control register that can be used to modify the function of the timer module. The main control register can be used to set the count speed by utilizing different clocks as well as pre-dividers. The main register also sets the count mode into up, up/down, or continuous; each has their own benifits and purposes. From there, each possible interrupt has its own register that controls wether or not it is active, what output mode it uses, and has yet another register to tell how many ticks it waits before interrupting.

##Hardware Abstraction Layers using Macros
Code for one MSP430 device can not be directly used a different MSP430. By using #ifdef statements placed in a header file, the precompiler can determined which board is being used, and translate specific marcos from board to board. Every file here execpt for the G2553 uses these macros. After the header file was complete, translating code from board to board only rarely took more than a few minutes.  Not everything can be translated; there are very specific scenarios and these macos do not cover every possible combination.

### Macro list
-Timer Macros
	-TA0SET(x) Configures timer to up mode, using SMCLK/8, and sets the frequency of interrupts to the input value x. This is available for TA0, TA1, TB0, and TB1.
	-TA0STOP   Sets the timer input to 0, effectively stopping the timer. This is available for TA0, TA1, TB0, and TB1.
	-TA0START  Reconfigures the timer to up mode and SMCLK/8. This is available for TA0, TA1, TB0, and TB1.
-LED Macros
	-LED1INIT  Initializes the port with the right LED to an I/O as an output. Also available for LED2
	-LED1ON    Sets the output bit active for the corresponding port. Also available for LED2
	-LED1OFF   Sets the output bit off for the corresponding port. Also available for LED2
	-LED1SWITCH Toggles the output of the corresponding port. Also available for LED2
-Button Macros
	-BTN1INIT Initializes the port with the right LED to an I/O as an input with a pull-up resistor. Also available for button 2 if there is one.
	-BTN1UP Checks to see if the button is not pressed. Can be inverted by !BTN1UP. Also available for button 2 if there is one.
	-BTN1CLR Clears the interrupt flag for that port. Also available for button 2 if there is one.
	-BTN1SWAP Swaps the interrupt edge on that port. Also available for button 2 if there is one.





