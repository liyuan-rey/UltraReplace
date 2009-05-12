# Microsoft Developer Studio Project File - Name="UR" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UR - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UR.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UR.mak" CFG="UR - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UR - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UR - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UR - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /version:1.0 /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /out:"Release/Ultra Replace.exe"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "UR - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcd.lib" /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "UR - Win32 Release"
# Name "UR - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgResultView.cpp
# End Source File
# Begin Source File

SOURCE=.\DotNetBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\FileFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\FileListPage.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\include\LBTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MatchVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplaceAdvSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplaceCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplacePage.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Scheduler.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleResult.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleTask.cpp
# End Source File
# Begin Source File

SOURCE=.\include\StackDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TaskItem.cpp
# End Source File
# Begin Source File

SOURCE=.\UR.cpp
# End Source File
# Begin Source File

SOURCE=.\UR.rc
# End Source File
# Begin Source File

SOURCE=.\URDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\URListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UserData.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutPage.h
# End Source File
# Begin Source File

SOURCE=.\DlgInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgResultView.h
# End Source File
# Begin Source File

SOURCE=.\DotNetBtn.h
# End Source File
# Begin Source File

SOURCE=.\FileFilter.h
# End Source File
# Begin Source File

SOURCE=.\FileListPage.h
# End Source File
# Begin Source File

SOURCE=.\FlatPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\include\LBTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MatchVariable.h
# End Source File
# Begin Source File

SOURCE=.\ReplaceAdvSetting.h
# End Source File
# Begin Source File

SOURCE=.\ReplaceCommon.h
# End Source File
# Begin Source File

SOURCE=.\ReplacePage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResultPage.h
# End Source File
# Begin Source File

SOURCE=.\Scheduler.h
# End Source File
# Begin Source File

SOURCE=.\SettingPage.h
# End Source File
# Begin Source File

SOURCE=.\SimpleResult.h
# End Source File
# Begin Source File

SOURCE=.\SimpleTask.h
# End Source File
# Begin Source File

SOURCE=.\include\StackDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TaskItem.h
# End Source File
# Begin Source File

SOURCE=.\UR.h
# End Source File
# Begin Source File

SOURCE=.\URDlg.h
# End Source File
# Begin Source File

SOURCE=.\URListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UserData.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DragOut.cur
# End Source File
# Begin Source File

SOURCE=.\res\handcur.cur
# End Source File
# Begin Source File

SOURCE=.\res\info.ICO
# End Source File
# Begin Source File

SOURCE=.\res\OutLookBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tittleba.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UR.ico
# End Source File
# Begin Source File

SOURCE=.\res\UR.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
