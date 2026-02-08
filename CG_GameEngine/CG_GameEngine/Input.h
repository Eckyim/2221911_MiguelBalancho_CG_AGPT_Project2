#pragma once

namespace Key {
    const int A = 4;
    const int B = 5;
    const int C = 6;
    const int D = 7;
    const int E = 8;
    const int F = 9;
    const int G = 10;
    const int H = 11;
    const int I = 12;
    const int J = 13;
    const int K = 14;
    const int L = 15;
    const int M = 16;
    const int N = 17;
    const int O = 18;
    const int P = 19;
    const int Q = 20;
    const int R = 21;
    const int S = 22;
    const int T = 23;
    const int U = 24;
    const int V = 25;
    const int W = 26;
    const int X = 27;
    const int Y = 28;
    const int Z = 29;

    const int NUM1 = 30;
    const int NUM2 = 31;
    const int NUM3 = 32;
    const int NUM4 = 33;
    const int NUM5 = 34;
    const int NUM6 = 35;
    const int NUM7 = 36;
    const int NUM8 = 37;
    const int NUM9 = 38;
    const int NUM0 = 39;

    const int RETURN = 40;
    const int ESCAPE = 41;
    const int BACKSPACE = 42;
    const int TAB = 43;
    const int SPACE = 44;

    const int MINUS = 45;
    const int EQUALS = 46;
    const int LEFTBRACKET = 47;
    const int RIGHTBRACKET = 48;
    const int BACKSLASH = 49;
    const int CAPSLOCK = 57;

    const int F1 = 58;
    const int F2 = 59;
    const int F3 = 60;
    const int F4 = 61;
    const int F5 = 62;
    const int F6 = 63;
    const int F7 = 64;
    const int F8 = 65;
    const int F9 = 66;
    const int F10 = 67;
    const int F11 = 68;
    const int F12 = 69;

    const int RIGHT = 79;
    const int LEFT = 80;
    const int DOWN = 81;
    const int UP = 82;
}

namespace GamepadButton {
    const int SOUTH_FACE_BUTTON = 0;
    const int XBOX_A = 0;
    const int PS_X = 0;
    const int EAST_FACE_BUTTON = 1;
    const int XBOX_B = 1;
    const int PS_CIRCLE = 1;
    const int WEST_FACE_BUTTON = 2;
    const int XBOX_X = 2;
    const int PS_SQUARE = 2;
    const int NORTH_FACE_BUTTON = 3;
    const int XBOX_Y = 3;
    const int PS_TRIANGLE = 3;

    const int BACK = 4;
    const int GUIDE = 5;
    const int START = 6;
    const int LEFT_STICK = 7;
    const int RIGHT_STICK = 8;
    const int LEFT_SHOULDER = 9;
    const int RIGHT_SHOULDER = 10;
    const int DPAD_UP = 11;
    const int DPAD_DOWN = 12;
    const int DPAD_LEFT = 13;
    const int DPAD_RIGHT = 14;
}

namespace GamepadAxis {
    const int LEFT_X = 0;
    const int LEFT_Y = 1;
    const int RIGHT_X = 2;
    const int RIGHT_Y = 3;
    const int LEFT_TRIGGER = 4;
    const int RIGHT_TRIGGER = 5;
}

struct SDL_Gamepad;

class Input
{
private:
	const bool* keyboardState;
    SDL_Gamepad* controller;

public:
	Input();
    ~Input();

	bool GetKey(int key);

    bool IsControllerConnected();
    bool GetControllerButton(int button);
    float GetControllerAxis(int axis); 

    void OnControllerAdded(int deviceID);
    void OnControllerRemoved(int deviceID);

};

