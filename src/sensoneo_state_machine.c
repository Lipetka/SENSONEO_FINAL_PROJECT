#include "sensoneo_state_machine.h"

// private functions
static void no_leds(void *o);
static void one_led(void *o);
static void both_leds(void *o);
static void last_led(void *o);

struct s_object led_state_machine_handler; // use the extern handler (from header)


// create the state machine by defining all states and their functions
// this can be used by multiple state machines !!!
static const struct smf_state state_machine_states_list[4] = {
    [NO_LEDS] = SMF_CREATE_STATE(NULL, no_leds, NULL, NULL, NULL), // entry, run and exit functions for each state
    [ONE_LED] = SMF_CREATE_STATE(NULL, one_led, NULL, NULL, NULL), // entry, run and exit functions for each state
    [BOTH_LEDS] = SMF_CREATE_STATE(NULL, both_leds, NULL, NULL, NULL), // entry, run and exit functions for each state
    [LAST_LED] = SMF_CREATE_STATE(NULL, last_led, NULL, NULL, NULL) // entry, run and exit functions for each state
};


/**
 * @brief Sets up the Sensoneo LED state machine.
 *
 * This function creates the state machine and initializes it with the initial state.
 *
 * @param None
 * @return None
 */
void sensoneo_led_state_machine_setup(void){
    // create the state machine
    smf_set_initial(SMF_CTX(&led_state_machine_handler), &state_machine_states_list[NO_LEDS]); // initialize the state machine
}

/**
 * @brief Turns off all LEDs, sleeps for 500ms, and changes the state of the state machine.
 *
 * This function turns off all LEDs by calling the `set_leds` function with the argument `0b00`.
 * It then sleeps for 500 milliseconds using the `k_msleep` function.
 * Finally, it changes the state of the state machine by calling the `smf_set_state` function with the next state as an argument.
 *
 * @param o A pointer to the object.
 */
static void no_leds(void *o){
    // turn off all leds
    set_leds(0b00);
    k_msleep(500); // sleep for 500ms

    // change state
    smf_set_state(SMF_CTX(&led_state_machine_handler), &state_machine_states_list[ONE_LED]); // set the next state
}

/**
 *
 * @brief Turns on/off all LEDs, sleeps for 500ms, and changes the state of the state machine.
 *
 * This works basiccaly the same as the \ref no_leds function, but it turns on only one LED.
 */
static void one_led(void *o){
    // turn off all leds
    set_leds(0b10);
    k_msleep(500); // sleep for 500ms

    // change state
    smf_set_state(SMF_CTX(&led_state_machine_handler), &state_machine_states_list[BOTH_LEDS]); // set the next state
}

/**
 *
 * @brief Turns on/off all LEDs, sleeps for 500ms, and changes the state of the state machine.
 *
 * This works basiccaly the same as the \ref no_leds function, but it turns on only one LED.
 */
static void both_leds(void *o){
    // turn off all leds
    set_leds(0b11);
    k_msleep(500); // sleep for 500ms

    // change state
    smf_set_state(SMF_CTX(&led_state_machine_handler), &state_machine_states_list[LAST_LED]); // set the next state
}

/**
 *
 * @brief Turns on/off all LEDs, sleeps for 500ms, and changes the state of the state machine.
 *
 * This works basiccaly the same as the \ref no_leds function, but it turns on only one LED.
 */
static void last_led(void *o){
    // turn off all leds
    set_leds(0b01);
    k_msleep(500); // sleep for 500ms

    // change state
    smf_set_state(SMF_CTX(&led_state_machine_handler), &state_machine_states_list[NO_LEDS]); // set the next state
}