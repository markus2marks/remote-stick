/* mbed Microcontroller Library
 * Copyright (c) 2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "USBMouseKeyboard.h"


#define WAIT                                                    120
#define WAIT_MOUSE_THREAD                                       40

InterruptIn buttonCenter(PA_2);
InterruptIn buttonUp(PA_1);
InterruptIn buttonDown(PA_6);
InterruptIn buttonLeft(PA_4);
InterruptIn buttonRight(PA_0);

InterruptIn buttonF1(PA_7);
InterruptIn buttonF2(PB_5);
InterruptIn buttonF3(PA_3);
InterruptIn buttonStf(PB_12);

USBMouseKeyboard key_mouse;
uint8_t button_center = 0;
uint8_t button_up = 0;
uint8_t button_down = 0;
uint8_t button_left = 0;
uint8_t button_right = 0;
uint8_t button_f1 = 0;
uint8_t button_f2 = 0;
uint8_t button_f3 = 0;
uint8_t button_stf = 0;


int16_t y = 0;
int16_t x = 0;

Thread thread;
bool mouse_mode = false;
/**
 * start the DFU bootloader
 */
void startBootloader(void)
{
    key_mouse.deinit();
    void (*SysMemBootJump)(void);
    volatile uint32_t addr = 0x1FFF0000;
    HAL_RCC_DeInit();
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;
    __disable_irq();
    SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));
    __set_PRIMASK(0x20010000); // Set the main stack pointer to its default value
    __set_MSP(*(uint32_t *)addr);
    SysMemBootJump();
}

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

void buttonF1_pressed()
{
    button_f1 = 1;
}

void buttonF1_unpressed()
{
    button_f1 = 0;
}

void buttonF2_pressed()
{
    button_f2 = 1;
}

void buttonF2_unpressed()
{
    button_f2 = 0;
}

void buttonF3_pressed()
{
    button_f3 = 1;
}

void buttonF3_unpressed()
{
    button_f3 = 0;
}

void buttonStf_pressed()
{
    button_stf = 1;
}

void buttonStf_unpressed()
{
    button_stf = 0;
}



void mouse_thread()
{
    while (true)
    {
        if(mouse_mode == true)
        {
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

            if( button_down == 1)
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
            key_mouse.press(button_center);
            key_mouse.move(x,y);
        }
        else
        {
            if(button_center == 1)
            {
               key_mouse.key_code(10U);
               button_center = 0;
            }

            if(button_left == 1)
            {
               key_mouse.key_code(LEFT_ARROW);
               button_left = 0;
            }

            if(button_right == 1)
            {
               key_mouse.key_code(RIGHT_ARROW);
               button_right = 0;
            }

            if(button_down == 1)
            {
               key_mouse.key_code(DOWN_ARROW);
               button_down = 0;
            }

            if(button_up == 1)
            {
               key_mouse.key_code(UP_ARROW);
               button_up = 0;
            }
        }
        ThisThread::sleep_for(WAIT_MOUSE_THREAD);
    }
}


int main()
{
    uint8_t stf_mode = 0;

    buttonCenter.mode(PullDown);
    buttonUp.mode(PullDown);
    buttonDown.mode(PullDown);
    buttonLeft.mode(PullDown);
    buttonRight.mode(PullDown);

    buttonF1.mode(PullDown);
    buttonF2.mode(PullDown);
    buttonF3.mode(PullDown);
    buttonStf.mode(PullDown);

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

    buttonF1.rise(&buttonF1_pressed);
    buttonF1.fall(&buttonF1_unpressed);

    buttonF2.rise(&buttonF2_pressed);
    buttonF2.fall(&buttonF2_unpressed);

    buttonF3.rise(&buttonF3_pressed);
    buttonF3.fall(&buttonF3_unpressed);

    buttonStf.rise(&buttonStf_pressed);
    buttonStf.fall(&buttonStf_unpressed);
    thread.start(mouse_thread);

    uint32_t button_timer = 0;
    bool long_press = false;

    while (true)
    {
        //key_mouse.press(button_center);
        //key_mouse.move(x,y);



        if((button_f1 == 1) && (button_f2 != 1) && (button_f3 != 1))
        {
            key_mouse.key_code(KEY_F1);
            button_f1 = 0;
        }

        if((button_f2 == 1) && (button_f1 != 1) && (button_f3 != 1))
        {
            key_mouse.key_code(KEY_F2);
            button_f2 = 0;
        }

        if((button_f3 == 1) && (button_f1 != 1) && (button_f2 != 1) && (long_press == false))
        {
            //keycode escape
            key_mouse.key_code(0);
            long_press = true;
        }
        else if((long_press == true) && (button_f3 == 1))
        {
            button_timer++;
            if(button_timer > 10)
            {
                mouse_mode^= true;
                button_timer = 0;
                long_press = false;
            }
        }
        else
        {
            long_press = false;
            button_timer = 0;
            button_f3 = 0;
        }


        if(button_stf == 1)
        {
            if(stf_mode == 1)
            {
                key_mouse.key_code(86, KEY_SHIFT); //V
                stf_mode = 0;
            }
            else
            {
                key_mouse.key_code(83, KEY_SHIFT); //S
                stf_mode = 1;
            }

             button_f1 = 0;
        }

        if((button_f1 == 1) && (button_f2 == 1) && (button_f3 == 1))
        {

            startBootloader();
        }
        thread_sleep_for(WAIT);
    }
}
