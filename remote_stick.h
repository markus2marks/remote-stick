/*
 * isr_functions.h
 *
 *  Created on: 29.07.2022
 *      Author: Marks_Markus
 */

#ifndef REMOTE_STICK_H_
#define REMOTE_STICK_H_

#include "mbed.h"

class Remote_Stick
{
    private:
            InterruptIn &m_buttonCenter;
            InterruptIn &m_buttonUp;
            InterruptIn &m_buttonDown;
            InterruptIn &m_buttonLeft;
            InterruptIn &m_buttonRight;

            InterruptIn &m_buttonF1;
            InterruptIn &m_buttonF2;
            InterruptIn &m_buttonF3;
            InterruptIn &m_buttonStf;

    public:
        static bool button_center;
        static bool button_up;
        static bool button_down;
        static bool button_left;
        static bool button_right;
        static bool button_f1;
        static bool button_f2;
        static bool button_f3;
        static bool button_stf;




        Remote_Stick(InterruptIn& buttonCenter,
                InterruptIn &buttonUp,
                InterruptIn &buttonDown,
                InterruptIn &buttonLeft,
                InterruptIn &buttonRight,
                InterruptIn &buttonF1,
                InterruptIn &buttonF2,
                InterruptIn &buttonF3,
                InterruptIn &buttonStf);

        static void buttonCenter_pressed();

        static void buttonCenter_unpressed();

        static void buttonUp_pressed();

        static void buttonUp_unpressed();

        static void buttonDown_pressed();

        static void buttonDown_unpressed();

        static void buttonLeft_pressed();

        static void buttonLeft_unpressed();

        static void buttonRight_pressed();

        static void buttonRight_unpressed();

        static void buttonF1_pressed();

        static void buttonF1_unpressed();

        static void buttonF2_pressed();

        static void buttonF2_unpressed();

        static void buttonF3_pressed();

        static void buttonF3_unpressed();

        static void buttonStf_pressed();

        static void buttonStf_unpressed();
};

#endif /* REMOTE_STICK_H_ */
