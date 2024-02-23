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
#include "DirectSound3DBuffer.hxx"
#include "DirectSound3DListener.hxx"
#include "DirectSoundBuffer.hxx"
#include "DirectSoundBuffer8.hxx"
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
#include "KsPropertySet.hxx"
#include "Unknown.hxx"

DirectSoundBuffer8::DirectSoundBuffer8(AgentConstructorParameters(DirectSoundBuffer8))
{
    AgentConstructor();
}

DirectSoundBuffer8::~DirectSoundBuffer8()
{
    AgentDestructor();
}

HRESULT DirectSoundBuffer8::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSound3DBuffer, riid)) { *ppvObj = ActivateAgent(DirectSound3DBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSound3DListener, riid)) { *ppvObj = ActivateAgent(DirectSound3DListener, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundBuffer, riid)) { *ppvObj = ActivateAgent(DirectSoundBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundBuffer8, riid)) { *ppvObj = ActivateAgent(DirectSoundBuffer8, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundNotify, riid)) { *ppvObj = ActivateAgent(DirectSoundNotify, *ppvObj); }
            else if (IsEqualIID(IID_IKsPropertySet, riid)) { *ppvObj = ActivateAgent(KsPropertySet, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSoundBuffer8::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundBuffer8::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves the capabilities of the DirectSoundBuffer8 object.
HRESULT DirectSoundBuffer8::GetCaps(LPDSBCAPS pDSBufferCaps)
{
    return this->State.Self->GetCaps(pDSBufferCaps);
}

// Retrieves the current position of the play and write cursors in the sound buffer.
HRESULT DirectSoundBuffer8::GetCurrentPosition(LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor)
{
    return this->State.Self->GetCurrentPosition(pdwCurrentPlayCursor, pdwCurrentWriteCursor);
}

// Retrieves a description of the format of the sound data in the buffer, or the buffer size needed to retrieve the format description.
HRESULT DirectSoundBuffer8::GetFormat(LPWAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, LPDWORD pdwSizeWritten)
{
    return this->State.Self->GetFormat(pwfxFormat, dwSizeAllocated, pdwSizeWritten);
}

// Retrieves the current volume for this sound buffer.
HRESULT DirectSoundBuffer8::GetVolume(LPLONG plVolume)
{
    return this->State.Self->GetVolume(plVolume);
}

// Retrieves a variable that represents the relative volume between the left and right audio channels.
HRESULT DirectSoundBuffer8::GetPan(LPLONG plPan)
{
    return this->State.Self->GetPan(plPan);
}

// Retrieves the frequency, in samples per second, at which the buffer is playing.
HRESULT DirectSoundBuffer8::GetFrequency(LPDWORD pdwFrequency)
{
    return this->State.Self->GetFrequency(pdwFrequency);
}

// Retrieves the current status of the sound buffer.
HRESULT DirectSoundBuffer8::GetStatus(LPDWORD pdwStatus)
{
    return this->State.Self->GetStatus(pdwStatus);
}

// Initializes a DirectSoundBuffer8 object if it has not yet been initialized.
HRESULT DirectSoundBuffer8::Initialize(LPDIRECTSOUND pDirectSound, LPCDSBUFFERDESC pcDSBufferDesc)
{
    AttemptAccessAgentValue(DirectSound, pDirectSound);

    return this->State.Self->Initialize(pDirectSound, pcDSBufferDesc);
}

// Obtains a valid write pointer to the sound buffer's audio data.
HRESULT DirectSoundBuffer8::Lock(DWORD dwOffset, DWORD dwBytes, LPVOID* ppvAudioPtr1, LPDWORD pdwAudioBytes1, LPVOID* ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags)
{
    return this->State.Self->Lock(dwOffset, dwBytes, ppvAudioPtr1, pdwAudioBytes1, ppvAudioPtr2, pdwAudioBytes2, dwFlags);
}

// Causes the sound buffer to play from the current position.
HRESULT DirectSoundBuffer8::Play(DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags)
{
    return this->State.Self->Play(dwReserved1, dwPriority, dwFlags);
}

// Moves the current play position for secondary sound buffers.
HRESULT DirectSoundBuffer8::SetCurrentPosition(DWORD dwNewPosition)
{
    return this->State.Self->SetCurrentPosition(dwNewPosition);
}

// Sets the format of the primary sound buffer for the application.
// Whenever this application has the input focus, DirectSound will set the primary buffer to the specified format.
HRESULT DirectSoundBuffer8::SetFormat(LPCWAVEFORMATEX pcfxFormat)
{
    return this->State.Self->SetFormat(pcfxFormat);
}

// Changes the volume of a sound buffer.
HRESULT DirectSoundBuffer8::SetVolume(LONG lVolume)
{
    return this->State.Self->SetVolume(lVolume);
}

// Specifies the relative volume between the left and right channels.
HRESULT DirectSoundBuffer8::SetPan(LONG lPan)
{
    return this->State.Self->SetPan(lPan);
}

// Sets the frequency at which the audio samples are played.
HRESULT DirectSoundBuffer8::SetFrequency(DWORD dwFrequency)
{
    return this->State.Self->SetFrequency(dwFrequency);
}

// Causes the sound buffer to stop playing.
HRESULT DirectSoundBuffer8::Stop()
{
    return this->State.Self->Stop();
}

// Releases a locked sound buffer.
HRESULT DirectSoundBuffer8::Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2)
{
    return this->State.Self->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2);
}

// Restores the memory allocation for a lost sound buffer for the specified DirectSoundBuffer8 object.
HRESULT DirectSoundBuffer8::Restore()
{
    return this->State.Self->Restore();
}

// Enables effects on a buffer. The buffer must not be playing or locked.
HRESULT DirectSoundBuffer8::SetFX(DWORD dwEffectsCount, LPDSEFFECTDESC pDSFXDesc, LPDWORD pdwResultCodes)
{
    return this->State.Self->SetFX(dwEffectsCount, pDSFXDesc, pdwResultCodes);
}

// Allocates resources for a buffer that was created with the DSBCAPS_LOCDEFER flag in the DSBUFFERDESC structure. 
HRESULT DirectSoundBuffer8::AcquireResources(DWORD dwFlags, DWORD dwEffectsCount, LPDWORD pdwResultCodes)
{
    return this->State.Self->AcquireResources(dwFlags, dwEffectsCount, pdwResultCodes);
}

// Retrieves an interface for an effect object associated with the buffer.
HRESULT DirectSoundBuffer8::GetObjectInPath(REFGUID rguidObject, DWORD dwIndex, REFGUID rguidInterface, LPVOID* ppObject)
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