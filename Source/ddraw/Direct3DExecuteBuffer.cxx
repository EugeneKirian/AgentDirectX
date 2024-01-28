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

#include "Direct3DDevice.hxx"
#include "Direct3DExecuteBuffer.hxx"

struct ValidateCallbackContext
{
    LPD3DVALIDATECALLBACK lpFunc;
    LPVOID lpContext;
};

static HRESULT CALLBACK ValidateCallback(LPVOID lpContext, DWORD dwOffset)
{
    ValidateCallbackContext* context = (ValidateCallbackContext*)lpContext;

    return context->lpFunc(context->lpContext, dwOffset);
}

Direct3DExecuteBuffer::Direct3DExecuteBuffer(AgentConstructorParameters(Direct3DExecuteBuffer))
{
    AgentConstructor();
}

Direct3DExecuteBuffer::~Direct3DExecuteBuffer()
{
    AgentDestructor();
}

HRESULT Direct3DExecuteBuffer::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DExecuteBuffer, riid)) { *ppvObj = ActivateAgent(Direct3DExecuteBuffer, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DExecuteBuffer::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DExecuteBuffer::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

HRESULT Direct3DExecuteBuffer::Initialize(LPDIRECT3DDEVICE lpDirect3DDevice, LPD3DEXECUTEBUFFERDESC lpDesc)
{
    AttemptAccessAgentValue(Direct3DDevice, lpDirect3DDevice);

    return this->State.Self->Initialize(lpDirect3DDevice, lpDesc);
}

// Obtains a direct pointer to the commands in the execute buffer.
HRESULT Direct3DExecuteBuffer::Lock(LPD3DEXECUTEBUFFERDESC lpDesc)
{
    return this->State.Self->Lock(lpDesc);
}

// Releases the direct pointer to the commands in the execute buffer.
HRESULT Direct3DExecuteBuffer::Unlock()
{
    return this->State.Self->Unlock();
}

// Sets the execute data state of the Direct3DExecuteBuffer object.
// The execute data is used to describe the contents of the Direct3DExecuteBuffer object.
HRESULT Direct3DExecuteBuffer::SetExecuteData(LPD3DEXECUTEDATA lpData)
{
    return this->State.Self->SetExecuteData(lpData);
}

// Retrieves the execute data state of the Direct3DExecuteBuffer object.
// The execute data is used to describe the contents of the Direct3DExecuteBuffer object.
HRESULT Direct3DExecuteBuffer::GetExecuteData(LPD3DEXECUTEDATA lpData)
{
    return this->State.Self->GetExecuteData(lpData);
}

// This method is not currently implemented.
HRESULT Direct3DExecuteBuffer::Validate(LPDWORD lpdwOffset, LPD3DVALIDATECALLBACK lpFunc, LPVOID lpContext, DWORD dwReserved)
{
    if (lpFunc == NULL) { return DDERR_INVALIDPARAMS; }

    ValidateCallbackContext context;

    context.lpFunc = lpFunc;
    context.lpContext = lpContext;

    return this->State.Self->Validate(lpdwOffset, ValidateCallback, &context, dwReserved);
}

// This method is not currently supported.
HRESULT Direct3DExecuteBuffer::Optimize(DWORD dwFlags)
{
    return this->State.Self->Optimize(dwFlags);
}