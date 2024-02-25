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

#include "Direct3DDevice7.hxx"
#include "Direct3DVertexBuffer.hxx"
#include "Direct3DVertexBuffer7.hxx"

Direct3DVertexBuffer7::Direct3DVertexBuffer7(AgentConstructorParameters(Direct3DVertexBuffer7))
{
    AgentConstructor();
}

Direct3DVertexBuffer7::~Direct3DVertexBuffer7()
{
    AgentDestructor();
}

HRESULT Direct3DVertexBuffer7::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DVertexBuffer7, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3DVertexBuffer7, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DVertexBuffer7::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DVertexBuffer7::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Locks a vertex buffer and obtains a pointer to the vertex buffer memory.
HRESULT Direct3DVertexBuffer7::Lock(DWORD dwFlags, LPVOID* lplpData, LPDWORD lpdwSize)
{
    return this->State.Self->Lock(dwFlags, lplpData, lpdwSize);
}

// Unlocks a previously locked vertex buffer.
HRESULT Direct3DVertexBuffer7::Unlock()
{
    return this->State.Self->Unlock();
}

// Processes untransformed vertices into a transformed or optimized vertex buffer.
HRESULT Direct3DVertexBuffer7::ProcessVertices(DWORD dwVertexOp, DWORD dwDestIndex, DWORD dwCount, LPDIRECT3DVERTEXBUFFER7 lpSrcBuffer, DWORD dwSrcIndex, LPDIRECT3DDEVICE7 lpD3DDevice, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DVertexBuffer7, lpSrcBuffer);
    AttemptAccessAgentValue(Direct3DDevice7, lpD3DDevice);

    return this->State.Self->ProcessVertices(dwVertexOp, dwDestIndex, dwCount, lpSrcBuffer, dwSrcIndex, lpD3DDevice, dwFlags);
}

// Retrieves a description of the vertex buffer.
HRESULT Direct3DVertexBuffer7::GetVertexBufferDesc(LPD3DVERTEXBUFFERDESC lpVBDesc)
{
    return this->State.Self->GetVertexBufferDesc(lpVBDesc);
}

// Converts an unoptimized vertex buffer into an optimized vertex buffer.
HRESULT Direct3DVertexBuffer7::Optimize(LPDIRECT3DDEVICE7 lpD3DDevice, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DDevice7, lpD3DDevice);

    return this->State.Self->Optimize(lpD3DDevice, dwFlags);
}

// Processes untransformed strided vertices into a transformed or optimized vertex buffer.
HRESULT Direct3DVertexBuffer7::ProcessVerticesStrided(DWORD dwVertexOp, DWORD dwDestIndex, DWORD dwCount, LPD3DDRAWPRIMITIVESTRIDEDDATA lpVertexArray, DWORD dwSrcIndex, LPDIRECT3DDEVICE7 lpD3DDevice, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DDevice7, lpD3DDevice);

    return this->State.Self->ProcessVerticesStrided(dwVertexOp, dwDestIndex, dwCount, lpVertexArray, dwSrcIndex, lpD3DDevice, dwFlags);
}