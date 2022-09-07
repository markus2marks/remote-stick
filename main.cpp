/* mbed Microcontroller Library
 * Copyright (c) 2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "remote_stick.h"
#include "USBMouseKeyboard.h"

#define WAIT                                                    120
#define WAIT_MOUSE_THREAD                                       40
#define BUTTON_VALUE_V                                          86
#define BUTTON_VALUE_S                                          83

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


int16_t y = 0;
int16_t x = 0;

Thread thread;
bool mouse_mode = false;
Remote_Stick remote_stick(buttonCenter, buttonUp, buttonDown, buttonLeft, buttonRight, buttonF1, buttonF2, buttonF3, buttonStf);
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

/*
 * mouse thread
 */
void mouse_thread()
{
    while (true)
    {
        if(mouse_mode == true)
        {
            if(Remote_Stick::button_left == true)
            {
                x -= 2u;
            }
            else if(Remote_Stick::button_right == true)
            {
                x+= 2u;
            }
            else
            {
                x = 0;
            }

            if(Remote_Stick::button_down == true)
            {
                y += 2u;
            }
            else if(Remote_Stick::button_up == true)
            {
                y -= 2u;
            }
            else
            {
                y = 0;
            }
            key_mouse.press(Remote_Stick::button_center);
            key_mouse.move(x,y);
        }
        else
        {
            if(Remote_Stick::button_center == true)
            {
               key_mouse.key_code(10U);
               Remote_Stick::button_center = false;
            }

            if(Remote_Stick::button_left == true)
            {
               key_mouse.key_code(LEFT_ARROW);
               Remote_Stick::button_left = false;
            }

            if(Remote_Stick::button_right == true)
            {
               key_mouse.key_code(RIGHT_ARROW);
               Remote_Stick::button_right = false;
            }

            if(Remote_Stick::button_down == true)
            {
               key_mouse.key_code(DOWN_ARROW);
               Remote_Stick::button_down = false;
            }

            if(Remote_Stick::button_up == true)
            {
               key_mouse.key_code(UP_ARROW);
               Remote_Stick::button_up = false;
            }
        }
        ThisThread::sleep_for(WAIT_MOUSE_THREAD);
    }
}

/*
 * main function
 */
int main()
{
    bool stf_mode = false;
    uint32_t button_press_time= 0;

    bool button_f3_temp = false;
    bool button_stf_temp = false;

    thread.start(mouse_thread);

    while (true)
    {
        if((Remote_Stick::button_f1 == true) && (Remote_Stick::button_f2 != true) && (Remote_Stick::button_f3 != true))
        {
            key_mouse.key_code(KEY_F1);
            Remote_Stick::button_f1 = false;
        }

        if((Remote_Stick::button_f2 == true) && (Remote_Stick::button_f1 != true) && (Remote_Stick::button_f3 != true))
        {
            key_mouse.key_code(KEY_F2);
            Remote_Stick::button_f2 = false;
        }
//rising edge
        if((Remote_Stick::button_f3 == true) && (button_f3_temp == false) && (Remote_Stick::button_f1 != true) && (Remote_Stick::button_f2 != true))
        {
            button_press_time = Kernel::get_ms_count();
        }
//falling edge
        else if((Remote_Stick::button_f3 == false) && (button_f3_temp == true) && (Remote_Stick::button_f1 != true) && (Remote_Stick::button_f2 != true))
        {

            if((Kernel::get_ms_count() - button_press_time) < 1000)
            {
                //keycode escape
                key_mouse.key_code(0);
            }
            else
            {
                mouse_mode ^= true;
            }
        }


        if((Remote_Stick::button_stf == true) && (button_stf_temp == false))
        {
            if(stf_mode == true)
            {
                key_mouse.key_code(BUTTON_VALUE_V, KEY_SHIFT); //V
                stf_mode = false;
            }
            else
            {
                key_mouse.key_code(BUTTON_VALUE_S, KEY_SHIFT); //S
                stf_mode = true;
            }
        }

        if((Remote_Stick::button_f1 == true) && (Remote_Stick::button_f2 == true) && (Remote_Stick::button_f3 == true))
        {

            startBootloader();
        }


        button_f3_temp = Remote_Stick::button_f3;
        button_stf_temp = Remote_Stick::button_stf;

        thread_sleep_for(WAIT);
    }
}
