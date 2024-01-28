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

ModuleState Module;

BOOL InitializeModule()
{
    char directory[DIRECT_DRAW_LIBRARY_PATH_LENGTH];
    ZeroMemory(directory, DIRECT_DRAW_LIBRARY_PATH_LENGTH);

    if (GetSystemDirectoryA(directory, DIRECT_DRAW_LIBRARY_PATH_LENGTH) >= DIRECT_DRAW_LIBRARY_PATH_LENGTH) { return FALSE; }

    char path[DIRECT_DRAW_LIBRARY_FILE_PATH_LENGTH];
    ZeroMemory(path, DIRECT_DRAW_LIBRARY_FILE_PATH_LENGTH);

    if (PathCombineA(path, directory, DIRECT_DRAW_LIBRARY_NAME) == NULL) { return FALSE; }

    Module.hModule = LoadLibraryA(path);

    if (Module.hModule == NULL) { return FALSE; }

    Module.lpAcquireInternalLock = (LPACQUIREDIRECTDRAWTHREADLOCK)GetProcAddress(Module.hModule, DIRECT_DRAW_ACQUIRE_DIRECT_DRAW_THREAD_LOCK_NAME);
    if (Module.lpAcquireInternalLock == NULL) { ReleaseModule(); return NULL; }

    Module.lpCompleteCreateSysmemSurface = (LPCOMPLETECREATESYSTEMMEMORYSURFACE)GetProcAddress(Module.hModule, DIRECT_DRAW_COMPLETE_CREATE_SYSTEM_MEMORY_SURFACE_NAME);
    if (Module.lpCompleteCreateSysmemSurface == NULL) { ReleaseModule(); return NULL; }

    Module.lpParseUnknownCommand = (LPDIRECT3DPARSEUNKNOWNCOMMAND)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_3D_PARSE_UNKNOWN_COMMAND_NAME);
    if (Module.lpParseUnknownCommand == NULL) { ReleaseModule(); return NULL; }

    Module.lpGetAttachedSurfaceLocal = (LPDIRECTDRAWGETATTACHEDSURFACELOCAL)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_GET_ATTACHED_SURFACE_LOCAL_NAME);
    if (Module.lpGetAttachedSurfaceLocal == NULL) { ReleaseModule(); return NULL; }

    Module.lpInternalLock = (LPDIRECTDRAWINTERNALLOCK)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_INTERNAL_LOCK_NAME);
    if (Module.lpInternalLock == NULL) { ReleaseModule(); return NULL; }

    Module.lpInternalUnlock = (LPDIRECTDRAWINTERNALUNLOCK)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_INTERAL_UNLOCK_NAME);
    if (Module.lpInternalUnlock == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectSoundHelp = (LPDIRECTSOUNDHELP)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_SOUND_HELP_NAME);
    if (Module.lpDirectSoundHelp == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectDrawCreate = (LPDIRECTDRAWCREATE)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_CREATE_NAME);
    if (Module.lpDirectDrawCreate == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectDrawCreateClipper = (LPDIRECTDRAWCREATECLIPPER)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_CREATE_CLIPPER_NAME);
    if (Module.lpDirectDrawCreateClipper == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectDrawCreateEx = (LPDIRECTDRAWCREATEEX)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_CREATE_EX_NAME);
    if (Module.lpDirectDrawCreateEx == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectDrawEnumerateA = (LPDIRECTDRAWENUMA)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_A_NAME);
    if (Module.lpDirectDrawEnumerateA == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectDrawEnumerateExA = (LPDIRECTDRAWENUMERATEEXA)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_EX_A_NAME);
    if (Module.lpDirectDrawEnumerateExA == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectDrawEnumerateExW = (LPDIRECTDRAWENUMERATEEXW)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_EX_W_NAME);
    if (Module.lpDirectDrawEnumerateExW == NULL) { ReleaseModule(); return NULL; }

    Module.lpDirectDrawEnumerateW = (LPDIRECTDRAWENUMW)GetProcAddress(Module.hModule, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_W_NAME);
    if (Module.lpDirectDrawEnumerateW == NULL) { ReleaseModule(); return NULL; }

    Module.lpCanUnloadNow = (LPDLLCANUNLOADNOW)GetProcAddress(Module.hModule, DIRECT_DRAW_CAN_UNLOAD_NOW_NAME);
    if (Module.lpCanUnloadNow == NULL) { ReleaseModule(); return NULL; }

    Module.lpGetClassObject = (LPGETCLASSOBJECT)GetProcAddress(Module.hModule, DIRECT_DRAW_GET_CLASS_OBJECT_NAME);
    if (Module.lpGetClassObject == NULL) { ReleaseModule(); return NULL; }

    Module.lpGetDirectDrawSurfaceLocal = (LPGETDIRECTDRAWSURFACELOCAL)GetProcAddress(Module.hModule, DIRECT_DRAW_GET_DIRECT_DRAW_SURFACE_LOCAL_NAME);
    if (Module.lpGetDirectDrawSurfaceLocal == NULL) { ReleaseModule(); return NULL; }

    Module.lpGetOLEThunkData = (LPGETOLETHUNKDATA)GetProcAddress(Module.hModule, DIRECT_DRAW_GET_OLE_THUNK_DATA_NAME);
    if (Module.lpGetOLEThunkData == NULL) { ReleaseModule(); return NULL; }

    Module.lpGetSurfaceFromDeviceContext = (LPGETSURFACEFROMDEVICECONTEXT)GetProcAddress(Module.hModule, DIRECT_DRAW_GET_SURFACE_FROM_DEVICE_CONTEXT_NAME);
    if (Module.lpGetSurfaceFromDeviceContext == NULL) { ReleaseModule(); return NULL; }

    Module.lpRegisterSpecialCase = (LPREGISTERSPECIALCASE)GetProcAddress(Module.hModule, DIRECT_DRAW_REGISTER_SPECIAL_CASE_NAME);
    if (Module.lpRegisterSpecialCase == NULL) { ReleaseModule(); return NULL; }

    Module.lpReleaseThreadLock = (LPRELEASEDIRECTDRAWTHREADLOCK)GetProcAddress(Module.hModule, DIRECT_DRAW_RELEASE_DIRECT_DRAW_THREAD_LOCK_NAME);
    if (Module.lpReleaseThreadLock == NULL) { ReleaseModule(); return NULL; }

    Module.lpSetApplicationCompatibilityData = (LPSETAPPLICATIONCOMPATIBILITYDATA)GetProcAddress(Module.hModule, DIRECT_DRAW_SET_APPLICATION_COMPATIBILITY_DATA_NAME);

    Module.Assembler = new Assembler();

    Module.Initialized = TRUE;

    return TRUE;
}

BOOL ReleaseModule()
{
    delete Module.Assembler;

    BOOL result = Module.hModule != NULL ? FreeLibrary(Module.hModule) : FALSE;

    ZeroMemory(&Module, sizeof(ModuleState));

    return result;
}