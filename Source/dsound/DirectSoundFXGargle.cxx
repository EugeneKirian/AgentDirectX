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

#include "DirectSoundFXGargle.hxx"
#include "Unknown.hxx"

DirectSoundFXGargle::DirectSoundFXGargle(AgentConstructorParameters(DirectSoundFXGargle))
{
    AgentConstructor();
}

DirectSoundFXGargle::~DirectSoundFXGargle()
{
    AgentDestructor();
}

HRESULT DirectSoundFXGargle::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundFXGargle, riid)) { *ppvObj = ActivateAgent(DirectSoundFXGargle, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectSoundFXGargle::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundFXGargle::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Sets the amplitude modulation parameters of a buffer.
HRESULT DirectSoundFXGargle::SetAllParameters(LPCDSFXGargle pcDsFxGargle)
{
    return this->State.Self->SetAllParameters(pcDsFxGargle);
}

// Retrieves the amplitude modulation parameters of a buffer.
HRESULT DirectSoundFXGargle::GetAllParameters(LPDSFXGargle pDsFxGargle)
{
    return this->State.Self->GetAllParameters(pDsFxGargle);
}