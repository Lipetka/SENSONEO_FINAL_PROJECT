#ifndef SENSONEO_TIMERS_H
#define SENSONEO_TIMERS_H

// Check GPIO header for details
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

// timers are tied to our own libraries also
#include "sensoneo_gpio.h"

extern uint16_t alternating_leds_interval_ms; // so we can print the value in main loop

void sensoneo_timers_setup(void);
void sensoneo_run_timers(void);
void increase_alternating_leds_interval(void);
void decrease_alternating_leds_interval(void);

#endif