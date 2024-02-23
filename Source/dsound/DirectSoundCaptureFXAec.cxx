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

#include "DirectSoundCaptureFXAec.hxx"
#include "Unknown.hxx"

DirectSoundCaptureFXAec::DirectSoundCaptureFXAec(AgentConstructorParameters(DirectSoundCaptureFXAec))
{
    AgentConstructor();
}

DirectSoundCaptureFXAec::~DirectSoundCaptureFXAec()
{
    AgentDestructor();
}

HRESULT DirectSoundCaptureFXAec::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundCaptureFXAec, riid)) { *ppvObj = ActivateAgent(DirectSoundCaptureFXAec, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSoundCaptureFXAec::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundCaptureFXAec::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Sets the acoustic echo cancellation parameters of a buffer.
// This method requires Microsoft Windows XP Home Edition or Windows XP Professional.
HRESULT DirectSoundCaptureFXAec::SetAllParameters(LPCDSCFXAec pDscFxAec)
{
    return this->State.Self->SetAllParameters(pDscFxAec);
}

// Retrieves the acoustic echo cancellation parameters of a buffer.
// This method requires Microsoft Windows XP Home Edition or Windows XP Professional.
HRESULT DirectSoundCaptureFXAec::GetAllParameters(LPDSCFXAec pDscFxAec)
{
    return this->State.Self->GetAllParameters(pDscFxAec);
}

// Retrieves the status of the effect.
HRESULT DirectSoundCaptureFXAec::GetStatus(LPDWORD pdwStatus)
{
    return this->State.Self->GetStatus(pdwStatus);
}

// Resets the effect to its initial state.
HRESULT DirectSoundCaptureFXAec::Reset()
{
    return this->State.Self->Reset();
}