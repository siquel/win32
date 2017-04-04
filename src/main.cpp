/*
* Copyright(c) 2017 Jani Niemelä.
* License: https://github.com/siquel/win32/blob/master/LICENSE
*/

#include <Windows.h>

static bool s_exit = false;

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

    int width = 1280;
    int height = 720;

    HWND window = CreateWindowA("win32_window", "Win32 Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);

    if (0 == window)
    {
        return 1;
    }

    ShowWindow(window, SW_SHOW);
    UpdateWindow(window);

    while (!s_exit)
    {
        MSG message;
        while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
    }

    return 0;
}