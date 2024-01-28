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

#include "Direct3D.hxx"
#include "Direct3D2.hxx"
#include "Direct3D3.hxx"
#include "Direct3D7.hxx"
#include "Direct3DDevice7.hxx"
#include "Direct3DVertexBuffer7.hxx"
#include "DirectDraw.hxx"
#include "DirectDraw2.hxx"
#include "DirectDraw4.hxx"
#include "DirectDraw7.hxx"
#include "DirectDrawSurface7.hxx"
#include "DirectDrawVideoPortContainer.hxx"

struct EnumDevicesCallbackContext
{
    LPD3DENUMDEVICESCALLBACK7 lpEnumDevicesCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumDevicesCallback(LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC7 lpD3DDeviceDesc, LPVOID lpContext)
{
    EnumDevicesCallbackContext* context = (EnumDevicesCallbackContext*)lpContext;

    return context->lpEnumDevicesCallback(lpDeviceDescription, lpDeviceName, lpD3DDeviceDesc, context->lpContext);
}

struct EnumZBufferFormatsCallbackContext
{
    LPD3DENUMPIXELFORMATSCALLBACK lpEnumCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumZBufferFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext)
{
    EnumZBufferFormatsCallbackContext* context = (EnumZBufferFormatsCallbackContext*)lpContext;

    return context->lpEnumCallback(lpDDPixFmt, context->lpContext);
}

Direct3D7::Direct3D7(AgentConstructorParameters(Direct3D7))
{
    AgentConstructor();
}

Direct3D7::~Direct3D7()
{
    AgentDestructor();
}

HRESULT Direct3D7::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectDraw, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDraw, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw2, riid)) { *ppvObj = ActivateAgent(DirectDraw2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw4, riid)) { *ppvObj = ActivateAgent(DirectDraw4, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw7, riid)) { *ppvObj = ActivateAgent(DirectDraw7, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawVideoPortContainer, riid)) { *ppvObj = ActivateAgent(DirectDrawVideoPortContainer, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3D7::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3D7::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Enumerates all Direct3D device drivers installed on the system.
HRESULT Direct3D7::EnumDevices(LPD3DENUMDEVICESCALLBACK7 lpEnumDevicesCallback, LPVOID lpContext)
{
    if (lpEnumDevicesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumDevicesCallbackContext context;

    context.lpEnumDevicesCallback = lpEnumDevicesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumDevices(EnumDevicesCallback, &context);
}

// Creates a Direct3D device to be used with the DrawPrimitive methods.
HRESULT Direct3D7::CreateDevice(REFCLSID rclsid, LPDIRECTDRAWSURFACE7 lpDDS, LPDIRECT3DDEVICE7* lplpD3DDevice)
{
    AttemptAccessAgentValue(DirectDrawSurface7, lpDDS);

    const HRESULT result = this->State.Self->CreateDevice(rclsid, lpDDS, lplpD3DDevice);

    if (SUCCEEDED(result)) { *lplpD3DDevice = ActivateAgentDelegate(Direct3DDevice7, *lplpD3DDevice); }

    return result;
}

// Creates a vertex buffer object.
HRESULT Direct3D7::CreateVertexBuffer(LPD3DVERTEXBUFFERDESC lpVBDesc, LPDIRECT3DVERTEXBUFFER7* lplpD3DVertexBuffer, DWORD dwFlags)
{
    const HRESULT result = this->State.Self->CreateVertexBuffer(lpVBDesc, lplpD3DVertexBuffer, dwFlags);

    if (SUCCEEDED(result)) { *lplpD3DVertexBuffer = ActivateAgentDelegate(Direct3DVertexBuffer7, *lplpD3DVertexBuffer); }

    return result;
}

// Enumerates the supported depth-buffer formats for a specified device.
HRESULT Direct3D7::EnumZBufferFormats(REFCLSID riidDevice, LPD3DENUMPIXELFORMATSCALLBACK lpEnumCallback, LPVOID lpContext)
{
    if (lpEnumCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumZBufferFormatsCallbackContext context;

    context.lpEnumCallback = lpEnumCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumZBufferFormats(riidDevice, EnumZBufferFormatsCallback, &context);
}

// Evicts all managed textures from local or nonlocal video memory.
HRESULT Direct3D7::EvictManagedTextures()
{
    return this->State.Self->EvictManagedTextures();
}