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

#include "Direct3D8.hxx"
#include "Direct3DBaseTexture8.hxx"
#include "Direct3DCubeTexture8.hxx"
#include "Direct3DDevice8.hxx"
#include "Direct3DIndexBuffer8.hxx"
#include "Direct3DSurface8.hxx"
#include "Direct3DSwapChain8.hxx"
#include "Direct3DTexture8.hxx"
#include "Direct3DVertexBuffer8.hxx"
#include "Direct3DVolumeTexture8.hxx"

Direct3DDevice8::Direct3DDevice8(AgentConstructorParameters(Direct3DDevice8))
{
    AgentConstructor();
}

Direct3DDevice8::~Direct3DDevice8()
{
    AgentDestructor();
}

HRESULT Direct3DDevice8::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DDevice8, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3DDevice8, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DDevice8::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DDevice8::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Reports the current cooperative-level status of the Microsoft® Direct3D® device for a windowed or full-screen application.
HRESULT Direct3DDevice8::TestCooperativeLevel()
{
    return this->State.Self->TestCooperativeLevel();
}

// Returns an estimate of the amount of available texture memory.
UINT Direct3DDevice8::GetAvailableTextureMem()
{
    return this->State.Self->GetAvailableTextureMem();
}

// Invokes the resource manager to free memory. 
HRESULT Direct3DDevice8::ResourceManagerDiscardBytes(DWORD Bytes)
{
    return this->State.Self->ResourceManagerDiscardBytes(Bytes);
}

// Returns an interface to the instance of the Microsoft® Direct3D® object that created the device.
HRESULT Direct3DDevice8::GetDirect3D(LPDIRECT3D8* ppD3D8)
{
    CONST HRESULT result = this->State.Self->GetDirect3D(ppD3D8);

    if (SUCCEEDED(result)) { *ppD3D8 = ActivateAgent(Direct3D8, *ppD3D8); }

    return result;
}

// Retrieves the capabilities of the rendering device.
HRESULT Direct3DDevice8::GetDeviceCaps(D3DCAPS8* pCaps)
{
    return this->State.Self->GetDeviceCaps(pCaps);
}

// Retrieves the display mode's spatial resolution, color resolution, and refresh frequency.
HRESULT Direct3DDevice8::GetDisplayMode(D3DDISPLAYMODE* pMode)
{
    return this->State.Self->GetDisplayMode(pMode);
}

// Retrieves the creation parameters of the device.
HRESULT Direct3DDevice8::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
    return this->State.Self->GetCreationParameters(pParameters);
}

// Sets properties for the cursor.
HRESULT Direct3DDevice8::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, LPDIRECT3DSURFACE8 pCursorBitmap)
{
    AttemptAccessAgentValue(Direct3DSurface8, pCursorBitmap);

    return this->State.Self->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

// Sets the cursor position and update options.
VOID Direct3DDevice8::SetCursorPosition(UINT XScreenSpace, UINT YScreenSpace, DWORD Flags)
{
    this->State.Self->SetCursorPosition(XScreenSpace, YScreenSpace, Flags);
}

// Displays or hides the cursor.
BOOL Direct3DDevice8::ShowCursor(BOOL bShow)
{
    return this->State.Self->ShowCursor(bShow);
}

// Creates an additional swap chain for rendering multiple views.
HRESULT Direct3DDevice8::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, LPDIRECT3DSWAPCHAIN8* pSwapChain)
{
    CONST HRESULT result = this->State.Self->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);

    if (SUCCEEDED(result)) { *pSwapChain = ActivateAgentDelegate(Direct3DSwapChain8, *pSwapChain); }

    return result;
}

// Resets the type, size, and format of the swap chain.
HRESULT Direct3DDevice8::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return this->State.Self->Reset(pPresentationParameters);
}

// Presents the contents of the next in the sequence of back buffers owned by the device. 
HRESULT Direct3DDevice8::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
    return this->State.Self->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

// Retrieves a back buffer from the device's swap chain.
HRESULT Direct3DDevice8::GetBackBuffer(UINT BackBuffer, D3DBACKBUFFER_TYPE Type, LPDIRECT3DSURFACE8* ppBackBuffer)
{
    CONST HRESULT result = this->State.Self->GetBackBuffer(BackBuffer, Type, ppBackBuffer);

    if (SUCCEEDED(result)) { *ppBackBuffer = ActivateAgent(Direct3DSurface8, *ppBackBuffer); }

    return result;
}

// Returns information describing the raster of the monitor on which the swap chain is presented.
HRESULT Direct3DDevice8::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus)
{
    return this->State.Self->GetRasterStatus(pRasterStatus);
}

// Sets the gamma correction ramp for the implicit swap chain.
VOID Direct3DDevice8::SetGammaRamp(DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
    this->State.Self->SetGammaRamp(Flags, pRamp);
}

// Retrieves the gamma correction ramp for the swap chain.
VOID Direct3DDevice8::GetGammaRamp(D3DGAMMARAMP* pRamp)
{
    this->State.Self->GetGammaRamp(pRamp);
}

// Creates a texture resource.
HRESULT Direct3DDevice8::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DTEXTURE8* ppTexture)
{
    CONST HRESULT result = this->State.Self->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture);

    if (SUCCEEDED(result)) { *ppTexture = ActivateAgent(Direct3DTexture8, *ppTexture); }

    return result;
}

// Creates a volume texture resource.
HRESULT Direct3DDevice8::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture)
{
    CONST HRESULT result = this->State.Self->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture);

    if (SUCCEEDED(result)) { *ppVolumeTexture = ActivateAgent(Direct3DVolumeTexture8, *ppVolumeTexture); }

    return result;
}

// Creates a cube texture resource.
HRESULT Direct3DDevice8::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DCUBETEXTURE8* ppCubeTexture)
{
    CONST HRESULT result = this->State.Self->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture);

    if (SUCCEEDED(result)) { *ppCubeTexture = ActivateAgent(Direct3DCubeTexture8, *ppCubeTexture); }

    return result;
}

// Creates a vertex buffer.
HRESULT Direct3DDevice8::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, LPDIRECT3DVERTEXBUFFER8* ppVertexBuffer)
{
    CONST HRESULT result = this->State.Self->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer);

    if (SUCCEEDED(result)) { *ppVertexBuffer = ActivateAgentDelegate(Direct3DVertexBuffer8, *ppVertexBuffer); }

    return result;
}

// Creates an index buffer.
HRESULT Direct3DDevice8::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DINDEXBUFFER8* ppIndexBuffer)
{
    CONST HRESULT result = this->State.Self->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer);

    if (SUCCEEDED(result)) { *ppIndexBuffer = ActivateAgentDelegate(Direct3DIndexBuffer8, *ppIndexBuffer); }

    return result;
}

// Creates a render target surface.
HRESULT Direct3DDevice8::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, LPDIRECT3DSURFACE8* ppSurface)
{
    CONST HRESULT result = this->State.Self->CreateRenderTarget(Width, Height, Format, MultiSample, Lockable, ppSurface);

    if (SUCCEEDED(result)) { *ppSurface = ActivateAgentDelegate(Direct3DSurface8, *ppSurface); }

    return result;
}

// Creates a depth-stencil resource.
HRESULT Direct3DDevice8::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, LPDIRECT3DSURFACE8* ppSurface)
{
    CONST HRESULT result = this->State.Self->CreateDepthStencilSurface(Width, Height, Format, MultiSample, ppSurface);

    if (SUCCEEDED(result)) { *ppSurface = ActivateAgentDelegate(Direct3DSurface8, *ppSurface); }

    return result;
}

// Creates an image surface.
HRESULT Direct3DDevice8::CreateImageSurface(UINT Width, UINT Height, D3DFORMAT Format, LPDIRECT3DSURFACE8* ppSurface)
{
    CONST HRESULT result = this->State.Self->CreateImageSurface(Width, Height, Format, ppSurface);

    if (SUCCEEDED(result)) { *ppSurface = ActivateAgentDelegate(Direct3DSurface8, *ppSurface); }

    return result;
}

// Copies rectangular subsets of pixels from one surface to another.
HRESULT Direct3DDevice8::CopyRects(LPDIRECT3DSURFACE8 pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, LPDIRECT3DSURFACE8 pDestinationSurface, CONST POINT* pDestPointsArray)
{
    AttemptAccessAgentValue(Direct3DSurface8, pSourceSurface);
    AttemptAccessAgentValue(Direct3DSurface8, pDestinationSurface);

    return this->State.Self->CopyRects(pSourceSurface, pSourceRectsArray, cRects, pDestinationSurface, pDestPointsArray);
}

// Updates the dirty portions of a texture.
HRESULT Direct3DDevice8::UpdateTexture(LPDIRECT3DBASETEXTURE8 pSourceTexture, LPDIRECT3DBASETEXTURE8 pDestinationTexture)
{
    AttemptAccessAgentValue(Direct3DBaseTexture8, pSourceTexture);
    AttemptAccessAgentValue(Direct3DBaseTexture8, pDestinationTexture);

    return this->State.Self->UpdateTexture(pSourceTexture, pDestinationTexture);
}

// Generates a copy of the device's front buffer and places that copy in a system memory buffer provided by the application. 
HRESULT Direct3DDevice8::GetFrontBuffer(LPDIRECT3DSURFACE8 pDestSurface)
{
    AttemptAccessAgentValue(Direct3DSurface8, pDestSurface);

    return this->State.Self->GetFrontBuffer(pDestSurface);
}

// Sets a new color buffer, depth buffer, or both for the device.
HRESULT Direct3DDevice8::SetRenderTarget(LPDIRECT3DSURFACE8 pRenderTarget, LPDIRECT3DSURFACE8 pNewZStencil)
{
    AttemptAccessAgentValue(Direct3DSurface8, pRenderTarget);
    AttemptAccessAgentValue(Direct3DSurface8, pNewZStencil);

    return this->State.Self->SetRenderTarget(pRenderTarget, pNewZStencil);
}

// Retrieves a pointer to the Microsoft® Direct3D® surface that is being used as a render target.
HRESULT Direct3DDevice8::GetRenderTarget(LPDIRECT3DSURFACE8* ppRenderTarget)
{
    CONST HRESULT result = this->State.Self->GetRenderTarget(ppRenderTarget);

    if (SUCCEEDED(result)) { *ppRenderTarget = ActivateAgent(Direct3DSurface8, *ppRenderTarget); }

    return result;
}

// Retrieves the depth-stencil surface owned by the Direct3DDevice object.
HRESULT Direct3DDevice8::GetDepthStencilSurface(LPDIRECT3DSURFACE8* ppZStencilSurface)
{
    CONST HRESULT result = this->State.Self->GetDepthStencilSurface(ppZStencilSurface);

    if (SUCCEEDED(result)) { *ppZStencilSurface = ActivateAgent(Direct3DSurface8, *ppZStencilSurface); }

    return result;
}

// Begins a scene. 
HRESULT Direct3DDevice8::BeginScene()
{
    return this->State.Self->BeginScene();
}

// Ends a scene that was begun by calling the IDirect3DDevice8::BeginScene method.
HRESULT Direct3DDevice8::EndScene()
{
    return this->State.Self->EndScene();
}

// Clears the viewport, or a set of rectangles in the viewport, to a specified RGBA color, clears the depth buffer, and erases the stencil buffer.
HRESULT Direct3DDevice8::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, FLOAT Z, DWORD Stencil)
{
    return this->State.Self->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

// Sets a single device transformation-related state.
HRESULT Direct3DDevice8::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
    return this->State.Self->SetTransform(State, pMatrix);
}

// Retrieves a matrix describing a transformation state.
HRESULT Direct3DDevice8::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
    return this->State.Self->GetTransform(State, pMatrix);
}

// Multiplies a device's world, view, or projection matrices by a specified matrix.
HRESULT Direct3DDevice8::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
    return this->State.Self->MultiplyTransform(State, pMatrix);
}

// Sets the viewport parameters for the device.
HRESULT Direct3DDevice8::SetViewport(CONST D3DVIEWPORT8* pViewport)
{
    return this->State.Self->SetViewport(pViewport);
}

// Retrieves the viewport parameters currently set for the device.
HRESULT Direct3DDevice8::GetViewport(D3DVIEWPORT8* pViewport)
{
    return this->State.Self->GetViewport(pViewport);
}

// Sets the material properties for the device.
HRESULT Direct3DDevice8::SetMaterial(CONST D3DMATERIAL8* pMaterial)
{
    return this->State.Self->SetMaterial(pMaterial);
}

// Retrieves the current material properties for the device.
HRESULT Direct3DDevice8::GetMaterial(D3DMATERIAL8* pMaterial)
{
    return this->State.Self->GetMaterial(pMaterial);
}

// Assigns a set of lighting properties for this device.
HRESULT Direct3DDevice8::SetLight(DWORD Index, CONST D3DLIGHT8* pLight)
{
    return this->State.Self->SetLight(Index, pLight);
}

// Retrieves a set of lighting properties that this device uses.
HRESULT Direct3DDevice8::GetLight(DWORD Index, D3DLIGHT8* pLight)
{
    return this->State.Self->GetLight(Index, pLight);
}

// Enables or disables a set of lighting parameters within a device.
HRESULT Direct3DDevice8::LightEnable(DWORD Index, BOOL bEnable)
{
    return this->State.Self->LightEnable(Index, bEnable);
}

// Retrieves the activity status—enabled or disabled—for a set of lighting parameters within a device.
HRESULT Direct3DDevice8::GetLightEnable(DWORD Index, BOOL* pEnable)
{
    return this->State.Self->GetLightEnable(Index, pEnable);
}

// Sets the coefficients of a user-defined clipping plane for the device.
HRESULT Direct3DDevice8::SetClipPlane(DWORD Index, CONST FLOAT* pPlane)
{
    return this->State.Self->SetClipPlane(Index, pPlane);
}

// Retrieves the coefficients of a user-defined clipping plane for the device.
HRESULT Direct3DDevice8::GetClipPlane(DWORD Index, FLOAT* pPlane)
{
    return this->State.Self->GetClipPlane(Index, pPlane);
}

// Sets a single device render-state parameter.
HRESULT Direct3DDevice8::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
    return this->State.Self->SetRenderState(State, Value);
}

// Retrieves a render-state value for a device.
HRESULT Direct3DDevice8::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
    return this->State.Self->GetRenderState(State, pValue);
}

// Signals Microsoft® Direct3D® to begin recording a device-state block.
HRESULT Direct3DDevice8::BeginStateBlock()
{
    return this->State.Self->BeginStateBlock();
}

// Signals Microsoft® Direct3D® to stop recording a device-state block and retrieve a handle to the state block.
HRESULT Direct3DDevice8::EndStateBlock(DWORD* pToken)
{
    return this->State.Self->EndStateBlock(pToken);
}

// Applies an existing device-state block to the rendering device.
HRESULT Direct3DDevice8::ApplyStateBlock(DWORD Token)
{
    return this->State.Self->ApplyStateBlock(Token);
}

// Updates the values within an existing state block to the values set for the device.
HRESULT Direct3DDevice8::CaptureStateBlock(DWORD Token)
{
    return this->State.Self->CaptureStateBlock(Token);
}

// Deletes a previously recorded device-state block.
HRESULT Direct3DDevice8::DeleteStateBlock(DWORD Token)
{
    return this->State.Self->DeleteStateBlock(Token);
}

// Creates a new state block that contains the values for all device states, vertex-related states, or pixel-related states.
HRESULT Direct3DDevice8::CreateStateBlock(D3DSTATEBLOCKTYPE Type, DWORD* pToken)
{
    return this->State.Self->CreateStateBlock(Type, pToken);
}

// Sets the clip status.
HRESULT Direct3DDevice8::SetClipStatus(CONST D3DCLIPSTATUS8* pClipStatus)
{
    return this->State.Self->SetClipStatus(pClipStatus);
}

// Retrieves the clip status.
HRESULT Direct3DDevice8::GetClipStatus(D3DCLIPSTATUS8* pClipStatus)
{
    return this->State.Self->GetClipStatus(pClipStatus);
}

// Retrieves a texture assigned to a stage for a device.
HRESULT Direct3DDevice8::GetTexture(DWORD Stage, LPDIRECT3DBASETEXTURE8* ppTexture)
{
    CONST HRESULT result = this->State.Self->GetTexture(Stage, ppTexture);

    if (SUCCEEDED(result)) { *ppTexture = ActivateAgentBase(Direct3DBaseTexture8, *ppTexture); }

    return result;
}

// Assigns a texture to a stage for a device.
HRESULT Direct3DDevice8::SetTexture(DWORD Stage, LPDIRECT3DBASETEXTURE8 pTexture)
{
    AttemptAccessAgentBaseValue(Direct3DBaseTexture8, pTexture);

    return this->State.Self->SetTexture(Stage, pTexture);
}

// Retrieves a state value for an assigned texture.
HRESULT Direct3DDevice8::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
    return this->State.Self->GetTextureStageState(Stage, Type, pValue);
}

// Sets the state value for the currently assigned texture.
HRESULT Direct3DDevice8::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
    return this->State.Self->SetTextureStageState(Stage, Type, Value);
}

// Reports the device's ability to render the current texture-blending operations and arguments in a single pass.
HRESULT Direct3DDevice8::ValidateDevice(DWORD* pNumPasses)
{
    return this->State.Self->ValidateDevice(pNumPasses);
}

// Retrieves information about the rendering device.
HRESULT Direct3DDevice8::GetInfo(DWORD DevInfoID, LPVOID pDevInfoStruct, DWORD DevInfoStructSize)
{
    return this->State.Self->GetInfo(DevInfoID, pDevInfoStruct, DevInfoStructSize);
}

// Sets palette entries.
HRESULT Direct3DDevice8::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
    return this->State.Self->SetPaletteEntries(PaletteNumber, pEntries);
}

// Retrieves palette entries.
HRESULT Direct3DDevice8::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
    return this->State.Self->GetPaletteEntries(PaletteNumber, pEntries);
}

// Sets the current texture palette.
HRESULT Direct3DDevice8::SetCurrentTexturePalette(UINT PaletteNumber)
{
    return this->State.Self->SetCurrentTexturePalette(PaletteNumber);
}

// Retrieves the current texture palette.
HRESULT Direct3DDevice8::GetCurrentTexturePalette(UINT* PaletteNumber)
{
    return this->State.Self->GetCurrentTexturePalette(PaletteNumber);
}

// Renders a sequence of nonindexed, geometric primitives of the specified type from the current set of data input streams.
HRESULT Direct3DDevice8::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
    return this->State.Self->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

// Renders the indexed geometric primitive into an array of vertices.
HRESULT Direct3DDevice8::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
    return this->State.Self->DrawIndexedPrimitive(PrimitiveType, MinIndex, NumVertices, StartIndex, PrimitiveCount);
}

// Renders data specified by a user memory pointer as a sequence of geometric primitives of the specified type.
HRESULT Direct3DDevice8::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, LPCVOID pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return this->State.Self->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

// Renders the specified geometric primitive with data specified by a user memory pointer.
HRESULT Direct3DDevice8::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, LPCVOID pIndexData, D3DFORMAT IndexDataFormat, LPCVOID pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return this->State.Self->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

// Applies the vertex processing defined by the vertex shader to the set of input data streams, generating a single stream of interleaved vertex data to the destination vertex buffer. 
HRESULT Direct3DDevice8::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, LPDIRECT3DVERTEXBUFFER8 pDestBuffer, DWORD Flags)
{
    AttemptAccessAgentValue(Direct3DVertexBuffer8, pDestBuffer);

    return this->State.Self->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, Flags);
}

// Creates a vertex shader.
HRESULT Direct3DDevice8::CreateVertexShader(CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* pHandle, DWORD Usage)
{
    return this->State.Self->CreateVertexShader(pDeclaration, pFunction, pHandle, Usage);
}

// Sets the current vertex shader to a previously created vertex shader or to a flexible vertex format (FVF) fixed function shader.
HRESULT Direct3DDevice8::SetVertexShader(DWORD Handle)
{
    return this->State.Self->SetVertexShader(Handle);
}

// Retrieves the currently set vertex shader.
HRESULT Direct3DDevice8::GetVertexShader(DWORD* pHandle)
{
    return this->State.Self->GetVertexShader(pHandle);
}

// Deletes the vertex shader referred to by the specified handle and frees up the associated resources.
HRESULT Direct3DDevice8::DeleteVertexShader(DWORD Handle)
{
    return this->State.Self->DeleteVertexShader(Handle);
}

// Sets values in the vertex constant array.
HRESULT Direct3DDevice8::SetVertexShaderConstant(DWORD Register, LPCVOID pConstantData, DWORD ConstantCount)
{
    return this->State.Self->SetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

// Retrieves the values in the vertex constant array.
HRESULT Direct3DDevice8::GetVertexShaderConstant(DWORD Register, LPVOID pConstantData, DWORD ConstantCount)
{
    return this->State.Self->GetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

// Retrieves the vertex shader declaration token array.
HRESULT Direct3DDevice8::GetVertexShaderDeclaration(DWORD Handle, LPVOID pData, DWORD* pSizeOfData)
{
    return this->State.Self->GetVertexShaderDeclaration(Handle, pData, pSizeOfData);
}

// Retrieves the vertex shader function.
HRESULT Direct3DDevice8::GetVertexShaderFunction(DWORD Handle, LPVOID pData, DWORD* pSizeOfData)
{
    return this->State.Self->GetVertexShaderFunction(Handle, pData, pSizeOfData);
}

// Binds a vertex buffer to a device data stream.
HRESULT Direct3DDevice8::SetStreamSource(UINT StreamNumber, LPDIRECT3DVERTEXBUFFER8 pStreamData, UINT Stride)
{
    AttemptAccessAgentValue(Direct3DVertexBuffer8, pStreamData);

    return this->State.Self->SetStreamSource(StreamNumber, pStreamData, Stride);
}

// Retrieves a vertex buffer bound to the specified data stream.
HRESULT Direct3DDevice8::GetStreamSource(UINT StreamNumber, LPDIRECT3DVERTEXBUFFER8* ppStreamData, UINT* pStride)
{
    CONST HRESULT result = this->State.Self->GetStreamSource(StreamNumber, ppStreamData, pStride);

    if (SUCCEEDED(result)) { *ppStreamData = ActivateAgent(Direct3DVertexBuffer8, *ppStreamData); }

    return result;
}

// Sets index data.
HRESULT Direct3DDevice8::SetIndices(LPDIRECT3DINDEXBUFFER8 pIndexData, UINT BaseVertexIndex)
{
    AttemptAccessAgentValue(Direct3DIndexBuffer8, pIndexData);

    return this->State.Self->SetIndices(pIndexData, BaseVertexIndex);
}

// Retrieves index data.
HRESULT Direct3DDevice8::GetIndices(LPDIRECT3DINDEXBUFFER8* ppIndexData, UINT* pBaseVertexIndex)
{
    CONST HRESULT result = this->State.Self->GetIndices(ppIndexData, pBaseVertexIndex);

    if (SUCCEEDED(result)) { *ppIndexData = ActivateAgent(Direct3DIndexBuffer8, *ppIndexData); }

    return result;
}

// Creates a pixel shader.
HRESULT Direct3DDevice8::CreatePixelShader(CONST DWORD* pFunction, DWORD* pHandle)
{
    return this->State.Self->CreatePixelShader(pFunction, pHandle);
}

// Sets the current pixel shader to a previously created pixel shader.
HRESULT Direct3DDevice8::SetPixelShader(DWORD Handle)
{
    return this->State.Self->SetPixelShader(Handle);
}

// Retrieves the currently set pixel shader.
HRESULT Direct3DDevice8::GetPixelShader(DWORD* pHandle)
{
    return this->State.Self->GetPixelShader(pHandle);
}

// Deletes the pixel shader referred to by the specified handle.
HRESULT Direct3DDevice8::DeletePixelShader(DWORD Handle)
{
    return this->State.Self->DeletePixelShader(Handle);
}

// Sets the values in the pixel constant array.
HRESULT Direct3DDevice8::SetPixelShaderConstant(DWORD Register, LPCVOID pConstantData, DWORD ConstantCount)
{
    return this->State.Self->SetPixelShaderConstant(Register, pConstantData, ConstantCount);
}

// Retrieves the values in the pixel constant array.
HRESULT Direct3DDevice8::GetPixelShaderConstant(DWORD Register, LPVOID pConstantData, DWORD ConstantCount)
{
    return this->State.Self->GetPixelShaderConstant(Register, pConstantData, ConstantCount);
}

// Retrieves the pixel shader function.
HRESULT Direct3DDevice8::GetPixelShaderFunction(DWORD Handle, LPVOID pData, DWORD* pSizeOfData)
{
    return this->State.Self->GetPixelShaderFunction(Handle, pData, pSizeOfData);
}

// Draws a rectangular high-order patch using the currently set streams.
HRESULT Direct3DDevice8::DrawRectPatch(UINT Handle, CONST FLOAT* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
    return this->State.Self->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

// Draws a triangular high-order patch using the currently set streams.
HRESULT Direct3DDevice8::DrawTriPatch(UINT Handle, CONST FLOAT* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
    return this->State.Self->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

// Frees a cached high-order patch.
HRESULT Direct3DDevice8::DeletePatch(UINT Handle)
{
    return this->State.Self->DeletePatch(Handle);
}