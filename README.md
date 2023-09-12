ATMega2560 Button Debouncing
==================

This program is an elaborated, yet very useful, solution to debounce the signal of a click from a push button. The implementation is to the level of the hardware, by means of using 
falling/rising and time interruptions. The distinctive advantage of this algorithm is its capability of rejecting the noise from both the pressing and releasing of the button. It's configured for normally high level signal, but the order from falling edge interruption to rising edge interruption enablement can be reversed to attend for normally low level input.

---

## How to Run

To compile and load the file into the AtMega2560 microcontroller, it's suggested to use the Arduino IDE. 

---

#### Practical Importance

The following captures shows the bouncing effect during pressing and releasing of a push button.

<img src="https://github.com/rodrigojost/megaDebouncing/blob/master/captures/fallingEdgeBouncing.bmp">
<img src="https://github.com/rodrigojost/megaDebouncing/blob/master/captures/risingEdgeBouncing.bmp">
<img src="https://github.com/rodrigojost/megaDebouncing/blob/master/captures/setup.jpg">