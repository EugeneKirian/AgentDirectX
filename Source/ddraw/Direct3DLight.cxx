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

Direct3DLight::Direct3DLight(AgentConstructorParameters(Direct3DLight))
{
    AgentConstructor();
}

Direct3DLight::~Direct3DLight()
{
    AgentDestructor();
}

HRESULT Direct3DLight::QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
{
    CONST HRESULT result = this->State.Self->QueryInterface(riid, ppvObj);

    if (SUCCEEDED(result))
    {
        if (!AcquireAgent(riid, ppvObj))
        {
            if (IsEqualIID(IID_IDirect3DLight, riid) || IsEqualIID(IID_IUnknown, riid)) { *ppvObj = ActivateAgent(Direct3DLight, *ppvObj); }
            /* else { HANDLE UNKNOWN IDENTIFIER } */
        }
    }

    return result;
}

ULONG Direct3DLight::AddRef()
{
    return this->State.Self->AddRef();
}

ULONG Direct3DLight::Release()
{
    CONST ULONG result = this->State.Self->Release();

    if (result == 0) { delete this; }

    return result;
}

// This method is not currently implemented.
HRESULT Direct3DLight::Initialize(LPDIRECT3D lpDirect3D)
{
    AttemptAccessAgentValue(Direct3D, lpDirect3D);

    return this->State.Self->Initialize(lpDirect3D);
}

// Sets the light information for the Direct3DLight object.
HRESULT Direct3DLight::SetLight(LPD3DLIGHT lpLight)
{
    return this->State.Self->SetLight(lpLight);
}

// Retrieves the light information for the Direct3DLight object.
HRESULT Direct3DLight::GetLight(LPD3DLIGHT lpLight)
{
    return this->State.Self->GetLight(lpLight);
}