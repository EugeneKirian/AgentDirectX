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

#include "DirectSoundCapture.hxx"
#include "DirectSoundCaptureBuffer8.hxx"
#include "Unknown.hxx"

DirectSoundCapture::DirectSoundCapture(AgentConstructorParameters(DirectSoundCapture))
{
    AgentConstructor();
}

DirectSoundCapture::~DirectSoundCapture()
{
    AgentDestructor();
}

HRESULT DirectSoundCapture::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundCapture, riid)) { *ppvObj = ActivateAgent(DirectSoundCapture, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectSoundCapture::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundCapture::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Creates a capture buffer.
HRESULT DirectSoundCapture::CreateCaptureBuffer(LPCDSCBUFFERDESC pcDSCBufferDesc, LPDIRECTSOUNDCAPTUREBUFFER* ppDSCBuffer, LPUNKNOWN pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateCaptureBuffer(pcDSCBufferDesc, ppDSCBuffer, pUnkOuter);

    if (SUCCEEDED(result)) { *ppDSCBuffer = ActivateAgentDelegate(DirectSoundCaptureBuffer8, *ppDSCBuffer); }

    return result;
}

// Retrieves the capabilities of the capture device.
HRESULT DirectSoundCapture::GetCaps(LPDSCCAPS pDSCCaps)
{
    return this->State.Self->GetCaps(pDSCCaps);
}

// Initializes a DirectSoundCapture object created by using CoCreateInstance.
// Calling this method is not required when the DirectSoundCaptureCreate8 or DirectSoundFullDuplexCreate8 function is used to create the object. 
HRESULT DirectSoundCapture::Initialize(LPCGUID pcGuidDevice)
{
    return this->State.Self->Initialize(pcGuidDevice);
}