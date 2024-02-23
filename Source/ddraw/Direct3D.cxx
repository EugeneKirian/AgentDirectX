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
#include "Direct3DLight.hxx"
#include "Direct3DMaterial.hxx"
#include "Direct3DViewport.hxx"
#include "DirectDraw.hxx"
#include "DirectDraw2.hxx"
#include "DirectDraw4.hxx"
#include "DirectDraw7.hxx"
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

Direct3D::Direct3D(AgentConstructorParameters(Direct3D))
{
    AgentConstructor();
}

Direct3D::~Direct3D()
{
    AgentDestructor();
}

HRESULT Direct3D::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
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

ULONG Direct3D::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3D::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// This method is not currently implemented.
HRESULT Direct3D::Initialize(REFCLSID rclsid)
{
    return this->State.Self->Initialize(rclsid);
}

// Enumerates all Direct3D device drivers installed on the system.
HRESULT Direct3D::EnumDevices(LPD3DENUMDEVICESCALLBACK lpEnumDevicesCallback, LPVOID lpContext)
{
    if (lpEnumDevicesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumDevicesCallbackContext context;

    context.lpEnumDevicesCallback = lpEnumDevicesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumDevices(EnumDevicesCallback, &context);
}

// Allocates a Direct3DLight object.
HRESULT Direct3D::CreateLight(LPDIRECT3DLIGHT* lplpDirect3DLight, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateLight(lplpDirect3DLight, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDirect3DLight = ActivateAgentDelegate(Direct3DLight, *lplpDirect3DLight); }

    return result;
}

// Allocates a Direct3DMaterial object.
HRESULT Direct3D::CreateMaterial(LPDIRECT3DMATERIAL* lplpDirect3DMaterial, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateMaterial(lplpDirect3DMaterial, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDirect3DMaterial = ActivateAgentDelegate(Direct3DMaterial, *lplpDirect3DMaterial); }

    return result;
}

// Creates a Direct3DViewport object.
HRESULT Direct3D::CreateViewport(LPDIRECT3DVIEWPORT* lplpD3DViewport, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateViewport(lplpD3DViewport, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpD3DViewport = ActivateAgentDelegate(Direct3DViewport, *lplpD3DViewport); }

    return result;
}

// Finds a device with specified characteristics and retrieves a description of it.
HRESULT Direct3D::FindDevice(LPD3DFINDDEVICESEARCH lpD3DFDS, LPD3DFINDDEVICERESULT lpD3DFDR)
{
    return this->State.Self->FindDevice(lpD3DFDS, lpD3DFDR);
}