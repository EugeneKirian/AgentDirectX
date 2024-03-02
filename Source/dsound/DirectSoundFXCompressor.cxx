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

#include "DirectSoundFXCompressor.hxx"
#include "Unknown.hxx"

DirectSoundFXCompressor::DirectSoundFXCompressor(AgentConstructorParameters(DirectSoundFXCompressor))
{
    AgentConstructor();
}

DirectSoundFXCompressor::~DirectSoundFXCompressor()
{
    AgentDestructor();
}

HRESULT DirectSoundFXCompressor::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectSoundFXCompressor, riid)) { *ppvObj = ActivateAgent(DirectSoundFXCompressor, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectSoundFXCompressor::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectSoundFXCompressor::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Sets the compression parameters of a buffer.
HRESULT DirectSoundFXCompressor::SetAllParameters(LPCDSFXCompressor pcDsFxCompressor)
{
    return this->State.Self->SetAllParameters(pcDsFxCompressor);
}

// Retrieves the compression parameters of a buffer.
HRESULT DirectSoundFXCompressor::GetAllParameters(LPDSFXCompressor pDsFxCompressor)
{
    return this->State.Self->GetAllParameters(pDsFxCompressor);
}