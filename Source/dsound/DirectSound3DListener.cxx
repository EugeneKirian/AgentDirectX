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

#include "DirectSound3DListener.hxx"
#include "DirectSoundBuffer.hxx"
#include "KsPropertySet.hxx"
#include "Unknown.hxx"

DirectSound3DListener::DirectSound3DListener(AgentConstructorParameters(DirectSound3DListener))
{
    AgentConstructor();
}

DirectSound3DListener::~DirectSound3DListener()
{
    AgentDestructor();
}

HRESULT DirectSound3DListener::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSound3DListener, riid)) { *ppvObj = ActivateAgent(DirectSound3DListener, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundBuffer, riid)) { *ppvObj = ActivateAgent(DirectSoundBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IKsPropertySet, riid)) { *ppvObj = ActivateAgent(KsPropertySet, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSound3DListener::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSound3DListener::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves information that describes the current state of the 3-D world and listener.
HRESULT DirectSound3DListener::GetAllParameters(LPDS3DLISTENER pListener)
{
    return this->State.Self->GetAllParameters(pListener);
}

// Retrieves the current distance factor.
HRESULT DirectSound3DListener::GetDistanceFactor(D3DVALUE* pflDistanceFactor)
{
    return this->State.Self->GetDistanceFactor(pflDistanceFactor);
}

// Retrieves the current Doppler effect factor.
HRESULT DirectSound3DListener::GetDopplerFactor(D3DVALUE* pflDopplerFactor)
{
    return this->State.Self->GetDopplerFactor(pflDopplerFactor);
}

// Retrieves the listener's current orientation in vectors: a front vector and a top vector.
HRESULT DirectSound3DListener::GetOrientation(D3DVECTOR* pvOrientFront, D3DVECTOR* pvOrientTop)
{
    return this->State.Self->GetOrientation(pvOrientFront, pvOrientTop);
}

// Retrieves the listener's current position in distance units.
// By default, these units are meters, but this can be changed by calling the IDirectSound3DListener::SetDistanceFactor method.
HRESULT DirectSound3DListener::GetPosition(D3DVECTOR* pvPosition)
{
    return this->State.Self->GetPosition(pvPosition);
}

// Retrieves the current rolloff factor.
HRESULT DirectSound3DListener::GetRolloffFactor(D3DVALUE* pflRolloffFactor)
{
    return this->State.Self->GetRolloffFactor(pflRolloffFactor);
}

// Retrieves the listener's current velocity.
HRESULT DirectSound3DListener::GetVelocity(D3DVECTOR* pvVelocity)
{
    return this->State.Self->GetVelocity(pvVelocity);
}

// Sets all 3-D listener parameters from a given DS3DLISTENER structure that describes all aspects of the 3-D listener at a moment in time.
HRESULT DirectSound3DListener::SetAllParameters(LPCDS3DLISTENER pcListener, DWORD dwApply)
{
    return this->State.Self->SetAllParameters(pcListener, dwApply);
}

// Sets the current distance factor.
HRESULT DirectSound3DListener::SetDistanceFactor(D3DVALUE flDistanceFactor, DWORD dwApply)
{
    return this->State.Self->SetDistanceFactor(flDistanceFactor, dwApply);
}

// Sets the current Doppler effect factor.
HRESULT DirectSound3DListener::SetDopplerFactor(D3DVALUE flDopplerFactor, DWORD dwApply)
{
    return this->State.Self->SetDopplerFactor(flDopplerFactor, dwApply);
}

// Sets the listener's current orientation in terms of two vectors: a front vector and a top vector.
HRESULT DirectSound3DListener::SetOrientation(D3DVALUE xFront, D3DVALUE yFront, D3DVALUE zFront, D3DVALUE xTop, D3DVALUE yTop, D3DVALUE zTop, DWORD dwApply)
{
    return this->State.Self->SetOrientation(xFront, yFront, zFront, xTop, yTop, zTop, dwApply);
}

// Sets the listener's current position, in distance units.
// By default, these units are meters, but this can be changed by calling the IDirectSound3DListener::SetDistanceFactor method.
HRESULT DirectSound3DListener::SetPosition(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    return this->State.Self->SetPosition(x, y, z, dwApply);
}

// Sets the rolloff factor.
HRESULT DirectSound3DListener::SetRolloffFactor(D3DVALUE flRolloffFactor, DWORD dwApply)
{
    return this->State.Self->SetRolloffFactor(flRolloffFactor, dwApply);
}

// Sets the listener's velocity.
HRESULT DirectSound3DListener::SetVelocity(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    return this->State.Self->SetVelocity(x, y, z, dwApply);
}

// Commits any deferred settings made since the last call to this method.
HRESULT DirectSound3DListener::CommitDeferredSettings()
{
    return this->State.Self->CommitDeferredSettings();
}