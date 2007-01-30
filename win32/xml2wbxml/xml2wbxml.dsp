# Microsoft Developer Studio Project File - Name="xml2wbxml" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=xml2wbxml - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xml2wbxml.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xml2wbxml.mak" CFG="xml2wbxml - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xml2wbxml - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "xml2wbxml - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xml2wbxml - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../src" /I "../expat" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "WBXML_SUPPORT_WML" /D "WBXML_SUPPORT_WTA" /D "WBXML_SUPPORT_SI" /D "WBXML_SUPPORT_SL" /D "WBXML_SUPPORT_CO" /D "WBXML_SUPPORT_PROV" /D "WBXML_SUPPORT_EMN" /D "WBXML_SUPPORT_DRMREL" /D "WBXML_SUPPORT_OTA_SETTINGS" /D "WBXML_SUPPORT_SYNCML" /D "WBXML_SUPPORT_WV" /D "WBXML_SUPPORT_AIRSYNC" /D "WBXML_ENCODER_USE_STRTBL" /D "HAVE_EXPAT" /D "WBXML_WRAPPERS" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libwbxml2.lib /nologo /subsystem:console /machine:I386 /libpath:"../libwbxml2/Release"

!ELSEIF  "$(CFG)" == "xml2wbxml - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../src" /I "../expat" /I "../leaktrack" /D "_DEBUG" /D "WBXML_LIB_VERBOSE" /D "WBXML_USE_LEAKTRACKER" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "WBXML_SUPPORT_WML" /D "WBXML_SUPPORT_WTA" /D "WBXML_SUPPORT_SI" /D "WBXML_SUPPORT_SL" /D "WBXML_SUPPORT_CO" /D "WBXML_SUPPORT_PROV" /D "WBXML_SUPPORT_EMN" /D "WBXML_SUPPORT_DRMREL" /D "WBXML_SUPPORT_OTA_SETTINGS" /D "WBXML_SUPPORT_SYNCML" /D "WBXML_SUPPORT_WV" /D "WBXML_SUPPORT_AIRSYNC" /D "WBXML_ENCODER_USE_STRTBL" /D "HAVE_EXPAT" /D "WBXML_WRAPPERS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libwbxml2.lib leaktrack.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"../libwbxml2/Debug" /libpath:"../leaktrack"

!ENDIF 

# Begin Target

# Name "xml2wbxml - Win32 Release"
# Name "xml2wbxml - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\tools\attgetopt.c
# End Source File
# Begin Source File

SOURCE=..\..\tools\xml2wbxml_tool.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\tools\getopt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
