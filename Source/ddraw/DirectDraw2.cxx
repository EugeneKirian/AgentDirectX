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
#include "Direct3D2.hxx"
#include "Direct3D3.hxx"
#include "Direct3D7.hxx"
#include "DirectDraw.hxx"
#include "DirectDraw2.hxx"
#include "DirectDraw4.hxx"
#include "DirectDraw7.hxx"
#include "DirectDrawClipper.hxx"
#include "DirectDrawPalette.hxx"
#include "DirectDrawSurface.hxx"
#include "DirectDrawVideoPortContainer.hxx"

struct DirectDrawEnumModesCallbackContext
{
    LPDDENUMMODESCALLBACK lpEnumModesCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumModesCallback(LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext)
{
    DirectDrawEnumModesCallbackContext* context = (DirectDrawEnumModesCallbackContext*)lpContext;

    return context->lpEnumModesCallback(lpDDSurfaceDesc, context->lpContext);
}

struct DirectDrawEnumSurfaceCallbackContext
{
    LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumSurfacesCallback(LPDIRECTDRAWSURFACE lpDDSurface, LPDDSURFACEDESC lpDDSD, LPVOID lpContext)
{
    DirectDrawEnumSurfaceCallbackContext* context = (DirectDrawEnumSurfaceCallbackContext*)lpContext;

    return context->lpEnumSurfacesCallback(lpDDSurface, lpDDSD, context->lpContext);
}

DirectDraw2::DirectDraw2(AgentConstructorParameters(DirectDraw2))
{
    AgentConstructor();
}

DirectDraw2::~DirectDraw2()
{
    AgentDestructor();
}

HRESULT DirectDraw2::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3D, riid)) { *ppvObj = ActivateAgent(Direct3D, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D2, riid)) { *ppvObj = ActivateAgent(Direct3D2, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D3, riid)) { *ppvObj = ActivateAgent(Direct3D3, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D7, riid)) { *ppvObj = ActivateAgent(Direct3D7, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDraw, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw2, riid)) { *ppvObj = ActivateAgent(DirectDraw2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw4, riid)) { *ppvObj = ActivateAgent(DirectDraw4, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw7, riid)) { *ppvObj = ActivateAgent(DirectDraw7, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawVideoPortContainer, riid)) { *ppvObj = ActivateAgent(DirectDrawVideoPortContainer, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectDraw2::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectDraw2::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// This method is not currently implemented.
HRESULT DirectDraw2::Compact()
{
    return this->State.Self->Compact();
}

// Creates a DirectDrawClipper object.
HRESULT DirectDraw2::CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR* lplpDDClipper, IUnknown FAR* pUnkOuter)
{
    const HRESULT result = this->State.Self->CreateClipper(dwFlags, lplpDDClipper, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDClipper = ActivateAgentDelegate(DirectDrawClipper, *lplpDDClipper); }

    return result;
}

// Creates a DirectDrawPalette object for this DirectDraw object.
HRESULT DirectDraw2::CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE FAR* lplpDDPalette, IUnknown FAR* pUnkOuter)
{
    const HRESULT result = this->State.Self->CreatePalette(dwFlags, lpColorTable, lplpDDPalette, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDPalette = ActivateAgentDelegate(DirectDrawPalette, *lplpDDPalette); }

    return result;
}

// Creates a DirectDrawSurface object for this DirectDraw object.
HRESULT DirectDraw2::CreateSurface(LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE FAR* lplpDDSurface, IUnknown FAR* pUnkOuter)
{
    const HRESULT result = this->State.Self->CreateSurface(lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDSurface = ActivateAgentDelegate(DirectDrawSurface, *lplpDDSurface); }

    return result;
}

// Duplicates a DirectDrawSurface object.
HRESULT DirectDraw2::DuplicateSurface(LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE FAR* lplpDupDDSurface)
{
    AttemptAccessAgentValue(DirectDrawSurface, lpDDSurface);

    const HRESULT result = this->State.Self->DuplicateSurface(lpDDSurface, lplpDupDDSurface);

    if (SUCCEEDED(result)) { *lplpDupDDSurface = ActivateAgentDelegate(DirectDrawSurface, *lplpDupDDSurface); }

    return result;
}

// Enumerates all the display modes that the hardware exposes through the DirectDraw object
// and that are compatible with a provided surface description.
HRESULT DirectDraw2::EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModesCallback)
{
    if (lpEnumModesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumModesCallbackContext context;

    context.lpEnumModesCallback = lpEnumModesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumDisplayModes(dwFlags, lpDDSurfaceDesc, &context, EnumModesCallback);
}

// Enumerates all the existing or possible surfaces that meet the specified surface description.
HRESULT DirectDraw2::EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback)
{
    if (lpEnumSurfacesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumSurfaceCallbackContext context;

    context.lpEnumSurfacesCallback = lpEnumSurfacesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumSurfaces(dwFlags, lpDDSD, &context, EnumSurfacesCallback);
}

// Makes the surface that the GDI writes to the primary surface.
HRESULT DirectDraw2::FlipToGDISurface()
{
    return this->State.Self->FlipToGDISurface();
}

// Retrieves the capabilities of the device driver for the hardware and the hardware emulation layer (HEL).
HRESULT DirectDraw2::GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps)
{
    return this->State.Self->GetCaps(lpDDDriverCaps, lpDDHELCaps);
}

// Retrieves the current display mode.
HRESULT DirectDraw2::GetDisplayMode(LPDDSURFACEDESC lpDDSurfaceDesc)
{
    return this->State.Self->GetDisplayMode(lpDDSurfaceDesc);
}

// Retrieves the four-character codes (FOURCC) that are supported by the DirectDraw object.
// This method can also retrieve the number of codes that are supported.
HRESULT DirectDraw2::GetFourCCCodes(LPDWORD lpdwNumCodes, LPDWORD lpdwCodes)
{
    return this->State.Self->GetFourCCCodes(lpdwNumCodes, lpdwCodes);
}

// Retrieves the DirectDrawSurface object that currently represents the surface memory that GDI is treating as the primary surface.
HRESULT DirectDraw2::GetGDISurface(LPDIRECTDRAWSURFACE FAR* lplpGDIDDSSurface)
{
    const HRESULT result = this->State.Self->GetGDISurface(lplpGDIDDSSurface);

    if (SUCCEEDED(result)) { *lplpGDIDDSSurface = ActivateAgentDelegate(DirectDrawSurface, *lplpGDIDDSSurface); }

    return result;
}

// Retrieves the frequency of the monitor that the DirectDraw object controls.
HRESULT DirectDraw2::GetMonitorFrequency(LPDWORD lpdwFrequency)
{
    return this->State.Self->GetMonitorFrequency(lpdwFrequency);
}

// Retrieves the scan line that is currently being drawn on the monitor.
HRESULT DirectDraw2::GetScanLine(LPDWORD lpdwScanLine)
{
    return this->State.Self->GetScanLine(lpdwScanLine);
}

// Retrieves the status of the vertical blank.
HRESULT DirectDraw2::GetVerticalBlankStatus(LPBOOL lpbIsInVB)
{
    return this->State.Self->GetVerticalBlankStatus(lpbIsInVB);
}

// Initializes a DirectDraw object that was created by using the CoCreateInstance COM function.
HRESULT DirectDraw2::Initialize(GUID FAR* lpGUID)
{
    return this->State.Self->Initialize(lpGUID);
}

// Resets the mode of the display device hardware for the primary surface to what it was before
// the IDirectDraw::SetDisplayMode method was called. Exclusive-level access is required to use this method.
HRESULT DirectDraw2::RestoreDisplayMode()
{
    return this->State.Self->RestoreDisplayMode();
}

// Determines the top-level behavior of the application.
HRESULT DirectDraw2::SetCooperativeLevel(HWND hWnd, DWORD dwFlags)
{
    return this->State.Self->SetCooperativeLevel(hWnd, dwFlags);
}

// Sets the mode of the display-device hardware.
HRESULT DirectDraw2::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags)
{
    return this->State.Self->SetDisplayMode(dwWidth, dwHeight, dwBPP, dwRefreshRate, dwFlags);
}

// Helps the application synchronize itself with the vertical-blank interval.
HRESULT DirectDraw2::WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent)
{
    return this->State.Self->WaitForVerticalBlank(dwFlags, hEvent);
}

// Retrieves the total amount of display memory available and the amount of display memory currently free for a given type of surface.
HRESULT DirectDraw2::GetAvailableVidMem(LPDDSCAPS lpDDSCaps, LPDWORD lpdwTotal, LPDWORD lpdwFree)
{
    return this->State.Self->GetAvailableVidMem(lpDDSCaps, lpdwTotal, lpdwFree);
}