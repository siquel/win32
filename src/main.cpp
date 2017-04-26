/*
* Copyright(c) 2017 Jani Niemelä.
* License: https://github.com/siquel/win32/blob/master/LICENSE
*/

#include "platform.h"
#if HOTSWAP_PLATFORM_WIN32

#include <Windows.h>
#include <stdint.h> // uint8_t
#include "hotswap.h"

// http://cnicholson.net/2011/01/stupid-c-tricks-a-better-sizeof_array/
template<typename T, size_t N> char(&COUNTOF_REQUIRES_ARRAY_ARGUMENT(const T(&)[N]))[N];
#define HOTSWAP_COUNTOF(x) sizeof(COUNTOF_REQUIRES_ARRAY_ARGUMENT(x))


#define HOTSWAP_ASSERT(condition) if (!(condition)) { *(int*)0x0 = 0; }

static bool s_exit = false;

#define MAX_INPUT_KEYS 256
static uint8_t s_translateKey[MAX_INPUT_KEYS];

static
void memCopy(void* destination, const void* source, size_t numBytes)
{
    uint8_t* dst = (uint8_t*)destination;
    const uint8_t* end = dst + numBytes;
    const uint8_t* src = (const uint8_t*)source;

    while (dst != end)
    {
        *dst++ = *src++;
    }
}

LRESULT CALLBACK win32WindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
    case WM_CLOSE:
    {
        s_exit = true;
    } break;

    default:
        return DefWindowProc(window, message, wparam, lparam);
    }
    return 0;
}

void win32InitTranslateKeys()
{
    using namespace hotswap;

    s_translateKey[VK_BACK] = Keyboard::Key::Backspace;
    s_translateKey[VK_TAB] = Keyboard::Key::Tab;
    s_translateKey[VK_RETURN] = Keyboard::Key::Enter;
    s_translateKey[VK_CAPITAL] = Keyboard::Key::CapsLock;
    s_translateKey[VK_ESCAPE] = Keyboard::Key::Escape;
    s_translateKey[VK_SPACE] = Keyboard::Key::Space;
    s_translateKey[VK_PRIOR] = Keyboard::Key::PageUp;
    s_translateKey[VK_NEXT] = Keyboard::Key::PageDown;
    s_translateKey[VK_END] = Keyboard::Key::End;
    s_translateKey[VK_HOME] = Keyboard::Key::Home;
    s_translateKey[VK_LEFT] = Keyboard::Key::Left;
    s_translateKey[VK_UP] = Keyboard::Key::Up;
    s_translateKey[VK_RIGHT] = Keyboard::Key::Right;
    s_translateKey[VK_DOWN] = Keyboard::Key::Down;
    s_translateKey[VK_SELECT] = Keyboard::Key::Select;
    s_translateKey[VK_PRINT] = Keyboard::Key::Print;
    s_translateKey[VK_EXECUTE] = Keyboard::Key::Execute;
    s_translateKey[VK_SNAPSHOT] = Keyboard::Key::PrintScreen;
    s_translateKey[VK_INSERT] = Keyboard::Key::Insert;
    s_translateKey[VK_DELETE] = Keyboard::Key::Delete;
    s_translateKey[VK_HELP] = Keyboard::Key::Help;

    s_translateKey[uint8_t('0')] = Keyboard::Key::D0;
    s_translateKey[uint8_t('1')] = Keyboard::Key::D1;
    s_translateKey[uint8_t('2')] = Keyboard::Key::D2;
    s_translateKey[uint8_t('3')] = Keyboard::Key::D3;
    s_translateKey[uint8_t('4')] = Keyboard::Key::D4;
    s_translateKey[uint8_t('5')] = Keyboard::Key::D5;
    s_translateKey[uint8_t('6')] = Keyboard::Key::D6;
    s_translateKey[uint8_t('7')] = Keyboard::Key::D7;
    s_translateKey[uint8_t('8')] = Keyboard::Key::D8;
    s_translateKey[uint8_t('9')] = Keyboard::Key::D9;

    s_translateKey[uint8_t('A')] = Keyboard::Key::A;
    s_translateKey[uint8_t('B')] = Keyboard::Key::B;
    s_translateKey[uint8_t('C')] = Keyboard::Key::C;
    s_translateKey[uint8_t('D')] = Keyboard::Key::D;
    s_translateKey[uint8_t('E')] = Keyboard::Key::E;
    s_translateKey[uint8_t('F')] = Keyboard::Key::F;
    s_translateKey[uint8_t('G')] = Keyboard::Key::G;
    s_translateKey[uint8_t('H')] = Keyboard::Key::H;
    s_translateKey[uint8_t('I')] = Keyboard::Key::I;
    s_translateKey[uint8_t('J')] = Keyboard::Key::J;
    s_translateKey[uint8_t('K')] = Keyboard::Key::K;
    s_translateKey[uint8_t('L')] = Keyboard::Key::L;
    s_translateKey[uint8_t('M')] = Keyboard::Key::M;
    s_translateKey[uint8_t('N')] = Keyboard::Key::N;
    s_translateKey[uint8_t('O')] = Keyboard::Key::O;
    s_translateKey[uint8_t('P')] = Keyboard::Key::P;
    s_translateKey[uint8_t('Q')] = Keyboard::Key::Q;
    s_translateKey[uint8_t('R')] = Keyboard::Key::R;
    s_translateKey[uint8_t('S')] = Keyboard::Key::S;
    s_translateKey[uint8_t('T')] = Keyboard::Key::T;
    s_translateKey[uint8_t('U')] = Keyboard::Key::U;
    s_translateKey[uint8_t('V')] = Keyboard::Key::V;
    s_translateKey[uint8_t('W')] = Keyboard::Key::W;
    s_translateKey[uint8_t('X')] = Keyboard::Key::X;
    s_translateKey[uint8_t('Y')] = Keyboard::Key::Y;
    s_translateKey[uint8_t('Z')] = Keyboard::Key::Z;

    s_translateKey[VK_LWIN] = Keyboard::Key::LeftSystem;
    s_translateKey[VK_RWIN] = Keyboard::Key::RightSystem;
    s_translateKey[VK_APPS] = Keyboard::Key::Applications;
    s_translateKey[VK_SLEEP] = Keyboard::Key::Sleep;
    s_translateKey[VK_NUMPAD0] = Keyboard::Key::NumPad0;
    s_translateKey[VK_NUMPAD1] = Keyboard::Key::NumPad1;
    s_translateKey[VK_NUMPAD2] = Keyboard::Key::NumPad2;
    s_translateKey[VK_NUMPAD3] = Keyboard::Key::NumPad3;
    s_translateKey[VK_NUMPAD4] = Keyboard::Key::NumPad4;
    s_translateKey[VK_NUMPAD5] = Keyboard::Key::NumPad5;
    s_translateKey[VK_NUMPAD6] = Keyboard::Key::NumPad6;
    s_translateKey[VK_NUMPAD7] = Keyboard::Key::NumPad7;
    s_translateKey[VK_NUMPAD8] = Keyboard::Key::NumPad8;
    s_translateKey[VK_NUMPAD9] = Keyboard::Key::NumPad9;
    s_translateKey[VK_MULTIPLY] = Keyboard::Key::Multiply;
    s_translateKey[VK_ADD] = Keyboard::Key::Add;
    s_translateKey[VK_SEPARATOR] = Keyboard::Key::NumpadEnter;
    s_translateKey[VK_SUBTRACT] = Keyboard::Key::Subtract;
    s_translateKey[VK_DECIMAL] = Keyboard::Key::Decimal;
    s_translateKey[VK_DIVIDE] = Keyboard::Key::Divide;
    s_translateKey[VK_F1] = Keyboard::Key::F1;
    s_translateKey[VK_F2] = Keyboard::Key::F2;
    s_translateKey[VK_F3] = Keyboard::Key::F3;
    s_translateKey[VK_F4] = Keyboard::Key::F4;
    s_translateKey[VK_F5] = Keyboard::Key::F5;
    s_translateKey[VK_F6] = Keyboard::Key::F6;
    s_translateKey[VK_F7] = Keyboard::Key::F7;
    s_translateKey[VK_F8] = Keyboard::Key::F8;
    s_translateKey[VK_F9] = Keyboard::Key::F9;
    s_translateKey[VK_F10] = Keyboard::Key::F10;
    s_translateKey[VK_F11] = Keyboard::Key::F11;
    s_translateKey[VK_F12] = Keyboard::Key::F12;
    s_translateKey[VK_F13] = Keyboard::Key::F13;
    s_translateKey[VK_F14] = Keyboard::Key::F14;
    s_translateKey[VK_F15] = Keyboard::Key::F15;
    s_translateKey[VK_F16] = Keyboard::Key::F16;
    s_translateKey[VK_F17] = Keyboard::Key::F17;
    s_translateKey[VK_F18] = Keyboard::Key::F18;
    s_translateKey[VK_F19] = Keyboard::Key::F19;
    s_translateKey[VK_F20] = Keyboard::Key::F20;
    s_translateKey[VK_F21] = Keyboard::Key::F21;
    s_translateKey[VK_F22] = Keyboard::Key::F22;
    s_translateKey[VK_F23] = Keyboard::Key::F23;
    s_translateKey[VK_F24] = Keyboard::Key::F24;
    s_translateKey[VK_NUMLOCK] = Keyboard::Key::NumLock;
    s_translateKey[VK_SCROLL] = Keyboard::Key::ScrollLock;
    s_translateKey[VK_LSHIFT] = Keyboard::Key::LeftShift;
    s_translateKey[VK_RSHIFT] = Keyboard::Key::RightShift;
    s_translateKey[VK_LCONTROL] = Keyboard::Key::LeftControl;
    s_translateKey[VK_RCONTROL] = Keyboard::Key::RightControl;
    s_translateKey[VK_LMENU] = Keyboard::Key::LeftAlt;
    s_translateKey[VK_RMENU] = Keyboard::Key::RightAlt;
    s_translateKey[VK_BROWSER_BACK] = Keyboard::Key::BrowserBack;
    s_translateKey[VK_BROWSER_FORWARD] = Keyboard::Key::BrowserForward;
    s_translateKey[VK_BROWSER_REFRESH] = Keyboard::Key::BrowserRefresh;
    s_translateKey[VK_BROWSER_STOP] = Keyboard::Key::BrowserStop;
    s_translateKey[VK_BROWSER_SEARCH] = Keyboard::Key::BrowserSearch;
    s_translateKey[VK_BROWSER_FAVORITES] = Keyboard::Key::BrowserFavorites;
    s_translateKey[VK_BROWSER_HOME] = Keyboard::Key::BrowserHome;
    s_translateKey[VK_VOLUME_MUTE] = Keyboard::Key::VolumeMute;
    s_translateKey[VK_VOLUME_DOWN] = Keyboard::Key::VolumeDown;
    s_translateKey[VK_VOLUME_UP] = Keyboard::Key::VolumeUp;
    s_translateKey[VK_MEDIA_NEXT_TRACK] = Keyboard::Key::MediaNextTrack;
    s_translateKey[VK_MEDIA_PREV_TRACK] = Keyboard::Key::MediaPreviousTrack;
    s_translateKey[VK_MEDIA_STOP] = Keyboard::Key::MediaStop;
    s_translateKey[VK_MEDIA_PLAY_PAUSE] = Keyboard::Key::MediaPlayPause;
    s_translateKey[VK_LAUNCH_MAIL] = Keyboard::Key::LaunchMail;
    s_translateKey[VK_LAUNCH_MEDIA_SELECT] = Keyboard::Key::SelectMedia;
    s_translateKey[VK_LAUNCH_APP1] = Keyboard::Key::LaunchApplication1;
    s_translateKey[VK_LAUNCH_APP2] = Keyboard::Key::LaunchApplication2;
    s_translateKey[VK_OEM_1] = Keyboard::Key::OemSemicolon;
    s_translateKey[VK_OEM_PLUS] = Keyboard::Key::OemPlus;
    s_translateKey[VK_OEM_COMMA] = Keyboard::Key::OemComma;
    s_translateKey[VK_OEM_MINUS] = Keyboard::Key::OemMinus;
    s_translateKey[VK_OEM_PERIOD] = Keyboard::Key::OemPeriod;
    s_translateKey[VK_OEM_2] = Keyboard::Key::OemQuestion;
    s_translateKey[VK_OEM_3] = Keyboard::Key::OemTilde;
    s_translateKey[VK_OEM_4] = Keyboard::Key::OemOpenBrackets;
    s_translateKey[VK_OEM_5] = Keyboard::Key::OemPipe;
    s_translateKey[VK_OEM_6] = Keyboard::Key::OemCloseBrackets;
    s_translateKey[VK_OEM_7] = Keyboard::Key::OemQuotes;
    s_translateKey[VK_OEM_8] = Keyboard::Key::Oem8;
    s_translateKey[VK_OEM_102] = Keyboard::Key::OemBackslash;
    s_translateKey[VK_PROCESSKEY] = Keyboard::Key::ProcessKey;
    s_translateKey[VK_ATTN] = Keyboard::Key::Attn;
    s_translateKey[VK_CRSEL] = Keyboard::Key::Crsel;
    s_translateKey[VK_EXSEL] = Keyboard::Key::Exsel;
    s_translateKey[VK_EREOF] = Keyboard::Key::EraseEof;
    s_translateKey[VK_PLAY] = Keyboard::Key::Play;
    s_translateKey[VK_ZOOM] = Keyboard::Key::Zoom;
    s_translateKey[VK_PA1] = Keyboard::Key::Pa1;
    s_translateKey[VK_OEM_CLEAR] = Keyboard::Key::OemClear;
    s_translateKey[VK_PAUSE] = Keyboard::Key::Pause;
    s_translateKey[VK_CONVERT] = Keyboard::Key::ImeConvert;
    s_translateKey[VK_NONCONVERT] = Keyboard::Key::ImeNoConvert;
    s_translateKey[VK_KANA] = Keyboard::Key::Kana;
    s_translateKey[VK_KANJI] = Keyboard::Key::Kanji;
}

void win32ProcessInput(uint8_t* state, LPARAM lparam)
{
    // Adapted from https://blog.molecular-matters.com/2011/09/05/properly-handling-keyboard-input/

    char inputBuffer[sizeof(RAWINPUT)];
    UINT inputBufferSize = sizeof(inputBuffer);

    GetRawInputData((HRAWINPUT)lparam, RID_INPUT, inputBuffer, &inputBufferSize, sizeof(RAWINPUTHEADER));

    RAWINPUT* input = (RAWINPUT*)inputBuffer;

    if (input->header.dwType != RIM_TYPEKEYBOARD) return;

    const RAWKEYBOARD* rawKeyboard = &input->data.keyboard;

    UINT vkey = rawKeyboard->VKey;
    UINT flags = rawKeyboard->Flags;

    // Fake key
    if (255 == vkey)
    {
        return;
    }
    else if (vkey == VK_SHIFT) // Map VK_SHIFT to VK_LSHIFT or VK_RSHIFT
    {
        // MapVirtualKey maps left and right hand keys
        // but can't map it with Control and Alt keys
        vkey = MapVirtualKeyA(rawKeyboard->MakeCode, MAPVK_VSC_TO_VK_EX);
    }

    // Reference: https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
    bool isE0 = (flags & RI_KEY_E0) != 0;

    switch (vkey)
    {
    case VK_CONTROL: vkey = (isE0) ? VK_RCONTROL : VK_LCONTROL; break;
    case VK_MENU: vkey = (isE0) ? VK_RMENU : VK_LMENU; break;
        // the standard INSERT, DELETE, HOME, END, PRIOR and NEXT 
        // keys will always have their e0 bit set, but the
        // corresponding keys on the NUMPAD will not.
    case VK_INSERT: vkey = (!isE0) ? VK_NUMPAD0 : VK_INSERT; break;
    case VK_DELETE: vkey = (!isE0) ? VK_DECIMAL : VK_DELETE; break;
    case VK_HOME: vkey = (!isE0) ? VK_NUMPAD7 : VK_HOME; break;
    case VK_END: vkey = (!isE0) ? VK_NUMPAD1 : VK_END; break;
    case VK_PRIOR: vkey = (!isE0) ? VK_NUMPAD9 : VK_PRIOR; break;
    case VK_NEXT: vkey = (!isE0) ? VK_NUMPAD3 : VK_NEXT; break;
        // the standard arrow keys will always have their e0 bit set, but the
        // corresponding keys on the NUMPAD will not.
    case VK_LEFT: vkey = (!isE0) ? VK_NUMPAD4 : VK_LEFT; break;
    case VK_RIGHT: vkey = (!isE0) ? VK_NUMPAD6 : VK_RIGHT; break;
    case VK_UP: vkey = (!isE0) ? VK_NUMPAD8 : VK_UP; break;
    case VK_DOWN: vkey = (!isE0) ? VK_NUMPAD2 : VK_DOWN; break;
    case VK_CLEAR: vkey = (!isE0) ? VK_NUMPAD5 : VK_CLEAR; break;
    }

    bool pressed = !((flags & RI_KEY_BREAK) != 0);

    state[s_translateKey[vkey]] = pressed;
}

struct Input
{
    uint8_t keyboardNewState[MAX_INPUT_KEYS];
    uint8_t keyboardOldState[MAX_INPUT_KEYS];
};

static Input s_input;
namespace hotswap
{
    bool inputIsKeyPressed(Keyboard::Key key)
    {
        return (~s_input.keyboardOldState[key] & s_input.keyboardNewState[key]) != 0;
    }

    bool inputIsKeyReleased(Keyboard::Key key)
    {
        return (s_input.keyboardOldState[key] & ~s_input.keyboardNewState[key]) != 0;
    }

    bool inputIsKeyDown(Keyboard::Key key)
    {
        return s_input.keyboardNewState[key] != 0;
    }
}

struct State
{
    void* permanentStorage;
    uint64_t permanentStorageSize;

    void* transientStorage;
    uint64_t transientStorageSize;
};

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE /* hPrevInstance */,
    LPSTR /* lpCmdLine */, 
    int /* nCmdShow */ )
{
    WNDCLASSEX wndClass = {};
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = win32WindowProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = "win32_window";

    if (0 == RegisterClassExA(&wndClass))
    {
        return 1;
    }

    win32InitTranslateKeys();

    // Only keyboard for now
    RAWINPUTDEVICE inputDevices[1];
    inputDevices[0].usUsagePage = 0x01;       // To get the keyboard TLC, set UsagePage = 1 
    inputDevices[0].usUsage = 0x06;           // ... and Usage = 6
    inputDevices[0].dwFlags = RIDEV_NOLEGACY; // No WM_KEYDOWN messages
    inputDevices[0].hwndTarget = 0;           // TODO: Do we need this?

    if (FALSE == RegisterRawInputDevices(inputDevices, HOTSWAP_COUNTOF(inputDevices), sizeof(RAWINPUTDEVICE)))
    {
        return 1;
    }

    int windowWidth = 1280;
    int windowHeight = 720;

    HWND window = CreateWindowA(
        "win32_window", 
        "Hotswapping", 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        windowWidth, windowHeight,
        0, 
        0, 
        hInstance, 
        0);

    if (0 == window)
    {
        return 1;
    }

    ShowWindow(window, SW_SHOW);
    UpdateWindow(window);

    State memory = {};
    memory.permanentStorageSize = 16 * 1024 * 1024;
    memory.transientStorageSize = 512 * 1024 * 1024;

#if HOTSWAP_DEBUG
    void* baseAddress = (void*)uint64_t(2ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL);
#else
    void* baseAddress = (void*)0;
#endif

    uint64_t totalMemory = memory.permanentStorageSize + memory.transientStorageSize;

    memory.permanentStorage = VirtualAlloc(baseAddress, totalMemory, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    memory.transientStorage = ((uint8_t*)memory.permanentStorage + memory.permanentStorageSize);

    while (!s_exit)
    {
        MSG message;
        while (0 != PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_INPUT)
            {
                win32ProcessInput(s_input.keyboardNewState, message.lParam);
            }
            else
            {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            }
        }

        hotswap::gameUpdate();

        // Update game board state
        memCopy(s_input.keyboardOldState, s_input.keyboardNewState, sizeof(uint8_t) * MAX_INPUT_KEYS);
    }

    return 0;
}

#endif