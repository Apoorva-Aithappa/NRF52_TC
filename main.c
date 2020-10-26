#include "timer_simple.h" // calling driver
#include <stdio.h>

#define time_interval 592 //value in millisecond
#define counter_value 0 


void setup()
{
    Serial.begin(115200);   //setting baud rate for serial communication
}

void loop()
{
    start_timer(time_interval, callback_function);       // pass
}

void callback_function(void)
{
    
    counter_value = get_counter_val();                                 // getting the value of counter
    callback_reset();                                                 // resetting after comparing
    printf ("the current value of counter is %d", counter_value);    // printing counter value
    //delay (100);                                                    // delay is optional
}