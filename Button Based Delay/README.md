# Button Based Delay
#### Nick Kluzynski
Further expanding upon using the button to control the LED, this has the button directly controlling the delay of the LED instead of looping through set frequencies.

## Usage
Upon start, the LED blinks at 10Hz. The button can do 1 of 2 things to change the frequency. Either the button can be pressed, which increments the LED by 1 Hz each time; or the button can be held, setting the frequency to the amount of time held.
## Implementation
In this code, 2 timers are used, along with a single button.
### Timers
The 2 timers are very simple but very important. The first timer is used to count how long the button is held down for, and the second is used to actually blink the LED. For the purposes of debugging the other LED is turned on when the first timer is counting.
### Button
The button's ISR is much more complex, but can be broken down into 2 parts: when the button is pressed, and when the button is released.
#### Button Pressed
By swapping the interrupt edge on the button, the ISR executes on both button press and release. It detects when the button pressed by reading the input logically "and"ed with the port. When the button is pressed, it clears the count register and the timer register, then starts the counting timer.
#### Button Released
When the button is released agian, it stops the timer so it can read how many times it has interrupted, which indicates how long the button was held for. The accuracy on the timer is .01 seconds. 

If the button was held for more than .35 seconds, it is considered a hold. The frequency is then changed to match the time the button was held down. 

If the button was held for less than .35 seconds, it is considered a press. When pressed, then the frequency is incremented by 1.


## Known problems
The limitations of the control register prevent the LED from blinking slower than 2 Hz. This is only a problem for when the button is held for more than 2 seconds.
