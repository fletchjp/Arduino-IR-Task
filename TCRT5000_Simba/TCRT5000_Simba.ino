 /**
 * @section License
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2017, Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This file is part of the Simba project.
 */

/* Documentation on how to define pins is non existent.
 *  I cannot find descriptions of pin_driver_t and pin_device_t.
 *  There are instances to be used e.g. pin_d5_dev and I cannot find a list of them.
 *  I have not found an example with more than one pin in use (pin_led_dev) so I am 
 *  flying blind. This is NOT HELPFUL.
 */

#include "simba.h"

// This should be defined internally - why is it not?
//#define PIN_INPUT_PULL_UP                                   4

int main()
{
    struct pin_driver_t signal_pin;
    struct pin_driver_t ir_pin;
    struct pin_driver_t led_pin;

    int ir_signal = 0;
    int previous_signal = -1;
    
    /* Start the system. */
    sys_start();

    std_printf(FSTR("TCRT Simba\r\n"));
    pin_module_init();

    pin_init(&signal_pin, &pin_d5_dev, PIN_INPUT_PULL_UP);
    pin_init(&ir_pin,     &pin_d6_dev, PIN_OUTPUT);

    /* Initialize the LED pin as output and set its value to 1. */
    pin_init(&led_pin, &pin_led_dev, PIN_OUTPUT);
    pin_write(&led_pin, 0);
    pin_write(&ir_pin, 1);

    while (1) {
        ir_signal = pin_read(&signal_pin);
        /* Wait half a second. */
        thrd_sleep_ms(500);
        if (ir_signal != previous_signal) {
            previous_signal = ir_signal;
            std_printf(FSTR("%d \r\n"),ir_signal);
            /* Toggle the LED on/off. */
            pin_toggle(&led_pin);
        }
    }


    return (0);
}
