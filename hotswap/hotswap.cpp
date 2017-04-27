/*
* Copyright(c) 2017 Jani Niemelä.
* License: https://github.com/siquel/win32/blob/master/LICENSE
*/

#include <stdint.h>
#include <hotswap.h>
#include <Windows.h>

namespace hotswap
{
    extern "C" __declspec(dllexport) 
    void gameUpdate(const GameInput* input)
    {
        (void)input;
        OutputDebugStringA("Hello from DLL!\n");
    }
}