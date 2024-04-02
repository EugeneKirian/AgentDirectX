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

#include "Direct3DSurface8.hxx"
#include "Direct3DSwapChain8.hxx"

Direct3DSwapChain8::Direct3DSwapChain8(AgentConstructorParameters(Direct3DSwapChain8))
{
    AgentConstructor();
}

Direct3DSwapChain8::~Direct3DSwapChain8()
{
    AgentDestructor();
}

HRESULT Direct3DSwapChain8::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DSwapChain8, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3DSwapChain8, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DSwapChain8::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DSwapChain8::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Presents the contents of the next in the sequence of back buffers owned by the swap chain. 
HRESULT Direct3DSwapChain8::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
    return this->State.Self->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

// Retrieves a back buffer from the swap chain of the device.
HRESULT Direct3DSwapChain8::GetBackBuffer(UINT BackBuffer, D3DBACKBUFFER_TYPE Type, LPDIRECT3DSURFACE8* ppBackBuffer)
{
    CONST HRESULT result = this->State.Self->GetBackBuffer(BackBuffer, Type, ppBackBuffer);

    if (SUCCEEDED(result)) { *ppBackBuffer = ActivateAgent(Direct3DSurface8, *ppBackBuffer); }

    return result;
}