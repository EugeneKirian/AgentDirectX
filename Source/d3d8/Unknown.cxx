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
#include "Direct3DBaseTexture8.hxx"
#include "Direct3DCubeTexture8.hxx"
#include "Direct3DDevice8.hxx"
#include "Direct3DIndexBuffer8.hxx"
#include "Direct3DResource8.hxx"
#include "Direct3DSurface8.hxx"
#include "Direct3DSwapChain8.hxx"
#include "Direct3DTexture8.hxx"
#include "Direct3DVertexBuffer8.hxx"
#include "Direct3DVolume8.hxx"
#include "Direct3DVolumeTexture8.hxx"
#include "Unknown.hxx"

Unknown::Unknown(AgentConstructorParameters(Unknown))
{
    AgentConstructor();
}

Unknown::~Unknown()
{
    AgentDestructor();
}

HRESULT Unknown::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D8, riid)) { *ppvObj = ActivateAgent(Direct3D8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DBaseTexture8, riid)) { *ppvObj = ActivateAgent(Direct3DBaseTexture8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DCubeTexture8, riid)) { *ppvObj = ActivateAgent(Direct3DCubeTexture8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DDevice8, riid)) { *ppvObj = ActivateAgent(Direct3DDevice8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DIndexBuffer8, riid)) { *ppvObj = ActivateAgent(Direct3DIndexBuffer8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DResource8, riid)) { *ppvObj = ActivateAgent(Direct3DResource8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DSurface8, riid)) { *ppvObj = ActivateAgent(Direct3DSurface8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DSwapChain8, riid)) { *ppvObj = ActivateAgent(Direct3DSwapChain8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DTexture8, riid)) { *ppvObj = ActivateAgent(Direct3DTexture8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DVertexBuffer8, riid)) { *ppvObj = ActivateAgent(Direct3DVertexBuffer8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DVolume8, riid)) { *ppvObj = ActivateAgent(Direct3DVolume8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DVolumeTexture8, riid)) { *ppvObj = ActivateAgent(Direct3DVolumeTexture8, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Unknown::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Unknown::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}