/*
* Copyright(c) 2017 Jani Niemelä.
* License: https://github.com/siquel/win32/blob/master/LICENSE
*/
#pragma once

namespace hotswap
{
    struct GameInput
    {
        uint8_t state[4];
        union
        {
            uint8_t w;
            uint8_t a;
            uint8_t s;
            uint8_t d;
        };
    };

    struct Keyboard
    {
        enum Key
        {
            Backspace,
            Tab,
            Enter,
            CapsLock,
            Escape,
            Space,
            PageUp,
            PageDown,
            End,
            Home,
            Left,
            Up,
            Right,
            Down,
            Select,
            Print,
            Execute,
            PrintScreen,
            Insert,
            Delete,
            Help,
            D0,              ///< The 0 key
            D1,              ///< The 1 key
            D2,              ///< The 2 key
            D3,              ///< The 3 key
            D4,              ///< The 4 key
            D5,              ///< The 5 key
            D6,              ///< The 6 key
            D7,              ///< The 7 key
            D8,              ///< The 8 key
            D9,              ///< The 9 key
            A,               ///< The A key
            B,               ///< The B key
            C,               ///< The C key
            D,               ///< The D key
            E,               ///< The E key
            F,               ///< The F key
            G,               ///< The G key
            H,               ///< The H key
            I,               ///< The I key
            J,               ///< The J key
            K,               ///< The K key
            L,               ///< The L key
            M,               ///< The M key
            N,               ///< The N key
            O,               ///< The O key
            P,               ///< The P key
            Q,               ///< The Q key
            R,               ///< The R key
            S,               ///< The S key
            T,               ///< The T key
            U,               ///< The U key
            V,               ///< The V key
            W,               ///< The W key
            X,               ///< The X key
            Y,               ///< The Y key
            Z,               ///< The Z key
            LeftSystem,      ///< The left system key
            RightSystem,     ///< The right system key
            Applications,
            Sleep,
            NumPad0,         ///< The numpad 0 key
            NumPad1,         ///< The numpad 1 key
            NumPad2,         ///< The numpad 2 key
            NumPad3,         ///< The numpad 3 key
            NumPad4,         ///< The numpad 4 key
            NumPad5,         ///< The numpad 5 key
            NumPad6,         ///< The numpad 6 key
            NumPad7,         ///< The numpad 7 key
            NumPad8,         ///< The numpad 8 key
            NumPad9,         ///< The numpad 9 key
            Multiply,        ///< The numpad multiply key
            Add,             ///< The numpad add key
            NumpadEnter,     ///< The numpad enter (separator) key  
            Subtract,        ///< The numpad subtract add key
            Decimal,         ///< The numpad decimal add key
            Divide,          ///< The numpad divide add key
            F1,              ///< The F1 key
            F2,              ///< The F2 key
            F3,              ///< The F3 key
            F4,              ///< The F4 key
            F5,              ///< The F5 key
            F6,              ///< The F6 key
            F7,              ///< The F7 key
            F8,              ///< The F8 key
            F9,              ///< The F9 key
            F10,             ///< The F10 key
            F11,             ///< The F11 key
            F12,             ///< The F12 key
            F13,             ///< The F13 key
            F14,             ///< The F14 key
            F15,             ///< The F15 key
            F16,             ///< The F16 key
            F17,             ///< The F17 key
            F18,             ///< The F18 key
            F19,             ///< The F19 key
            F20,             ///< The F20 key
            F21,             ///< The F21 key
            F22,             ///< The F22 key
            F23,             ///< The F23 key
            F24,             ///< The F24 key
            NumLock,         ///< The numlock key
            ScrollLock,      ///< The scroll lock key
            LeftShift,       ///< The left shift key
            RightShift,      ///< The right shift key
            LeftControl,     ///< The left control key
            RightControl,    ///< The left control key
            LeftAlt,
            RightAlt,
            BrowserBack,
            BrowserForward,
            BrowserRefresh,
            BrowserStop,
            BrowserSearch,
            BrowserFavorites,
            BrowserHome,
            VolumeMute,
            VolumeDown,
            VolumeUp,
            MediaNextTrack,
            MediaPreviousTrack,
            MediaStop,
            MediaPlayPause,
            LaunchMail,
            SelectMedia,
            LaunchApplication1,
            LaunchApplication2,
            OemSemicolon,
            OemPlus,
            OemComma,
            OemMinus,
            OemPeriod,
            OemQuestion,
            OemTilde,
            OemOpenBrackets,
            OemPipe,
            OemCloseBrackets,
            OemQuotes,
            Oem8,
            OemBackslash,
            ProcessKey,
            Attn,
            Crsel,
            Exsel,
            EraseEof,
            Play,
            Zoom,
            Pa1,
            OemClear,
            Pause,
            ImeConvert,
            ImeNoConvert,
            Kana,        ///< The Kana key on Japanese keyboards.
            Kanji,       ///< The Kanji key on Japanese keyboards
            Count
        };
    };

    bool inputIsKeyPressed(Keyboard::Key key);

    bool inputIsKeyDown(Keyboard::Key key);

    bool inputIsKeyReleased(Keyboard::Key key);

    void engineUpdate();

    typedef void(*game_update_t)(const GameInput* input);
}
