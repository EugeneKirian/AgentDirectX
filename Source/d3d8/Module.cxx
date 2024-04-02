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

ModuleState Module;

BOOL InitializeModule()
{
    char directory[DIRECT3D_LIBRARY_PATH_LENGTH];
    ZeroMemory(directory, DIRECT3D_LIBRARY_PATH_LENGTH);

    if (GetSystemDirectoryA(directory, DIRECT3D_LIBRARY_PATH_LENGTH) >= DIRECT3D_LIBRARY_PATH_LENGTH) { return FALSE; }

    char path[DIRECT3D_LIBRARY_FILE_PATH_LENGTH];
    ZeroMemory(path, DIRECT3D_LIBRARY_FILE_PATH_LENGTH);

    if (PathCombineA(path, directory, DIRECT3D_LIBRARY_NAME) == NULL) { return FALSE; }

    Module.Module = LoadLibraryA(path);

    if (Module.Module == NULL) { return FALSE; }

    Module.Direct3D8EnableMaximizedWindowedModeShim = (LPENABLEMAXIMIZEDWINDOWEDMODE)GetProcAddress(Module.Module, DIRECT3D_ENABLE_MAXIMIZED_WINDOWED_MODE_NAME);

    Module.ValidatePixelShader = (LPVALIDATEPIXELSHADER)GetProcAddress(Module.Module, DIRECT3D_VALIDATE_PIXEL_SHADER_NAME);
    if (Module.ValidatePixelShader == NULL) { ReleaseModule(); return NULL; }

    Module.ValidateVertexShader = (LPVALIDATEVERTEXSHADER)GetProcAddress(Module.Module, DIRECT3D_VALIDATE_VERTEX_SHADER_NAME);
    if (Module.ValidateVertexShader == NULL) { ReleaseModule(); return NULL; }

    Module.DebugSetMute = (LPDEBUGSETMUTE)GetProcAddress(Module.Module, DIRECT3D_DEBUG_SET_MUTE_NAME);
    if (Module.DebugSetMute == NULL) { ReleaseModule(); return NULL; }

    Module.Direct3DCreate8 = (LPDIRECT3DCREATE8)GetProcAddress(Module.Module, DIRECT3D_DIRECT3DCREATE8_NAME);
    if (Module.Direct3DCreate8 == NULL) { ReleaseModule(); return NULL; }

    Module.Assembler = new Assembler();

    Module.Initialized = TRUE;

    return TRUE;
}

BOOL ReleaseModule()
{
    if (Module.Assembler != NULL) { delete Module.Assembler; }

    CONST BOOL result = Module.Module != NULL ? FreeLibrary(Module.Module) : FALSE;

    ZeroMemory(&Module, sizeof(ModuleState));

    return result;
}