# Reaction Game
### Nick Kluzynski
By using a combination of button interrupts and timers, many different behaviors are possible. To demonstrate this, a reaction game was made using the MSPF5529. 

## Usage
The timer will wait a random time from 5 to 10 seconds, then both LEDs will turn on. The first person the press their button after the LEDs activate will win the game. If either player presses early, then the other player is automatically the winner.

## Implementation
### Delay 
The standard c library had to be implemented to generate the random number. This random number is generated from 5 to 10, and is used as the delay.  
### Timers
2 timers were also used: 1 is used for the delay and turning the LEDs on, and the other timer is used to display the winner. 

The 1st timer used for the delay is set to 1kHz, giving a 1ms accuracy on the delay. Every time it interrupts, a register is incremented until it reaches the delay, upon reaching the delay, both LEDs turn on.

The 2nd timer is used to display the winner. A global bit is used to keep track of which side is the winner; depending on the state of that bit, the corresponding LED will be blinked at 3 Hz, and the other is turned off.
### Buttons
Whenever a button is pressed, it checks to see if the delay has passed. If it is not, it sets the winner to the other side, then disables further interrupts from that button. If it is past the delay, it sets the winner to that side, and disables interrupts from the other button. By disabling those interrupts, it prevents the winner bit from accidentally switching.
