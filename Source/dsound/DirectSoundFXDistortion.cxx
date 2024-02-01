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

#include "DirectSoundFXDistortion.hxx"
#include "Unknown.hxx"

DirectSoundFXDistortion::DirectSoundFXDistortion(AgentConstructorParameters(DirectSoundFXDistortion))
{
    AgentConstructor();
}

DirectSoundFXDistortion::~DirectSoundFXDistortion()
{
    AgentDestructor();
}

HRESULT DirectSoundFXDistortion::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundFXDistortion, riid)) { *ppvObj = ActivateAgent(DirectSoundFXDistortion, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            else { DebugBreak(); }
        }
    }

    return result;
}

ULONG DirectSoundFXDistortion::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundFXDistortion::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Sets the distortion parameters of a buffer.
HRESULT DirectSoundFXDistortion::SetAllParameters(LPCDSFXDistortion pcDsFxDistortion)
{
    return this->State.Self->SetAllParameters(pcDsFxDistortion);
}

// Retrieves the distortion parameters of a buffer.
HRESULT DirectSoundFXDistortion::GetAllParameters(LPDSFXDistortion pDsFxDistortion)
{
    return this->State.Self->GetAllParameters(pDsFxDistortion);
}