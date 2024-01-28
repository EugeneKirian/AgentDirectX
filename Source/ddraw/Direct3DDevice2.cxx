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

#include "Direct3D2.hxx"
#include "Direct3DDevice.hxx"
#include "Direct3DDevice2.hxx"
#include "Direct3DDevice3.hxx"
#include "Direct3DDevice7.hxx"
#include "Direct3DTexture2.hxx"
#include "Direct3DViewport2.hxx"
#include "DirectDrawSurface.hxx"
#include "Unknown.hxx"

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

Direct3DDevice2::Direct3DDevice2(AgentConstructorParameters(Direct3DDevice2))
{
    AgentConstructor();
}

Direct3DDevice2::~Direct3DDevice2()
{
    AgentDestructor();
}

HRESULT Direct3DDevice2::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    const HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DDevice, riid)) { *ppvObj = ActivateAgent(Direct3DDevice, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DDevice2, riid)) { *ppvObj = ActivateAgent(Direct3DDevice2, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DDevice3, riid)) { *ppvObj = ActivateAgent(Direct3DDevice3, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DDevice7, riid)) { *ppvObj = ActivateAgent(Direct3DDevice7, *ppvObj); }
            else if (IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Unknown, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DDevice2::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DDevice2::Release()
{
    const ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves the capabilities of the Direct3D device.
HRESULT Direct3DDevice2::GetCaps(LPD3DDEVICEDESC lpD3DHWDevDesc, LPD3DDEVICEDESC lpD3DHELDevDesc)
{
    return this->State.Self->GetCaps(lpD3DHWDevDesc, lpD3DHELDevDesc);
}

// Swaps two texture handles.
HRESULT Direct3DDevice2::SwapTextureHandles(LPDIRECT3DTEXTURE2 lpD3DTex1, LPDIRECT3DTEXTURE2 lpD3DTex2)
{
    AttemptAccessAgentValue(Direct3DTexture2, lpD3DTex1);
    AttemptAccessAgentValue(Direct3DTexture2, lpD3DTex2);

    return this->State.Self->SwapTextureHandles(lpD3DTex1, lpD3DTex2);
}

// Retrieves statistics about a device.
HRESULT Direct3DDevice2::GetStats(LPD3DSTATS lpD3DStats)
{
    return this->State.Self->GetStats(lpD3DStats);
}

// Adds the specified viewport to the list of viewport objects associated with the device
// and increments the reference count of the viewport.
HRESULT Direct3DDevice2::AddViewport(LPDIRECT3DVIEWPORT2 lpDirect3DViewport)
{
    AttemptAccessAgentValue(Direct3DViewport2, lpDirect3DViewport);

    return this->State.Self->AddViewport(lpDirect3DViewport);
}

// Removes the specified viewport from the list of viewport objects associated with the device
// and decrements the reference count of the viewport.
HRESULT Direct3DDevice2::DeleteViewport(LPDIRECT3DVIEWPORT2 lpDirect3DViewport)
{
    AttemptAccessAgentValue(Direct3DViewport2, lpDirect3DViewport);

    return this->State.Self->DeleteViewport(lpDirect3DViewport);
}

// Enumerates the viewports associated with the device.
HRESULT Direct3DDevice2::NextViewport(LPDIRECT3DVIEWPORT2 lpDirect3DViewport, LPDIRECT3DVIEWPORT2* lplpAnotherViewport, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DViewport2, lpDirect3DViewport);

    const HRESULT result = this->State.Self->NextViewport(lpDirect3DViewport, lplpAnotherViewport, dwFlags);

    if (SUCCEEDED(result)) { *lplpAnotherViewport = ActivateAgentDelegate(Direct3DViewport2, *lplpAnotherViewport); }

    return result;
}

// Queries the current driver for a list of supported texture formats.
HRESULT Direct3DDevice2::EnumTextureFormats(LPD3DENUMTEXTUREFORMATSCALLBACK lpd3dEnumTextureProc, LPVOID lpContext)
{
    if (lpd3dEnumTextureProc == NULL) { return DDERR_INVALIDPARAMS; }

    EnumTextureFormatsCallbackContext context;

    context.lpd3dEnumTextureProc = lpd3dEnumTextureProc;
    context.lpContext = lpContext;

    return this->State.Self->EnumTextureFormats(EnumTextureFormatsCallback, &context);
}

// Begins a scene.
HRESULT Direct3DDevice2::BeginScene()
{
    return this->State.Self->BeginScene();
}

// Ends a scene.
HRESULT Direct3DDevice2::EndScene()
{
    return this->State.Self->EndScene();
}

// Retrieves the Direct3D object for this device.
HRESULT Direct3DDevice2::GetDirect3D(LPDIRECT3D2* lplpD3D)
{
    const HRESULT result = this->State.Self->GetDirect3D(lplpD3D);

    if (SUCCEEDED(result)) { *lplpD3D = ActivateAgentDelegate(Direct3D2, *lplpD3D); }

    return result;
}

// Sets the current viewport.
HRESULT Direct3DDevice2::SetCurrentViewport(LPDIRECT3DVIEWPORT2 lpd3dViewport)
{
    AttemptAccessAgentValue(Direct3DViewport2, lpd3dViewport);

    return this->State.Self->SetCurrentViewport(lpd3dViewport);
}

// Retrieves the current viewport.
HRESULT Direct3DDevice2::GetCurrentViewport(LPDIRECT3DVIEWPORT2* lplpd3dViewport)
{
    const HRESULT result = this->State.Self->GetCurrentViewport(lplpd3dViewport);

    if (SUCCEEDED(result)) { *lplpd3dViewport = ActivateAgentDelegate(Direct3DViewport2, *lplpd3dViewport); }

    return result;
}

// Permits the application to easily route rendering output to a new DirectDraw surface as a render target.
HRESULT Direct3DDevice2::SetRenderTarget(LPDIRECTDRAWSURFACE lpNewRenderTarget, DWORD dwFlags)
{
    AttemptAccessAgentValue(DirectDrawSurface, lpNewRenderTarget);

    return this->State.Self->SetRenderTarget(lpNewRenderTarget, dwFlags);
}

// Retrieves a pointer to the DirectDraw surface that is being used as a render target.
HRESULT Direct3DDevice2::GetRenderTarget(LPDIRECTDRAWSURFACE* lplpRenderTarget)
{
    const HRESULT result = this->State.Self->GetRenderTarget(lplpRenderTarget);

    if (SUCCEEDED(result)) { *lplpRenderTarget = ActivateAgentDelegate(DirectDrawSurface, *lplpRenderTarget); }

    return result;
}

// Indicates the start of a sequence of rendered primitives.
HRESULT Direct3DDevice2::Begin(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dptVertexType, DWORD dwFlags)
{
    return this->State.Self->Begin(dptPrimitiveType, dptVertexType, dwFlags);
}

// Defines the start of a primitive based on indexing into an array of vertices.
HRESULT Direct3DDevice2::BeginIndexed(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dptVertexType, LPVOID lpvVertices, DWORD dwNumVertices, DWORD dwFlags)
{
    return this->State.Self->BeginIndexed(dptPrimitiveType, dptVertexType, lpvVertices, dwNumVertices, dwFlags);
}

// Adds a new Direct3D vertex to the primitive sequence started with a previous call to the IDirect3DDevice2::Begin method.
HRESULT Direct3DDevice2::Vertex(LPVOID lpVertex)
{
    return this->State.Self->Vertex(lpVertex);
}

// Adds a new index to the primitive sequence started with a previous call to the IDirect3DDevice3::BeginIndexed method.
HRESULT Direct3DDevice2::Index(WORD wVertexIndex)
{
    return this->State.Self->Index(wVertexIndex);
}

// Signals the completion of a primitive sequence.
HRESULT Direct3DDevice2::End(DWORD dwFlags)
{
    return this->State.Self->End(dwFlags);
}

// Gets a single Direct3DDevice rendering state parameter.
HRESULT Direct3DDevice2::GetRenderState(D3DRENDERSTATETYPE dwRenderStateType, LPDWORD lpdwRenderState)
{
    return this->State.Self->GetRenderState(dwRenderStateType, lpdwRenderState);
}

//  Sets a single Direct3DDevice rendering state parameter.
HRESULT Direct3DDevice2::SetRenderState(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState)
{
    return this->State.Self->SetRenderState(dwRenderStateType, dwRenderState);
}

// Gets a single Direct3D device lighting-related state value.
HRESULT Direct3DDevice2::GetLightState(D3DLIGHTSTATETYPE dwLightStateType, LPDWORD lpdwLightState)
{
    return this->State.Self->GetLightState(dwLightStateType, lpdwLightState);
}

// Sets a single Direct3DDevice lighting-related state value.
HRESULT Direct3DDevice2::SetLightState(D3DLIGHTSTATETYPE dwLightStateType, DWORD dwLightState)
{
    return this->State.Self->SetLightState(dwLightStateType, dwLightState);
}

// Sets a single Direct3DDevice transformation-related state.
HRESULT Direct3DDevice2::SetTransform(D3DTRANSFORMSTATETYPE dtstTransformStateType, LPD3DMATRIX lpD3DMatrix)
{
    return this->State.Self->SetTransform(dtstTransformStateType, lpD3DMatrix);
}

// Gets a matrix describing a transformation state.
HRESULT Direct3DDevice2::GetTransform(D3DTRANSFORMSTATETYPE dtstTransformStateType, LPD3DMATRIX lpD3DMatrix)
{
    return this->State.Self->GetTransform(dtstTransformStateType, lpD3DMatrix);
}

// Multiplies a device's world, view, or projection matrices by a specified matrix.
// The multiplication order is lpD3DMatrix times dtstTransformStateType.
HRESULT Direct3DDevice2::MultiplyTransform(D3DTRANSFORMSTATETYPE dtstTransformStateType, LPD3DMATRIX lpD3DMatrix)
{
    return this->State.Self->MultiplyTransform(dtstTransformStateType, lpD3DMatrix);
}

// Renders the specified array of vertices as a sequence of geometric primitives of the specified type.
HRESULT Direct3DDevice2::DrawPrimitive(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dptVertexType, LPVOID lpvVertices, DWORD dwVertexCount, DWORD dwFlags)
{
    return this->State.Self->DrawPrimitive(dptPrimitiveType, dptVertexType, lpvVertices, dwVertexCount, dwFlags);
}

// Renders the specified geometric primitive based on indexing into an array of vertices.
HRESULT Direct3DDevice2::DrawIndexedPrimitive(D3DPRIMITIVETYPE d3dptPrimitiveType, D3DVERTEXTYPE dptVertexType, LPVOID lpvVertices, DWORD dwVertexCount, LPWORD lpwIndices, DWORD dwIndexCount, DWORD dwFlags)
{
    return this->State.Self->DrawIndexedPrimitive(d3dptPrimitiveType, dptVertexType, lpvVertices, dwVertexCount, lpwIndices, dwIndexCount, dwFlags);
}

// Sets the current clip status.
HRESULT Direct3DDevice2::SetClipStatus(LPD3DCLIPSTATUS lpD3DClipStatus)
{
    return this->State.Self->SetClipStatus(lpD3DClipStatus);
}

// Gets the current clip status.
HRESULT Direct3DDevice2::GetClipStatus(LPD3DCLIPSTATUS lpD3DClipStatus)
{
    return this->State.Self->GetClipStatus(lpD3DClipStatus);
}