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

#include "Direct3DBaseTexture8.hxx"
#include "Direct3DDevice8.hxx"
#include "Direct3DResource8.hxx"
#include "Direct3DSurface8.hxx"
#include "Direct3DTexture8.hxx"

Direct3DTexture8::Direct3DTexture8(AgentConstructorParameters(Direct3DTexture8))
{
    AgentConstructor();
}

Direct3DTexture8::~Direct3DTexture8()
{
    AgentDestructor();
}

HRESULT Direct3DTexture8::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DTexture8, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3DTexture8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DBaseTexture8, riid)) { *ppvObj = ActivateAgent(Direct3DBaseTexture8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DResource8, riid)) { *ppvObj = ActivateAgent(Direct3DResource8, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DTexture8::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DTexture8::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// Retrieves the device associated with a resource.
HRESULT Direct3DTexture8::GetDevice(LPDIRECT3DDEVICE8* ppDevice)
{
    CONST HRESULT result = this->State.Self->GetDevice(ppDevice);

    if (SUCCEEDED(result)) { *ppDevice = ActivateAgent(Direct3DDevice8, *ppDevice); }

    return result;
}

// Associates data with the resource that is intended for use by the application, not by Microsoft® Direct3D®.
// Data is passed by value, and multiple sets of data can be associated with a single resource.
HRESULT Direct3DTexture8::SetPrivateData(REFGUID refguid, LPCVOID pData, DWORD SizeOfData, DWORD Flags)
{
    return this->State.Self->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

// Copies the private data associated with the resource to a provided buffer.
HRESULT Direct3DTexture8::GetPrivateData(REFGUID refguid, LPVOID pData, DWORD* pSizeOfData)
{
    return this->State.Self->GetPrivateData(refguid, pData, pSizeOfData);
}

// Frees the specified private data associated with this resource.
HRESULT Direct3DTexture8::FreePrivateData(REFGUID refguid)
{
    return this->State.Self->FreePrivateData(refguid);
}

// Assigns the resource-management priority for this resource.
DWORD Direct3DTexture8::SetPriority(DWORD PriorityNew)
{
    return this->State.Self->SetPriority(PriorityNew);
}

// Retrieves the priority for this resource. 
DWORD Direct3DTexture8::GetPriority()
{
    return this->State.Self->GetPriority();
}

// Preloads a managed resource.
VOID Direct3DTexture8::PreLoad()
{
    this->State.Self->PreLoad();
}

// Returns the type of the resource.
D3DRESOURCETYPE Direct3DTexture8::GetType()
{
    return this->State.Self->GetType();
}

// Sets the most detailed level of detail (LOD) for a managed texture.
DWORD Direct3DTexture8::SetLOD(DWORD LODNew)
{
    return this->State.Self->SetLOD(LODNew);
}

// Returns a value clamped to the maximum level of detail (LOD) set for a managed texture.
DWORD Direct3DTexture8::GetLOD()
{
    return this->State.Self->GetLOD();
}

// Returns the number of texture levels in a multilevel texture.
DWORD Direct3DTexture8::GetLevelCount()
{
    return this->State.Self->GetLevelCount();
}

// Retrieves a level description of a texture resource.
HRESULT Direct3DTexture8::GetLevelDesc(UINT Level, D3DSURFACE_DESC* pDesc)
{
    return this->State.Self->GetLevelDesc(Level, pDesc);
}

// Retrieves the specified texture surface level.
HRESULT Direct3DTexture8::GetSurfaceLevel(UINT Level, LPDIRECT3DSURFACE8* ppSurfaceLevel)
{
    CONST HRESULT result = this->State.Self->GetSurfaceLevel(Level, ppSurfaceLevel);

    if (SUCCEEDED(result)) { *ppSurfaceLevel = ActivateAgent(Direct3DSurface8, *ppSurfaceLevel); }

    return result;
}

// Locks a rectangle on a texture resource.
HRESULT Direct3DTexture8::LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
    return this->State.Self->LockRect(Level, pLockedRect, pRect, Flags);
}

// Unlocks a rectangle on a texture resource.
HRESULT Direct3DTexture8::UnlockRect(UINT Level)
{
    return this->State.Self->UnlockRect(Level);
}

// Adds a dirty region to a texture resource.
HRESULT Direct3DTexture8::AddDirtyRect(CONST RECT* pDirtyRect)
{
    return this->State.Self->AddDirtyRect(pDirtyRect);
}