#include "pch.h"
#include "AUIKeycode.h"

#if defined(_WIN32)

#include <winuser.h>

const unsigned int MAUIKeycode::kBackspace = VK_BACK;
const unsigned int MAUIKeycode::kDelete = VK_DELETE;
const unsigned int MAUIKeycode::kArrowUp = VK_UP;
const unsigned int MAUIKeycode::kArrowDown = VK_DOWN;
const unsigned int MAUIKeycode::kArrowLeft = VK_LEFT;
const unsigned int MAUIKeycode::kArrowRight = VK_RIGHT;
const unsigned int MAUIKeycode::kCapslock = VK_CAPITAL;
const unsigned int MAUIKeycode::kContextMenu = VK_APPS;
const unsigned int MAUIKeycode::kBreak = VK_CANCEL;
const unsigned int MAUIKeycode::kHome = VK_HOME;
const unsigned int MAUIKeycode::kEnd = VK_END;
const unsigned int MAUIKeycode::kInsert = VK_INSERT;
const unsigned int MAUIKeycode::kKana = VK_KANA;
const unsigned int MAUIKeycode::kKanji = VK_KANJI;
const unsigned int MAUIKeycode::kJunja = VK_JUNJA;
const unsigned int MAUIKeycode::kHelp = VK_HELP;
const unsigned int MAUIKeycode::kFinal = VK_FINAL;
const unsigned int MAUIKeycode::kLeftControl = VK_LCONTROL;
const unsigned int MAUIKeycode::kLeftAlt = VK_LMENU;
const unsigned int MAUIKeycode::kLeftShift = VK_LSHIFT;
const unsigned int MAUIKeycode::kLeftWin = VK_LWIN;
const unsigned int MAUIKeycode::kRightControl = VK_RCONTROL;
const unsigned int MAUIKeycode::kRightAlt = VK_RMENU;
const unsigned int MAUIKeycode::kRightShift = VK_RSHIFT;
const unsigned int MAUIKeycode::kRightWin = VK_RWIN;
const unsigned int MAUIKeycode::kMouseLeftButton = VK_LBUTTON;
const unsigned int MAUIKeycode::kMouseRightButton = VK_RBUTTON;
const unsigned int MAUIKeycode::kMouseMiddleButton = VK_MBUTTON;
const unsigned int MAUIKeycode::kPrintScreen = VK_SNAPSHOT;
const unsigned int MAUIKeycode::kClear = VK_CLEAR;
const unsigned int MAUIKeycode::kDecimal = VK_DECIMAL;
const unsigned int MAUIKeycode::kDivide = VK_DIVIDE;
const unsigned int MAUIKeycode::kMultiply = VK_MULTIPLY;
const unsigned int MAUIKeycode::kAdd = VK_ADD;
const unsigned int MAUIKeycode::kSubtract = VK_SUBTRACT;
const unsigned int MAUIKeycode::kNumpad_0 = VK_NUMPAD0;
const unsigned int MAUIKeycode::kNumpad_1 = VK_NUMPAD1;
const unsigned int MAUIKeycode::kNumpad_2 = VK_NUMPAD2;
const unsigned int MAUIKeycode::kNumpad_3 = VK_NUMPAD3;
const unsigned int MAUIKeycode::kNumpad_4 = VK_NUMPAD4;
const unsigned int MAUIKeycode::kNumpad_5 = VK_NUMPAD5;
const unsigned int MAUIKeycode::kNumpad_6 = VK_NUMPAD6;
const unsigned int MAUIKeycode::kNumpad_7 = VK_NUMPAD7;
const unsigned int MAUIKeycode::kNumpad_8 = VK_NUMPAD8;
const unsigned int MAUIKeycode::kNumpad_9 = VK_NUMPAD9;
const unsigned int MAUIKeycode::kTab = VK_TAB;
const unsigned int MAUIKeycode::kBackTab = VK_OEM_BACKTAB;
const unsigned int MAUIKeycode::kJump = VK_OEM_JUMP;
const unsigned int MAUIKeycode::kReset = VK_OEM_RESET;
const unsigned int MAUIKeycode::kEnter = VK_RETURN;
const unsigned int MAUIKeycode::kSpace = VK_SPACE;
const unsigned int MAUIKeycode::kEscape = VK_ESCAPE;
const unsigned int MAUIKeycode::kExecute = VK_EXECUTE;
const unsigned int MAUIKeycode::kKey_0 = 0x30;
const unsigned int MAUIKeycode::kKey_1 = 0x31;
const unsigned int MAUIKeycode::kKey_2 = 0x32;
const unsigned int MAUIKeycode::kKey_3 = 0x33;
const unsigned int MAUIKeycode::kKey_4 = 0x34;
const unsigned int MAUIKeycode::kKey_5 = 0x35;
const unsigned int MAUIKeycode::kKey_6 = 0x36;
const unsigned int MAUIKeycode::kKey_7 = 0x37;
const unsigned int MAUIKeycode::kKey_8 = 0x38;
const unsigned int MAUIKeycode::kKey_9 = 0x39;
const unsigned int MAUIKeycode::kKey_A = 0x41;
const unsigned int MAUIKeycode::kKey_B = 0x42;
const unsigned int MAUIKeycode::kKey_C = 0x43;
const unsigned int MAUIKeycode::kKey_D = 0x44;
const unsigned int MAUIKeycode::kKey_E = 0x45;
const unsigned int MAUIKeycode::kKey_F = 0x46;
const unsigned int MAUIKeycode::kKey_G = 0x47;
const unsigned int MAUIKeycode::kKey_H = 0x48;
const unsigned int MAUIKeycode::kKey_I = 0x49;
const unsigned int MAUIKeycode::kKey_J = 0x4A;
const unsigned int MAUIKeycode::kKey_K = 0x4B;
const unsigned int MAUIKeycode::kKey_L = 0x4C;
const unsigned int MAUIKeycode::kKey_M = 0x4D;
const unsigned int MAUIKeycode::kKey_N = 0x4E;
const unsigned int MAUIKeycode::kKey_O = 0x4F;
const unsigned int MAUIKeycode::kKey_P = 0x50;
const unsigned int MAUIKeycode::kKey_Q = 0x51;
const unsigned int MAUIKeycode::kKey_R = 0x52;
const unsigned int MAUIKeycode::kKey_S = 0x53;
const unsigned int MAUIKeycode::kKey_T = 0x54;
const unsigned int MAUIKeycode::kKey_U = 0x55;
const unsigned int MAUIKeycode::kKey_V = 0x56;
const unsigned int MAUIKeycode::kKey_W = 0x57;
const unsigned int MAUIKeycode::kKey_X = 0x58;
const unsigned int MAUIKeycode::kKey_Y = 0x59;
const unsigned int MAUIKeycode::kKey_Z = 0x5A;
const unsigned int MAUIKeycode::kF1 = VK_F1;
const unsigned int MAUIKeycode::kF2 = VK_F2;
const unsigned int MAUIKeycode::kF3 = VK_F3;
const unsigned int MAUIKeycode::kF4 = VK_F4;
const unsigned int MAUIKeycode::kF5 = VK_F5;
const unsigned int MAUIKeycode::kF6 = VK_F6;
const unsigned int MAUIKeycode::kF7 = VK_F7;
const unsigned int MAUIKeycode::kF8 = VK_F8;
const unsigned int MAUIKeycode::kF9 = VK_F9;
const unsigned int MAUIKeycode::kF10 = VK_F10;
const unsigned int MAUIKeycode::kF11 = VK_F11;
const unsigned int MAUIKeycode::kF12 = VK_F12;
const unsigned int MAUIKeycode::kF13 = VK_F13;
const unsigned int MAUIKeycode::kF14 = VK_F14;
const unsigned int MAUIKeycode::kF15 = VK_F15;
const unsigned int MAUIKeycode::kF16 = VK_F16;
const unsigned int MAUIKeycode::kF17 = VK_F17;
const unsigned int MAUIKeycode::kF18 = VK_F18;
const unsigned int MAUIKeycode::kF19 = VK_F19;
const unsigned int MAUIKeycode::kF20 = VK_F20;
const unsigned int MAUIKeycode::kF21 = VK_F21;
const unsigned int MAUIKeycode::kF22 = VK_F22;
const unsigned int MAUIKeycode::kF23 = VK_F23;
const unsigned int MAUIKeycode::kF24 = VK_F24;

#elif defined(__APPLE__)

// TODO : Get keycodes from Cocoa Framework
/*
 *  Summary:
 *    Virtual keycodes
 *
 *  Discussion:
 *    These constants are the virtual keycodes defined originally in
 *    Inside Mac Volume V, pg. V-191. They identify physical keys on a
 *    keyboard. Those constants with "ANSI" in the name are labeled
 *    according to the key position on an ANSI-standard US keyboard.
 *    For example, kVK_ANSI_A indicates the virtual keycode for the key
 *    with the letter 'A' in the US keyboard layout. Other keyboard
 *    layouts may have the 'A' key label on a different physical key;
 *    in this case, pressing 'A' will generate a different virtual
 *    keycode.
 */
enum {
    kVK_ANSI_A                    = 0x00,
    kVK_ANSI_S                    = 0x01,
    kVK_ANSI_D                    = 0x02,
    kVK_ANSI_F                    = 0x03,
    kVK_ANSI_H                    = 0x04,
    kVK_ANSI_G                    = 0x05,
    kVK_ANSI_Z                    = 0x06,
    kVK_ANSI_X                    = 0x07,
    kVK_ANSI_C                    = 0x08,
    kVK_ANSI_V                    = 0x09,
    kVK_ANSI_B                    = 0x0B,
    kVK_ANSI_Q                    = 0x0C,
    kVK_ANSI_W                    = 0x0D,
    kVK_ANSI_E                    = 0x0E,
    kVK_ANSI_R                    = 0x0F,
    kVK_ANSI_Y                    = 0x10,
    kVK_ANSI_T                    = 0x11,
    kVK_ANSI_1                    = 0x12,
    kVK_ANSI_2                    = 0x13,
    kVK_ANSI_3                    = 0x14,
    kVK_ANSI_4                    = 0x15,
    kVK_ANSI_6                    = 0x16,
    kVK_ANSI_5                    = 0x17,
    kVK_ANSI_Equal                = 0x18,
    kVK_ANSI_9                    = 0x19,
    kVK_ANSI_7                    = 0x1A,
    kVK_ANSI_Minus                = 0x1B,
    kVK_ANSI_8                    = 0x1C,
    kVK_ANSI_0                    = 0x1D,
    kVK_ANSI_RightBracket         = 0x1E,
    kVK_ANSI_O                    = 0x1F,
    kVK_ANSI_U                    = 0x20,
    kVK_ANSI_LeftBracket          = 0x21,
    kVK_ANSI_I                    = 0x22,
    kVK_ANSI_P                    = 0x23,
    kVK_ANSI_L                    = 0x25,
    kVK_ANSI_J                    = 0x26,
    kVK_ANSI_Quote                = 0x27,
    kVK_ANSI_K                    = 0x28,
    kVK_ANSI_Semicolon            = 0x29,
    kVK_ANSI_Backslash            = 0x2A,
    kVK_ANSI_Comma                = 0x2B,
    kVK_ANSI_Slash                = 0x2C,
    kVK_ANSI_N                    = 0x2D,
    kVK_ANSI_M                    = 0x2E,
    kVK_ANSI_Period               = 0x2F,
    kVK_ANSI_Grave                = 0x32,
    kVK_ANSI_KeypadDecimal        = 0x41,
    kVK_ANSI_KeypadMultiply       = 0x43,
    kVK_ANSI_KeypadPlus           = 0x45,
    kVK_ANSI_KeypadClear          = 0x47,
    kVK_ANSI_KeypadDivide         = 0x4B,
    kVK_ANSI_KeypadEnter          = 0x4C,
    kVK_ANSI_KeypadMinus          = 0x4E,
    kVK_ANSI_KeypadEquals         = 0x51,
    kVK_ANSI_Keypad0              = 0x52,
    kVK_ANSI_Keypad1              = 0x53,
    kVK_ANSI_Keypad2              = 0x54,
    kVK_ANSI_Keypad3              = 0x55,
    kVK_ANSI_Keypad4              = 0x56,
    kVK_ANSI_Keypad5              = 0x57,
    kVK_ANSI_Keypad6              = 0x58,
    kVK_ANSI_Keypad7              = 0x59,
    kVK_ANSI_Keypad8              = 0x5B,
    kVK_ANSI_Keypad9              = 0x5C
};

/* keycodes for keys that are independent of keyboard layout*/
enum {
    kVK_Return                    = 0x24,
    kVK_Tab                       = 0x30,
    kVK_Space                     = 0x31,
    kVK_Delete                    = 0x33,
    kVK_Escape                    = 0x35,
    kVK_Command                   = 0x37,
    kVK_Shift                     = 0x38,
    kVK_CapsLock                  = 0x39,
    kVK_Option                    = 0x3A,
    kVK_Control                   = 0x3B,
    kVK_RightShift                = 0x3C,
    kVK_RightOption               = 0x3D,
    kVK_RightControl              = 0x3E,
    kVK_Function                  = 0x3F,
    kVK_F17                       = 0x40,
    kVK_VolumeUp                  = 0x48,
    kVK_VolumeDown                = 0x49,
    kVK_Mute                      = 0x4A,
    kVK_F18                       = 0x4F,
    kVK_F19                       = 0x50,
    kVK_F20                       = 0x5A,
    kVK_F5                        = 0x60,
    kVK_F6                        = 0x61,
    kVK_F7                        = 0x62,
    kVK_F3                        = 0x63,
    kVK_F8                        = 0x64,
    kVK_F9                        = 0x65,
    kVK_F11                       = 0x67,
    kVK_F13                       = 0x69,
    kVK_F16                       = 0x6A,
    kVK_F14                       = 0x6B,
    kVK_F10                       = 0x6D,
    kVK_F12                       = 0x6F,
    kVK_F15                       = 0x71,
    kVK_Help                      = 0x72,
    kVK_Home                      = 0x73,
    kVK_PageUp                    = 0x74,
    kVK_ForwardDelete             = 0x75,
    kVK_F4                        = 0x76,
    kVK_End                       = 0x77,
    kVK_F2                        = 0x78,
    kVK_PageDown                  = 0x79,
    kVK_F1                        = 0x7A,
    kVK_LeftArrow                 = 0x7B,
    kVK_RightArrow                = 0x7C,
    kVK_DownArrow                 = 0x7D,
    kVK_UpArrow                   = 0x7E
};

/* ISO keyboards only*/
enum {
    kVK_ISO_Section               = 0x0A
};

/* JIS keyboards only*/
enum {
    kVK_JIS_Yen                   = 0x5D,
    kVK_JIS_Underscore            = 0x5E,
    kVK_JIS_KeypadComma           = 0x5F,
    kVK_JIS_Eisu                  = 0x66,
    kVK_JIS_Kana                  = 0x68
};

const unsigned int kVK_Undefined  = static_cast<unsigned int>(-1);

const unsigned int MAUIKeycode::kBackspace = kVK_Delete;
const unsigned int MAUIKeycode::kDelete = kVK_ForwardDelete;
const unsigned int MAUIKeycode::kArrowUp = kVK_UpArrow;
const unsigned int MAUIKeycode::kArrowDown = kVK_DownArrow;
const unsigned int MAUIKeycode::kArrowLeft = kVK_LeftArrow;
const unsigned int MAUIKeycode::kArrowRight = kVK_RightArrow;
const unsigned int MAUIKeycode::kCapslock = kVK_CapsLock;
const unsigned int MAUIKeycode::kContextMenu = kVK_Undefined;
const unsigned int MAUIKeycode::kBreak = kVK_Undefined;
const unsigned int MAUIKeycode::kHome = kVK_Home;
const unsigned int MAUIKeycode::kEnd = kVK_End;
const unsigned int MAUIKeycode::kInsert = kVK_Undefined;
const unsigned int MAUIKeycode::kKana = kVK_JIS_Kana;
const unsigned int MAUIKeycode::kKanji = kVK_Undefined;
const unsigned int MAUIKeycode::kJunja = kVK_Undefined;
const unsigned int MAUIKeycode::kHelp = kVK_Help;
const unsigned int MAUIKeycode::kFinal = kVK_Undefined;
const unsigned int MAUIKeycode::kLeftControl = kVK_Control;
const unsigned int MAUIKeycode::kLeftAlt = kVK_Option;
const unsigned int MAUIKeycode::kLeftShift = kVK_Shift;
const unsigned int MAUIKeycode::kLeftWin = kVK_Command;
const unsigned int MAUIKeycode::kRightControl = kVK_RightControl;
const unsigned int MAUIKeycode::kRightAlt = kVK_RightOption;
const unsigned int MAUIKeycode::kRightShift = kVK_RightShift;
const unsigned int MAUIKeycode::kRightWin = 231;
const unsigned int MAUIKeycode::kMouseLeftButton = kVK_Undefined;       // TODO
const unsigned int MAUIKeycode::kMouseRightButton = kVK_Undefined;      // TODO
const unsigned int MAUIKeycode::kMouseMiddleButton = kVK_Undefined;     // TODO
const unsigned int MAUIKeycode::kPrintScreen = kVK_Undefined;
const unsigned int MAUIKeycode::kClear = kVK_Undefined;
const unsigned int MAUIKeycode::kDecimal = kVK_ANSI_KeypadDecimal;
const unsigned int MAUIKeycode::kDivide = kVK_ANSI_KeypadDivide;
const unsigned int MAUIKeycode::kMultiply = kVK_ANSI_KeypadMultiply;
const unsigned int MAUIKeycode::kAdd = kVK_ANSI_KeypadPlus;
const unsigned int MAUIKeycode::kSubtract = kVK_ANSI_KeypadMinus;
const unsigned int MAUIKeycode::kNumpad_0 = kVK_ANSI_Keypad0;
const unsigned int MAUIKeycode::kNumpad_1 = kVK_ANSI_Keypad1;
const unsigned int MAUIKeycode::kNumpad_2 = kVK_ANSI_Keypad2;
const unsigned int MAUIKeycode::kNumpad_3 = kVK_ANSI_Keypad3;
const unsigned int MAUIKeycode::kNumpad_4 = kVK_ANSI_Keypad4;
const unsigned int MAUIKeycode::kNumpad_5 = kVK_ANSI_Keypad5;
const unsigned int MAUIKeycode::kNumpad_6 = kVK_ANSI_Keypad6;
const unsigned int MAUIKeycode::kNumpad_7 = kVK_ANSI_Keypad7;
const unsigned int MAUIKeycode::kNumpad_8 = kVK_ANSI_Keypad8;
const unsigned int MAUIKeycode::kNumpad_9 = kVK_ANSI_Keypad9;
const unsigned int MAUIKeycode::kTab = kVK_Tab;
const unsigned int MAUIKeycode::kBackTab = kVK_Undefined;
const unsigned int MAUIKeycode::kJump = kVK_Undefined;
const unsigned int MAUIKeycode::kReset = kVK_Undefined;
const unsigned int MAUIKeycode::kEnter = kVK_Return;
const unsigned int MAUIKeycode::kSpace = kVK_Space;
const unsigned int MAUIKeycode::kEscape = kVK_Escape;
const unsigned int MAUIKeycode::kExecute = kVK_Undefined;
const unsigned int MAUIKeycode::kKey_0 = kVK_ANSI_0;
const unsigned int MAUIKeycode::kKey_1 = kVK_ANSI_1;
const unsigned int MAUIKeycode::kKey_2 = kVK_ANSI_2;
const unsigned int MAUIKeycode::kKey_3 = kVK_ANSI_3;
const unsigned int MAUIKeycode::kKey_4 = kVK_ANSI_4;
const unsigned int MAUIKeycode::kKey_5 = kVK_ANSI_5;
const unsigned int MAUIKeycode::kKey_6 = kVK_ANSI_6;
const unsigned int MAUIKeycode::kKey_7 = kVK_ANSI_7;
const unsigned int MAUIKeycode::kKey_8 = kVK_ANSI_8;
const unsigned int MAUIKeycode::kKey_9 = kVK_ANSI_9;
const unsigned int MAUIKeycode::kKey_A = kVK_ANSI_A;
const unsigned int MAUIKeycode::kKey_B = kVK_ANSI_B;
const unsigned int MAUIKeycode::kKey_C = kVK_ANSI_C;
const unsigned int MAUIKeycode::kKey_D = kVK_ANSI_D;
const unsigned int MAUIKeycode::kKey_E = kVK_ANSI_E;
const unsigned int MAUIKeycode::kKey_F = kVK_ANSI_F;
const unsigned int MAUIKeycode::kKey_G = kVK_ANSI_G;
const unsigned int MAUIKeycode::kKey_H = kVK_ANSI_H;
const unsigned int MAUIKeycode::kKey_I = kVK_ANSI_I;
const unsigned int MAUIKeycode::kKey_J = kVK_ANSI_J;
const unsigned int MAUIKeycode::kKey_K = kVK_ANSI_K;
const unsigned int MAUIKeycode::kKey_L = kVK_ANSI_L;
const unsigned int MAUIKeycode::kKey_M = kVK_ANSI_M;
const unsigned int MAUIKeycode::kKey_N = kVK_ANSI_N;
const unsigned int MAUIKeycode::kKey_O = kVK_ANSI_O;
const unsigned int MAUIKeycode::kKey_P = kVK_ANSI_P;
const unsigned int MAUIKeycode::kKey_Q = kVK_ANSI_Q;
const unsigned int MAUIKeycode::kKey_R = kVK_ANSI_R;
const unsigned int MAUIKeycode::kKey_S = kVK_ANSI_S;
const unsigned int MAUIKeycode::kKey_T = kVK_ANSI_T;
const unsigned int MAUIKeycode::kKey_U = kVK_ANSI_U;
const unsigned int MAUIKeycode::kKey_V = kVK_ANSI_V;
const unsigned int MAUIKeycode::kKey_W = kVK_ANSI_W;
const unsigned int MAUIKeycode::kKey_X = kVK_ANSI_X;
const unsigned int MAUIKeycode::kKey_Y = kVK_ANSI_Y;
const unsigned int MAUIKeycode::kKey_Z = kVK_ANSI_Z;
const unsigned int MAUIKeycode::kF1 = kVK_F1;
const unsigned int MAUIKeycode::kF2 = kVK_F2;
const unsigned int MAUIKeycode::kF3 = kVK_F3;
const unsigned int MAUIKeycode::kF4 = kVK_F4;
const unsigned int MAUIKeycode::kF5 = kVK_F5;
const unsigned int MAUIKeycode::kF6 = kVK_F6;
const unsigned int MAUIKeycode::kF7 = kVK_F7;
const unsigned int MAUIKeycode::kF8 = kVK_F8;
const unsigned int MAUIKeycode::kF9 = kVK_F9;
const unsigned int MAUIKeycode::kF10 = kVK_F10;
const unsigned int MAUIKeycode::kF11 = kVK_F11;
const unsigned int MAUIKeycode::kF12 = kVK_F12;
const unsigned int MAUIKeycode::kF13 = kVK_F13;
const unsigned int MAUIKeycode::kF14 = kVK_F14;
const unsigned int MAUIKeycode::kF15 = kVK_F15;
const unsigned int MAUIKeycode::kF16 = kVK_F16;
const unsigned int MAUIKeycode::kF17 = kVK_F17;
const unsigned int MAUIKeycode::kF18 = kVK_F18;
const unsigned int MAUIKeycode::kF19 = kVK_F19;
const unsigned int MAUIKeycode::kF20 = kVK_F20;
const unsigned int MAUIKeycode::kF21 = kVK_Undefined;
const unsigned int MAUIKeycode::kF22 = kVK_Undefined;
const unsigned int MAUIKeycode::kF23 = kVK_Undefined;
const unsigned int MAUIKeycode::kF24 = kVK_Undefined;

#else

#   error TODO: Implement for other OS

#endif
