# Microsoft Developer Studio Project File - Name="ddraw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ddraw - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ddraw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ddraw.mak" CFG="ddraw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ddraw - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ddraw - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ddraw - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DDRAW_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\SDK\DX70\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DDRAW_EXPORTS" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "ddraw - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DDRAW_EXPORTS" /YX /FD /GZ  /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\SDK\DX70\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DDRAW_EXPORTS" /YX /FD /GZ  /c
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

# Name "ddraw - Win32 Release"
# Name "ddraw - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Assembler.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\AssemblerDelegate.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D7.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice7.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DExecuteBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DLight.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DMaterial.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DMaterial2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DMaterial3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DTexture.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DTexture2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DVertexBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DVertexBuffer7.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DViewport.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DViewport2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DViewport3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw4.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw7.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawClipper.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawColorControl.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawGammaControl.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawPalette.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface4.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface7.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawVideoPort.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawVideoPortContainer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Export.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Main.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Module.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Module.def
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Unknown.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Array.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Assembler.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Base.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D2.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D3.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3D7.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice2.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice3.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DDevice7.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DExecuteBuffer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DLight.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DMaterial.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DMaterial2.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DMaterial3.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DTexture.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DTexture2.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DVertexBuffer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DVertexBuffer7.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DViewport.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DViewport2.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Direct3DViewport3.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw2.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw4.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDraw7.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawClipper.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawColorControl.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawGammaControl.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawPalette.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface2.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface3.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface4.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawSurface7.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawVideoPort.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\DirectDrawVideoPortContainer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Export.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Module.hxx
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ddraw\Unknown.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
