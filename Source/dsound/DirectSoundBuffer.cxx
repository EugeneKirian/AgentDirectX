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

#include "DirectSound3DBuffer.hxx"
#include "DirectSound3DListener.hxx"
#include "DirectSoundBuffer.hxx"
#include "DirectSoundBuffer8.hxx"
#include "DirectSoundNotify.hxx"
#include "KsPropertySet.hxx"
#include "Unknown.hxx"

DirectSoundBuffer::DirectSoundBuffer(AgentConstructorParameters(DirectSoundBuffer))
{
    AgentConstructor();
}

DirectSoundBuffer::~DirectSoundBuffer()
{
    AgentDestructor();
}

HRESULT DirectSoundBuffer::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

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

ULONG DirectSoundBuffer::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundBuffer::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves the capabilities of the DirectSoundBuffer object.
HRESULT DirectSoundBuffer::GetCaps(LPDSBCAPS pDSBufferCaps)
{
    return this->State.Self->GetCaps(pDSBufferCaps);
}

// Retrieves the current position of the play and write cursors in the sound buffer.
HRESULT DirectSoundBuffer::GetCurrentPosition(LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor)
{
    return this->State.Self->GetCurrentPosition(pdwCurrentPlayCursor, pdwCurrentWriteCursor);
}

// Retrieves a description of the format of the sound data in the buffer, or the buffer size needed to retrieve the format description.
HRESULT DirectSoundBuffer::GetFormat(LPWAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, LPDWORD pdwSizeWritten)
{
    return this->State.Self->GetFormat(pwfxFormat, dwSizeAllocated, pdwSizeWritten);
}

// Retrieves the current volume for this sound buffer.
HRESULT DirectSoundBuffer::GetVolume(LPLONG plVolume)
{
    return this->State.Self->GetVolume(plVolume);
}

// Retrieves a variable that represents the relative volume between the left and right audio channels.
HRESULT DirectSoundBuffer::GetPan(LPLONG plPan)
{
    return this->State.Self->GetPan(plPan);
}

// Retrieves the frequency, in samples per second, at which the buffer is playing.
HRESULT DirectSoundBuffer::GetFrequency(LPDWORD pdwFrequency)
{
    return this->State.Self->GetFrequency(pdwFrequency);
}

// Retrieves the current status of the sound buffer.
HRESULT DirectSoundBuffer::GetStatus(LPDWORD pdwStatus)
{
    return this->State.Self->GetStatus(pdwStatus);
}

// Initializes a DirectSoundBuffer object if it has not yet been initialized.
HRESULT DirectSoundBuffer::Initialize(LPDIRECTSOUND pDirectSound, LPCDSBUFFERDESC pcDSBufferDesc)
{
    AttemptAccessAgentValue(DirectSound, pDirectSound);

    return this->State.Self->Initialize(pDirectSound, pcDSBufferDesc);
}

// Obtains a valid write pointer to the sound buffer's audio data.
HRESULT DirectSoundBuffer::Lock(DWORD dwOffset, DWORD dwBytes, LPVOID* ppvAudioPtr1, LPDWORD pdwAudioBytes1, LPVOID* ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags)
{
    return this->State.Self->Lock(dwOffset, dwBytes, ppvAudioPtr1, pdwAudioBytes1, ppvAudioPtr2, pdwAudioBytes2, dwFlags);
}

// Causes the sound buffer to play from the current position.
HRESULT DirectSoundBuffer::Play(DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags)
{
    return this->State.Self->Play(dwReserved1, dwPriority, dwFlags);
}

// Moves the current play position for secondary sound buffers.
HRESULT DirectSoundBuffer::SetCurrentPosition(DWORD dwNewPosition)
{
    return this->State.Self->SetCurrentPosition(dwNewPosition);
}

// Sets the format of the primary sound buffer for the application.
// Whenever this application has the input focus, DirectSound will set the primary buffer to the specified format.
HRESULT DirectSoundBuffer::SetFormat(LPCWAVEFORMATEX pcfxFormat)
{
    return this->State.Self->SetFormat(pcfxFormat);
}

// Changes the volume of a sound buffer.
HRESULT DirectSoundBuffer::SetVolume(LONG lVolume)
{
    return this->State.Self->SetVolume(lVolume);
}

// Specifies the relative volume between the left and right channels.
HRESULT DirectSoundBuffer::SetPan(LONG lPan)
{
    return this->State.Self->SetPan(lPan);
}

// Sets the frequency at which the audio samples are played.
HRESULT DirectSoundBuffer::SetFrequency(DWORD dwFrequency)
{
    return this->State.Self->SetFrequency(dwFrequency);
}

// Causes the sound buffer to stop playing.
HRESULT DirectSoundBuffer::Stop()
{
    return this->State.Self->Stop();
}

// Releases a locked sound buffer.
HRESULT DirectSoundBuffer::Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2)
{
    return this->State.Self->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2);
}

// Restores the memory allocation for a lost sound buffer for the specified DirectSoundBuffer object.
HRESULT DirectSoundBuffer::Restore()
{
    return this->State.Self->Restore();
}