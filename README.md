# NRF52_TC
To create a driver for the timer peripheral of the nRF52810 series chip. 

The aim of the driver is to generate an event periodically after a specified amount of microseconds. 
Here are the driver specifications:
  - It should have a start function that starts the periodic event generation (initializes too) with two arguments: a integer specifying the time in us and a function pointer specifying the callback function.

  - It should have a stop function stops the periodic event generation.

Used the driver in a simple application that prints a counter value that increments every 509 ms. 

Standard libraries from nrf52 sdk are used here.
