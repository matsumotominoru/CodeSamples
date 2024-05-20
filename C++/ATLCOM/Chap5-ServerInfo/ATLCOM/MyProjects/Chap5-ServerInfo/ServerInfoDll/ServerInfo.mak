# Microsoft Developer Studio Generated NMAKE File, Based on ServerInfo.dsp
!IF "$(CFG)" == ""
CFG=ServerInfo - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの ServerInfo - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "ServerInfo - Win32 Debug" && "$(CFG)" != "ServerInfo - Win32 Unicode Debug" && "$(CFG)" != "ServerInfo - Win32 Release MinSize" && "$(CFG)" != "ServerInfo - Win32 Release MinDependency" && "$(CFG)" != "ServerInfo - Win32 Unicode Release MinSize" && "$(CFG)" != "ServerInfo - Win32 Unicode Release MinDependency"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "ServerInfo.mak" CFG="ServerInfo - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "ServerInfo - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "ServerInfo - Win32 Unicode Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "ServerInfo - Win32 Release MinSize" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "ServerInfo - Win32 Release MinDependency" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "ServerInfo - Win32 Unicode Release MinSize" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "ServerInfo - Win32 Unicode Release MinDependency" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ServerInfo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ServerInfo.dll"
	-@erase "$(OUTDIR)\ServerInfo.exp"
	-@erase "$(OUTDIR)\ServerInfo.ilk"
	-@erase "$(OUTDIR)\ServerInfo.lib"
	-@erase "$(OUTDIR)\ServerInfo.pdb"
	-@erase ".\ServerInfo.h"
	-@erase ".\ServerInfo.tlb"
	-@erase ".\ServerInfo_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ServerInfo.pdb" /debug /machine:I386 /def:".\ServerInfo.def" /out:"$(OUTDIR)\ServerInfo.dll" /implib:"$(OUTDIR)\ServerInfo.lib" /pdbtype:sept 
DEF_FILE= \
	".\ServerInfo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiskInfo.obj" \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res"

"$(OUTDIR)\ServerInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ServerInfo.dll
InputPath=.\Debug\ServerInfo.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.dll" ".\ServerInfo.tlb" ".\ServerInfo.h" ".\ServerInfo_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ServerInfo.dll"
	-@erase "$(OUTDIR)\ServerInfo.exp"
	-@erase "$(OUTDIR)\ServerInfo.ilk"
	-@erase "$(OUTDIR)\ServerInfo.lib"
	-@erase "$(OUTDIR)\ServerInfo.pdb"
	-@erase ".\ServerInfo.h"
	-@erase ".\ServerInfo.tlb"
	-@erase ".\ServerInfo_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ServerInfo.pdb" /debug /machine:I386 /def:".\ServerInfo.def" /out:"$(OUTDIR)\ServerInfo.dll" /implib:"$(OUTDIR)\ServerInfo.lib" /pdbtype:sept 
DEF_FILE= \
	".\ServerInfo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiskInfo.obj" \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res"

"$(OUTDIR)\ServerInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ServerInfo.dll
InputPath=.\DebugU\ServerInfo.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo 警告 : Windows 95 に Unicode DLL を登録することはできません 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.dll" ".\ServerInfo.tlb" ".\ServerInfo.h" ".\ServerInfo_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.dll"
	-@erase "$(OUTDIR)\ServerInfo.exp"
	-@erase "$(OUTDIR)\ServerInfo.lib"
	-@erase ".\ServerInfo.h"
	-@erase ".\ServerInfo.tlb"
	-@erase ".\ServerInfo_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /def:".\ServerInfo.def" /out:"$(OUTDIR)\ServerInfo.dll" /implib:"$(OUTDIR)\ServerInfo.lib" 
DEF_FILE= \
	".\ServerInfo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiskInfo.obj" \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res"

"$(OUTDIR)\ServerInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ServerInfo.dll
InputPath=.\ReleaseMinSize\ServerInfo.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.dll" ".\ServerInfo.tlb" ".\ServerInfo.h" ".\ServerInfo_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.dll"
	-@erase "$(OUTDIR)\ServerInfo.exp"
	-@erase "$(OUTDIR)\ServerInfo.lib"
	-@erase ".\ServerInfo.h"
	-@erase ".\ServerInfo.tlb"
	-@erase ".\ServerInfo_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /def:".\ServerInfo.def" /out:"$(OUTDIR)\ServerInfo.dll" /implib:"$(OUTDIR)\ServerInfo.lib" 
DEF_FILE= \
	".\ServerInfo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiskInfo.obj" \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res"

"$(OUTDIR)\ServerInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ServerInfo.dll
InputPath=.\ReleaseMinDependency\ServerInfo.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.dll" ".\ServerInfo.tlb" ".\ServerInfo.h" ".\ServerInfo_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.dll"
	-@erase "$(OUTDIR)\ServerInfo.exp"
	-@erase "$(OUTDIR)\ServerInfo.lib"
	-@erase ".\ServerInfo.h"
	-@erase ".\ServerInfo.tlb"
	-@erase ".\ServerInfo_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /def:".\ServerInfo.def" /out:"$(OUTDIR)\ServerInfo.dll" /implib:"$(OUTDIR)\ServerInfo.lib" 
DEF_FILE= \
	".\ServerInfo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiskInfo.obj" \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res"

"$(OUTDIR)\ServerInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ServerInfo.dll
InputPath=.\ReleaseUMinSize\ServerInfo.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo 警告 : Windows 95 に Unicode DLL を登録することはできません 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.dll" ".\ServerInfo.tlb" ".\ServerInfo.h" ".\ServerInfo_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.dll"
	-@erase "$(OUTDIR)\ServerInfo.exp"
	-@erase "$(OUTDIR)\ServerInfo.lib"
	-@erase ".\ServerInfo.h"
	-@erase ".\ServerInfo.tlb"
	-@erase ".\ServerInfo_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /def:".\ServerInfo.def" /out:"$(OUTDIR)\ServerInfo.dll" /implib:"$(OUTDIR)\ServerInfo.lib" 
DEF_FILE= \
	".\ServerInfo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiskInfo.obj" \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res"

"$(OUTDIR)\ServerInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ServerInfo.dll
InputPath=.\ReleaseUMinDependency\ServerInfo.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo 警告 : Windows 95 に Unicode DLL を登録することはできません 
	:end 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ServerInfo.dep")
!INCLUDE "ServerInfo.dep"
!ELSE 
!MESSAGE Warning: cannot find "ServerInfo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ServerInfo - Win32 Debug" || "$(CFG)" == "ServerInfo - Win32 Unicode Debug" || "$(CFG)" == "ServerInfo - Win32 Release MinSize" || "$(CFG)" == "ServerInfo - Win32 Release MinDependency" || "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize" || "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"
SOURCE=.\DiskInfo.cpp

"$(INTDIR)\DiskInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ServerInfo.pch" ".\ServerInfo.h"


SOURCE=.\ServerInfo.cpp

"$(INTDIR)\ServerInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ServerInfo.pch" ".\ServerInfo_i.c" ".\ServerInfo.h"


SOURCE=.\ServerInfo.idl

!IF  "$(CFG)" == "ServerInfo - Win32 Debug"

MTL_SWITCHES=/tlb ".\ServerInfo.tlb" /h "ServerInfo.h" /iid "ServerInfo_i.c" /Oicf 

".\ServerInfo.tlb"	".\ServerInfo.h"	".\ServerInfo_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\ServerInfo.tlb" /h "ServerInfo.h" /iid "ServerInfo_i.c" /Oicf 

".\ServerInfo.tlb"	".\ServerInfo.h"	".\ServerInfo_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\ServerInfo.tlb" /h "ServerInfo.h" /iid "ServerInfo_i.c" /Oicf 

".\ServerInfo.tlb"	".\ServerInfo.h"	".\ServerInfo_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\ServerInfo.tlb" /h "ServerInfo.h" /iid "ServerInfo_i.c" /Oicf 

".\ServerInfo.tlb"	".\ServerInfo.h"	".\ServerInfo_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\ServerInfo.tlb" /h "ServerInfo.h" /iid "ServerInfo_i.c" /Oicf 

".\ServerInfo.tlb"	".\ServerInfo.h"	".\ServerInfo_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\ServerInfo.tlb" /h "ServerInfo.h" /iid "ServerInfo_i.c" /Oicf 

".\ServerInfo.tlb"	".\ServerInfo.h"	".\ServerInfo_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ServerInfo.rc

"$(INTDIR)\ServerInfo.res" : $(SOURCE) "$(INTDIR)" ".\ServerInfo.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ServerInfo - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

