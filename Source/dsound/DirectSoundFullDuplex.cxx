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

#include "DirectSound.hxx"
#include "DirectSound8.hxx"
#include "DirectSoundBuffer8.hxx"
#include "DirectSoundCapture.hxx"
#include "DirectSoundCaptureBuffer8.hxx"
#include "DirectSoundFullDuplex.hxx"
#include "Unknown.hxx"

DirectSoundFullDuplex::DirectSoundFullDuplex(AgentConstructorParameters(DirectSoundFullDuplex))
{
    AgentConstructor();
}

DirectSoundFullDuplex::~DirectSoundFullDuplex()
{
    AgentDestructor();
}

HRESULT DirectSoundFullDuplex::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSound8, riid) || IsEqualIID(IID_IDirectSound, riid)) { *ppvObj = ActivateAgent(DirectSound8, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundCapture, riid)) { *ppvObj = ActivateAgent(DirectSoundCapture, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundFullDuplex, riid)) { *ppvObj = ActivateAgent(DirectSoundFullDuplex, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSoundFullDuplex::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundFullDuplex::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

HRESULT DirectSoundFullDuplex::Initialize(LPCGUID pCaptureGuid, LPCGUID pRenderGuid, LPCDSCBUFFERDESC lpDscBufferDesc, LPCDSBUFFERDESC lpDsBufferDesc, HWND hWnd, DWORD dwLevel, LPLPDIRECTSOUNDCAPTUREBUFFER8 lplpDirectSoundFullDuplexCaptureBuffer8, LPLPDIRECTSOUNDBUFFER8 lplpDirectSoundFullDuplexBuffer8)
{
    const HRESULT result = this->State.Self->Initialize(pCaptureGuid, pRenderGuid, lpDscBufferDesc, lpDsBufferDesc, hWnd, dwLevel, lplpDirectSoundFullDuplexCaptureBuffer8, lplpDirectSoundFullDuplexBuffer8);

    if (SUCCEEDED(result))
    {
        *lplpDirectSoundFullDuplexCaptureBuffer8 = ActivateAgentDelegate(DirectSoundCaptureBuffer8, *lplpDirectSoundFullDuplexCaptureBuffer8);
        *lplpDirectSoundFullDuplexBuffer8 = ActivateAgentDelegate(DirectSoundBuffer8, *lplpDirectSoundFullDuplexBuffer8);
    }

    return result;
}