# Volatile Laboratories Memory Puzzle
 
A quick puzzle that involves players remembering the correct sequence of coloured light flashes that they then input into a control panel. This gives them a 4 digit code that unlocks one of the gate power switches. 
 
 
## How does it work?
* A sequence of 5 coloured bulkhead lights mounted on the walls will flash in the hallway of Volatile Laboratories.

* The player will study the sequence of flashing lights and try to remember them. Or another member of their team will call them out to them.

* The players task is to repeat the correct sequence of flashing lights back by pressing the 5 coloured buttons mounted on the wall in the smaller room. It would beep loud on correct and give a 4 digit code for the switches 

* If they do so correctly a piezo will sound and a small LCD screen will display a 4 digit code that they need to progress.

* Else a piezo will sound for longer and the LCD screen will tell them to try again.

## What will I use?
* Arduino Mega or Leonardo (Likely elegoo as they are cheaper).

* Loads of jumper cables.

* LCD screen with backpack that interfaces well with arduino IDE to avoid the hassle of programming it from scratch.

* 5 different coloured push buttons. 

* A reset button or switch if needed.

## Some Things to Note

* The bulkhead lights will be controlled by Qlab and the sequence (order) will not change. 

* The buttons and control panel in general function as a 5 digit combination lock.

* There will need to be a reset button to restart the arduino if they get it incorrect. Alternatively a time-out system that lets the players know on screen that they need to try again.


* The colours of the buttons and lights will be:
> White
> Red
> Blue
> Green
> Yellow

## Pitfalls to Avoid

* Not implementing proper debounce on all 5/6 buttons to avoid double presses registering.

* Loose wiring if using jumper cables for final design.

* Accidentally frying the hardware...


## Example

* These coloured lights will flash in this order: Yellow, Red, White, Blue, Green.

* The user must then push the coloured buttons in this order: Yellow, Red, White, Blue, Green.

* The player gets the 4 digit code off the LCD screen and progresses through the game from there.
