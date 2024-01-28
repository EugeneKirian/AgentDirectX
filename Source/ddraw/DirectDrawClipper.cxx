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
#include "DirectDrawClipper.hxx"

DirectDrawClipper::DirectDrawClipper(AgentConstructorParameters(DirectDrawClipper))
{
    AgentConstructor();
}

DirectDrawClipper::~DirectDrawClipper()
{
    AgentDestructor();
}

HRESULT DirectDrawClipper::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirectDrawClipper, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDrawClipper, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectDrawClipper::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectDrawClipper::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves a copy of the clip list that is associated with a DirectDrawClipper object.
// To select a subset of the clip list, you can pass a rectangle that clips the clip list.
HRESULT DirectDrawClipper::GetClipList(LPRECT lpRect, LPRGNDATA lpClipList, LPDWORD lpdwSize)
{
    return this->State.Self->GetClipList(lpRect, lpClipList, lpdwSize);
}

// Retrieves the window handle that was previously associated with this DirectDrawClipper object by the IDirectDrawClipper::SetHWnd method.
HRESULT DirectDrawClipper::GetHWnd(HWND FAR* lphWnd)
{
    return this->State.Self->GetHWnd(lphWnd);
}

// Initializes a DirectDrawClipper object that was created by using the CoCreateInstance COM function.
HRESULT DirectDrawClipper::Initialize(LPDIRECTDRAW lpDD, DWORD dwFlags)
{
    AttemptAccessAgentValue(DirectDraw, lpDD);

    return this->State.Self->Initialize(lpDD, dwFlags);
}

// Retrieves the status of the clip list if a window handle is associated with a DirectDrawClipper object.
HRESULT DirectDrawClipper::IsClipListChanged(BOOL FAR* lpbChanged)
{
    return this->State.Self->IsClipListChanged(lpbChanged);
}

// Sets or deletes the clip list that is used by the IDirectDrawSurface7::Blt, IDirectDrawSurface7::BltBatch,
// and IDirectDrawSurface7::UpdateOverlay methods on surfaces to which the parent DirectDrawClipper object is attached.
HRESULT DirectDrawClipper::SetClipList(LPRGNDATA lpClipList, DWORD dwFlags)
{
    return this->State.Self->SetClipList(lpClipList, dwFlags);
}

// Sets the window handle that the clipper object uses to obtain clipping information.
HRESULT DirectDrawClipper::SetHWnd(DWORD dwFlags, HWND hWnd)
{
    return this->State.Self->SetHWnd(dwFlags, hWnd);
}