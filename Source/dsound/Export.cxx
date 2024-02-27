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

#include "DirectSound.hxx"
#include "DirectSound8.hxx"
#include "DirectSoundBuffer8.hxx"
#include "DirectSoundCapture.hxx"
#include "DirectSoundCaptureBuffer8.hxx"
#include "DirectSoundFullDuplex.hxx"

#include "Export.hxx"
#include "Module.hxx"

struct DirectSoundCaptureEnumerateCallbackContextA
{
    LPDSENUMCALLBACKA lpDSEnumCallback;
    LPVOID lpContext;
};

static BOOL CALLBACK DirectSoundCaptureEnumerateCallbackA(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
    DirectSoundCaptureEnumerateCallbackContextA* context = (DirectSoundCaptureEnumerateCallbackContextA*)lpContext;

    return context->lpDSEnumCallback(lpGuid, lpcstrDescription, lpcstrModule, context->lpContext);
}

struct DirectSoundCaptureEnumerateCallbackContextW
{
    LPDSENUMCALLBACKW lpDSEnumCallback;
    LPVOID lpContext;
};

static BOOL CALLBACK DirectSoundCaptureEnumerateCallbackW(LPGUID lpGuid, LPCWSTR lpcstrDescription, LPCWSTR lpcstrModule, LPVOID lpContext)
{
    DirectSoundCaptureEnumerateCallbackContextW* context = (DirectSoundCaptureEnumerateCallbackContextW*)lpContext;

    return context->lpDSEnumCallback(lpGuid, lpcstrDescription, lpcstrModule, context->lpContext);
}

struct DirectSoundEnumerateCallbackContextA
{
    LPDSENUMCALLBACKA lpDSEnumCallback;
    LPVOID lpContext;
};

static BOOL CALLBACK DirectSoundEnumerateCallbackA(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
    DirectSoundEnumerateCallbackContextA* context = (DirectSoundEnumerateCallbackContextA*)lpContext;

    return context->lpDSEnumCallback(lpGuid, lpcstrDescription, lpcstrModule, context->lpContext);
}

struct DirectSoundEnumerateCallbackContextW
{
    LPDSENUMCALLBACKW lpDSEnumCallback;
    LPVOID lpContext;
};

static BOOL CALLBACK DirectSoundEnumerateCallbackW(LPGUID lpGuid, LPCWSTR lpcstrDescription, LPCWSTR lpcstrModule, LPVOID lpContext)
{
    DirectSoundEnumerateCallbackContextW* context = (DirectSoundEnumerateCallbackContextW*)lpContext;

    return context->lpDSEnumCallback(lpGuid, lpcstrDescription, lpcstrModule, context->lpContext);
}

// The DirectSoundCaptureCreate function creates and initializes an object that supports the IDirectSoundCapture interface.
extern "C" HRESULT WINAPI DirectSoundCaptureCreate(LPCGUID lpcGUID, LPDIRECTSOUNDCAPTURE * lplpDSC, LPUNKNOWN pUnkOuter)
{
    CONST HRESULT result = Module.DirectSoundCaptureCreate(lpcGUID, lplpDSC, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDSC = AssembleAgent(DirectSoundCapture, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), *lplpDSC); }

    return result;
}

// The DirectSoundCaptureCreate8 function creates and initializes an object that supports the IDirectSoundCapture8 interface.
// Although the older DirectSoundCaptureCreate function can also be used to obtain the IDirectSoundCapture8 interface,
// the object created by that function cannot be used to create capture buffers that support the IDirectSoundCaptureBuffer8 interface.
extern "C" HRESULT WINAPI DirectSoundCaptureCreate8(LPCGUID lpcGUID, LPDIRECTSOUNDCAPTURE8 * lplpDSC, LPUNKNOWN pUnkOuter)
{
    if (Module.DirectSoundCaptureCreate8 == NULL) { return DSERR_UNSUPPORTED; }

    CONST HRESULT result = Module.DirectSoundCaptureCreate8(lpcGUID, lplpDSC, pUnkOuter);

    if (SUCCEEDED(result)) { *lplpDSC = AssembleAgent(DirectSoundCapture, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), *lplpDSC); }

    return result;
}

// The DirectSoundCaptureEnumerate function enumerates the DirectSoundCapture objects installed in the system.
extern "C" HRESULT WINAPI DirectSoundCaptureEnumerateA(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext)
{
    if (lpDSEnumCallback == NULL) { return DSERR_INVALIDPARAM; }

    DirectSoundCaptureEnumerateCallbackContextA context;

    context.lpDSEnumCallback = lpDSEnumCallback;
    context.lpContext = lpContext;

    return Module.DirectSoundCaptureEnumerateA(DirectSoundCaptureEnumerateCallbackA, &context);
}

// The DirectSoundCaptureEnumerate function enumerates the DirectSoundCapture objects installed in the system.
extern "C" HRESULT WINAPI DirectSoundCaptureEnumerateW(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext)
{
    if (lpDSEnumCallback == NULL) { return DSERR_INVALIDPARAM; }

    DirectSoundCaptureEnumerateCallbackContextW context;

    context.lpDSEnumCallback = lpDSEnumCallback;
    context.lpContext = lpContext;

    return Module.DirectSoundCaptureEnumerateW(DirectSoundCaptureEnumerateCallbackW, &context);
}

// This function creates and initializes an IDirectSound interface.
extern "C" HRESULT WINAPI DirectSoundCreate(LPCGUID lpcGuid, LPDIRECTSOUND * ppDS, LPUNKNOWN pUnkOuter)
{
    CONST HRESULT result = Module.DirectSoundCreate(lpcGuid, ppDS, pUnkOuter);

    if (SUCCEEDED(result)) { *ppDS = AssembleAgent(DirectSound, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), *ppDS); }

    return result;
}

// The DirectSoundCreate8 function creates and initializes an object that supports the IDirectSound8 interface.
extern "C" HRESULT WINAPI DirectSoundCreate8(LPCGUID lpcGuidDevice, LPDIRECTSOUND8 * ppDS8, LPUNKNOWN pUnkOuter)
{
    if (Module.DirectSoundCreate8 == NULL) { return DSERR_UNSUPPORTED; }

    CONST HRESULT result = Module.DirectSoundCreate8(lpcGuidDevice, ppDS8, pUnkOuter);

    if (SUCCEEDED(result)) { *ppDS8 = AssembleAgent(DirectSound8, Module.Assembler, (new AssemblerDelegate(Module.Assembler)), *ppDS8); }

    return result;
}

// The DirectSoundEnumerate function enumerates the DirectSound drivers installed in the system.
extern "C" HRESULT WINAPI DirectSoundEnumerateA(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext)
{
    if (lpDSEnumCallback == NULL) { return DSERR_INVALIDPARAM; }

    DirectSoundEnumerateCallbackContextA context;

    context.lpDSEnumCallback = lpDSEnumCallback;
    context.lpContext = lpContext;

    return Module.DirectSoundEnumerateA(DirectSoundEnumerateCallbackA, &context);
}

// The DirectSoundEnumerate function enumerates the DirectSound drivers installed in the system.
extern "C" HRESULT WINAPI DirectSoundEnumerateW(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext)
{
    if (lpDSEnumCallback == NULL) { return DSERR_INVALIDPARAM; }

    DirectSoundEnumerateCallbackContextW context;

    context.lpDSEnumCallback = lpDSEnumCallback;
    context.lpContext = lpContext;

    return Module.DirectSoundEnumerateW(DirectSoundEnumerateCallbackW, &context);
}

// he DirectSoundFullDuplexCreate8 function creates the DirectSound and DirectSoundCapture objects and returns the IDirectSoundFullDuplex8 interface.
// This function requires Microsoft Windows XP. Full duplex can be implemented on other operating systems, but the capture and rendering devices must be created separately.
extern "C" HRESULT WINAPI DirectSoundFullDuplexCreate(LPCGUID pcGuidCaptureDevice, LPCGUID pcGuidRenderDevice, LPCDSCBUFFERDESC pcDSCBufferDesc, LPCDSBUFFERDESC pcDSBufferDesc, HWND hWnd, DWORD dwLevel, LPDIRECTSOUNDFULLDUPLEX * ppDSFD, LPDIRECTSOUNDCAPTUREBUFFER8 * ppDSCBuffer8, LPDIRECTSOUNDBUFFER8 * ppDSBuffer8, LPUNKNOWN pUnkOuter)
{
    if (Module.DirectSoundFullDuplexCreate == NULL) { return DSERR_UNSUPPORTED; }

    CONST HRESULT result = Module.DirectSoundFullDuplexCreate(pcGuidCaptureDevice, pcGuidRenderDevice, pcDSCBufferDesc, pcDSBufferDesc, hWnd, dwLevel, ppDSFD, ppDSCBuffer8, ppDSBuffer8, pUnkOuter);

    if (SUCCEEDED(result))
    {
        LPASSEMBLERDELEGATE delegate = new AssemblerDelegate(Module.Assembler);

        *ppDSFD = AssembleAgent(DirectSoundFullDuplex, Module.Assembler, delegate, *ppDSFD);
        *ppDSCBuffer8 = AssembleAgent(DirectSoundCaptureBuffer8, Module.Assembler, delegate, *ppDSCBuffer8);
        *ppDSBuffer8 = AssembleAgent(DirectSoundBuffer8, Module.Assembler, delegate, *ppDSBuffer8);
    }

    return result;
}

extern "C" HRESULT WINAPI DllCanUnloadNow()
{
    return Module.DllCanUnloadNow();
}

extern "C" HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID * ppv)
{
    return Module.DllGetClassObject(rclsid, riid, ppv);
}

// The GetDeviceID function retrieves the unique device identifier of the default playback and capture devices selected by the user in Control Panel.
extern "C" HRESULT WINAPI GetDeviceID(LPCGUID pGuidSrc, LPGUID pGuidDest)
{
    return Module.GetDeviceID(pGuidSrc, pGuidDest);
}