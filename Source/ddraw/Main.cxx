/*
Copyright (c) 2024 Eugene Kirian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Module.hxx"

#define DIRECT_DRAW_TITLE "DirectDraw"
#define DIRECT_DRAW_LOAD_ERROR_MESSAGE "Unable to load ddraw.dll library."
#define DIRECT_DRAW_ALREADY_LOADED_ERROR_MESSAGE "The ddraw.dll library already loaded."

static VOID Exit(CONST LPCSTR title, CONST LPCSTR message)
{
    MessageBoxA(NULL, message, title, MB_OK | MB_ICONEXCLAMATION);

    ExitProcess(0);
}

VOID Initialize()
{
    if (Module.Initialized) { Exit(DIRECT_DRAW_TITLE, DIRECT_DRAW_ALREADY_LOADED_ERROR_MESSAGE); }

    if (!InitializeModule()) { Exit(DIRECT_DRAW_TITLE, DIRECT_DRAW_LOAD_ERROR_MESSAGE); }
}

VOID Release()
{
    ReleaseModule();
}

BOOL APIENTRY DllMain(HMODULE, DWORD ul_reason_for_call, LPVOID)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: { Initialize(); break; }
    case DLL_THREAD_ATTACH: { break; }
    case DLL_THREAD_DETACH: { break; }
    case DLL_PROCESS_DETACH: { Release(); break; }
    }

    return TRUE;
}