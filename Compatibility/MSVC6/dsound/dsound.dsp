# Microsoft Developer Studio Project File - Name="dsound" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=dsound - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dsound.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dsound.mak" CFG="dsound - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dsound - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsound - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dsound - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSOUND_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\Source\common" /I "..\..\..\SDK\DX90\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSOUND_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "dsound - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSOUND_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\Source\common" /I "..\..\..\SDK\DX90\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSOUND_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "dsound - Win32 Release"
# Name "dsound - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound3DBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound3DListener.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound8.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundBuffer8.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCapture.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureBuffer8.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureFXAec.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureFXNoiseSuppress.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFullDuplex.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXChorus.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXCompressor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXDistortion.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXEcho.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXFlanger.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXGargle.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXI3DL2Reverb.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXParamEq.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXWavesReverb.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundNotify.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Export.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\KsPropertySet.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Main.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Module.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Module.def
# End Source File
# Begin Source File

SOURCE=.\res.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Unknown.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\Source\dsound\Base.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound3DBuffer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound3DListener.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSound8.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundBuffer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundBuffer8.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCapture.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureBuffer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureBuffer8.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureFXAec.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundCaptureFXNoiseSuppress.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFullDuplex.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXChorus.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXCompressor.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXDistortion.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXEcho.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXFlanger.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXGargle.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXI3DL2Reverb.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXParamEq.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundFXWavesReverb.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\DirectSoundNotify.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Export.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\KsPropertySet.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Module.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\dsound\Unknown.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
