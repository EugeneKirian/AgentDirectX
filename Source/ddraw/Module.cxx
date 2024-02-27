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

    Module.Module = LoadLibraryA(path);

    if (Module.Module == NULL) { return FALSE; }

    Module.AcquireInternalLock = (LPACQUIREDIRECTDRAWTHREADLOCK)GetProcAddress(Module.Module, DIRECT_DRAW_ACQUIRE_DIRECT_DRAW_THREAD_LOCK_NAME);
    if (Module.AcquireInternalLock == NULL) { ReleaseModule(); return NULL; }

    Module.CompleteCreateSysmemSurface = (LPCOMPLETECREATESYSTEMMEMORYSURFACE)GetProcAddress(Module.Module, DIRECT_DRAW_COMPLETE_CREATE_SYSTEM_MEMORY_SURFACE_NAME);
    if (Module.CompleteCreateSysmemSurface == NULL) { ReleaseModule(); return NULL; }

    Module.ParseUnknownCommand = (LPDIRECT3DPARSEUNKNOWNCOMMAND)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_3D_PARSE_UNKNOWN_COMMAND_NAME);
    if (Module.ParseUnknownCommand == NULL) { ReleaseModule(); return NULL; }

    Module.GetAttachedSurfaceLocal = (LPDIRECTDRAWGETATTACHEDSURFACELOCAL)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_GET_ATTACHED_SURFACE_LOCAL_NAME);
    if (Module.GetAttachedSurfaceLocal == NULL) { ReleaseModule(); return NULL; }

    Module.InternalLock = (LPDIRECTDRAWINTERNALLOCK)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_INTERNAL_LOCK_NAME);
    if (Module.InternalLock == NULL) { ReleaseModule(); return NULL; }

    Module.InternalUnlock = (LPDIRECTDRAWINTERNALUNLOCK)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_INTERAL_UNLOCK_NAME);
    if (Module.InternalUnlock == NULL) { ReleaseModule(); return NULL; }

    Module.DirectSoundHelp = (LPDIRECTSOUNDHELP)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_SOUND_HELP_NAME);
    if (Module.DirectSoundHelp == NULL) { ReleaseModule(); return NULL; }

    Module.DirectDrawCreate = (LPDIRECTDRAWCREATE)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_CREATE_NAME);
    if (Module.DirectDrawCreate == NULL) { ReleaseModule(); return NULL; }

    Module.DirectDrawCreateClipper = (LPDIRECTDRAWCREATECLIPPER)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_CREATE_CLIPPER_NAME);
    if (Module.DirectDrawCreateClipper == NULL) { ReleaseModule(); return NULL; }

    Module.DirectDrawCreateEx = (LPDIRECTDRAWCREATEEX)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_CREATE_EX_NAME);
    if (Module.DirectDrawCreateEx == NULL) { ReleaseModule(); return NULL; }

    Module.DirectDrawEnumerateA = (LPDIRECTDRAWENUMA)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_A_NAME);
    if (Module.DirectDrawEnumerateA == NULL) { ReleaseModule(); return NULL; }

    Module.DirectDrawEnumerateExA = (LPDIRECTDRAWENUMERATEEXA)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_EX_A_NAME);
    if (Module.DirectDrawEnumerateExA == NULL) { ReleaseModule(); return NULL; }

    Module.DirectDrawEnumerateExW = (LPDIRECTDRAWENUMERATEEXW)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_EX_W_NAME);
    if (Module.DirectDrawEnumerateExW == NULL) { ReleaseModule(); return NULL; }

    Module.DirectDrawEnumerateW = (LPDIRECTDRAWENUMW)GetProcAddress(Module.Module, DIRECT_DRAW_DIRECT_DRAW_ENUMERATE_W_NAME);
    if (Module.DirectDrawEnumerateW == NULL) { ReleaseModule(); return NULL; }

    Module.DllCanUnloadNow = (LPDLLCANUNLOADNOW)GetProcAddress(Module.Module, DIRECT_DRAW_DLL_CAN_UNLOAD_NOW_NAME);
    if (Module.DllCanUnloadNow == NULL) { ReleaseModule(); return NULL; }

    Module.DllGetClassObject = (LPDLLGETCLASSOBJECT)GetProcAddress(Module.Module, DIRECT_DRAW_DLL_GET_CLASS_OBJECT_NAME);
    if (Module.DllGetClassObject == NULL) { ReleaseModule(); return NULL; }

    Module.GetDirectDrawSurfaceLocal = (LPGETDIRECTDRAWSURFACELOCAL)GetProcAddress(Module.Module, DIRECT_DRAW_GET_DIRECT_DRAW_SURFACE_LOCAL_NAME);
    if (Module.GetDirectDrawSurfaceLocal == NULL) { ReleaseModule(); return NULL; }

    Module.GetOLEThunkData = (LPGETOLETHUNKDATA)GetProcAddress(Module.Module, DIRECT_DRAW_GET_OLE_THUNK_DATA_NAME);
    if (Module.GetOLEThunkData == NULL) { ReleaseModule(); return NULL; }

    Module.GetSurfaceFromDeviceContext = (LPGETSURFACEFROMDEVICECONTEXT)GetProcAddress(Module.Module, DIRECT_DRAW_GET_SURFACE_FROM_DEVICE_CONTEXT_NAME);
    if (Module.GetSurfaceFromDeviceContext == NULL) { ReleaseModule(); return NULL; }

    Module.RegisterSpecialCase = (LPREGISTERSPECIALCASE)GetProcAddress(Module.Module, DIRECT_DRAW_REGISTER_SPECIAL_CASE_NAME);
    if (Module.RegisterSpecialCase == NULL) { ReleaseModule(); return NULL; }

    Module.ReleaseThreadLock = (LPRELEASEDIRECTDRAWTHREADLOCK)GetProcAddress(Module.Module, DIRECT_DRAW_RELEASE_DIRECT_DRAW_THREAD_LOCK_NAME);
    if (Module.ReleaseThreadLock == NULL) { ReleaseModule(); return NULL; }

    Module.SetApplicationCompatibilityData = (LPSETAPPLICATIONCOMPATIBILITYDATA)GetProcAddress(Module.Module, DIRECT_DRAW_SET_APPLICATION_COMPATIBILITY_DATA_NAME);

    Module.Assembler = new Assembler();

    Module.Initialized = TRUE;

    return TRUE;
}

BOOL ReleaseModule()
{
    if (Module.Assembler != NULL) { delete Module.Assembler; }

    CONST  BOOL result = Module.Module != NULL ? FreeLibrary(Module.Module) : FALSE;

    ZeroMemory(&Module, sizeof(ModuleState));

    return result;
}