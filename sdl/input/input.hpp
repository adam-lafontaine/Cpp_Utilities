#pragma once

#include "../util/types.hpp"
#include "keyboard_input.hpp"
#include "mouse_input.hpp"
#include "gamepad_input.hpp"
#include "joystick_input.hpp"


/* button state */

namespace input
{
	constexpr u32 N_STATES = 3;
	

	union ButtonState
	{
		b8 states[N_STATES];
		struct
		{
			b8 pressed;
			b8 is_down;
			b8 raised;
		};
	};


	template <typename T>
	class VectorState
	{
	public:
		Vec2D<T> vec;

		f32 magnitude;

		union
		{
			Vec2Df32 unit;

			struct
			{
				f32 cosine;
				f32 sine;
			};
		};		
	};
}


/* keyboard */

namespace input
{
	class KeyboardInput
	{
	public:
		b8 is_active;
		
		union
		{
			ButtonState keys[N_KEYBOARD_KEYS];
			
			struct
			{

			#if KEYBOARD_A
				ButtonState kbd_A;
			#endif
			#if KEYBOARD_B
				ButtonState kbd_B;
			#endif
			#if KEYBOARD_C
				ButtonState kbd_C;
			#endif
			#if KEYBOARD_D
				ButtonState kbd_D;
            #endif
            #if KEYBOARD_E
				ButtonState kbd_E;
            #endif
            #if KEYBOARD_F
				ButtonState kbd_F;
            #endif
            #if KEYBOARD_G
				ButtonState kbd_G;
            #endif
            #if KEYBOARD_H
				ButtonState kbd_H;
            #endif
            #if KEYBOARD_I
				ButtonState kbd_I;
            #endif
            #if KEYBOARD_J
				ButtonState kbd_J;
            #endif
            #if KEYBOARD_K
				ButtonState kbd_K;
            #endif
            #if KEYBOARD_L
				ButtonState kbd_L;
            #endif
            #if KEYBOARD_M
				ButtonState kbd_M;
            #endif
            #if KEYBOARD_N
				ButtonState kbd_N;
            #endif
            #if KEYBOARD_O
				ButtonState kbd_O;
            #endif
            #if KEYBOARD_P
				ButtonState kbd_P;
            #endif
            #if KEYBOARD_Q
				ButtonState kbd_Q;
            #endif
            #if KEYBOARD_R
				ButtonState kbd_R;
            #endif
            #if KEYBOARD_S
				ButtonState kbd_S;
            #endif
            #if KEYBOARD_T
				ButtonState kbd_T;
            #endif
            #if KEYBOARD_U
				ButtonState kbd_U;
            #endif
            #if KEYBOARD_V
				ButtonState kbd_V;
            #endif
            #if KEYBOARD_W
				ButtonState kbd_W;
            #endif
            #if KEYBOARD_X
				ButtonState kbd_X;
            #endif
            #if KEYBOARD_Y
				ButtonState kbd_Y;
            #endif
            #if KEYBOARD_Z
				ButtonState kbd_Z;
            #endif
            #if KEYBOARD_0
				ButtonState kbd_0;
            #endif
            #if KEYBOARD_1
				ButtonState kbd_1;
            #endif
            #if KEYBOARD_2
				ButtonState kbd_2;
            #endif
            #if KEYBOARD_3
				ButtonState kbd_3;
            #endif
            #if KEYBOARD_4
				ButtonState kbd_4;
            #endif
            #if KEYBOARD_5
				ButtonState kbd_5;
            #endif
            #if KEYBOARD_6
				ButtonState kbd_6;
            #endif
            #if KEYBOARD_7
				ButtonState kbd_7;
            #endif
            #if KEYBOARD_8
				ButtonState kbd_8;
            #endif
            #if KEYBOARD_9
				ButtonState kbd_9;
            #endif
            #if KEYBOARD_UP
				ButtonState kbd_up;
            #endif
            #if KEYBOARD_DOWN
				ButtonState kbd_down;
            #endif
            #if KEYBOARD_LEFT
				ButtonState kbd_left;
            #endif
            #if KEYBOARD_RIGHT
				ButtonState kbd_right;
            #endif
            #if KEYBOARD_RETURN
				ButtonState kbd_return;
            #endif
            #if KEYBOARD_ESCAPE
				ButtonState kbd_escape;
            #endif
            #if KEYBOARD_SPACE
				ButtonState kbd_space;
            #endif
            #if KEYBOARD_LSHIFT
				ButtonState kbd_left_shift;
            #endif
            #if KEYBOARD_RSHIFT
				ButtonState kbd_right_shift;
            #endif
            #if KEYBOARD_NUMPAD_0
				ButtonState npd_0;
            #endif
            #if KEYBOARD_NUMPAD_1
				ButtonState npd_1;
            #endif
            #if KEYBOARD_NUMPAD_2
				ButtonState npd_2;
            #endif
            #if KEYBOARD_NUMPAD_3
				ButtonState npd_3;
            #endif
            #if KEYBOARD_NUMPAD_4
				ButtonState npd_4;
            #endif
            #if KEYBOARD_NUMPAD_5
				ButtonState npd_5;
            #endif
            #if KEYBOARD_NUMPAD_6
				ButtonState npd_6;
            #endif
            #if KEYBOARD_NUMPAD_7
				ButtonState npd_7;
            #endif
            #if KEYBOARD_NUMPAD_8
				ButtonState npd_8;
            #endif
            #if KEYBOARD_NUMPAD_9
				ButtonState npd_9;
            #endif
            #if KEYBOARD_NUMPAD_PLUS
				ButtonState npd_plus;
            #endif
            #if KEYBOARD_NUMPAD_MINUS
				ButtonState npd_minus;
            #endif
            #if KEYBOARD_NUMPAD_MULTIPLY
				ButtonState npd_mult;
            #endif
            #if KEYBOARD_NUMPAD_DIVIDE
				ButtonState npd_div;
            #endif
            #if KEYBOARD_CTRL
				ButtonState kbd_ctrl;
			#endif

			};

		};
	};
}


/* mouse */

namespace input
{
	class MouseInput
	{
	public:

		b8 is_active;

	#if MOUSE_POSITION

		Point2Di32 window_pos;

	#endif
	#if MOUSE_WHEEL

		Vec2Di32 wheel;

	#endif

		union
		{
			ButtonState buttons[N_MOUSE_BUTTONS];
			struct
			{
			#if MOUSE_LEFT
				ButtonState btn_left;
			#endif
			#if MOUSE_RIGHT
				ButtonState btn_right;
			#endif
			#if MOUSE_MIDDLE
				ButtonState btn_middle;
			#endif
			#if MOUSE_X1
				ButtonState btn_x1;
			#endif
			#if MOUSE_X2
				ButtonState btn_x2;
			#endif
			};
		};

	};
}


/* gamepad */

namespace input
{
    class GamepadInput
    {
    public:

		b8 is_active = 0;
		u64 handle = 0;
	
        union
        {
            ButtonState buttons[N_GAMEPAD_BUTTONS];

            struct
            {
			#if GAMEPAD_BTN_SOUTH
                ButtonState btn_south;
			#endif
			#if GAMEPAD_BTN_EAST
                ButtonState btn_east;
			#endif
			#if GAMEPAD_BTN_WEST
                ButtonState btn_west;
			#endif
			#if GAMEPAD_BTN_NORTH
                ButtonState btn_north;
			#endif
			#if GAMEPAD_BTN_DPAD_UP
                ButtonState btn_dpad_up;
			#endif
			#if GAMEPAD_BTN_DPAD_DOWN
                ButtonState btn_dpad_down;
			#endif
			#if GAMEPAD_BTN_DPAD_LEFT
                ButtonState btn_dpad_left;
			#endif
			#if GAMEPAD_BTN_DPAD_RIGHT
                ButtonState btn_dpad_right;
			#endif
			#if GAMEPAD_BTN_START
                ButtonState btn_start;
			#endif
			#if GAMEPAD_BTN_BACK
                ButtonState btn_back;
			#endif
			#if GAMEPAD_BTN_SHOULDER_LEFT
                ButtonState btn_shoulder_left;
			#endif
			#if GAMEPAD_BTN_SHOULDER_RIGHT
                ButtonState btn_shoulder_right;
			#endif
			#if GAMEPAD_BTN_STICK_LEFT
                ButtonState btn_stick_left;
			#endif
			#if GAMEPAD_BTN_STICK_RIGHT
                ButtonState btn_stick_right;
			#endif
            };
        };

	#if GAMEPAD_AXIS_STICK_LEFT
        VectorState<f32> stick_left;
	#endif
	#if GAMEPAD_AXIS_STICK_RIGHT
        VectorState<f32> stick_right;
	#endif
	#if GAMEPAD_TRIGGER_LEFT
        f32 trigger_left;
	#endif
	#if GAMEPAD_TRIGGER_RIGHT
        f32 trigger_right;
	#endif
	#if GAMEPAD_BTN_DPAD_ALL
		VectorState<i8> vec_dpad;
	#endif	

    };
	
}


/* joystick */

namespace input
{
	class JoystickInput
	{
	public:

		b8 is_active= 0;
		u64 handle = 0;
	
		union
		{
			ButtonState buttons[N_JOYSTICK_BUTTONS];

			struct
			{
			#if JOYSTICK_BTN_0
				ButtonState btn_0;
			#endif
			#if JOYSTICK_BTN_1
				ButtonState btn_1;
			#endif
			#if JOYSTICK_BTN_2
				ButtonState btn_2;
			#endif
			#if JOYSTICK_BTN_3
				ButtonState btn_3;
			#endif
			#if JOYSTICK_BTN_4
				ButtonState btn_4;
			#endif
			#if JOYSTICK_BTN_5
				ButtonState btn_5;
			#endif
			#if JOYSTICK_BTN_6
				ButtonState btn_6;
			#endif
			#if JOYSTICK_BTN_7
				ButtonState btn_7;
			#endif
			#if JOYSTICK_BTN_8
				ButtonState btn_8;
			#endif
			#if JOYSTICK_BTN_9
				ButtonState btn_9;
			#endif
			};
		};

		union
		{
			f32 axes[N_JOYSTICK_AXES];

			struct
			{
			#if JOYSTICK_AXIS_0
				f32 axis_0;
			#endif
			#if JOYSTICK_AXIS_1
				f32 axis_1;
			#endif
			#if JOYSTICK_AXIS_2
				f32 axis_2;
			#endif
			#if JOYSTICK_AXIS_3
				f32 axis_3;
			#endif
			#if JOYSTICK_AXIS_4
				f32 axis_4;
			#endif
			#if JOYSTICK_AXIS_5
				f32 axis_5;
			#endif
			};
		};
	};
	
}


/* max inputs */

namespace input
{

#ifndef NO_GAMEPAD
#ifdef SINGLE_GAMEPAD
	constexpr u32 MAX_GAMEPADS = 1;
#else
	constexpr u32 MAX_GAMEPADS = 4;
#endif
#endif

#ifndef NO_JOYSTICK
#ifdef SINGLE_JOYSTICK
	constexpr u32 MAX_JOYSTICKS = 1;
#else
	constexpr u32 MAX_JOYSTICKS = 4;
#endif
#endif

}


/* input */

namespace input
{

	class Input
	{
	public:
		u64 frame;
		f32 dt_frame;

		b32 window_size_changed;

	#ifndef NO_KEYBOARD
		KeyboardInput keyboard;
	#endif

	#ifndef NO_MOUSE
		MouseInput mouse;
	#endif

	#ifndef NO_JOYSTICK
	#ifdef SINGLE_JOYSTICK
		union
		{
			JoystickInput joystick;
			JoystickInput joysticks[MAX_JOYSTICKS];
		};
	#else
		JoystickInput joysticks[MAX_JOYSTICKS];
	#endif
	#endif

	#ifndef NO_GAMEPAD
	#ifdef SINGLE_GAMEPAD
		union
		{
			GamepadInput gamepad;
			GamepadInput gamepads[MAX_GAMEPADS];
		};
	#else
		GamepadInput gamepads[MAX_GAMEPADS];		
	#endif

	#endif // NO_GAMEPAD		
	};


	class InputArray
	{
	private:
		b8 p = 0;
		b8 c = 1;

		Input inputs[2];

	public:	
		
		u32 n_gamepads = 0;
		u32 n_joysticks = 0;

		Input& prev() { return inputs[p]; }

		Input& curr() { return inputs[c]; }

		void swap() { p = c; c = !p; }
	};
}



/* api */

namespace input
{
	typedef void (*event_cb)(void *event);


	bool init(InputArray& inputs);

	void close();

	void record_input(InputArray& inputs);

	void record_input(InputArray& inputs, event_cb handle_event);

}

void end_program(); // define in main.cpp