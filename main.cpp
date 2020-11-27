/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "USBMouse.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS                                                    1000

InterruptIn button(PA_6);
USBMouse mouse;

void button1_push()
{
	mouse.press(1);
}


void button1_unpressed()
{
	mouse.press(0);
}


int main()
{


	button.rise(&button1_push);
	button.fall(&button1_unpressed);
    while (true) {

        thread_sleep_for(BLINKING_RATE_MS);

    }
}
