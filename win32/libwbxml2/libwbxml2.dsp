# Microsoft Developer Studio Project File - Name="libwbxml2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libwbxml2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libwbxml2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libwbxml2.mak" CFG="libwbxml2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libwbxml2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libwbxml2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libwbxml2 - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBWBXML2_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../expat" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBWBXML2_EXPORTS" /D "WBXML_SUPPORT_WML" /D "WBXML_SUPPORT_WTA" /D "WBXML_SUPPORT_SI" /D "WBXML_SUPPORT_SL" /D "WBXML_SUPPORT_CO" /D "WBXML_SUPPORT_PROV" /D "WBXML_SUPPORT_EMN" /D "WBXML_SUPPORT_DRMREL" /D "WBXML_SUPPORT_OTA_SETTINGS" /D "WBXML_SUPPORT_SYNCML" /D "WBXML_SUPPORT_WV" /D "WBXML_SUPPORT_AIRSYNC" /D "WBXML_ENCODER_USE_STRTBL" /D "HAVE_EXPAT" /D "WBXML_WRAPPERS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libexpat.lib /nologo /dll /machine:I386 /libpath:"../expat"

!ELSEIF  "$(CFG)" == "libwbxml2 - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBWBXML2_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../expat" /I "../leaktrack" /D "_DEBUG" /D "WBXML_LIB_VERBOSE" /D "WBXML_USE_LEAKTRACKER" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBWBXML2_EXPORTS" /D "WBXML_SUPPORT_WML" /D "WBXML_SUPPORT_WTA" /D "WBXML_SUPPORT_SI" /D "WBXML_SUPPORT_SL" /D "WBXML_SUPPORT_CO" /D "WBXML_SUPPORT_PROV" /D "WBXML_SUPPORT_EMN" /D "WBXML_SUPPORT_DRMREL" /D "WBXML_SUPPORT_OTA_SETTINGS" /D "WBXML_SUPPORT_SYNCML" /D "WBXML_SUPPORT_WV" /D "WBXML_SUPPORT_AIRSYNC" /D "WBXML_ENCODER_USE_STRTBL" /D "HAVE_EXPAT" /D "WBXML_WRAPPERS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libexpat.lib leaktrack.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"../expat" /libpath:"../leaktrack"

!ENDIF 

# Begin Target

# Name "libwbxml2 - Win32 Release"
# Name "libwbxml2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\wbxml_base64.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_buffers.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_charset.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_conv.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_elt.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_encoder.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_errors.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_lists.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_log.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_parser.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tables.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tree_clb_wbxml.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tree_clb_xml.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_wrap_syncml.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\wbxml.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_base64.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_buffers.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_charset.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_conv.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_elt.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_encoder.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_errors.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_handlers.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_lists.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_log.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_mem.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_parser.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tables.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tree.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tree_clb_wbxml.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_tree_clb_xml.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wbxml_wrap_syncml.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
