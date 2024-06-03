#include "sensoneo_timers.h"

struct k_timer alternating_leds_timer;
extern uint16_t alternating_leds_interval_ms = 500; // 500ms default value

/**
 * @brief Initializes the Sensoneo timers.
 */
void sensoneo_timers_setup(void){
    // Setup the timers
    k_timer_init(&alternating_leds_timer, alternating_leds_timer_callback, NULL); // NULL -> Stop function (not used now)
    return;
}

/**
 * @brief Starts running the Sensoneo timers.
 *
 * This must be called after init function
 */
void sensoneo_run_timers(void){
    k_timer_start(&alternating_leds_timer, K_MSEC(500), K_MSEC(alternating_leds_interval_ms)); // timer, initial delay, period
    return;
}

/**
 * @brief Increases the interval of the alternating LEDs timer.
 */
void increase_alternating_leds_interval(void){
    if(alternating_leds_interval_ms < 1000){
        alternating_leds_interval_ms += 100;
    }
    k_timer_start(&alternating_leds_timer, K_MSEC(500), K_MSEC(alternating_leds_interval_ms)); // timer, initial delay, period
    return;
}

/**
 * @brief Decreases the interval of the alternating LEDs timer.
 */
void decrease_alternating_leds_interval(void){
    if(alternating_leds_interval_ms > 100){
        alternating_leds_interval_ms -= 100;
        k_timer_start(&alternating_leds_timer, K_MSEC(500), K_MSEC(alternating_leds_interval_ms)); // timer, initial delay, period
    }
    return;
}
