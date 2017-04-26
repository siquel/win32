/*
* Copyright(c) 2017 Jani Niemelä.
* License: https://github.com/siquel/win32/blob/master/LICENSE
*/

#include "hotswap.h"
#include <Windows.h>
#include <stdint.h>
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

    static HANDLE inputFile;

    void gameUpdate()
    {
        static bool playing = false, recording = false;

        if (hotswap::inputIsKeyPressed(hotswap::Keyboard::L))
        {
            if (playing && !recording)
            {
                playing = false;
                OutputDebugStringA("Playing stopped\n");
            }
            else if (recording)
            {
                recording = false;
                playing = true;

                OutputDebugStringA("Playing started\n");
            }
            else
            {
                recording = true;
                OutputDebugStringA("Recording started\n");

                inputFile = ::CreateFileA("input",
                    GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ,
                    NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            }
        }

        GameInput input;

        if (playing)
        {
            DWORD readBytes;
            ::ReadFile(inputFile, &input, sizeof(GameInput), &readBytes, NULL);

            if (0 == readBytes)
            {
                OutputDebugStringA("Looping recording\n");
                ::SetFilePointer(inputFile, 0, 0, FILE_BEGIN);
                ::ReadFile(inputFile, &input, sizeof(GameInput), &readBytes, NULL);
            }
        }
        else
        {
            input.w = inputIsKeyDown(Keyboard::W);
            input.a = inputIsKeyDown(Keyboard::A);
            input.s = inputIsKeyDown(Keyboard::S);
            input.d = inputIsKeyDown(Keyboard::D);

            if (recording)
            {
                ::WriteFile(inputFile,
                    &input,
                    sizeof(GameInput),
                    NULL,
                    NULL);
            }
        }


        if (playing)
        {
            char buffer[128];
            wsprintfA(buffer, "W: %s, A: %s, S: %s, D: %s\n",
                input.w ? "down" : "up",
                input.a ? "down" : "up",
                input.s ? "down" : "up",
                input.d ? "down" : "up"
                );

            OutputDebugStringA(buffer);
        }

        ::Sleep(100);
    }
}