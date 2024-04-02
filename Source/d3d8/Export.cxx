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

#include "Base.hxx"

#include "Direct3D8.hxx"

#include "Export.hxx"
#include "Module.hxx"

// NOTE: The method is called CheckFullscreen in Windows XP.
extern "C" INT WINAPI Direct3D8EnableMaximizedWindowedModeShim(BOOL Enable)
{
    if (Module.Direct3D8EnableMaximizedWindowedModeShim == NULL) { return E_NOTIMPL; }

    return Module.Direct3D8EnableMaximizedWindowedModeShim(Enable);
}

extern "C" HRESULT WINAPI ValidatePixelShader(CONST DWORD * Shader, CONST D3DCAPS8 * Caps, BOOL ReturnErrors, CHAR * *Errors)
{
    return Module.ValidatePixelShader(Shader, Caps, ReturnErrors, Errors);
}

extern "C" HRESULT WINAPI ValidateVertexShader(CONST DWORD * Shader, CONST DWORD * Declaration, CONST D3DCAPS8 * Caps, BOOL ReturnErrors, CHAR * *Errors)
{
    return Module.ValidateVertexShader(Shader, Declaration, Caps, ReturnErrors, Errors);
}

extern "C" void WINAPI DebugSetMute(VOID)
{
    Module.DebugSetMute();
}

// Creates an instance of a Direct3D8 object.
extern "C" LPDIRECT3D8 WINAPI Direct3DCreate8(UINT Version)
{
    LPDIRECT3D8 d3d = Module.Direct3DCreate8(Version);

    if (d3d != NULL) { d3d = AssembleAgent(Direct3D8, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), d3d); }

    return d3d;
}