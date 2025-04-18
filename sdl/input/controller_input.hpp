#pragma once

//#define NO_CONTROLLER

#define SINGLE_CONTROLLER


#define CONTROLLER_BTN_DPAD_UP 1
#define CONTROLLER_BTN_DPAD_DOWN 1
#define CONTROLLER_BTN_DPAD_LEFT 1
#define CONTROLLER_BTN_DPAD_RIGHT 1
#define CONTROLLER_BTN_START 1
#define CONTROLLER_BTN_BACK 1
#define CONTROLLER_BTN_A 1
#define CONTROLLER_BTN_B 1
#define CONTROLLER_BTN_X 1
#define CONTROLLER_BTN_Y 1
#define CONTROLLER_BTN_SHOULDER_LEFT 1
#define CONTROLLER_BTN_SHOULDER_RIGHT 1
#define CONTROLLER_BTN_STICK_LEFT 1
#define CONTROLLER_BTN_STICK_RIGHT 1
#define CONTROLLER_AXIS_STICK_LEFT 1
#define CONTROLLER_AXIS_STICK_RIGHT 1
#define CONTROLLER_TRIGGER_LEFT 1
#define CONTROLLER_TRIGGER_RIGHT 1

#if CONTROLLER_BTN_DPAD_UP && CONTROLLER_BTN_DPAD_DOWN && CONTROLLER_BTN_DPAD_LEFT && CONTROLLER_BTN_DPAD_RIGHT
#define CONTROLLER_BTN_DPAD_ALL 1
#else
#define CONTROLLER_BTN_DPAD_ALL 0
#endif




namespace input
{
    constexpr unsigned N_CONTROLLER_BUTTONS = 
    CONTROLLER_BTN_DPAD_UP +
    CONTROLLER_BTN_DPAD_DOWN +
    CONTROLLER_BTN_DPAD_LEFT +
    CONTROLLER_BTN_DPAD_RIGHT +
    CONTROLLER_BTN_START +
    CONTROLLER_BTN_BACK +    
    CONTROLLER_BTN_A +
    CONTROLLER_BTN_B +
    CONTROLLER_BTN_X +
    CONTROLLER_BTN_Y +
    CONTROLLER_BTN_SHOULDER_LEFT +
    CONTROLLER_BTN_SHOULDER_RIGHT +
    CONTROLLER_BTN_STICK_LEFT +
    CONTROLLER_BTN_STICK_RIGHT;
}
