/*
All file structures, naming overall organization does not follow any known standard.
However the structure is as simple and easy to understand as possible.

Whole project contains sometimes more documentation and comments as needed.
 */



#include <zephyr/kernel.h>
#include "sensoneo_gpio.h"
#include "sensoneo_timers.h"

#define PRINT_DEBUG // Print debug messages, all debug messages are printed with printk in main loop
#define SLEEP_TIME 250 // Sleep time in while loop



int main(void)
{
        // setup all gpios, tasks, timers, etc.
        sensoneo_gpio_setup(); // setup all GPIO pins (Buttons, Leds, basic I/O)
        sensoneo_timers_setup(); // setup all timers

        // Initiate all tasks and timers etc.
        sensoneo_run_timers(); // start all timers

        while(true){
                #ifdef PRINT_DEBUG
                        printk("-----------------------\n");
                        printk("Alternating leds period: %i\n", alternating_leds_interval_ms);
                #endif
                k_msleep(SLEEP_TIME); // This is just to prevent tight loop problems
        }

        return 0; // Code should never reach this point
}
