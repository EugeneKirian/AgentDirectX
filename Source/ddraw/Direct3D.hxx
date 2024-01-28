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

#pragma once

#include "Assembler.hxx"

class Direct3D : public IDirect3D
{
public:
    Direct3D(AgentConstructorParameters(Direct3D));
    virtual ~Direct3D();

    /*** IUnknown ***/

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID* ppvObj);
    STDMETHOD_(ULONG, AddRef)(THIS);
    STDMETHOD_(ULONG, Release)(THIS);

    /*** IDirect3D ***/

    STDMETHOD(Initialize)(THIS_ REFCLSID);
    STDMETHOD(EnumDevices)(THIS_ LPD3DENUMDEVICESCALLBACK, LPVOID);
    STDMETHOD(CreateLight)(THIS_ LPDIRECT3DLIGHT*, IUnknown*);
    STDMETHOD(CreateMaterial)(THIS_ LPDIRECT3DMATERIAL*, IUnknown*);
    STDMETHOD(CreateViewport)(THIS_ LPDIRECT3DVIEWPORT*, IUnknown*);
    STDMETHOD(FindDevice)(THIS_ LPD3DFINDDEVICESEARCH, LPD3DFINDDEVICERESULT);

protected:
    AgentStateStruct(Direct3D);
};