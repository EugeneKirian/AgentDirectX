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

#include "DirectSoundCaptureBuffer.hxx"
#include "DirectSoundCaptureBuffer8.hxx"
#include "DirectSoundFXChorus.hxx"
#include "DirectSoundFXCompressor.hxx"
#include "DirectSoundFXDistortion.hxx"
#include "DirectSoundFXEcho.hxx"
#include "DirectSoundFXFlanger.hxx"
#include "DirectSoundFXGargle.hxx"
#include "DirectSoundFXI3DL2Reverb.hxx"
#include "DirectSoundFXParamEq.hxx"
#include "DirectSoundFXWavesReverb.hxx"
#include "DirectSoundNotify.hxx"
#include "Unknown.hxx"

DirectSoundCaptureBuffer8::DirectSoundCaptureBuffer8(AgentConstructorParameters(DirectSoundCaptureBuffer8))
{
    AgentConstructor();
}

DirectSoundCaptureBuffer8::~DirectSoundCaptureBuffer8()
{
    AgentDestructor();
}

HRESULT DirectSoundCaptureBuffer8::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundCaptureBuffer, riid)) { *ppvObj = ActivateAgent(DirectSoundCaptureBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundCaptureBuffer8, riid)) { *ppvObj = ActivateAgent(DirectSoundCaptureBuffer8, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundNotify, riid)) { *ppvObj = ActivateAgent(DirectSoundNotify, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSoundCaptureBuffer8::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundCaptureBuffer8::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves the capabilities of the buffer.
HRESULT DirectSoundCaptureBuffer8::GetCaps(LPDSCBCAPS pDSCBCaps)
{
    return this->State.Self->GetCaps(pDSCBCaps);
}

// Retrieves the capture and read cursors in the buffer.
// The capture cursor is ahead of the read cursor.
// The data after the read position up to and including the capture position is not necessarily valid data.
HRESULT DirectSoundCaptureBuffer8::GetCurrentPosition(LPDWORD pdwCapturePosition, LPDWORD pdwReadPosition)
{
    return this->State.Self->GetCurrentPosition(pdwCapturePosition, pdwReadPosition);
}

// Retrieves the format of the capture buffer.
HRESULT DirectSoundCaptureBuffer8::GetFormat(LPWAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, LPDWORD pdwSizeWritten)
{
    return this->State.Self->GetFormat(pwfxFormat, dwSizeAllocated, pdwSizeWritten);
}

// Retrieves the status of the capture buffer.
HRESULT DirectSoundCaptureBuffer8::GetStatus(LPDWORD pdwStatus)
{
    return this->State.Self->GetStatus(pdwStatus);
}

// Initializes a capture buffer object.
// Because the IDirectSoundCapture::CreateCaptureBuffer method and the DirectSoundFullDuplexCreate function call
// the IDirectSoundCaptureBuffer8::Initialize method internally, this method is not used by applications.
// It is provided for future extensibility.
HRESULT DirectSoundCaptureBuffer8::Initialize(LPDIRECTSOUNDCAPTURE pDirectSoundCapture, LPCDSCBUFFERDESC pcDSCBufferDesc)
{
    AttemptAccessAgentValue(DirectSoundCapture, pDirectSoundCapture);

    return this->State.Self->Initialize(pDirectSoundCapture, pcDSCBufferDesc);
}

// Locks a portion of the buffer.
// Locking the buffer returns pointers into the buffer, allowing the application to read or write audio data into memory.
HRESULT DirectSoundCaptureBuffer8::Lock(DWORD dwOffset, DWORD dwBytes, LPVOID* ppvAudioPtr1, LPDWORD pdwAudioBytes1, LPVOID* ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags)
{
    return this->State.Self->Lock(dwOffset, dwBytes, ppvAudioPtr1, pdwAudioBytes1, ppvAudioPtr2, pdwAudioBytes2, dwFlags);
}

// Begins capturing data into the buffer.
// If the buffer is already capturing, the method has no effect.
HRESULT DirectSoundCaptureBuffer8::Start(DWORD dwFlags)
{
    return this->State.Self->Start(dwFlags);
}

// Stops the buffer so that it is no longer capturing data.
// If the buffer is not capturing, the method has no effect.
HRESULT DirectSoundCaptureBuffer8::Stop()
{
    return this->State.Self->Stop();
}

// Unlocks the buffer.
HRESULT DirectSoundCaptureBuffer8::Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2)
{
    return this->State.Self->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2);
}

// Retrieves an interface to an effect object associated with the buffer.
HRESULT DirectSoundCaptureBuffer8::GetObjectInPath(REFGUID rguidObject, DWORD dwIndex, REFGUID rguidInterface, LPVOID* ppObject)
{
    CONST HRESULT result = this->State.Self->GetObjectInPath(rguidObject, dwIndex, rguidInterface, ppObject);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(rguidInterface, ppObject))
        {
            if (IsEqualIID(IID_IDirectSoundFXChorus, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXChorus, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXCompressor, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXCompressor, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXDistortion, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXDistortion, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXEcho, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXEcho, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXFlanger, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXFlanger, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXGargle, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXGargle, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXI3DL2Reverb, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXI3DL2Reverb, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXParamEq, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXParamEq, *ppObject); }
            else if (IsEqualIID(IID_IDirectSoundFXWavesReverb, rguidInterface)) { *ppObject = ActivateAgentDelegate(DirectSoundFXWavesReverb, *ppObject); }
            //else if (IsEqualIID(IID_IMediaObject, rguidInterface)) { *ppObject = ActivateAgentDelegate(MediaObject, *ppObject); } // NOT IMPLEMENTED
            //else if (IsEqualIID(IID_IMediaObjectInPlace, rguidInterface)) { *ppObject = ActivateAgentDelegate(MediaObjectInPlace, *ppObject); } // NOT IMPLEMENTED
            //else if (IsEqualIID(IID_IMediaParams, rguidInterface)) { *ppObject = ActivateAgentDelegate(MediaParams, *ppObject); } // NOT IMPLEMENTED
            else { DebugBreak(); }
        }
    }

    return result;
}

// Retrieves the status of capture effects.
HRESULT DirectSoundCaptureBuffer8::GetFXStatus(DWORD dwEffectsCount, LPDWORD pdwFXStatus)
{
    return this->State.Self->GetFXStatus(dwEffectsCount, pdwFXStatus);
}