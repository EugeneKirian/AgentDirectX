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
#include "DirectSoundBuffer.hxx"
#include "KsPropertySet.hxx"
#include "Unknown.hxx"

DirectSound3DBuffer::DirectSound3DBuffer(AgentConstructorParameters(DirectSound3DBuffer))
{
    AgentConstructor();
}

DirectSound3DBuffer::~DirectSound3DBuffer()
{
    AgentDestructor();
}

HRESULT DirectSound3DBuffer::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSound3DBuffer, riid)) { *ppvObj = ActivateAgent(DirectSound3DBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundBuffer, riid)) { *ppvObj = ActivateAgent(DirectSoundBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IKsPropertySet, riid)) { *ppvObj = ActivateAgent(KsPropertySet, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSound3DBuffer::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSound3DBuffer::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves information that describes the 3-D characteristics of a sound buffer at a given point in time.
HRESULT DirectSound3DBuffer::GetAllParameters(LPDS3DBUFFER pDs3dBuffer)
{
    return this->State.Self->GetAllParameters(pDs3dBuffer);
}

// Retrieves the inside and outside angles of the sound projection cone for this sound buffer.
HRESULT DirectSound3DBuffer::GetConeAngles(LPDWORD pdwInsideConeAngle, LPDWORD pdwOutsideConeAngle)
{
    return this->State.Self->GetConeAngles(pdwInsideConeAngle, pdwOutsideConeAngle);
}

// Retrieves the orientation of the sound projection cone for this sound buffer.
HRESULT DirectSound3DBuffer::GetConeOrientation(D3DVECTOR* pvOrientation)
{
    return this->State.Self->GetConeOrientation(pvOrientation);
}

// Retrieves the current cone outside volume for this sound buffer.
HRESULT DirectSound3DBuffer::GetConeOutsideVolume(LPLONG plConeOutsideVolume)
{
    return this->State.Self->GetConeOutsideVolume(plConeOutsideVolume);
}

// Retrieves the current maximum distance for this sound buffer.
HRESULT DirectSound3DBuffer::GetMaxDistance(D3DVALUE* pflMaxDistance)
{
    return this->State.Self->GetMaxDistance(pflMaxDistance);
}

// Retrieves the current minimum distance for this sound buffer.
HRESULT DirectSound3DBuffer::GetMinDistance(D3DVALUE* pflMinDistance)
{
    return this->State.Self->GetMinDistance(pflMinDistance);
}

// Retrieves the current operation mode for 3-D sound processing.
HRESULT DirectSound3DBuffer::GetMode(LPDWORD pdwMode)
{
    return this->State.Self->GetMode(pdwMode);
}

// Retrieves the sound buffer's current position, in distance units.
// By default, distance units are meters, but the units can be changed by using the IDirectSound3DListener::SetDistanceFactor method.
HRESULT DirectSound3DBuffer::GetPosition(D3DVECTOR* pvPosition)
{
    return this->State.Self->GetPosition(pvPosition);
}

// Retrieves the current velocity for this sound buffer.
// Velocity is measured in units per second. The default unit is one meter, but this can be changed by using the IDirectSound3DListener::SetDistanceFactor method.
HRESULT DirectSound3DBuffer::GetVelocity(D3DVECTOR* pvVelocity)
{
    return this->State.Self->GetVelocity(pvVelocity);
}

// Sets all 3-D sound buffer parameters from a given DS3DBUFFER structure that describes all aspects of the sound buffer at a moment in time.
HRESULT DirectSound3DBuffer::SetAllParameters(LPCDS3DBUFFER pcDs3dBuffer, DWORD dwApply)
{
    return this->State.Self->SetAllParameters(pcDs3dBuffer, dwApply);
}

// Sets the inside and outside angles of the sound projection cone for this sound buffer.
HRESULT DirectSound3DBuffer::SetConeAngles(DWORD dwInsideConeAngle, DWORD dwOutsideConeAngle, DWORD dwApply)
{
    return this->State.Self->SetConeAngles(dwInsideConeAngle, dwOutsideConeAngle, dwApply);
}

// Sets the orientation of the sound projection cone for this sound buffer.
// This method has no effect unless the cone angle and cone volume factor have also been set.
HRESULT DirectSound3DBuffer::SetConeOrientation(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    return this->State.Self->SetConeOrientation(x, y, z, dwApply);
}

// Sets the current cone outside volume for this sound buffer.
HRESULT DirectSound3DBuffer::SetConeOutsideVolume(LONG lConeOutsideVolume, DWORD dwApply)
{
    return this->State.Self->SetConeOutsideVolume(lConeOutsideVolume, dwApply);
}

// Sets the current maximum distance value.
HRESULT DirectSound3DBuffer::SetMaxDistance(D3DVALUE flMaxDistance, DWORD dwApply)
{
    return this->State.Self->SetMaxDistance(flMaxDistance, dwApply);
}

// Sets the current minimum distance value.
HRESULT DirectSound3DBuffer::SetMinDistance(D3DVALUE flMinDistance, DWORD dwApply)
{
    return this->State.Self->SetMinDistance(flMinDistance, dwApply);
}

// Sets the operation mode for 3-D sound processing.
HRESULT DirectSound3DBuffer::SetMode(DWORD dwMode, DWORD dwApply)
{
    return this->State.Self->SetMode(dwMode, dwApply);
}

// Sets the sound buffer's current position, in distance units.
// By default, distance units are meters, but the units can be changed by using the IDirectSound3DListener::SetDistanceFactor method.
HRESULT DirectSound3DBuffer::SetPosition(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    return this->State.Self->SetPosition(x, y, z, dwApply);
}

// Sets the sound buffer's current velocity. 
HRESULT DirectSound3DBuffer::SetVelocity(D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    return this->State.Self->SetVelocity(x, y, z, dwApply);
}