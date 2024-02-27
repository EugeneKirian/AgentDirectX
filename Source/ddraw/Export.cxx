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

#include "Base.hxx"

#include "DirectDraw.hxx"
#include "DirectDraw7.hxx"
#include "DirectDrawClipper.hxx"

#include "Export.hxx"
#include "Module.hxx"

struct DirectDrawEnumerateCallbackContextA
{
    LPDDENUMCALLBACKA lpCallback;
    LPVOID lpContext;
};

struct DirectDrawEnumerateCallbackContextW
{
    LPDDENUMCALLBACKW lpCallback;
    LPVOID lpContext;
};

struct DirectDrawEnumerateExCallbackContextA
{
    LPDDENUMCALLBACKEXA lpCallback;
    LPVOID lpContext;
};

struct DirectDrawEnumerateExCallbackContextW
{
    LPDDENUMCALLBACKEXW lpCallback;
    LPVOID lpContext;
};

static BOOL CALLBACK DirectDrawEnumerateCallbackA(LPGUID lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext)
{
    DirectDrawEnumerateCallbackContextA* context = (DirectDrawEnumerateCallbackContextA*)lpContext;

    return context->lpCallback(lpGUID, lpDriverDescription, lpDriverName, context->lpContext);
}

static BOOL CALLBACK DirectDrawEnumerateExCallbackA(LPGUID lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hMonitor)
{
    DirectDrawEnumerateExCallbackContextA* context = (DirectDrawEnumerateExCallbackContextA*)lpContext;

    return context->lpCallback(lpGUID, lpDriverDescription, lpDriverName, context->lpContext, hMonitor);
}

static BOOL CALLBACK DirectDrawEnumerateExCallbackW(LPGUID lpGUID, LPWSTR lpDriverDescription, LPWSTR lpDriverName, LPVOID lpContext, HMONITOR hMonitor)
{
    DirectDrawEnumerateExCallbackContextW* context = (DirectDrawEnumerateExCallbackContextW*)lpContext;

    return context->lpCallback(lpGUID, lpDriverDescription, lpDriverName, context->lpContext, hMonitor);
}

static BOOL CALLBACK DirectDrawEnumerateCallbackW(LPGUID lpGUID, LPWSTR lpDriverDescription, LPWSTR lpDriverName, LPVOID lpContext)
{
    DirectDrawEnumerateCallbackContextW* context = (DirectDrawEnumerateCallbackContextW*)lpContext;

    return context->lpCallback(lpGUID, lpDriverDescription, lpDriverName, context->lpContext);
}

extern "C" VOID WINAPI AcquireDDThreadLock()
{
    Module.AcquireInternalLock();
}

extern "C" BOOL WINAPI CompleteCreateSysmemSurface(LPDDRAWI_DDRAWSURFACE_LCL lpSurfLcl)
{
    return Module.CompleteCreateSysmemSurface(lpSurfLcl);
}

extern "C" HRESULT WINAPI D3DParseUnknownCommand(LPVOID lpvCommands, LPVOID * lplpvReturnedCommand)
{
    return Module.ParseUnknownCommand(lpvCommands, lplpvReturnedCommand);
}

extern "C" HRESULT WINAPI DDGetAttachedSurfaceLcl(LPDDRAWI_DDRAWSURFACE_LCL this_lcl, LPDDSCAPS2 lpDDSCaps, LPDDRAWI_DDRAWSURFACE_LCL * lplpDDAttachedSurfaceLcl)
{
    return Module.GetAttachedSurfaceLocal(this_lcl, lpDDSCaps, lplpDDAttachedSurfaceLcl);
}

extern "C" HRESULT WINAPI DDInternalLock(LPDDRAWI_DDRAWSURFACE_LCL this_lcl, LPVOID * lpBits)
{
    return Module.InternalLock(this_lcl, lpBits);
}

extern "C" HRESULT WINAPI DDInternalUnlock(LPDDRAWI_DDRAWSURFACE_LCL this_lcl)
{
    return Module.InternalUnlock(this_lcl);
}

extern "C" HRESULT WINAPI DSoundHelp(HWND hWnd, WNDPROC lpWndProc, DWORD pid)
{
    return Module.DirectSoundHelp(hWnd, lpWndProc, pid);
}

// Creates an instance of a DirectDraw object.
extern "C" HRESULT WINAPI DirectDrawCreate(LPGUID lpGUID, LPDIRECTDRAW * lplpDD, LPUNKNOWN pUnkOuter)
{
    CONST HRESULT result = Module.DirectDrawCreate(lpGUID, lplpDD, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDD = AssembleAgent(DirectDraw, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), *lplpDD); }

    return result;
}

// Creates an instance of a DirectDrawClipper object not associated with a DirectDraw object.
extern "C" HRESULT WINAPI DirectDrawCreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER * lplpDDClipper, LPUNKNOWN pUnkOuter)
{
    CONST HRESULT result = Module.DirectDrawCreateClipper(dwFlags, lplpDDClipper, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDDClipper = AssembleAgent(DirectDrawClipper, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), *lplpDDClipper); }

    return result;
}

// Creates an instance of a DirectDraw object that supports the set of Direct3D interfaces in DirectX 7.0.
extern "C" HRESULT WINAPI DirectDrawCreateEx(LPGUID lpGuid, LPVOID * lplpDD, REFIID iid, LPUNKNOWN pUnkOuter)
{
    CONST HRESULT result = Module.DirectDrawCreateEx(lpGuid, lplpDD, iid, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDD = AssembleAgent(DirectDraw7, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), *lplpDD); }

    return result;
}

// Enumerates the primary DirectDraw display device and a non-display device
// (such as a 3-D accelerator that has no 2-D capabilities) if one is installed.
// The NULL entry always identifies the primary display device shared with GDI.
extern "C" HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext)
{
    if (lpCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumerateCallbackContextA context;

    context.lpCallback = lpCallback;
    context.lpContext = lpContext;

    return Module.DirectDrawEnumerateA(DirectDrawEnumerateCallbackA, &context);
}

// Enumerates all DirectDraw devices installed on the system.
// The NULL entry always identifies the primary display device shared with GDI.
extern "C" HRESULT WINAPI DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA lpCallback, LPVOID lpContext, DWORD dwFlags)
{
    if (lpCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumerateExCallbackContextA context;

    context.lpCallback = lpCallback;
    context.lpContext = lpContext;

    return Module.DirectDrawEnumerateExA(DirectDrawEnumerateExCallbackA, &context, dwFlags);
}

// Enumerates all DirectDraw devices installed on the system.
// The NULL entry always identifies the primary display device shared with GDI.
extern "C" HRESULT WINAPI DirectDrawEnumerateExW(LPDDENUMCALLBACKEXW lpCallback, LPVOID lpContext, DWORD dwFlags)
{
    if (lpCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumerateExCallbackContextW context;

    context.lpCallback = lpCallback;
    context.lpContext = lpContext;

    return Module.DirectDrawEnumerateExW(DirectDrawEnumerateExCallbackW, &context, dwFlags);
}

// Enumerates the primary DirectDraw display device and a non-display device
// (such as a 3-D accelerator that has no 2-D capabilities) if one is installed.
// The NULL entry always identifies the primary display device shared with GDI.
extern "C" HRESULT WINAPI DirectDrawEnumerateW(LPDDENUMCALLBACKW lpCallback, LPVOID lpContext)
{
    if (lpCallback == NULL) { return DDERR_INVALIDPARAMS; }

    DirectDrawEnumerateCallbackContextW context;

    context.lpCallback = lpCallback;
    context.lpContext = lpContext;

    return Module.DirectDrawEnumerateW(DirectDrawEnumerateCallbackW, &context);
}

extern "C" HRESULT WINAPI DllCanUnloadNow()
{
    return Module.DllCanUnloadNow();
}

extern "C" HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID * ppv)
{
    return Module.DllGetClassObject(rclsid, riid, ppv);
}

extern "C" LPDDRAWI_DDRAWSURFACE_LCL WINAPI GetDDSurfaceLocal(LPDDRAWI_DIRECTDRAW_LCL this_lcl, DWORD handle, BOOL * isnew)
{
    return Module.GetDirectDrawSurfaceLocal(this_lcl, handle, isnew);
}

extern "C" ULONG_PTR WINAPI GetOLEThunkData(ULONG_PTR dwOrdinal)
{
    return Module.GetOLEThunkData(dwOrdinal);
}

extern "C" HRESULT WINAPI GetSurfaceFromDC(HDC hDC, LPDIRECTDRAWSURFACE * ppdds, HDC * phdcDriver)
{
    return Module.GetSurfaceFromDeviceContext(hDC, ppdds, phdcDriver);
}

extern "C" HRESULT WINAPI RegisterSpecialCase(DWORD dwParam1, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4)
{
    return Module.RegisterSpecialCase(dwParam1, dwParam2, dwParam3, dwParam4);
}

extern "C" VOID WINAPI ReleaseDDThreadLock()
{
    Module.ReleaseThreadLock();
}

extern "C" HRESULT WINAPI SetAppCompatData(DWORD dwType, DWORD dwValue)
{
    if (Module.SetApplicationCompatibilityData == NULL) { return DDERR_UNSUPPORTED; }

    return Module.SetApplicationCompatibilityData(dwType, dwValue);
}