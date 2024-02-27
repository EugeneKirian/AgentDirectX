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

#include "Direct3D7.hxx"
#include "Direct3DDevice.hxx"
#include "Direct3DDevice2.hxx"
#include "Direct3DDevice3.hxx"
#include "Direct3DDevice7.hxx"
#include "Direct3DVertexBuffer7.hxx"
#include "DirectDrawSurface7.hxx"

struct EnumTextureFormatsCallbackContext
{
    LPD3DENUMPIXELFORMATSCALLBACK lpd3dEnumPixelProc;
    LPVOID lpContext;
};

static HRESULT CALLBACK EnumTextureFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext)
{
    EnumTextureFormatsCallbackContext* context = (EnumTextureFormatsCallbackContext*)lpContext;

    return context->lpd3dEnumPixelProc(lpDDPixFmt, context->lpContext);
}

Direct3DDevice7::Direct3DDevice7(AgentConstructorParameters(Direct3DDevice7))
{
    AgentConstructor();
}

Direct3DDevice7::~Direct3DDevice7()
{
    AgentDestructor();
}

HRESULT Direct3DDevice7::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
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
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DDevice7::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DDevice7::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves the capabilities of the Direct3D device.
HRESULT Direct3DDevice7::GetCaps(LPD3DDEVICEDESC7 lpD3DDevDesc)
{
    return this->State.Self->GetCaps(lpD3DDevDesc);
}

// Queries the current driver for a list of supported texture formats.
HRESULT Direct3DDevice7::EnumTextureFormats(LPD3DENUMPIXELFORMATSCALLBACK lpd3dEnumPixelProc, LPVOID lpContext)
{
    if (lpd3dEnumPixelProc == NULL) { return DDERR_INVALIDPARAMS; }

    EnumTextureFormatsCallbackContext context;

    context.lpd3dEnumPixelProc = lpd3dEnumPixelProc;
    context.lpContext = lpContext;

    return this->State.Self->EnumTextureFormats(EnumTextureFormatsCallback, &context);
}

// Begins a scene.
HRESULT Direct3DDevice7::BeginScene()
{
    return this->State.Self->BeginScene();
}

// Ends a scene.
HRESULT Direct3DDevice7::EndScene()
{
    return this->State.Self->EndScene();
}

// Retrieves the Direct3D object for this device.
HRESULT Direct3DDevice7::GetDirect3D(LPDIRECT3D7* lplpD3D)
{
    CONST HRESULT result = this->State.Self->GetDirect3D(lplpD3D);

    if (SUCCEEDED(result)) { *lplpD3D = ActivateAgentDelegate(Direct3D7, *lplpD3D); }

    return result;
}

// Permits the application to easily route rendering output to a new DirectDraw surface as a render target.
HRESULT Direct3DDevice7::SetRenderTarget(LPDIRECTDRAWSURFACE7 lpNewRenderTarget, DWORD dwFlags)
{
    AttemptAccessAgentValue(DirectDrawSurface7, lpNewRenderTarget);

    return this->State.Self->SetRenderTarget(lpNewRenderTarget, dwFlags);
}

// Retrieves a pointer to the DirectDraw surface that is being used as a render target.
HRESULT Direct3DDevice7::GetRenderTarget(LPDIRECTDRAWSURFACE7* lplpRenderTarget)
{
    CONST HRESULT result = this->State.Self->GetRenderTarget(lplpRenderTarget);

    if (SUCCEEDED(result)) { *lplpRenderTarget = ActivateAgentDelegate(DirectDrawSurface7, *lplpRenderTarget); }

    return result;
}

// Clears the viewport (or a set of rectangles in the viewport) to a specified RGBA color,
// clears the depth buffer, and erases the stencil buffer.
HRESULT Direct3DDevice7::Clear(DWORD dwCount, LPD3DRECT lpRects, DWORD dwFlags, D3DCOLOR dwColor, D3DVALUE dvZ, DWORD dwStencil)
{
    return this->State.Self->Clear(dwCount, lpRects, dwFlags, dwColor, dvZ, dwStencil);
}

// Sets a single Direct3DDevice transformation-related state.
HRESULT Direct3DDevice7::SetTransform(D3DTRANSFORMSTATETYPE dtstTransformStateType, LPD3DMATRIX lpD3DMatrix)
{
    return this->State.Self->SetTransform(dtstTransformStateType, lpD3DMatrix);
}

// Gets a matrix describing a transformation state.
HRESULT Direct3DDevice7::GetTransform(D3DTRANSFORMSTATETYPE dtstTransformStateType, LPD3DMATRIX lpD3DMatrix)
{
    return this->State.Self->GetTransform(dtstTransformStateType, lpD3DMatrix);
}

// Sets the viewport parameters for the device.
HRESULT Direct3DDevice7::SetViewport(LPD3DVIEWPORT7 lpViewport)
{
    return this->State.Self->SetViewport(lpViewport);
}

// Multiplies a device's world, view, or projection matrices by a specified matrix.
// The multiplication order is lpD3DMatrix times dtstTransformStateType.
HRESULT Direct3DDevice7::MultiplyTransform(D3DTRANSFORMSTATETYPE dtstTransformStateType, LPD3DMATRIX lpD3DMatrix)
{
    return this->State.Self->MultiplyTransform(dtstTransformStateType, lpD3DMatrix);
}

// Retrieves the viewport parameters currently set for the device.
HRESULT Direct3DDevice7::GetViewport(LPD3DVIEWPORT7 lpViewport)
{
    return this->State.Self->GetViewport(lpViewport);
}

// Sets the material properties for the device.
HRESULT Direct3DDevice7::SetMaterial(LPD3DMATERIAL7 lpMaterial)
{
    return this->State.Self->SetMaterial(lpMaterial);
}

// Retrieves the current material properties for the device.
HRESULT Direct3DDevice7::GetMaterial(LPD3DMATERIAL7 lpMaterial)
{
    return this->State.Self->GetMaterial(lpMaterial);
}

// Assigns a set of lighting properties for this device.
HRESULT Direct3DDevice7::SetLight(DWORD dwLightIndex, LPD3DLIGHT7 lpLight)
{
    return this->State.Self->SetLight(dwLightIndex, lpLight);
}

// Retrieves a set of lighting properties that this device uses.
HRESULT Direct3DDevice7::GetLight(DWORD dwLightIndex, LPD3DLIGHT7 lpLight)
{
    return this->State.Self->GetLight(dwLightIndex, lpLight);
}

// Sets a single Direct3DDevice render-state parameter.
HRESULT Direct3DDevice7::SetRenderState(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState)
{
    return this->State.Self->SetRenderState(dwRenderStateType, dwRenderState);
}

// Gets a single Direct3DDevice rendering-state parameter.
HRESULT Direct3DDevice7::GetRenderState(D3DRENDERSTATETYPE dwRenderStateType, LPDWORD lpdwRenderState)
{
    return this->State.Self->GetRenderState(dwRenderStateType, lpdwRenderState);
}

// Signals Direct3D to begin recording a device state block.
HRESULT Direct3DDevice7::BeginStateBlock()
{
    return this->State.Self->BeginStateBlock();
}

// Signals Direct3D to stop recording a device state block and retrieve a handle to the state block.
HRESULT Direct3DDevice7::EndStateBlock(LPDWORD lpdwBlockHandle)
{
    return this->State.Self->EndStateBlock(lpdwBlockHandle);
}

// Instructs the Direct3D texture manager to load a managed texture into video memory.
HRESULT Direct3DDevice7::PreLoad(LPDIRECTDRAWSURFACE7 lpddsTexture)
{
    AttemptAccessAgentValue(DirectDrawSurface7, lpddsTexture);

    return this->State.Self->PreLoad(lpddsTexture);
}

// Renders the specified array of vertices as a sequence of geometric primitives of the specified type.
HRESULT Direct3DDevice7::DrawPrimitive(D3DPRIMITIVETYPE dptPrimitiveType, DWORD dwVertexTypeDesc, LPVOID lpvVertices, DWORD dwVertexCount, DWORD dwFlags)
{
    return this->State.Self->DrawPrimitive(dptPrimitiveType, dwVertexTypeDesc, lpvVertices, dwVertexCount, dwFlags);
}

// Renders the specified geometric primitive, based on indexing into an array of vertices.
HRESULT Direct3DDevice7::DrawIndexedPrimitive(D3DPRIMITIVETYPE d3dptPrimitiveType, DWORD dwVertexTypeDesc, LPVOID lpvVertices, DWORD dwVertexCount, LPWORD lpwIndices, DWORD dwIndexCount, DWORD dwFlags)
{
    return this->State.Self->DrawIndexedPrimitive(d3dptPrimitiveType, dwVertexTypeDesc, lpvVertices, dwVertexCount, lpwIndices, dwIndexCount, dwFlags);
}

// Sets the current clip status.
HRESULT Direct3DDevice7::SetClipStatus(LPD3DCLIPSTATUS lpD3DClipStatus)
{
    return this->State.Self->SetClipStatus(lpD3DClipStatus);
}

// Gets the current clip status.
HRESULT Direct3DDevice7::GetClipStatus(LPD3DCLIPSTATUS lpD3DClipStatus)
{
    return this->State.Self->GetClipStatus(lpD3DClipStatus);
}

// Renders the specified array of strided vertices as a sequence of geometric primitives.
// For more information, see Strided Vertex Format.
HRESULT Direct3DDevice7::DrawPrimitiveStrided(D3DPRIMITIVETYPE dptPrimitiveType, DWORD dwVertexTypeDesc, LPD3DDRAWPRIMITIVESTRIDEDDATA lpVertexArray, DWORD dwVertexCount, DWORD dwFlags)
{
    return this->State.Self->DrawPrimitiveStrided(dptPrimitiveType, dwVertexTypeDesc, lpVertexArray, dwVertexCount, dwFlags);
}

// Renders a geometric primitive, based on indexing into an array of strided vertices.
// For more information, see Strided Vertex Format.
HRESULT Direct3DDevice7::DrawIndexedPrimitiveStrided(D3DPRIMITIVETYPE d3dptPrimitiveType, DWORD dwVertexTypeDesc, LPD3DDRAWPRIMITIVESTRIDEDDATA lpVertexArray, DWORD dwVertexCount, LPWORD lpwIndices, DWORD dwIndexCount, DWORD dwFlags)
{
    return this->State.Self->DrawIndexedPrimitiveStrided(d3dptPrimitiveType, dwVertexTypeDesc, lpVertexArray, dwVertexCount, lpwIndices, dwIndexCount, dwFlags);
}

// Renders an array of vertices in a vertex buffer as a sequence of geometric primitives.
HRESULT Direct3DDevice7::DrawPrimitiveVB(D3DPRIMITIVETYPE d3dptPrimitiveType, LPDIRECT3DVERTEXBUFFER7 lpd3dVertexBuffer, DWORD dwStartVertex, DWORD dwNumVertices, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DVertexBuffer7, lpd3dVertexBuffer);

    return this->State.Self->DrawPrimitiveVB(d3dptPrimitiveType, lpd3dVertexBuffer, dwStartVertex, dwNumVertices, dwFlags);
}

// Renders a geometric primitive based on indexing into an array of vertices within a vertex buffer.
HRESULT Direct3DDevice7::DrawIndexedPrimitiveVB(D3DPRIMITIVETYPE d3dptPrimitiveType, LPDIRECT3DVERTEXBUFFER7 lpd3dVertexBuffer, DWORD dwStartVertex, DWORD dwNumVertices, LPWORD lpwIndices, DWORD dwIndexCount, DWORD dwFlags)
{
    AttemptAccessAgentValue(Direct3DVertexBuffer7, lpd3dVertexBuffer);

    return this->State.Self->DrawIndexedPrimitiveVB(d3dptPrimitiveType, lpd3dVertexBuffer, dwStartVertex, dwNumVertices, lpwIndices, dwIndexCount, dwFlags);
}

// Calculates the visibility (complete, partial, or no visibility) of an array of spheres within the current viewport for this device.
HRESULT Direct3DDevice7::ComputeSphereVisibility(LPD3DVECTOR lpCenters, LPD3DVALUE lpRadii, DWORD dwNumSpheres, DWORD dwFlags, LPDWORD lpdwReturnValues)
{
    return this->State.Self->ComputeSphereVisibility(lpCenters, lpRadii, dwNumSpheres, dwFlags, lpdwReturnValues);
}

// Retrieves a texture assigned to a given stage for a device.
HRESULT Direct3DDevice7::GetTexture(DWORD dwStage, LPDIRECTDRAWSURFACE7* lplpTexture)
{
    CONST HRESULT result = this->State.Self->GetTexture(dwStage, lplpTexture);

    if (SUCCEEDED(result)) { *lplpTexture = ActivateAgentDelegate(DirectDrawSurface7, *lplpTexture); }

    return result;
}

// Assigns a texture to a given stage for a device.
HRESULT Direct3DDevice7::SetTexture(DWORD dwStage, LPDIRECTDRAWSURFACE7 lpTexture)
{
    AttemptAccessAgentValue(DirectDrawSurface7, lpTexture);

    return this->State.Self->SetTexture(dwStage, lpTexture);
}

// Retrieves a state value for a currently assigned texture.
HRESULT Direct3DDevice7::GetTextureStageState(DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState, LPDWORD lpdwValue)
{
    return this->State.Self->GetTextureStageState(dwStage, dwState, lpdwValue);
}

// Sets the state value for a currently assigned texture.
HRESULT Direct3DDevice7::SetTextureStageState(DWORD dwStage, D3DTEXTURESTAGESTATETYPE dwState, DWORD dwValue)
{
    return this->State.Self->SetTextureStageState(dwStage, dwState, dwValue);
}

// Reports the device's ability to render the currently set texture-blending operations and arguments in a single pass.
HRESULT Direct3DDevice7::ValidateDevice(LPDWORD lpdwPasses)
{
    return this->State.Self->ValidateDevice(lpdwPasses);
}

// Applies an existing device-state block to the rendering device.
HRESULT Direct3DDevice7::ApplyStateBlock(DWORD dwBlockHandle)
{
    return this->State.Self->ApplyStateBlock(dwBlockHandle);
}

// Updates the values within an existing state block to the values currently set for the device.
HRESULT Direct3DDevice7::CaptureStateBlock(DWORD dwBlockHandle)
{
    return this->State.Self->CaptureStateBlock(dwBlockHandle);
}

// Deletes a previously recorded device state block.
HRESULT Direct3DDevice7::DeleteStateBlock(DWORD dwBlockHandle)
{
    return this->State.Self->DeleteStateBlock(dwBlockHandle);
}

// Creates a new state block that contains the current values for all device states, vertex-related states, or pixel-related states.
HRESULT Direct3DDevice7::CreateStateBlock(D3DSTATEBLOCKTYPE d3dsbType, LPDWORD lpdwBlockHandle)
{
    return this->State.Self->CreateStateBlock(d3dsbType, lpdwBlockHandle);
}

// Loads a rectangular area of a source texture to a specified point in a destination texture or to faces within a cubic environment map.
HRESULT Direct3DDevice7::Load(LPDIRECTDRAWSURFACE7 lpDestTex, LPPOINT lpDestPoint, LPDIRECTDRAWSURFACE7 lpSrcTex, LPRECT lprcSrcRect, DWORD dwFlags)
{
    AttemptAccessAgentValue(DirectDrawSurface7, lpDestTex);
    AttemptAccessAgentValue(DirectDrawSurface7, lpSrcTex);

    return this->State.Self->Load(lpDestTex, lpDestPoint, lpSrcTex, lprcSrcRect, dwFlags);
}

// Enables or disables a set of lighting parameters within a device.
HRESULT Direct3DDevice7::LightEnable(DWORD dwLightIndex, BOOL bEnable)
{
    return this->State.Self->LightEnable(dwLightIndex, bEnable);
}

// Retrieves the activity status—enabled or disabled—for a set of lighting parameters within a device.
HRESULT Direct3DDevice7::GetLightEnable(DWORD dwLightIndex, BOOL* pbEnable)
{
    return this->State.Self->GetLightEnable(dwLightIndex, pbEnable);
}

// Sets the coefficients of a user-defined clipping plane for the device.
HRESULT Direct3DDevice7::SetClipPlane(DWORD dwIndex, D3DVALUE* pPlaneEquation)
{
    return this->State.Self->SetClipPlane(dwIndex, pPlaneEquation);
}

// Retrieves the coefficients of a user-defined clipping plane for the device.
HRESULT Direct3DDevice7::GetClipPlane(DWORD dwIndex, D3DVALUE* pPlaneEquation)
{
    return this->State.Self->GetClipPlane(dwIndex, pPlaneEquation);
}

// Retrieves information about the rendering device.
// Information can pertain to Direct3D or the underlying device driver.
HRESULT Direct3DDevice7::GetInfo(DWORD dwDevInfoID, LPVOID pDevInfoStruct, DWORD dwSize)
{
    return this->State.Self->GetInfo(dwDevInfoID, pDevInfoStruct, dwSize);
}