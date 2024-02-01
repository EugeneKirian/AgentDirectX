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

KsPropertySet::KsPropertySet(AgentConstructorParameters(KsPropertySet))
{
    AgentConstructor();
}

KsPropertySet::~KsPropertySet()
{
    AgentDestructor();
}

HRESULT KsPropertySet::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSound3DBuffer, riid)) { *ppvObj = ActivateAgent(KsPropertySet, *ppvObj); }
            else if (IsEqualIID(IID_IDirectSoundBuffer, riid)) { *ppvObj = ActivateAgent(DirectSoundBuffer, *ppvObj); }
            else if (IsEqualIID(IID_IKsPropertySet, riid)) { *ppvObj = ActivateAgent(KsPropertySet, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG KsPropertySet::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG KsPropertySet::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves data for an item in a property set.
HRESULT KsPropertySet::Get(REFGUID rguidPropSet, ULONG ulId, LPVOID pInstanceData, ULONG ulInstanceLength, LPVOID pPropertyData, ULONG ulDataLength, PULONG pulBytesReturned)
{
    return this->State.Self->Get(rguidPropSet, ulId, pInstanceData, ulInstanceLength, pPropertyData, ulDataLength, pulBytesReturned);
}

// Sets the value of a property in a property set.
HRESULT KsPropertySet::Set(REFGUID rguidPropSet, ULONG ulId, LPVOID pInstanceData, ULONG ulInstanceLength, LPVOID pPropertyData, ULONG ulDataLength)
{
    return this->State.Self->Set(rguidPropSet, ulId, pInstanceData, ulInstanceLength, pPropertyData, ulDataLength);
}

// Ascertains whether a property in a property set is supported on the port or device.
HRESULT KsPropertySet::QuerySupport(REFGUID rguidPropSet, ULONG ulId, PULONG pulTypeSupport)
{
    return this->State.Self->QuerySupport(rguidPropSet, ulId, pulTypeSupport);
}