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
#include "Direct3DDevice3.hxx"
#include "Direct3DLight.hxx"
#include "Direct3DMaterial3.hxx"
#include "Direct3DVertexBuffer.hxx"
#include "Direct3DViewport3.hxx"
#include "DirectDraw.hxx"
#include "DirectDraw2.hxx"
#include "DirectDraw4.hxx"
#include "DirectDraw7.hxx"
#include "DirectDrawSurface4.hxx"
#include "DirectDrawVideoPortContainer.hxx"

struct EnumDevicesCallbackContext
{
    LPD3DENUMDEVICESCALLBACK lpEnumDevicesCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumDevicesCallback(GUID FAR* lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc, LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpContext)
{
    EnumDevicesCallbackContext* context = (EnumDevicesCallbackContext*)lpContext;

    return context->lpEnumDevicesCallback(lpGuid, lpDeviceDescription, lpDeviceName, lpD3DHWDeviceDesc, lpD3DHELDeviceDesc, context->lpContext);
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

Direct3D3::Direct3D3(AgentConstructorParameters(Direct3D3))
{
    AgentConstructor();
}

Direct3D3::~Direct3D3()
{
    AgentDestructor();
}

HRESULT Direct3D3::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3D, riid)) { *ppvObj = ActivateAgent(Direct3D, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D2, riid)) { *ppvObj = ActivateAgent(Direct3D2, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D3, riid)) { *ppvObj = ActivateAgent(Direct3D3, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D7, riid)) { *ppvObj = ActivateAgent(Direct3D7, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDraw, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw2, riid)) { *ppvObj = ActivateAgent(DirectDraw2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw4, riid)) { *ppvObj = ActivateAgent(DirectDraw4, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw7, riid)) { *ppvObj = ActivateAgent(DirectDraw7, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawVideoPortContainer, riid)) { *ppvObj = ActivateAgent(DirectDrawVideoPortContainer, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3D3::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3D3::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Enumerates all Direct3D device drivers installed on the system.
HRESULT Direct3D3::EnumDevices(LPD3DENUMDEVICESCALLBACK lpEnumDevicesCallback, LPVOID lpContext)
{
    if (lpEnumDevicesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumDevicesCallbackContext context;

    context.lpEnumDevicesCallback = lpEnumDevicesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumDevices(EnumDevicesCallback, &context);
}

// Allocates a Direct3DLight object.
// This object can then be associated with a viewport by using the IDirect3DViewport3::AddLight method.
HRESULT Direct3D3::CreateLight(LPDIRECT3DLIGHT* lplpDirect3DLight, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateLight(lplpDirect3DLight, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDirect3DLight = ActivateAgentDelegate(Direct3DLight, *lplpDirect3DLight); }

    return result;
}

// Allocates a Direct3DMaterial3 object.
HRESULT Direct3D3::CreateMaterial(LPDIRECT3DMATERIAL3* lplpDirect3DMaterial, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateMaterial(lplpDirect3DMaterial, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDirect3DMaterial = ActivateAgentDelegate(Direct3DMaterial3, *lplpDirect3DMaterial); }

    return result;
}

// Creates a Direct3DViewport object.
// The viewport is associated with a Direct3DDevice object by using the IDirect3DDevice3::AddViewport method.
HRESULT Direct3D3::CreateViewport(LPDIRECT3DVIEWPORT3* lplpD3DViewport, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateViewport(lplpD3DViewport, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpD3DViewport = ActivateAgentDelegate(Direct3DViewport3, *lplpD3DViewport); }

    return result;
}

// Finds a device with specified characteristics and retrieves a description of it.
HRESULT Direct3D3::FindDevice(LPD3DFINDDEVICESEARCH lpD3DFDS, LPD3DFINDDEVICERESULT lpD3DFDR)
{
    return this->State.Self->FindDevice(lpD3DFDS, lpD3DFDR);
}

// Creates a Direct3D device to be used with the DrawPrimitive methods.
HRESULT Direct3D3::CreateDevice(REFCLSID rclsid, LPDIRECTDRAWSURFACE4 lpDDS, LPDIRECT3DDEVICE3* lplpD3DDevice, IUnknown* pUnkOuter)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDS);

    CONST HRESULT result = this->State.Self->CreateDevice(rclsid, lpDDS, lplpD3DDevice, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpD3DDevice = ActivateAgentDelegate(Direct3DDevice3, *lplpD3DDevice); }

    return result;
}

// Creates a vertex buffer object.
HRESULT Direct3D3::CreateVertexBuffer(LPD3DVERTEXBUFFERDESC lpVBDesc, LPDIRECT3DVERTEXBUFFER* lpD3DVertexBuffer, DWORD dwFlags, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateVertexBuffer(lpVBDesc, lpD3DVertexBuffer, dwFlags, pUnkOuter);

    if (SUCCEEDED(result)) { *lpD3DVertexBuffer = ActivateAgentDelegate(Direct3DVertexBuffer, *lpD3DVertexBuffer); }

    return result;
}

// Enumerates the supported depth-buffer formats for a specified device.
HRESULT Direct3D3::EnumZBufferFormats(REFCLSID rclsid, LPD3DENUMPIXELFORMATSCALLBACK lpEnumCallback, LPVOID lpContext)
{
    if (lpEnumCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumZBufferFormatsCallbackContext context;

    context.lpEnumCallback = lpEnumCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumZBufferFormats(rclsid, EnumZBufferFormatsCallback, &context);
}

// Evicts all managed textures from local or nonlocal video memory.
HRESULT Direct3D3::EvictManagedTextures()
{
    return this->State.Self->EvictManagedTextures();
}