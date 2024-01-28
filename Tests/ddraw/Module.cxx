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

#include "Module.hxx"

LPMODULE InitializeModule(LPCSTR path)
{
    LPMODULE result = new MODULE();

    result->hModule = LoadLibraryA(path);

    if (result->hModule == NULL) { return FALSE; }

    result->lpAcquireInternalLock = (LPACQUIREDIRECTDRAWTHREADLOCK)GetProcAddress(result->hModule, DIRECT_DRAW_ACQUIRE_DIRECT_DRAW_THREAD_LOCK_NAME);
    if (result->lpAcquireInternalLock == NULL) { ReleaseModule(result); return NULL; }

    result->lpCompleteCreateSysmemSurface = (LPCOMPLETECREATESYSTEMMEMORYSURFACE)GetProcAddress(result->hModule, DIRECT_DRAW_COMPLETE_CREATE_SYSTEM_MEMORY_SURFACE_NAME);
    if (result->lpCompleteCreateSysmemSurface == NULL) { ReleaseModule(result); return NULL; }

    result->lpParseUnknownCommand = (LPDIRECT3DPARSEUNKNOWNCOMMAND)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_3D_PARSE_UNKNOWN_COMMAND_NAME);
    if (result->lpParseUnknownCommand == NULL) { ReleaseModule(result); return NULL; }

    result->lpGetAttachedSurfaceLocal = (LPDIRECTDRAWGETATTACHEDSURFACELOCAL)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_GET_ATTACHED_SURFACE_LOCAL_NAME);
    if (result->lpGetAttachedSurfaceLocal == NULL) { ReleaseModule(result); return NULL; }

    result->lpInternalLock = (LPDIRECTDRAWINTERNALLOCK)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_INTERNAL_LOCK_NAME);
    if (result->lpInternalLock == NULL) { ReleaseModule(result); return NULL; }

    result->lpInternalUnlock = (LPDIRECTDRAWINTERNALUNLOCK)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_INTERAL_UNLOCK_NAME);
    if (result->lpInternalUnlock == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectSoundHelp = (LPDIRECTSOUNDHELP)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_SOUND_HELP_NAME);
    if (result->lpDirectSoundHelp == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectDrawCreate = (LPDIRECTDRAWCREATE)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_CREATE_NAME);
    if (result->lpDirectDrawCreate == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectDrawCreateClipper = (LPDIRECTDRAWCREATECLIPPER)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_CREATE_CLIPPER_NAME);
    if (result->lpDirectDrawCreateClipper == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectDrawCreateEx = (LPDIRECTDRAWCREATEEX)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_CREATE_EX_NAME);
    if (result->lpDirectDrawCreateEx == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectDrawEnumerateA = (LPDIRECTDRAWENUMA)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_A_NAME);
    if (result->lpDirectDrawEnumerateA == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectDrawEnumerateExA = (LPDIRECTDRAWENUMERATEEXA)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_EX_A_NAME);
    if (result->lpDirectDrawEnumerateExA == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectDrawEnumerateExW = (LPDIRECTDRAWENUMERATEEXW)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_EX_W_NAME);
    if (result->lpDirectDrawEnumerateExW == NULL) { ReleaseModule(result); return NULL; }

    result->lpDirectDrawEnumerateW = (LPDIRECTDRAWENUMW)GetProcAddress(result->hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_W_NAME);
    if (result->lpDirectDrawEnumerateW == NULL) { ReleaseModule(result); return NULL; }

    result->lpCanUnloadNow = (LPDLLCANUNLOADNOW)GetProcAddress(result->hModule, DIRECT_DRAW_CAN_UNLOAD_NOW_NAME);
    if (result->lpCanUnloadNow == NULL) { ReleaseModule(result); return NULL; }

    result->lpGetClassObject = (LPGETCLASSOBJECT)GetProcAddress(result->hModule, DIRECT_DRAW_GET_CLASS_OBJECT_NAME);
    if (result->lpGetClassObject == NULL) { ReleaseModule(result); return NULL; }

    result->lpGetDirectDrawSurfaceLocal = (LPGETDIRECTDRAWSURFACELOCAL)GetProcAddress(result->hModule, DIRECT_DRAW_GET_DIRECT_DRAW_SURFACE_LOCAL_NAME);
    if (result->lpGetDirectDrawSurfaceLocal == NULL) { ReleaseModule(result); return NULL; }

    result->lpGetOLEThunkData = (LPGETOLETHUNKDATA)GetProcAddress(result->hModule, DIRECT_DRAW_GET_OLE_THUNK_DATA_NAME);
    if (result->lpGetOLEThunkData == NULL) { ReleaseModule(result); return NULL; }

    result->lpGetSurfaceFromDeviceContext = (LPGETSURFACEFROMDEVICECONTEXT)GetProcAddress(result->hModule, DIRECT_DRAW_GET_SURFACE_FROM_DEVICE_CONTEXT_NAME);
    if (result->lpGetSurfaceFromDeviceContext == NULL) { ReleaseModule(result); return NULL; }

    result->lpRegisterSpecialCase = (LPREGISTERSPECIALCASE)GetProcAddress(result->hModule, DIRECT_DRAW_REGISTER_SPECIAL_CASE_NAME);
    if (result->lpRegisterSpecialCase == NULL) { ReleaseModule(result); return NULL; }

    result->lpReleaseThreadLock = (LPRELEASEDIRECTDRAWTHREADLOCK)GetProcAddress(result->hModule, DIRECT_DRAW_RELEASE_DIRECT_DRAW_THREAD_LOCK_NAME);
    if (result->lpReleaseThreadLock == NULL) { ReleaseModule(result); return NULL; }

    result->lpSetApplicationCompatibilityData = (LPSETAPPLICATIONCOMPATIBILITYDATA)GetProcAddress(result->hModule, DIRECT_DRAW_SET_APPLICATION_COMPATIBILITY_DATA_NAME);

    return result;
}

BOOL ReleaseModule(LPMODULE module)
{
    if (module == NULL || module->hModule == NULL) { return FALSE; }

    FreeLibrary(module->hModule);

    delete module;

    return TRUE;
}