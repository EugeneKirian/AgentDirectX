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
#include "DirectSoundBuffer.hxx"
#include "Unknown.hxx"

DirectSound::DirectSound(AgentConstructorParameters(DirectSound))
{
    AgentConstructor();
}

DirectSound::~DirectSound()
{
    AgentDestructor();
}

HRESULT DirectSound::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSound, riid)) { *ppvObj = ActivateAgent(DirectSound, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSound::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSound::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Creates a DirectSoundBuffer object to hold a sequence of audio samples.
HRESULT DirectSound::CreateSoundBuffer(LPCDSBUFFERDESC pcDSBufferDesc, LPDIRECTSOUNDBUFFER* ppDSBuffer, IUnknown* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateSoundBuffer(pcDSBufferDesc, ppDSBuffer, pUnkOuter);

    if (SUCCEEDED(result)) { *ppDSBuffer = ActivateAgentDelegate(DirectSoundBuffer, *ppDSBuffer); }

    return result;
}

// Retrieves the capabilities of the hardware device that is represented by the DirectSound object.
HRESULT DirectSound::GetCaps(LPDSCAPS pDSCaps)
{
    return this->State.Self->GetCaps(pDSCaps);
}

// Creates a new DirectSoundBuffer object that uses the same buffer memory as the original object.
HRESULT DirectSound::DuplicateSoundBuffer(LPDIRECTSOUNDBUFFER pDSBufferOriginal, LPDIRECTSOUNDBUFFER* ppDSBufferDuplicate)
{
    AttemptAccessAgentValue(DirectSoundBuffer, pDSBufferOriginal);

    CONST HRESULT result = this->State.Self->DuplicateSoundBuffer(pDSBufferOriginal, ppDSBufferDuplicate);

    if (SUCCEEDED(result)) { *ppDSBufferDuplicate = ActivateAgentDelegate(DirectSoundBuffer, *ppDSBufferDuplicate); }

    return result;
}

// Sets the cooperative level of the application for this sound device.
HRESULT DirectSound::SetCooperativeLevel(HWND hwnd, DWORD dwLevel)
{
    return this->State.Self->SetCooperativeLevel(hwnd, dwLevel);
}

// Moves the unused portions of on-board sound memory, if any, to a contiguous block so that the largest portion of free memory will be available.
HRESULT DirectSound::Compact()
{
    return this->State.Self->Compact();
}

// Retrieves the speaker configuration.
HRESULT DirectSound::GetSpeakerConfig(LPDWORD pdwSpeakerConfig)
{
    return this->State.Self->GetSpeakerConfig(pdwSpeakerConfig);
}

// Specifies the speaker configuration of the DirectSound object.
HRESULT DirectSound::SetSpeakerConfig(DWORD dwSpeakerConfig)
{
    return this->State.Self->SetSpeakerConfig(dwSpeakerConfig);
}

// Initializes the DirectSound object that was created by using the CoCreateInstance function.
HRESULT DirectSound::Initialize(LPCGUID pcGuidDevice)
{
    return this->State.Self->Initialize(pcGuidDevice);
}