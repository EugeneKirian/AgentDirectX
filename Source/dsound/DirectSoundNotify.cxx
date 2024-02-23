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

#include "DirectSoundBuffer.hxx"
#include "DirectSoundBuffer8.hxx"
#include "DirectSoundNotify.hxx"
#include "KsPropertySet.hxx"
#include "Unknown.hxx"

DirectSoundNotify::DirectSoundNotify(AgentConstructorParameters(DirectSoundNotify))
{
    AgentConstructor();
}

DirectSoundNotify::~DirectSoundNotify()
{
    AgentDestructor();
}

HRESULT DirectSoundNotify::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundBuffer, riid)) { *ppvObj = ActivateAgent(DirectSoundBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundBuffer8, riid)) { *ppvObj = ActivateAgent(DirectSoundBuffer8, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundNotify, riid)) { *ppvObj = ActivateAgent(DirectSoundNotify, *ppvObj); }
            else if (IsEqualIID(IID_IKsPropertySet, riid)) { *ppvObj = ActivateAgent(KsPropertySet, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSoundNotify::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundNotify::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Sets the notification positions. During capture or playback,
// whenever the read or play cursor reaches an offset specified in one of the DSBPOSITIONNOTIFY structures in the caller-supplied array,
// the associated event is signaled.
HRESULT DirectSoundNotify::SetNotificationPositions(DWORD dwPositionNotifies, LPCDSBPOSITIONNOTIFY pcPositionNotifies)
{
    return this->State.Self->SetNotificationPositions(dwPositionNotifies, pcPositionNotifies);
}