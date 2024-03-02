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

#include "DirectSoundFXI3DL2Reverb.hxx"
#include "Unknown.hxx"

DirectSoundFXI3DL2Reverb::DirectSoundFXI3DL2Reverb(AgentConstructorParameters(DirectSoundFXI3DL2Reverb))
{
    AgentConstructor();
}

DirectSoundFXI3DL2Reverb::~DirectSoundFXI3DL2Reverb()
{
    AgentDestructor();
}

HRESULT DirectSoundFXI3DL2Reverb::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundFXI3DL2Reverb, riid)) { *ppvObj = ActivateAgent(DirectSoundFXI3DL2Reverb, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectSoundFXI3DL2Reverb::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundFXI3DL2Reverb::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Sets the I3DL2 environmental reverberation parameters of a buffer.
HRESULT DirectSoundFXI3DL2Reverb::SetAllParameters(LPCDSFXI3DL2Reverb pcDsFxI3DL2Reverb)
{
    return this->State.Self->SetAllParameters(pcDsFxI3DL2Reverb);
}

// Retrieves the I3DL2 environmental reverberation parameters of a buffer.
HRESULT DirectSoundFXI3DL2Reverb::GetAllParameters(LPDSFXI3DL2Reverb pDsFxI3DL2Reverb)
{
    return this->State.Self->GetAllParameters(pDsFxI3DL2Reverb);
}

// Sets standard reverberation parameters of a buffer.
HRESULT DirectSoundFXI3DL2Reverb::SetPreset(DWORD dwPreset)
{
    return this->State.Self->SetPreset(dwPreset);
}

// Retrieves an identifier for standard reverberation parameters of a buffer.
HRESULT DirectSoundFXI3DL2Reverb::GetPreset(LPDWORD pdwPreset)
{
    return this->State.Self->GetPreset(pdwPreset);
}

// Sets the quality of the environmental reverberation effect.
// Higher values produce better quality at the expense of processing time. 
HRESULT DirectSoundFXI3DL2Reverb::SetQuality(LONG lQuality)
{
    return this->State.Self->SetQuality(lQuality);
}

// Retrieves the quality of the environmental reverberation effect.
HRESULT DirectSoundFXI3DL2Reverb::GetQuality(LONG* plQuality)
{
    return this->State.Self->GetQuality(plQuality);
}