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

#include "Direct3D8.hxx"
#include "Direct3DDevice8.hxx"

Direct3D8::Direct3D8(AgentConstructorParameters(Direct3D8))
{
    AgentConstructor();
}

Direct3D8::~Direct3D8()
{
    AgentDestructor();
}

HRESULT Direct3D8::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3D8, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3D8, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3D8::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3D8::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Registers a pluggable software device with Microsoft® Direct3D®.
// Because the pluggable software device feature is no longer supported in Microsoft DirectX® 8.x, do not use this method.
HRESULT Direct3D8::RegisterSoftwareDevice(LPVOID pInitializeFunction)
{
    return this->State.Self->RegisterSoftwareDevice(pInitializeFunction);
}

// Returns the number of adapters on the system.
UINT Direct3D8::GetAdapterCount()
{
    return this->State.Self->GetAdapterCount();
}

// Describes the physical display adapters present in the system when the IDirect3D8 interface was instantiated.
HRESULT Direct3D8::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier)
{
    return this->State.Self->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

// Returns the number of display modes available on this adapter.
UINT Direct3D8::GetAdapterModeCount(UINT Adapter)
{
    return this->State.Self->GetAdapterModeCount(Adapter);
}

// Enumerates the display modes of an adapter.
HRESULT Direct3D8::EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode)
{
    return this->State.Self->EnumAdapterModes(Adapter, Mode, pMode);
}

// Retrieves the current display mode of the adapter.
HRESULT Direct3D8::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
    return this->State.Self->GetAdapterDisplayMode(Adapter, pMode);
}

// Verifies whether or not a certain device type can be used on this adapter and expect hardware acceleration using the given formats.
HRESULT Direct3D8::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed)
{
    return this->State.Self->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
}

// Determines whether a surface format is available as a specified resource type and can be used as a texture,
// depth-stencil buffer, or render target, or any combination of the three, on a device representing this adapter.
HRESULT Direct3D8::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
    return this->State.Self->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

// Determines if a multisampling technique is available on this device.
HRESULT Direct3D8::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType)
{
    return this->State.Self->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType);
}

// Determines whether or not a depth-stencil format is compatible with a render target format in a particular display mode.
HRESULT Direct3D8::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
    return this->State.Self->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

// Retrieves device-specific information about a device. 
HRESULT Direct3D8::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps)
{
    return this->State.Self->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

// Returns the handle of the monitor associated with the Microsoft® Direct3D® object.
HMONITOR Direct3D8::GetAdapterMonitor(UINT Adapter)
{
    return this->State.Self->GetAdapterMonitor(Adapter);
}

// Creates a device to represent the display adapter.
HRESULT Direct3D8::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface)
{
    CONST HRESULT result = this->State.Self->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

    if (SUCCEEDED(result)) { *ppReturnedDeviceInterface = ActivateAgentDelegate(Direct3DDevice8, *ppReturnedDeviceInterface); }

    return result;
}