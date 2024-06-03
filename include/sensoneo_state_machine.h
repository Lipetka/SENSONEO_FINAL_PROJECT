#ifndef SENSONEO_STATE_MACHINE_H
#define SENSONEO_STATE_MACHINE_H

// Check GPIO header for details
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/smf.h>

#include "sensoneo_gpio.h"

static const struct smf_state state_machine_states_list[4]; // stores all states of any state machine

// define state machine states <- this is not used anywhere so idk if it is needed
enum led_state_machine_states{
    NO_LEDS,
    ONE_LED,
    BOTH_LEDS,
    LAST_LED
};

// create state machine object
extern struct s_object{
    struct smf_ctx ctx;
}led_state_machine_handler;

// Public function
void sensoneo_led_state_machine_setup(void);

#endif