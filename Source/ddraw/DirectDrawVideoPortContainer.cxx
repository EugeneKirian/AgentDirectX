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
#include "DirectDraw.hxx"
#include "DirectDraw2.hxx"
#include "DirectDraw4.hxx"
#include "DirectDraw7.hxx"
#include "DirectDrawVideoPort.hxx"
#include "DirectDrawVideoPortContainer.hxx"

struct EnumVideoPortsCallbackContext
{
    LPDDENUMVIDEOCALLBACK lpEnumVideoCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumVideoPortsCallback(LPDDVIDEOPORTCAPS lpDDVideoPortCaps, LPVOID lpContext)
{
    EnumVideoPortsCallbackContext* context = (EnumVideoPortsCallbackContext*)lpContext;

    return context->lpEnumVideoCallback(lpDDVideoPortCaps, context->lpContext);
}

DirectDrawVideoPortContainer::DirectDrawVideoPortContainer(AgentConstructorParameters(DirectDrawVideoPortContainer))
{
    AgentConstructor();
}

DirectDrawVideoPortContainer::~DirectDrawVideoPortContainer()
{
    AgentDestructor();
}

HRESULT DirectDrawVideoPortContainer::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

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

ULONG DirectDrawVideoPortContainer::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectDrawVideoPortContainer::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Creates a DirectDrawVideoPort object.
HRESULT DirectDrawVideoPortContainer::CreateVideoPort(DWORD dwFlags, LPDDVIDEOPORTDESC lpDDVideoPortDesc, LPDIRECTDRAWVIDEOPORT FAR* lplpDDVideoPort, IUnknown FAR* pUnkOuter)
{
    const HRESULT result = this->State.Self->CreateVideoPort(dwFlags, lpDDVideoPortDesc, lplpDDVideoPort, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDVideoPort = ActivateAgentDelegate(DirectDrawVideoPort, *lplpDDVideoPort); }

    return result;
}

// Enumerates all the video ports that the hardware exposes that are compatible with a provided video-port description.
HRESULT DirectDrawVideoPortContainer::EnumVideoPorts(DWORD dwFlags, LPDDVIDEOPORTCAPS lpDDVideoPortCaps, LPVOID lpContext, LPDDENUMVIDEOCALLBACK lpEnumVideoCallback)
{
    if (lpEnumVideoCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumVideoPortsCallbackContext context;

    context.lpEnumVideoCallback = lpEnumVideoCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumVideoPorts(dwFlags, lpDDVideoPortCaps, &context, EnumVideoPortsCallback);
}

// Retrieves the connection information supported by all video ports.
HRESULT DirectDrawVideoPortContainer::GetVideoPortConnectInfo(DWORD dwPortId, LPDWORD lpNumEntries, LPDDVIDEOPORTCONNECT lpConnectInfo)
{
    return this->State.Self->GetVideoPortConnectInfo(dwPortId, lpNumEntries, lpConnectInfo);
}

HRESULT DirectDrawVideoPortContainer::QueryVideoPortStatus(DWORD dwPortId, LPDDVIDEOPORTSTATUS lpVPStatus)
{
    return this->State.Self->QueryVideoPortStatus(dwPortId, lpVPStatus);
}