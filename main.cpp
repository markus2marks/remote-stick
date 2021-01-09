/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "USBMouseKeyboard.h"

// Blinking rate in milliseconds
#define WAIT                                                    150

InterruptIn buttonCenter(PA_0);
InterruptIn buttonUp(PA_6);
InterruptIn buttonDown(PA_1);
InterruptIn buttonLeft(PA_3);
InterruptIn buttonRight(PA_2);

USBMouseKeyboard key_mouse;
uint8_t button_center = 0;
uint8_t button_up = 0;
uint8_t button_down = 0;
uint8_t button_left = 0;
uint8_t button_right = 0;

int16_t y = 0;
int16_t x = 0;

Thread thread;

void buttonCenter_pressed()
{
	button_center = 1;
}


void buttonCenter_unpressed()
{
	button_center = 0;
}

void buttonUp_pressed()
{
	button_up = 1;
}


void buttonUp_unpressed()
{
	button_up = 0;
}

void buttonDown_pressed()
{
	button_down = 1;
}


void buttonDown_unpressed()
{
	button_down = 0;
}

void buttonLeft_pressed()
{
	button_left = 1;
}

void buttonLeft_unpressed()
{
	button_left = 0;
}

void buttonRight_pressed()
{
	button_right = 1;
}

void buttonRight_unpressed()
{
	button_right = 0;
}

void mouse_thread()
{
    while (true) {
    	if(button_left == 1)
		{
			x -= 2;
		}
    	else if(button_right == 1)
		{
			x+= 2;
		}
    	else
    	{
    		x = 0;
    	}

    	if( button_down== 1)
		{
			y += 2;
		}
		else if(button_up == 1)
		{
			y -= 2;
		}
		else
		{
			y = 0;
		}
        ThisThread::sleep_for(40);
    }
}


int main()
{


	buttonCenter.mode(PullDown);
	buttonUp.mode(PullDown);
	buttonDown.mode(PullDown);
	buttonLeft.mode(PullDown);
	buttonRight.mode(PullDown);

	buttonCenter.rise(&buttonCenter_pressed);
	buttonCenter.fall(&buttonCenter_unpressed);

	buttonUp.rise(&buttonUp_pressed);
	buttonUp.fall(&buttonUp_unpressed);

	buttonDown.rise(&buttonDown_pressed);
	buttonDown.fall(&buttonDown_unpressed);

	buttonLeft.rise(&buttonLeft_pressed);
	buttonLeft.fall(&buttonLeft_unpressed);

	buttonRight.rise(&buttonRight_pressed);
	buttonRight.fall(&buttonRight_unpressed);

	//thread.start(mouse_thread);


    while (true) {


    	//key_mouse.press(button_center);
    	//key_mouse.move(x,y);

    	if(button_center == 1)
		{
			key_mouse.key_code(10U);
		}

    	if(button_left == 1)
		{
    		key_mouse.key_code(149U);
		}

    	if(button_right == 1)
		{
			key_mouse.key_code(148U);
		}

    	if(button_down == 1)
		{
			key_mouse.key_code(150U);
		}

		if(button_up == 1)
		{
			key_mouse.key_code(151U);
		}

        thread_sleep_for(WAIT);
    }
}
