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
#include "Direct3DVolume8.hxx"
#include "Direct3DVolumeTexture8.hxx"

Direct3DVolumeTexture8::Direct3DVolumeTexture8(AgentConstructorParameters(Direct3DVolumeTexture8))
{
    AgentConstructor();
}

Direct3DVolumeTexture8::~Direct3DVolumeTexture8()
{
    AgentDestructor();
}

HRESULT Direct3DVolumeTexture8::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DVolumeTexture8, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3DVolumeTexture8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DBaseTexture8, riid)) { *ppvObj = ActivateAgent(Direct3DBaseTexture8, *ppvObj); }
            else if (IsEqualIID(IID_IDirect3DResource8, riid)) { *ppvObj = ActivateAgent(Direct3DResource8, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DVolumeTexture8::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DVolumeTexture8::Release()
{
    CONST ULONG result = this->State.Self->Release();

    //if (result == 0) { delete this; }

    return result;
}

// Retrieves the device associated with a resource.
HRESULT Direct3DVolumeTexture8::GetDevice(LPDIRECT3DDEVICE8* ppDevice)
{
    CONST HRESULT result = this->State.Self->GetDevice(ppDevice);

    if (SUCCEEDED(result)) { *ppDevice = ActivateAgent(Direct3DDevice8, *ppDevice); }

    return result;
}

// Associates data with the resource that is intended for use by the application, not by Microsoft® Direct3D®.
// Data is passed by value, and multiple sets of data can be associated with a single resource.
HRESULT Direct3DVolumeTexture8::SetPrivateData(REFGUID refguid, LPCVOID pData, DWORD SizeOfData, DWORD Flags)
{
    return this->State.Self->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

// Copies the private data associated with the resource to a provided buffer.
HRESULT Direct3DVolumeTexture8::GetPrivateData(REFGUID refguid, LPVOID pData, DWORD* pSizeOfData)
{
    return this->State.Self->GetPrivateData(refguid, pData, pSizeOfData);
}

// Frees the specified private data associated with this resource.
HRESULT Direct3DVolumeTexture8::FreePrivateData(REFGUID refguid)
{
    return this->State.Self->FreePrivateData(refguid);
}

// Assigns the resource-management priority for this resource.
DWORD Direct3DVolumeTexture8::SetPriority(DWORD PriorityNew)
{
    return this->State.Self->SetPriority(PriorityNew);
}

// Retrieves the priority for this resource. 
DWORD Direct3DVolumeTexture8::GetPriority()
{
    return this->State.Self->GetPriority();
}

// Preloads a managed resource.
VOID Direct3DVolumeTexture8::PreLoad()
{
    this->State.Self->PreLoad();
}

// Returns the type of the resource.
D3DRESOURCETYPE Direct3DVolumeTexture8::GetType()
{
    return this->State.Self->GetType();
}

// Sets the most detailed level of detail (LOD) for a managed texture.
DWORD Direct3DVolumeTexture8::SetLOD(DWORD LODNew)
{
    return this->State.Self->SetLOD(LODNew);
}

// Returns a value clamped to the maximum level of detail (LOD) set for a managed texture.
DWORD Direct3DVolumeTexture8::GetLOD()
{
    return this->State.Self->GetLOD();
}

// Returns the number of texture levels in a multilevel texture.
DWORD Direct3DVolumeTexture8::GetLevelCount()
{
    return this->State.Self->GetLevelCount();
}

// Retrieves a level description of a volume texture resource.
HRESULT Direct3DVolumeTexture8::GetLevelDesc(UINT Level, D3DVOLUME_DESC* pDesc)
{
    return this->State.Self->GetLevelDesc(Level, pDesc);
}

// Retrieves the specified volume texture level.
HRESULT Direct3DVolumeTexture8::GetVolumeLevel(UINT Level, LPDIRECT3DVOLUME8* ppVolumeLevel)
{
    CONST HRESULT result = this->State.Self->GetVolumeLevel(Level, ppVolumeLevel);

    if (SUCCEEDED(result)) { *ppVolumeLevel = ActivateAgent(Direct3DVolume8, *ppVolumeLevel); }

    return result;
}

// Locks a box on a volume texture resource.
HRESULT Direct3DVolumeTexture8::LockBox(UINT Level, D3DLOCKED_BOX* pLockedVolume, CONST D3DBOX* pBox, DWORD Flags)
{
    return this->State.Self->LockBox(Level, pLockedVolume, pBox, Flags);
}

// Unlocks a box on a volume texture resource.
HRESULT Direct3DVolumeTexture8::UnlockBox(UINT Level)
{
    return this->State.Self->UnlockBox(Level);
}

// Adds a dirty region to a volume texture resource.
HRESULT Direct3DVolumeTexture8::AddDirtyBox(CONST D3DBOX* pDirtyBox)
{
    return this->State.Self->AddDirtyBox(pDirtyBox);
}