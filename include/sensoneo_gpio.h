#ifndef SENSONEO_GPIO_H
#define SENSONEO_GPIO_H

// INCLUDES
/*
Zephyr includes are needed for overall functionality, the kernel will be included basically in every file.
Is that OK? IDK but it works.

Libraries that are needed are a mystery, I just use them when following a tutorial so I don't know what they do
and if there is a simpler way to do stuff.
*/
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>  // <- SOME DRIVERS MUST BE ENABLED IN prj.conf

// We will control some timers values
#include "sensoneo_timers.h"



/*
These defines are questionable IMO, I feel like there might later be problem with backwards compatibility if someone
changes device tree. However, getting nodes by alias is probably a good practice but we MUST keep the aliases as
simple and exact as possible. I dont agree with the initial project aliases led0, led1, sw0, sw1 so I will
change them to my liking. (_ and capitals are not allowed in aliases)

FOR SOME REASON top-left-led CANNOT BE USED. I DONT KNOW WHY SO FOR NOW WE HAVE TO GO WITH THE UGLY led0 ALIASES
# FIXME: Check why top-left-led cannot be used as an alias

Use DT_ALIAS to get a node by its alias, there are other options such as DT_NODELABEL, DT_PATH, DT_PATH_OR_NONE,...
*/
// Get nodes of LEDS
# define TOP_LEFT_LED_NODE          DT_ALIAS(led0)
# define TOP_RIGHT_LED_NODE         DT_ALIAS(led1)

// Get nodes of BUTTONS
# define TOP_LEFT_BUTTON_NODE       DT_ALIAS(btn0)
# define TOP_RIGHT_BUTTON_NODE      DT_ALIAS(btn1)

// PUBLIC FUNCTIONS

void sensoneo_gpio_setup(void);
void alternating_leds_timer_callback(void);


#endif // GPIO_SETUP_H