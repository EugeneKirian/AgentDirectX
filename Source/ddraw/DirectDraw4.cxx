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
#include "DirectDrawSurface4.hxx"
#include "DirectDrawVideoPortContainer.hxx"

struct DirectDrawEnumModesCallbackContext
{
    LPDDENUMMODESCALLBACK2 lpEnumModesCallback;
    LPVOID lpContext;
};

struct DirectDrawEnumSurfaceCallbackContext
{
    LPDDENUMSURFACESCALLBACK2 lpEnumSurfacesCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumSurfacesCallback(LPDIRECTDRAWSURFACE4 lpDDSurface, LPDDSURFACEDESC2 lpDDSD, LPVOID lpContext)
{
    DirectDrawEnumSurfaceCallbackContext* context = (DirectDrawEnumSurfaceCallbackContext*)lpContext;

    return context->lpEnumSurfacesCallback(lpDDSurface, lpDDSD, context->lpContext);
}

static HRESULT CALLBACK EnumModesCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext)
{
    DirectDrawEnumModesCallbackContext* context = (DirectDrawEnumModesCallbackContext*)lpContext;

    return context->lpEnumModesCallback(lpDDSurfaceDesc, context->lpContext);
}

DirectDraw4::DirectDraw4(AgentConstructorParameters(DirectDraw4))
{
    AgentConstructor();
}

DirectDraw4::~DirectDraw4()
{
    AgentDestructor();
}

HRESULT DirectDraw4::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3D, riid)) { *ppvObj = ActivateAgent(Direct3D, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D2, riid)) { *ppvObj = ActivateAgent(Direct3D2, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D3, riid)) { *ppvObj = ActivateAgent(Direct3D3, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3D7, riid)) { *ppvObj = ActivateAgent(Direct3D7, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw, riid)) { *ppvObj = ActivateAgent(DirectDraw, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw2, riid)) { *ppvObj = ActivateAgent(DirectDraw2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw4, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDraw4, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDraw7, riid)) { *ppvObj = ActivateAgent(DirectDraw7, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawVideoPortContainer, riid)) { *ppvObj = ActivateAgent(DirectDrawVideoPortContainer, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG DirectDraw4::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectDraw4::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// This method is not currently implemented.
HRESULT DirectDraw4::Compact()
{
    return this->State.Self->Compact();
}

// Creates a DirectDrawClipper object.
HRESULT DirectDraw4::CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR* lplpDDClipper, IUnknown FAR* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateClipper(dwFlags, lplpDDClipper, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDClipper = ActivateAgentDelegate(DirectDrawClipper, *lplpDDClipper); }

    return result;
}

// Creates a DirectDrawPalette object for this DirectDraw object.
HRESULT DirectDraw4::CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE FAR* lplpDDPalette, IUnknown FAR* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreatePalette(dwFlags, lpColorTable, lplpDDPalette, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDPalette = ActivateAgentDelegate(DirectDrawPalette, *lplpDDPalette); }

    return result;
}

// Creates a DirectDrawSurface object for this DirectDraw object.
HRESULT DirectDraw4::CreateSurface(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPDIRECTDRAWSURFACE4 FAR* lplpDDSurface, IUnknown FAR* pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateSurface(lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDSurface = ActivateAgentDelegate(DirectDrawSurface4, *lplpDDSurface); }

    return result;
}

// Duplicates a DirectDrawSurface object.
HRESULT DirectDraw4::DuplicateSurface(LPDIRECTDRAWSURFACE4 lpDDSurface, LPDIRECTDRAWSURFACE4 FAR* lplpDupDDSurface)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDSurface);

    CONST HRESULT result = this->State.Self->DuplicateSurface(lpDDSurface, lplpDupDDSurface);

    if (SUCCEEDED(result)) { *lplpDupDDSurface = ActivateAgentDelegate(DirectDrawSurface4, *lplpDupDDSurface); }

    return result;
}

// Enumerates all the display modes that the hardware exposes through the DirectDraw object
// and that are compatible with a provided surface description.
HRESULT DirectDraw4::EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK2 lpEnumModesCallback)
{
    if (lpEnumModesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumModesCallbackContext context;

    context.lpEnumModesCallback = lpEnumModesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumDisplayModes(dwFlags, lpDDSurfaceDesc, &context, EnumModesCallback);
}

// Enumerates all the existing or possible surfaces that meet the specified surface description.
HRESULT DirectDraw4::EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC2 lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK2 lpEnumSurfacesCallback)
{
    if (lpEnumSurfacesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumSurfaceCallbackContext context;

    context.lpEnumSurfacesCallback = lpEnumSurfacesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumSurfaces(dwFlags, lpDDSD, &context, EnumSurfacesCallback);
}

// Makes the surface that the GDI writes to the primary surface.
HRESULT DirectDraw4::FlipToGDISurface()
{
    return this->State.Self->FlipToGDISurface();
}

// Retrieves the capabilities of the device driver for the hardware and the hardware emulation layer (HEL).
HRESULT DirectDraw4::GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps)
{
    return this->State.Self->GetCaps(lpDDDriverCaps, lpDDHELCaps);
}

// Retrieves the current display mode.
HRESULT DirectDraw4::GetDisplayMode(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    return this->State.Self->GetDisplayMode(lpDDSurfaceDesc);
}

// Retrieves the four-character codes (FOURCC) that are supported by the DirectDraw object.
// This method can also retrieve the number of codes that are supported.
HRESULT DirectDraw4::GetFourCCCodes(LPDWORD lpdwNumCodes, LPDWORD lpdwCodes)
{
    return this->State.Self->GetFourCCCodes(lpdwNumCodes, lpdwCodes);
}

// Retrieves the DirectDrawSurface object that currently represents the surface memory that GDI is treating as the primary surface.
HRESULT DirectDraw4::GetGDISurface(LPDIRECTDRAWSURFACE4 FAR* lplpGDIDDSSurface)
{
    CONST HRESULT result = this->State.Self->GetGDISurface(lplpGDIDDSSurface);

    if (SUCCEEDED(result)) { *lplpGDIDDSSurface = ActivateAgent(DirectDrawSurface4, *lplpGDIDDSSurface); }

    return result;
}

// Retrieves the frequency of the monitor that the DirectDraw object controls.
HRESULT DirectDraw4::GetMonitorFrequency(LPDWORD lpdwFrequency)
{
    return this->State.Self->GetMonitorFrequency(lpdwFrequency);
}

// Retrieves the scan line that is currently being drawn on the monitor.
HRESULT DirectDraw4::GetScanLine(LPDWORD lpdwScanLine)
{
    return this->State.Self->GetScanLine(lpdwScanLine);
}

// Retrieves the status of the vertical blank.
HRESULT DirectDraw4::GetVerticalBlankStatus(LPBOOL lpbIsInVB)
{
    return this->State.Self->GetVerticalBlankStatus(lpbIsInVB);
}

// Initializes a DirectDraw object that was created by using the CoCreateInstance COM function.
HRESULT DirectDraw4::Initialize(GUID FAR* lpGUID)
{
    return this->State.Self->Initialize(lpGUID);
}

// Resets the mode of the display device hardware for the primary surface to what it was before
// the IDirectDraw::SetDisplayMode method was called. Exclusive-level access is required to use this method.
HRESULT DirectDraw4::RestoreDisplayMode()
{
    return this->State.Self->RestoreDisplayMode();
}

// Determines the top-level behavior of the application.
HRESULT DirectDraw4::SetCooperativeLevel(HWND hWnd, DWORD dwFlags)
{
    return this->State.Self->SetCooperativeLevel(hWnd, dwFlags);
}

// Sets the mode of the display-device hardware.
HRESULT DirectDraw4::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags)
{
    return this->State.Self->SetDisplayMode(dwWidth, dwHeight, dwBPP, dwRefreshRate, dwFlags);
}

// Helps the application synchronize itself with the vertical-blank interval.
HRESULT DirectDraw4::WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent)
{
    return this->State.Self->WaitForVerticalBlank(dwFlags, hEvent);
}

// Retrieves the total amount of display memory available and the amount of display memory currently free for a given type of surface.
HRESULT DirectDraw4::GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps, LPDWORD lpdwTotal, LPDWORD lpdwFree)
{
    return this->State.Self->GetAvailableVidMem(lpDDSCaps, lpdwTotal, lpdwFree);
}

// Retrieves the IDirectDrawSurface4 interface for a surface, based on its GDI device context handle.
HRESULT DirectDraw4::GetSurfaceFromDC(HDC hDC, LPDIRECTDRAWSURFACE4* lpDDS)
{
    CONST HRESULT result = this->State.Self->GetSurfaceFromDC(hDC, lpDDS);

    if (SUCCEEDED(result)) { *lpDDS = ActivateAgent(DirectDrawSurface4, *lpDDS); }

    return result;
}

// Restores all the surfaces that were created for the DirectDraw object, in the order that they were created.
HRESULT DirectDraw4::RestoreAllSurfaces()
{
    return this->State.Self->RestoreAllSurfaces();
}

// Reports the current cooperative-level status of the DirectDraw device for a windowed or full-screen application.
HRESULT DirectDraw4::TestCooperativeLevel()
{
    return this->State.Self->TestCooperativeLevel();
}

// Obtains information about the device driver. This method can be used, with caution,
// to recognize specific hardware installations to implement workarounds for poor driver or chipset behavior.
HRESULT DirectDraw4::GetDeviceIdentifier(LPDDDEVICEIDENTIFIER lpDDDI, DWORD dwFlags)
{
    return this->State.Self->GetDeviceIdentifier(lpDDDI, dwFlags);
}