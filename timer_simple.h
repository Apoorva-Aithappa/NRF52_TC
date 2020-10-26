#define timer_simple        // Assigning driver

#include <stdbool.h>
#include "nrf.h"
#include "boards.h"
#include "nrf_timer.h"
#include "nordic_common.h"
#include <stdio.h>

#define TIMER1_ENABLED 1

void start_timer(void, int trigger_interval, (*callback_function)())
{
  NRF_TIMER1->PRESCALER = 4;	// 16/(2^4) gives timer of resolution 1 micro second --->0x510 offset

  NRF_TIMER1->TASKS_STOP = 1;	// Stop timer--->0x004 offset
  NRF_TIMER1->TASKS_CLEAR = 1; // Clear timer----->0x00C offset
  NRF_TIMER1->MODE = TIMER_MODE_MODE_Timer; // Setiing TIMER mode to timer --->0x504 offset
  NRF_TIMER1->BITMODE = (TIMER_BITMODE_BITMODE_24Bit << TIMER_BITMODE_BITMODE_Pos); //setting the bitmode of the timer--->0x508 offset
  
  NRF_TIMER1->CC[0] = trigger_interval * 1000;  // meeting decimal requirement as the input is of millisecond resolution--->0x540 offset
  NRF_TIMER1->INTENSET = (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos) | (TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos); // recommonded to do as per some forum comments (for nrf52 series)--->0x304 offset
  attachInterrupt(TIMER1_IRQn, callback_function);    // setting up callback function
  NRF_TIMER1->TASKS_START = 1;	// Start TIMER---> 0x000 offset
}

void stop_timer(void)
{
  NRF_TIMER1->TASKS_STOP = 1;	// Stop timer  --->0x004 offset
  TIMER1_ENABLED = 0;
  NRF_TIMER1->TASKS_CLEAR = 1; // Clear timer ----->0x00C offset
  NVIC_DisableIRQ() // disable interupt assigned to timer function
}

int callback_reset(void)
{
  if (NRF_TIMER1->EVENTS_COMPARE[0] != 0)   // compare the value and step into the function
  { 
    Serial.println("Reset function is called");

    NRF_TIMER1->EVENTS_COMPARE[0] = 0;  // resetting the value to restart the count
  }
}

int get_counter_val(void)
{
  return  NRF_RTC1->COUNTER;    //returning counter value
}
