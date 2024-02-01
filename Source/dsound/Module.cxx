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
    char directory[DIRECT_SOUND_LIBRARY_PATH_LENGTH];
    ZeroMemory(directory, DIRECT_SOUND_LIBRARY_PATH_LENGTH);

    if (GetSystemDirectoryA(directory, DIRECT_SOUND_LIBRARY_PATH_LENGTH) >= DIRECT_SOUND_LIBRARY_PATH_LENGTH) { return FALSE; }

    char path[DIRECT_SOUND_LIBRARY_FILE_PATH_LENGTH];
    ZeroMemory(path, DIRECT_SOUND_LIBRARY_FILE_PATH_LENGTH);

    if (PathCombineA(path, directory, DIRECT_SOUND_LIBRARY_NAME) == NULL) { return FALSE; }

    Module.Module = LoadLibraryA(path);

    if (Module.Module == NULL) { return FALSE; }

    Module.DirectSoundCaptureCreate = (LPDIRECTSOUNDCAPTURECREATE)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_CAPTURE_CREATE_NAME);
    if (Module.DirectSoundCaptureCreate == NULL) { ReleaseModule(); return NULL; }

    Module.DirectSoundCaptureCreate8 = (LPDIRECTSOUNDCAPTURECREATE8)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_CAPTURE_CREATE_8_NAME);

    Module.DirectSoundCaptureEnumerateA = (LPDIRECTSOUNDCAPTUREENUMERATEA)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_CAPTURE_ENUMERATE_A_NAME);
    if (Module.DirectSoundCaptureEnumerateA == NULL) { ReleaseModule(); return NULL; }

    Module.DirectSoundCaptureEnumerateW = (LPDIRECTSOUNDCAPTUREENUMERATEW)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_CAPTURE_ENUMERATE_W_NAME);
    if (Module.DirectSoundCaptureEnumerateW == NULL) { ReleaseModule(); return NULL; }

    Module.DirectSoundCreate = (LPDIRECTSOUNDCREATE)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_CREATE_NAME);
    if (Module.DirectSoundCreate == NULL) { ReleaseModule(); return NULL; }

    Module.DirectSoundCreate8 = (LPDIRECTSOUNDCREATE8)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_CREATE_8_NAME);

    Module.DirectSoundEnumerateA = (LPDIRECTSOUNDENUMERATEA)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_ENUMERATE_A_NAME);
    if (Module.DirectSoundEnumerateA == NULL) { ReleaseModule(); return NULL; }

    Module.DirectSoundEnumerateW = (LPDIRECTSOUNDENUMERATEW)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_ENUMERATE_W_NAME);
    if (Module.DirectSoundEnumerateW == NULL) { ReleaseModule(); return NULL; }

    Module.DirectSoundFullDuplexCreate = (LPDIRECTSOUNDFULLDUPLEXCREATE)GetProcAddress(Module.Module, DIRECT_SOUND_DIRECT_SOUND_FULL_DUPLEX_CREATE_NAME);

    Module.DllCanUnloadNow = (LPDLLCANUNLOADNOW)GetProcAddress(Module.Module, DIRECT_SOUND_DLL_CAN_UNLOAD_NOW_NAME);
    if (Module.DllCanUnloadNow == NULL) { ReleaseModule(); return NULL; }

    Module.DllGetClassObject = (LPDLLGETCLASSOBJECT)GetProcAddress(Module.Module, DIRECT_SOUND_DLL_GET_CLASS_OBJECT_NAME);
    if (Module.DllGetClassObject == NULL) { ReleaseModule(); return NULL; }

    Module.GetDeviceID = (LPGETDEVICEID)GetProcAddress(Module.Module, DIRECT_SOUND_GET_DEVICE_ID_NAME);
    if (Module.GetDeviceID == NULL) { ReleaseModule(); return NULL; }

    Module.Assembler = new Assembler();

    Module.Initialized = TRUE;

    return TRUE;
}

BOOL ReleaseModule()
{
    delete Module.Assembler;

    BOOL result = Module.Module != NULL ? FreeLibrary(Module.Module) : FALSE;

    ZeroMemory(&Module, sizeof(ModuleState));

    return result;
}