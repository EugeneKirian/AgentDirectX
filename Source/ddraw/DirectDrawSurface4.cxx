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

#include "Direct3DDevice.hxx"
#include "Direct3DTexture.hxx"
#include "Direct3DTexture2.hxx"
#include "DirectDraw.hxx"
#include "DirectDraw4.hxx"
#include "DirectDrawClipper.hxx"
#include "DirectDrawColorControl.hxx"
#include "DirectDrawGammaControl.hxx"
#include "DirectDrawPalette.hxx"
#include "DirectDrawSurface.hxx"
#include "DirectDrawSurface2.hxx"
#include "DirectDrawSurface3.hxx"
#include "DirectDrawSurface4.hxx"
#include "DirectDrawSurface7.hxx"

struct EnumAttachedSurfacesCallbackContext
{
    LPDDENUMSURFACESCALLBACK2 lpEnumSurfacesCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumAttachedSurfacesCallback(LPDIRECTDRAWSURFACE4 lpDDSurface, LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext)
{
    EnumAttachedSurfacesCallbackContext* context = (EnumAttachedSurfacesCallbackContext*)lpContext;

    return context->lpEnumSurfacesCallback(lpDDSurface, lpDDSurfaceDesc, context->lpContext);
}

struct EnumOverlayZOrdersCallbackContext
{
    LPDDENUMSURFACESCALLBACK2 lpfnCallback;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumOverlayZOrdersCallback(LPDIRECTDRAWSURFACE4 lpDDSurface, LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext)
{
    EnumOverlayZOrdersCallbackContext* context = (EnumOverlayZOrdersCallbackContext*)lpContext;

    return context->lpfnCallback(lpDDSurface, lpDDSurfaceDesc, context->lpContext);
}

DirectDrawSurface4::DirectDrawSurface4(AgentConstructorParameters(DirectDrawSurface4))
{
    AgentConstructor();
}

DirectDrawSurface4::~DirectDrawSurface4()
{
    AgentDestructor();
}

HRESULT DirectDrawSurface4::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DTexture, riid)) { *ppvObj = ActivateAgent(Direct3DTexture, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DTexture2, riid)) { *ppvObj = ActivateAgent(Direct3DTexture2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawColorControl, riid)) { *ppvObj = ActivateAgent(DirectDrawColorControl, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawGammaControl, riid)) { *ppvObj = ActivateAgent(DirectDrawGammaControl, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface2, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface3, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface3, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface4, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface4, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface7, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface7, *ppvObj); }
            else { *ppvObj = ActivateAgent(Direct3DDevice, *ppvObj); } // NOTE: Surface Caps must have DDSCAPS_3DDEVICE flag set.
        }
    }

    return result;
}

ULONG DirectDrawSurface4::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG DirectDrawSurface4::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Attaches the specified z-buffer surface to this surface.
HRESULT DirectDrawSurface4::AddAttachedSurface(LPDIRECTDRAWSURFACE4 lpDDSAttachedSurface)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDSAttachedSurface);

    return this->State.Self->AddAttachedSurface(lpDDSAttachedSurface);
}

// This method is not currently implemented.
HRESULT DirectDrawSurface4::AddOverlayDirtyRect(LPRECT lpRect)
{
    return this->State.Self->AddOverlayDirtyRect(lpRect);
}

// Performs a bit block transfer (bitblt).
// This method does not support z-buffering or alpha blending during bitblt operations.
HRESULT DirectDrawSurface4::Blt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE4 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDSrcSurface);

    if (lpDDBltFx != NULL)
    {
        if (dwFlags & DDBLT_ZBUFFERDESTOVERRIDE) { AttemptAccessAgentValue(DirectDrawSurface, lpDDBltFx->lpDDSZBufferDest); }

        if (dwFlags & DDBLT_ZBUFFERSRCOVERRIDE) { AttemptAccessAgentValue(DirectDrawSurface, lpDDBltFx->lpDDSZBufferSrc); }

        if (dwFlags & DDBLT_ALPHADESTSURFACEOVERRIDE) { AttemptAccessAgentValue(DirectDrawSurface, lpDDBltFx->lpDDSAlphaDest); }

        if (dwFlags & DDBLT_ALPHASRCSURFACEOVERRIDE) { AttemptAccessAgentValue(DirectDrawSurface, lpDDBltFx->lpDDSAlphaSrc); }

        if (dwFlags & DDBLT_PRIVATE_ALIASPATTERN) { AttemptAccessAgentValue(DirectDrawSurface, lpDDBltFx->lpDDSPattern); }
    }

    CONST HRESULT result = this->State.Self->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);

    if (lpDDBltFx != NULL)
    {
        if (dwFlags & DDBLT_ZBUFFERDESTOVERRIDE) { lpDDBltFx->lpDDSZBufferDest = ActivateAgent(DirectDrawSurface, lpDDBltFx->lpDDSZBufferDest); }

        if (dwFlags & DDBLT_ZBUFFERSRCOVERRIDE) { lpDDBltFx->lpDDSZBufferSrc = ActivateAgent(DirectDrawSurface, lpDDBltFx->lpDDSZBufferSrc); }

        if (dwFlags & DDBLT_ALPHADESTSURFACEOVERRIDE) { lpDDBltFx->lpDDSAlphaDest = ActivateAgent(DirectDrawSurface, lpDDBltFx->lpDDSAlphaDest); }

        if (dwFlags & DDBLT_ALPHASRCSURFACEOVERRIDE) { lpDDBltFx->lpDDSAlphaSrc = ActivateAgent(DirectDrawSurface, lpDDBltFx->lpDDSAlphaSrc); }

        if (dwFlags & DDBLT_PRIVATE_ALIASPATTERN) { lpDDBltFx->lpDDSPattern = ActivateAgent(DirectDrawSurface, lpDDBltFx->lpDDSPattern); }
    }

    return result;
}

// This method is not currently implemented.
HRESULT DirectDrawSurface4::BltBatch(LPDDBLTBATCH lpDDBltBatch, DWORD dwCount, DWORD dwFlags)
{
    if (lpDDBltBatch != NULL) { AttemptAccessAgentValue(DirectDrawSurface, lpDDBltBatch->lpDDSSrc); }

    CONST HRESULT result = this->State.Self->BltBatch(lpDDBltBatch, dwCount, dwFlags);

    if (lpDDBltBatch != NULL) { lpDDBltBatch->lpDDSSrc = ActivateAgent(DirectDrawSurface, lpDDBltBatch->lpDDSSrc); }

    return result;
}

// Performs a source copy bitblt or transparent bitblt by using a source color key or destination color key.
HRESULT DirectDrawSurface4::BltFast(DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE4 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwTrans)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDSrcSurface);

    return this->State.Self->BltFast(dwX, dwY, lpDDSrcSurface, lpSrcRect, dwTrans);
}

// Detaches one or more attached surfaces.
HRESULT DirectDrawSurface4::DeleteAttachedSurface(DWORD dwFlags, LPDIRECTDRAWSURFACE4 lpDDSAttachedSurface)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDSAttachedSurface);

    return this->State.Self->DeleteAttachedSurface(dwFlags, lpDDSAttachedSurface);
}

// Enumerates all the surfaces that are attached to this surface.
HRESULT DirectDrawSurface4::EnumAttachedSurfaces(LPVOID lpContext, LPDDENUMSURFACESCALLBACK2 lpEnumSurfacesCallback)
{
    if (lpEnumSurfacesCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumAttachedSurfacesCallbackContext context;

    context.lpEnumSurfacesCallback = lpEnumSurfacesCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumAttachedSurfaces(&context, EnumAttachedSurfacesCallback);
}

// Enumerates the overlay surfaces on the specified destination.
// You can enumerate the overlays in front-to-back or back-to-front order.
HRESULT DirectDrawSurface4::EnumOverlayZOrders(DWORD dwFlags, LPVOID lpContext, LPDDENUMSURFACESCALLBACK2 lpfnCallback)
{
    if (lpfnCallback == NULL) { return DDERR_INVALIDPARAMS; }

    EnumOverlayZOrdersCallbackContext context;

    context.lpfnCallback = lpfnCallback;
    context.lpContext = lpContext;

    return this->State.Self->EnumOverlayZOrders(dwFlags, &context, EnumOverlayZOrdersCallback);
}

// Makes the surface memory that is associated with the DDSCAPS_BACKBUFFER surface become associated with the front-buffer surface.
HRESULT DirectDrawSurface4::Flip(LPDIRECTDRAWSURFACE4 lpDDSurfaceTargetOverride, DWORD dwFlags)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDSurfaceTargetOverride);

    return this->State.Self->Flip(lpDDSurfaceTargetOverride, dwFlags);
}

// Obtains the attached surface that has the specified capabilities,
// and increments the reference count of the retrieved interface.
HRESULT DirectDrawSurface4::GetAttachedSurface(LPDDSCAPS2 lpDDSCaps, LPDIRECTDRAWSURFACE4 FAR* lplpDDAttachedSurface)
{
    CONST HRESULT result = this->State.Self->GetAttachedSurface(lpDDSCaps, lplpDDAttachedSurface);

    if (SUCCEEDED(result)) { *lplpDDAttachedSurface = ActivateAgentDelegate(DirectDrawSurface4, *lplpDDAttachedSurface); }

    return result;
}

// Obtains status about a bit block transfer (bitblt) operation.
HRESULT DirectDrawSurface4::GetBltStatus(DWORD dwFlags)
{
    return this->State.Self->GetBltStatus(dwFlags);
}

// Retrieves the capabilities of this surface.
// These capabilities are not necessarily related to the capabilities of the display device.
HRESULT DirectDrawSurface4::GetCaps(LPDDSCAPS2 lpDDSCaps)
{
    return this->State.Self->GetCaps(lpDDSCaps);
}

// Retrieves the DirectDrawClipper object that is associated with this surface,
// and increments the reference count of the returned clipper.
HRESULT DirectDrawSurface4::GetClipper(LPDIRECTDRAWCLIPPER FAR* lplpDDClipper)
{
    CONST HRESULT result = this->State.Self->GetClipper(lplpDDClipper);

    if (SUCCEEDED(result)) { *lplpDDClipper = ActivateAgentDelegate(DirectDrawClipper, *lplpDDClipper); }

    return result;
}

// Retrieves the color key value for this surface.
HRESULT DirectDrawSurface4::GetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
    return this->State.Self->GetColorKey(dwFlags, lpDDColorKey);
}

// Creates a GDI-compatible handle of a device context for this surface.
HRESULT DirectDrawSurface4::GetDC(HDC FAR* lphDC)
{
    return this->State.Self->GetDC(lphDC);
}

// Retrieves status about whether this surface has finished its flipping process.
HRESULT DirectDrawSurface4::GetFlipStatus(DWORD dwFlags)
{
    return this->State.Self->GetFlipStatus(dwFlags);
}

// Retrieves the display coordinates of this surface.
// This method is used on a visible, active overlay surface
// (that is, a surface that has the DDSCAPS_OVERLAY flag set).
HRESULT DirectDrawSurface4::GetOverlayPosition(LPLONG lplX, LPLONG lplY)
{
    return this->State.Self->GetOverlayPosition(lplX, lplY);
}

// Retrieves the DirectDrawPalette object that is associated with this surface,
// and increments the reference count of the returned palette.
HRESULT DirectDrawSurface4::GetPalette(LPDIRECTDRAWPALETTE FAR* lplpDDPalette)
{
    CONST HRESULT result = this->State.Self->GetPalette(lplpDDPalette);

    if (SUCCEEDED(result)) { *lplpDDPalette = ActivateAgentDelegate(DirectDrawPalette, *lplpDDPalette); }

    return result;
}

// Retrieves the color and pixel format of this surface.
HRESULT DirectDrawSurface4::GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat)
{
    return this->State.Self->GetPixelFormat(lpDDPixelFormat);
}

// Retrieves a description of this surface in its current condition.
HRESULT DirectDrawSurface4::GetSurfaceDesc(LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    return this->State.Self->GetSurfaceDesc(lpDDSurfaceDesc);
}

// Initializes a DirectDrawSurface4 object.
HRESULT DirectDrawSurface4::Initialize(LPDIRECTDRAW lpDD, LPDDSURFACEDESC2 lpDDSurfaceDesc)
{
    AttemptAccessAgentValue(DirectDraw, lpDD);

    return this->State.Self->Initialize(lpDD, lpDDSurfaceDesc);
}

// Determines whether the surface memory that is associated with a DirectDrawSurface4 object has been freed.
HRESULT DirectDrawSurface4::IsLost()
{
    return this->State.Self->IsLost();
}

// Obtains a pointer to the surface memory.
HRESULT DirectDrawSurface4::Lock(LPRECT lpDestRect, LPDDSURFACEDESC2 lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent)
{
    return this->State.Self->Lock(lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);
}

// Releases the handle of a device context that was previously obtained by using the IDirectDrawSurface4::GetDC method.
HRESULT DirectDrawSurface4::ReleaseDC(HDC hDC)
{
    return this->State.Self->ReleaseDC(hDC);
}

// Restores a surface that has been lost.
// This occurs when the surface memory that is associated with the DirectDrawSurface4 object has been freed.
HRESULT DirectDrawSurface4::Restore()
{
    return this->State.Self->Restore();
}

// Attaches a clipper object to, or deletes one from, this surface.
HRESULT DirectDrawSurface4::SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper)
{
    AttemptAccessAgentValue(DirectDrawClipper, lpDDClipper);

    return this->State.Self->SetClipper(lpDDClipper);
}

// Sets the color key value for the DirectDrawSurface4 object if the hardware supports color keys on a per-surface basis.
HRESULT DirectDrawSurface4::SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
    return this->State.Self->SetColorKey(dwFlags, lpDDColorKey);
}

// Changes the display coordinates of an overlay surface.
HRESULT DirectDrawSurface4::SetOverlayPosition(LONG lX, LONG lY)
{
    return this->State.Self->SetOverlayPosition(lX, lY);
}

// Attaches a palette object to (or detaches one from) a surface.
// The surface uses this palette for all subsequent operations.
// The palette change takes place immediately, without regard to refresh timing.
HRESULT DirectDrawSurface4::SetPalette(LPDIRECTDRAWPALETTE lpDDPalette)
{
    AttemptAccessAgentValue(DirectDrawPalette, lpDDPalette);

    return this->State.Self->SetPalette(lpDDPalette);
}

// Notifies DirectDraw that the direct surface manipulations are complete.
HRESULT DirectDrawSurface4::Unlock(LPRECT lpRect)
{
    return this->State.Self->Unlock(lpRect);
}

// Repositions or modifies the visual attributes of an overlay surface.
// These surfaces must have the DDSCAPS_OVERLAY flag set.
HRESULT DirectDrawSurface4::UpdateOverlay(LPRECT lpSrcRect, LPDIRECTDRAWSURFACE4 lpDDDestSurface, LPRECT lpDestRect, DWORD dwFlags, LPDDOVERLAYFX lpDDOverlayFx)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDDestSurface);

    if (lpDDOverlayFx != NULL)
    {
        if (dwFlags & DDOVER_ALPHADESTSURFACEOVERRIDE) { AttemptAccessAgentValue(DirectDrawSurface, lpDDOverlayFx->lpDDSAlphaDest); }

        if (dwFlags & DDOVER_ALPHASRCSURFACEOVERRIDE) { AttemptAccessAgentValue(DirectDrawSurface, lpDDOverlayFx->lpDDSAlphaSrc); }
    }

    CONST HRESULT result = this->State.Self->UpdateOverlay(lpSrcRect, lpDDDestSurface, lpDestRect, dwFlags, lpDDOverlayFx);

    if (lpDDOverlayFx != NULL)
    {
        if (dwFlags & DDOVER_ALPHADESTSURFACEOVERRIDE) { lpDDOverlayFx->lpDDSAlphaDest = ActivateAgent(DirectDrawSurface, lpDDOverlayFx->lpDDSAlphaDest); }

        if (dwFlags & DDOVER_ALPHASRCSURFACEOVERRIDE) { lpDDOverlayFx->lpDDSAlphaSrc = ActivateAgent(DirectDrawSurface, lpDDOverlayFx->lpDDSAlphaSrc); }
    }

    return result;
}

// This method is not currently implemented.
HRESULT DirectDrawSurface4::UpdateOverlayDisplay(DWORD dwFlags)
{
    return this->State.Self->UpdateOverlayDisplay(dwFlags);
}

// Sets the z-order of an overlay.
HRESULT DirectDrawSurface4::UpdateOverlayZOrder(DWORD dwFlags, LPDIRECTDRAWSURFACE4 lpDDSReference)
{
    AttemptAccessAgentValue(DirectDrawSurface4, lpDDSReference);

    return this->State.Self->UpdateOverlayZOrder(dwFlags, lpDDSReference);
}

// Retrieves an interface to the DirectDraw object that was used to create this surface.
HRESULT DirectDrawSurface4::GetDDInterface(LPVOID FAR* lplpDD)
{
    CONST HRESULT result = this->State.Self->GetDDInterface(lplpDD);

    if (SUCCEEDED(result)) { *lplpDD = ActivateAgentDelegate(DirectDraw4, *lplpDD); }

    return result;
}

// Prevents a system-memory surface from being paged out while a bit block transfer (bitblt) operation
// that uses direct memory access (DMA) transfers to or from system memory is in progress.
HRESULT DirectDrawSurface4::PageLock(DWORD dwFlags)
{
    return this->State.Self->PageLock(dwFlags);
}

// Unlocks a system-memory surface, which then allows it to be paged out.
HRESULT DirectDrawSurface4::PageUnlock(DWORD dwFlags)
{
    return this->State.Self->PageUnlock(dwFlags);
}

// Sets the characteristics of an existing surface.
HRESULT DirectDrawSurface4::SetSurfaceDesc(LPDDSURFACEDESC2 lpDDSurfaceDesc, DWORD dwFlags)
{
    return this->State.Self->SetSurfaceDesc(lpDDSurfaceDesc, dwFlags);
}

// Associates data with the surface that is intended for use by the application, not by DirectDraw.
// Data is passed by value, and multiple sets of data can be associated with a single surface.
HRESULT DirectDrawSurface4::SetPrivateData(REFGUID riid, LPVOID lpData, DWORD dwDataSize, DWORD dwFlags)
{
    return this->State.Self->SetPrivateData(riid, lpData, dwDataSize, dwFlags);
}

// Copies the private data that is associated with this surface to a provided buffer.
HRESULT DirectDrawSurface4::GetPrivateData(REFGUID riid, LPVOID lpBuffer, LPDWORD lpdwBufferSize)
{
    return this->State.Self->GetPrivateData(riid, lpBuffer, lpdwBufferSize);
}

// Frees the specified private data that is associated with this surface.
HRESULT DirectDrawSurface4::FreePrivateData(REFGUID riid)
{
    return this->State.Self->FreePrivateData(riid);
}

// Retrieves the current uniqueness value for this surface.
HRESULT DirectDrawSurface4::GetUniquenessValue(LPDWORD lpdwValue)
{
    return this->State.Self->GetUniquenessValue(lpdwValue);
}

// Manually updates the uniqueness value for this surface.
HRESULT DirectDrawSurface4::ChangeUniquenessValue()
{
    return this->State.Self->ChangeUniquenessValue();
}