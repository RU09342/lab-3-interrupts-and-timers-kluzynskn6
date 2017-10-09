# Button Interrupt
#### Nick Kluzynski
This is an extension of the button blink from the previous lab. The goal is the same: use a button to control the blinking of an LED. Being vague, it leaves it open to the designer to determine how to change the LED upon button press.

## Usage
The LED starts at 5 Hz, upon button press, the LED turns off. When the button is released, the frequency of the LED is looped between 5Hz, 2.5Hz, 1.25Hz, and off. The other button changes the LED to the other colored LED. On boards with 1 button, the color is changed when the frequency completes 1 loop. 

## Implementation
### Timers
There is only one timer used, and it simply uses a global variable "color" to determine which LED to blink. The rate at which it is blinked is controlled by another global variable "count". Although, if count is 0, it turns off both LEDs.
### Buttons
Whenever the button is depressed, it turn the LED off. In addition, it also loops the frequency of the LED.  It does this by switching the interrupt edge within the ISR, then detecting wether or not it is pressed or not. If it is, the LED is turned off, else the frequency is looped. The color handler is different on boards with 1 or 2 buttons. On boards with only 1 button, whenever the frequency resets, it also switches the color bit, alternating the LED that is blinked. On boards with 2 buttons, the second button is soley used to change which LED is blinked.
