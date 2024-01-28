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

#include "DirectDraw.hxx"
#include "DirectDrawPalette.hxx"

DirectDrawPalette::DirectDrawPalette(AgentConstructorParameters(DirectDrawPalette))
{
    AgentConstructor();
}

DirectDrawPalette::~DirectDrawPalette()
{
    AgentDestructor();
}

HRESULT DirectDrawPalette::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectDrawPalette, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDrawPalette, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectDrawPalette::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectDrawPalette::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves the capabilities of the palette object.
HRESULT DirectDrawPalette::GetCaps(LPDWORD lpdwCaps)
{
    return this->State.Self->GetCaps(lpdwCaps);
}

// Retrieves palette values from a DirectDrawPalette object.
HRESULT DirectDrawPalette::GetEntries(DWORD dwFlags, DWORD dwBase, DWORD dwNumEntries, LPPALETTEENTRY lpEntries)
{
    return this->State.Self->GetEntries(dwFlags, dwBase, dwNumEntries, lpEntries);
}

// Initializes the DirectDrawPalette object.
HRESULT DirectDrawPalette::Initialize(LPDIRECTDRAW lpDD, DWORD dwFlags, LPPALETTEENTRY lpDDColorTable)
{
    AttemptAccessAgentValue(DirectDraw, lpDD);

    return this->State.Self->Initialize(lpDD, dwFlags, lpDDColorTable);
}

// Changes entries in a DirectDrawPalette object immediately.
HRESULT DirectDrawPalette::SetEntries(DWORD dwFlags, DWORD dwStartingEntry, DWORD dwCount, LPPALETTEENTRY lpEntries)
{
    return this->State.Self->SetEntries(dwFlags, dwStartingEntry, dwCount, lpEntries);
}