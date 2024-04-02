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
#include "Direct3DDevice.hxx"
#include "Direct3DDevice2.hxx"
#include "Direct3DDevice3.hxx"
#include "Direct3DDevice7.hxx"
#include "Direct3DExecuteBuffer.hxx"
#include "Direct3DTexture.hxx"
#include "Direct3DTexture.hxx"
#include "Direct3DTexture2.hxx"
#include "Direct3DViewport.hxx"
#include "DirectDrawColorControl.hxx"
#include "DirectDrawGammaControl.hxx"
#include "DirectDrawSurface.hxx"
#include "DirectDrawSurface2.hxx"
#include "DirectDrawSurface3.hxx"
#include "DirectDrawSurface4.hxx"

struct EnumTextureFormatsCallbackContext
{
    LPD3DENUMTEXTUREFORMATSCALLBACK lpd3dEnumTextureProc;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumTextureFormatsCallback(LPDDSURFACEDESC lpDdsd, LPVOID lpContext)
{
    EnumTextureFormatsCallbackContext* context = (EnumTextureFormatsCallbackContext*)lpContext;

    return context->lpd3dEnumTextureProc(lpDdsd, context->lpContext);
}

Direct3DDevice::Direct3DDevice(AgentConstructorParameters(Direct3DDevice))
{
    AgentConstructor();
}

Direct3DDevice::~Direct3DDevice()
{
    AgentDestructor();
}

HRESULT Direct3DDevice::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DDevice, riid)) { *ppvObj = ActivateAgent(Direct3DDevice, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DDevice2, riid)) { *ppvObj = ActivateAgent(Direct3DDevice2, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DDevice3, riid)) { *ppvObj = ActivateAgent(Direct3DDevice3, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DDevice7, riid)) { *ppvObj = ActivateAgent(Direct3DDevice7, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DTexture, riid)) { *ppvObj = ActivateAgent(Direct3DTexture, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DTexture2, riid)) { *ppvObj = ActivateAgent(Direct3DTexture2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawColorControl, riid)) { *ppvObj = ActivateAgent(DirectDrawColorControl, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawGammaControl, riid)) { *ppvObj = ActivateAgent(DirectDrawGammaControl, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface2, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface2, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface3, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface3, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface4, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface4, *ppvObj); }
            else if (IsEqualIID(IID_IDirectDrawSurface7, riid)) { *ppvObj = ActivateAgent(DirectDrawSurface4, *ppvObj); }
            else { *ppvObj = ActivateAgent(Direct3DDevice, *ppvObj); } // NOTE: Surface Caps must have DDSCAPS_3DDEVICE flag set.
        }
    }

    return result;
}

ULONG Direct3DDevice::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DDevice::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// This method is not currently implemented.
HRESULT Direct3DDevice::Initialize(LPDIRECT3D lpd3d, LPGUID lpGUID, LPD3DDEVICEDESC lpd3ddvdesc)
{
    AttemptAccessAgentValue(Direct3D, lpd3d);

    return this->State.Self->Initialize(lpd3d, lpGUID, lpd3ddvdesc);
}

// Retrieves the capabilities of the Direct3D device.
HRESULT Direct3DDevice::GetCaps(LPD3DDEVICEDESC lpD3DHWDevDesc, LPD3DDEVICEDESC lpD3DHELDevDesc)
{
    return this->State.Self->GetCaps(lpD3DHWDevDesc, lpD3DHELDevDesc);
}

// Swaps two texture handles.
HRESULT Direct3DDevice::SwapTextureHandles(LPDIRECT3DTEXTURE lpD3DTex1, LPDIRECT3DTEXTURE lpD3DTex2)
{
    AttemptAccessAgentValue(Direct3DTexture, lpD3DTex1);
    AttemptAccessAgentValue(Direct3DTexture, lpD3DTex2);

    return this->State.Self->SwapTextureHandles(lpD3DTex1, lpD3DTex2);
}

// Allocates an execute buffer for a display list.
HRESULT Direct3DDevice::CreateExecuteBuffer(LPD3DEXECUTEBUFFERDESC lpDesc, LPDIRECT3DEXECUTEBUFFER* lplpDirect3DExecuteBuffer, LPUNKNOWN pUnkOuter)
{
    CONST HRESULT result = this->State.Self->CreateExecuteBuffer(lpDesc, lplpDirect3DExecuteBuffer, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDirect3DExecuteBuffer = ActivateAgentDelegate(Direct3DExecuteBuffer, *lplpDirect3DExecuteBuffer); }

    return result;
}

// Retrieves statistics about a device.
HRESULT Direct3DDevice::GetStats(LPD3DSTATS lpD3DStats)
{
    return this->State.Self->GetStats(lpD3DStats);
}

// Executes a buffer.
HRESULT Direct3DDevice::Execute(LPDIRECT3DEXECUTEBUFFER lpDirect3DExecuteBuffer, LPDIRECT3DVIEWPORT lpDirect3DViewport, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DExecuteBuffer, lpDirect3DExecuteBuffer);
    AttemptAccessAgentValue(Direct3DViewport, lpDirect3DViewport);

    return this->State.Self->Execute(lpDirect3DExecuteBuffer, lpDirect3DViewport, dwFlags);
}

// Adds the specified viewport to the list of viewport objects associated with the device
// and increments the reference count of the viewport.
HRESULT Direct3DDevice::AddViewport(LPDIRECT3DVIEWPORT lpDirect3DViewport)
{
    AttemptAccessAgentValue(Direct3DViewport, lpDirect3DViewport);

    return this->State.Self->AddViewport(lpDirect3DViewport);
}

// removes the specified viewport from the list of viewport objects associated with the device
// and decrements the reference count of the viewport.
HRESULT Direct3DDevice::DeleteViewport(LPDIRECT3DVIEWPORT lpDirect3DViewport)
{
    AttemptAccessAgentValue(Direct3DViewport, lpDirect3DViewport);

    return this->State.Self->DeleteViewport(lpDirect3DViewport);
}

// Enumerates the viewports associated with the device.
HRESULT Direct3DDevice::NextViewport(LPDIRECT3DVIEWPORT lpDirect3DViewport, LPDIRECT3DVIEWPORT* lplpAnotherViewport, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DViewport, lpDirect3DViewport);

    CONST HRESULT result = this->State.Self->NextViewport(lpDirect3DViewport, lplpAnotherViewport, dwFlags);

    if (SUCCEEDED(result)) { *lplpAnotherViewport = ActivateAgent(Direct3DViewport, *lplpAnotherViewport); }

    return result;
}

// Executes a buffer without performing any rendering,
// but returns a z-ordered list of offsets to the primitives that intersect the upper-left corner of the rectangle specified by lpRect.
HRESULT Direct3DDevice::Pick(LPDIRECT3DEXECUTEBUFFER lpDirect3DExecuteBuffer, LPDIRECT3DVIEWPORT lpDirect3DViewport, DWORD dwFlags, LPD3DRECT lpRect)
{
    AttemptAccessAgentValue(Direct3DExecuteBuffer, lpDirect3DExecuteBuffer);
    AttemptAccessAgentValue(Direct3DViewport, lpDirect3DViewport);

    return this->State.Self->Pick(lpDirect3DExecuteBuffer, lpDirect3DViewport, dwFlags, lpRect);
}

// Retrieves the pick records for a device.
HRESULT Direct3DDevice::GetPickRecords(LPDWORD lpCount, LPD3DPICKRECORD lpD3DPickRec)
{
    return this->State.Self->GetPickRecords(lpCount, lpD3DPickRec);
}

// Queries the current driver for a list of supported texture formats.
HRESULT Direct3DDevice::EnumTextureFormats(LPD3DENUMTEXTUREFORMATSCALLBACK lpd3dEnumTextureProc, LPVOID lpContext)
{
    if (lpd3dEnumTextureProc == NULL) { return DDERR_INVALIDPARAMS; }

    EnumTextureFormatsCallbackContext context;

    context.lpd3dEnumTextureProc = lpd3dEnumTextureProc;
    context.lpContext = lpContext;

    return this->State.Self->EnumTextureFormats(EnumTextureFormatsCallback, &context);
}

// Creates a matrix.
HRESULT Direct3DDevice::CreateMatrix(LPD3DMATRIXHANDLE lpD3DMatHandle)
{
    return this->CreateMatrix(lpD3DMatHandle);
}

// Applies a matrix to a matrix handle.
HRESULT Direct3DDevice::SetMatrix(D3DMATRIXHANDLE d3dMatHandle, LPD3DMATRIX lpD3DMatrix)
{
    return this->SetMatrix(d3dMatHandle, lpD3DMatrix);
}

// Retrieves a matrix from a matrix handle.
HRESULT Direct3DDevice::GetMatrix(D3DMATRIXHANDLE d3dMatHandle, LPD3DMATRIX lpD3DMatrix)
{
    return this->State.Self->GetMatrix(d3dMatHandle, lpD3DMatrix);
}

// Deletes a matrix handle.
HRESULT Direct3DDevice::DeleteMatrix(D3DMATRIXHANDLE d3dMatHandle)
{
    return this->State.Self->DeleteMatrix(d3dMatHandle);
}

// Begins a scene.
HRESULT Direct3DDevice::BeginScene()
{
    return this->State.Self->BeginScene();
}

// Ends a scene.
HRESULT Direct3DDevice::EndScene()
{
    return this->State.Self->EndScene();
}

// Retrieves the Direct3D object for this device.
HRESULT Direct3DDevice::GetDirect3D(LPDIRECT3D* lplpD3D)
{
    CONST HRESULT result = this->State.Self->GetDirect3D(lplpD3D);

    if (SUCCEEDED(result)) { *lplpD3D = ActivateAgent(Direct3D, *lplpD3D); }

    return result;
}