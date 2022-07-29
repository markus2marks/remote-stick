/*
 * isr_functions.cpp
 *
 *  Created on: 29.07.2022
 *      Author: Marks_Markus
 */
#include "remote_stick.h"

Remote_Stick::Remote_Stick(InterruptIn& buttonCenter,
        InterruptIn& buttonUp,
        InterruptIn& buttonDown,
        InterruptIn& buttonLeft,
        InterruptIn& buttonRight,
        InterruptIn& buttonF1,
        InterruptIn& buttonF2,
        InterruptIn& buttonF3,
        InterruptIn& buttonStf) : m_buttonCenter(buttonCenter), m_buttonUp(buttonUp), m_buttonDown(buttonDown), m_buttonLeft(buttonLeft), m_buttonRight(buttonRight), m_buttonF1(buttonF1), m_buttonF2(buttonF2), m_buttonF3(buttonF3), m_buttonStf(buttonStf)
{
    m_buttonCenter.mode(PullDown);
    m_buttonUp.mode(PullDown);
    m_buttonDown.mode(PullDown);
    m_buttonLeft.mode(PullDown);
    m_buttonRight.mode(PullDown);

    m_buttonF1.mode(PullDown);
    m_buttonF2.mode(PullDown);
    m_buttonF3.mode(PullDown);
    m_buttonStf.mode(PullDown);

    m_buttonCenter.rise(&this->buttonCenter_pressed);
    m_buttonCenter.fall(&this->buttonCenter_unpressed);

    m_buttonUp.rise(&this->buttonUp_pressed);
    m_buttonUp.fall(&this->buttonUp_unpressed);

    m_buttonDown.rise(&this->buttonDown_pressed);
    m_buttonDown.fall(&this->buttonDown_unpressed);

    m_buttonLeft.rise(&this->buttonLeft_pressed);
    m_buttonLeft.fall(&this->buttonLeft_unpressed);

    m_buttonRight.rise(&this->buttonRight_pressed);
    m_buttonRight.fall(&this->buttonRight_unpressed);

    m_buttonF1.rise(&this->buttonF1_pressed);
    m_buttonF1.fall(&this->buttonF1_unpressed);

    m_buttonF2.rise(&this->buttonF2_pressed);
    m_buttonF2.fall(&this->buttonF2_unpressed);

    m_buttonF3.rise(&this->buttonF3_pressed);
    m_buttonF3.fall(&this->buttonF3_unpressed);

    m_buttonStf.rise(&this->buttonStf_pressed);
    m_buttonStf.fall(&this->buttonStf_unpressed);
}

bool Remote_Stick::button_center = false;
bool Remote_Stick::button_up = false;
bool Remote_Stick::button_down = false;
bool Remote_Stick::button_left = false;
bool Remote_Stick::button_right = false;
bool Remote_Stick::button_f1 = false;
bool Remote_Stick::button_f2 = false;
bool Remote_Stick::button_f3 = false;
bool Remote_Stick::button_stf = false;

void Remote_Stick::buttonCenter_pressed()
{
    button_center = true;
}

void Remote_Stick::buttonCenter_unpressed()
{
    button_center = false;
}

void Remote_Stick::buttonUp_pressed()
{
    button_up = true;
}

void Remote_Stick::buttonUp_unpressed()
{
    button_up = false;
}

void Remote_Stick::buttonDown_pressed()
{
    button_down = true;
}

void Remote_Stick::buttonDown_unpressed()
{
    button_down = false;
}

void Remote_Stick::buttonLeft_pressed()
{
    button_left = true;
}

void Remote_Stick::buttonLeft_unpressed()
{
    button_left = false;
}

void Remote_Stick::buttonRight_pressed()
{
    button_right = true;
}

void Remote_Stick::buttonRight_unpressed()
{
    button_right = false;
}

void Remote_Stick::buttonF1_pressed()
{
    button_f1 = true;
}

void Remote_Stick::buttonF1_unpressed()
{
    button_f1 = false;
}

void Remote_Stick::buttonF2_pressed()
{
    button_f2 = true;
}

void Remote_Stick::buttonF2_unpressed()
{
    button_f2 = false;
}

void Remote_Stick::buttonF3_pressed()
{
    button_f3 = true;
}

void Remote_Stick::buttonF3_unpressed()
{
    button_f3 = false;
}

void Remote_Stick::buttonStf_pressed()
{
    button_stf = true;
}

void Remote_Stick::buttonStf_unpressed()
{
    button_stf = false;
}


