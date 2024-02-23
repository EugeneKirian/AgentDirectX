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

#include "Direct3D.hxx"
#include "Direct3DLight.hxx"
#include "Direct3DViewport.hxx"
#include "Direct3DViewport2.hxx"
#include "Direct3DViewport3.hxx"
#include "DirectDrawSurface.hxx"

Direct3DViewport2::Direct3DViewport2(AgentConstructorParameters(Direct3DViewport2))
{
    AgentConstructor();
}

Direct3DViewport2::~Direct3DViewport2()
{
    AgentDestructor();
}

HRESULT Direct3DViewport2::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DViewport, riid)) { *ppvObj = ActivateAgent(Direct3DViewport, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DViewport2, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3DViewport2, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DViewport3, riid)) { *ppvObj = ActivateAgent(Direct3DViewport3, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DViewport2::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DViewport2::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// This method is not currently implemented.
HRESULT Direct3DViewport2::Initialize(LPDIRECT3D lpDirect3D)
{
    AttemptAccessAgentValue(Direct3D, lpDirect3D);

    return this->State.Self->Initialize(lpDirect3D);
}

// Retrieves the viewport registers of the viewport.
// This method is provided for backward compatibility.
// It has been superseded by the GetViewport2 method.
HRESULT Direct3DViewport2::GetViewport(LPD3DVIEWPORT lpData)
{
    return this->State.Self->GetViewport(lpData);
}

// Sets the viewport registers of the viewport.
// This method is provided for backward compatibility.
// It has been superseded by the SetViewport2 method.
HRESULT Direct3DViewport2::SetViewport(LPD3DVIEWPORT lpData)
{
    return this->State.Self->SetViewport(lpData);
}

// Transforms a set of vertices by the transformation matrix.
HRESULT Direct3DViewport2::TransformVertices(DWORD dwVertexCount, LPD3DTRANSFORMDATA lpData, DWORD dwFlags, LPDWORD lpOffscreen)
{
    return this->State.Self->TransformVertices(dwVertexCount, lpData, dwFlags, lpOffscreen);
}

// This method is not currently implemented.
HRESULT Direct3DViewport2::LightElements(DWORD dwElementCount, LPD3DLIGHTDATA lpData)
{
    return this->State.Self->LightElements(dwElementCount, lpData);
}

// Sets the background material associated with the viewport.
HRESULT Direct3DViewport2::SetBackground(D3DMATERIALHANDLE hMat)
{
    return this->State.Self->SetBackground(hMat);
}

// Retrieves the handle to a material that represents the current background associated with the viewport.
HRESULT Direct3DViewport2::GetBackground(LPD3DMATERIALHANDLE lphMat, LPBOOL lpValid)
{
    return this->State.Self->GetBackground(lphMat, lpValid);
}

// Sets the background-depth field for the viewport.
HRESULT Direct3DViewport2::SetBackgroundDepth(LPDIRECTDRAWSURFACE lpDDSurface)
{
    AttemptAccessAgentValue(DirectDrawSurface, lpDDSurface);

    return this->State.Self->SetBackgroundDepth(lpDDSurface);
}

// Retrieves a DirectDraw surface that represents the current background-depth field associated with the viewport.
HRESULT Direct3DViewport2::GetBackgroundDepth(LPDIRECTDRAWSURFACE* lplpDDSurface, LPBOOL lpValid)
{
    CONST HRESULT result = this->State.Self->GetBackgroundDepth(lplpDDSurface, lpValid);

    if (SUCCEEDED(result)) { *lplpDDSurface = ActivateAgentDelegate(DirectDrawSurface, *lplpDDSurface); }

    return result;
}

// Clears the viewport or a set of rectangles in the viewport to the current background material.
HRESULT Direct3DViewport2::Clear(DWORD dwCount, LPD3DRECT lpRects, DWORD dwFlags)
{
    return this->State.Self->Clear(dwCount, lpRects, dwFlags);
}

// Adds the specified light to the list of Direct3DLight objects associated with this viewport
// and increments the reference count of the light object.
HRESULT Direct3DViewport2::AddLight(LPDIRECT3DLIGHT lpDirect3DLight)
{
    AttemptAccessAgentValue(Direct3DLight, lpDirect3DLight);

    return this->State.Self->AddLight(lpDirect3DLight);
}

// Removes the specified light from the list of Direct3DLight objects associated with this viewport,
// and decrements the reference count for the light object.
HRESULT Direct3DViewport2::DeleteLight(LPDIRECT3DLIGHT lpDirect3DLight)
{
    AttemptAccessAgentValue(Direct3DLight, lpDirect3DLight);

    return this->State.Self->DeleteLight(lpDirect3DLight);
}

// Enumerates the Direct3DLight objects associated with the viewport.
HRESULT Direct3DViewport2::NextLight(LPDIRECT3DLIGHT lpDirect3DLight, LPDIRECT3DLIGHT* lplpDirect3DLight, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DLight, lpDirect3DLight);

    CONST HRESULT result = this->State.Self->NextLight(lpDirect3DLight, lplpDirect3DLight, dwFlags);

    if (SUCCEEDED(result)) { *lplpDirect3DLight = ActivateAgentDelegate(Direct3DLight, *lplpDirect3DLight); }

    return result;
}

// Retrieves the viewport registers of the viewport.
HRESULT Direct3DViewport2::GetViewport2(LPD3DVIEWPORT2 lpData)
{
    return this->State.Self->GetViewport2(lpData);
}

// Sets the viewport registers of the viewport.
HRESULT Direct3DViewport2::SetViewport2(LPD3DVIEWPORT2 lpData)
{
    return this->State.Self->SetViewport2(lpData);
}