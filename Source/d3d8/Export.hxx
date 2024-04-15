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

#pragma once

#include "Base.hxx"

#define DIRECT3D_DEBUG_SET_MUTE_NAME "DebugSetMute"
#define DIRECT3D_DIRECT3DCREATE8_NAME "Direct3DCreate8"
//#define DIRECT3D_CHECK_FULL_SCREEN_NAME "CheckFullscreen" /* WIN XP */
#define DIRECT3D_CHECK_FULL_SCREEN_NAME "Direct3D8EnableMaximizedWindowedModeShim" /* WIN 10*/
#define DIRECT3D_VALIDATE_PIXEL_SHADER_NAME "ValidatePixelShader"
#define DIRECT3D_VALIDATE_VERTEX_SHADER_NAME "ValidateVertexShader"

typedef HRESULT(WINAPI* LPENABLEMAXIMIZEDWINDOWEDMODE)(BOOL Enable);
typedef HRESULT(WINAPI* LPVALIDATEPIXELSHADER)(CONST DWORD* Shader, CONST D3DCAPS8* Caps, BOOL ReturnErrors, CHAR** Errors);
typedef HRESULT(WINAPI* LPVALIDATEVERTEXSHADER)(CONST DWORD* Shader, CONST DWORD* Declaration, CONST D3DCAPS8* Caps, BOOL ReturnErrors, CHAR** Errors);
typedef VOID(WINAPI* LPDEBUGSETMUTE)(VOID);
typedef LPDIRECT3D8(WINAPI* LPDIRECT3DCREATE8)(UINT Version);