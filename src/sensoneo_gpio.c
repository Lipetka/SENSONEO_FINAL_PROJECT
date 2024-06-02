#include "sensoneo_gpio.h"

// Private functions

static void gpio_configurations();
static void blink_leds(uint8_t num_of_blinks, uint8_t interval_ms);
static void button_pressed_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

/*
All "devices" have their own structures that keep their state and configuration.
I don't have an insight to these structures, I just use them as they are in the tutorials and docs.
*/

// I believe it's a good idea to keep all handlers in one place, so I will not define these structs as extern
// LEDS
static const struct gpio_dt_spec top_left_led = GPIO_DT_SPEC_GET(TOP_LEFT_LED_NODE, gpios);
static const struct gpio_dt_spec top_right_led = GPIO_DT_SPEC_GET(TOP_RIGHT_LED_NODE, gpios);

// BUTTONS
static const struct gpio_dt_spec top_left_button = GPIO_DT_SPEC_GET(TOP_LEFT_BUTTON_NODE, gpios);
static const struct gpio_dt_spec top_right_button = GPIO_DT_SPEC_GET(TOP_RIGHT_BUTTON_NODE, gpios);

// GPIO buttons are tied to interrupts, so we need to define interrupt handlers
static struct gpio_callback top_left_button_callback;
static struct gpio_callback top_right_button_callback;


/**
 * @brief Sets up the GPIO configurations and interrupt handlers for Sensoneo.
 *
 * This function initializes the GPIO configurations for input and output. It also ties the interrupt handlers to the buttons
 * and configures the interrupts to be triggered on button press. Finally, it blinks the LEDs to indicate the end of GPIO setup.
 */
void sensoneo_gpio_setup(void){
    gpio_configurations();  // setup INPUT, OUTPUT

    // Tie the interrupt handlers to the buttons
    // First we have to initiate the callback with target function and target pins (probably could be done with one traceback)
	gpio_init_callback(&top_left_button_callback, button_pressed_callback, BIT(top_left_button.pin));
	gpio_init_callback(&top_right_button_callback, button_pressed_callback, BIT(top_right_button.pin));
    // assign the callback to the buttons
	gpio_add_callback(top_left_button.port, &top_left_button_callback);
	gpio_add_callback(top_right_button.port, &top_right_button_callback);
    // configure the interrupts to be triggered on button press
	gpio_pin_interrupt_configure_dt(&top_left_button, GPIO_INT_EDGE_TO_ACTIVE);
	gpio_pin_interrupt_configure_dt(&top_right_button, GPIO_INT_EDGE_TO_ACTIVE);

    blink_leds(5, 100); // Blink leds to end GPIO setup, one will keep on
    return;
}

/**
 * @brief Callback function for alternating LEDs.
 *
 * This function is called by a timer to toggle the state of two LEDs.
 * It toggles the state of the top left LED and the top right LED.
 */
void alternating_leds_timer_callback(void){
    gpio_pin_toggle_dt(&top_left_led);
    gpio_pin_toggle_dt(&top_right_led);
}


/////////////////// STATIC FUNCTIONS ///////////////////////

/**
 * @brief Construct a new gpio pin configure dt object
 *
 * @brief Configures the GPIO settings.
 *
 * This function is responsible for configuring the GPIO settings.
 * It is a static function and does not return any value.
 *
 * The setup parameters are INPUT, OUTPUT values and some other parameters?
 */
static void gpio_configurations(){
    // LEDS
    // Configure the LED pins as output
    gpio_pin_configure_dt(&top_left_led, GPIO_OUTPUT);
    gpio_pin_configure_dt(&top_right_led, GPIO_OUTPUT);

    // BUTTONS
    // Configure the BUTTON pins as input
    gpio_pin_configure_dt(&top_left_button, GPIO_INPUT); // Copilot wants to import some more parameters (DEBOUNCE, ...)
    // gpio_pin_configure_dt(&top_left_button, GPIO_INPUT, GPIO_ACTIVE_HIGH | GPIO_PULL_UP | GPIO_INT_DEBOUNCE);
    gpio_pin_configure_dt(&top_right_button, GPIO_INPUT);
    return;
}

/**
 * @brief Blinks the LEDs for a specified number of times with a given interval.
 *
 * This function blinks the top left and top right LEDs for a specified number of times
 * with a given interval between blinks.
 *
 * @param num_of_blinks The number of times to blink the LEDs.
 * @param interval_ms The interval between each blink in milliseconds.
 */
static void blink_leds(uint8_t num_of_blinks, uint8_t interval_ms){
    for(uint8_t i = 0; i < num_of_blinks; i++){
        gpio_pin_set_dt(&top_left_led, 1);
        gpio_pin_set_dt(&top_right_led, 1);
        k_msleep(interval_ms);
        gpio_pin_set_dt(&top_left_led, 0);
        gpio_pin_set_dt(&top_right_led, 0);
        k_msleep(interval_ms);
    }
    gpio_pin_set_dt(&top_left_led, 1);
    return;
}

/**
 * @brief Callback function for button press event.
 *
 * This function is called when a button is pressed. It checks which button was pressed
 * and performs the corresponding action. It prevents scrolling through speeds too fast
 * by using a flag to track if the button is being held.
 *
 * @param dev The device structure for the GPIO device.
 * @param cb The callback structure for the GPIO callback.
 * @param pins The bitmask of pins that triggered the callback.
 */
static void button_pressed_callback(
    const struct device *dev,
    struct gpio_callback *cb,
    uint32_t pins)
{
    bool button_held = false; // to prevent holding button and scrolling though speeds too fast

    if (gpio_pin_get_dt(&top_left_button)) {
        if (!button_held) {
            increase_alternating_leds_interval();
            button_held = true;
        }
    } else if (gpio_pin_get_dt(&top_right_button)) {
        if (!button_held) {
            decrease_alternating_leds_interval();
            button_held = true;
        }
    } else {
        button_held = false;
    }
}