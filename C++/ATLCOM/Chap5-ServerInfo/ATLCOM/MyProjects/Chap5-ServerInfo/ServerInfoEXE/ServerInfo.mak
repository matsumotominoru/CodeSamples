# Microsoft Developer Studio Generated NMAKE File, Based on ServerInfo.dsp
!IF "$(CFG)" == ""
CFG=ServerInfo - Win32 Debug
!MESSAGE ç\ê¨Ç™éwíËÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒÅB√ﬁÃ´ŸƒÇÃ ServerInfo - Win32 Debug Çê›íËÇµÇ‹Ç∑ÅB
!ENDIF 

!IF "$(CFG)" != "ServerInfo - Win32 Debug" && "$(CFG)" != "ServerInfo - Win32 Unicode Debug" && "$(CFG)" != "ServerInfo - Win32 Release MinSize" && "$(CFG)" != "ServerInfo - Win32 Release MinDependency" && "$(CFG)" != "ServerInfo - Win32 Unicode Release MinSize" && "$(CFG)" != "ServerInfo - Win32 Unicode Release MinDependency"
!MESSAGE éwíËÇ≥ÇÍÇΩ ÀﬁŸƒﬁ ”∞ƒﬁ "$(CFG)" ÇÕê≥ÇµÇ≠Ç†ÇËÇ‹ÇπÇÒÅB
!MESSAGE NMAKE ÇÃé¿çséûÇ…ç\ê¨ÇéwíËÇ≈Ç´Ç‹Ç∑
!MESSAGE ∫œ›ƒﬁ ◊≤›è„Ç≈œ∏€ÇÃê›íËÇíËã`ÇµÇ‹Ç∑ÅBó·:
!MESSAGE 
!MESSAGE NMAKE /f "ServerInfo.mak" CFG="ServerInfo - Win32 Debug"
!MESSAGE 
!MESSAGE ëIëâ¬î\Ç»ÀﬁŸƒﬁ ”∞ƒﬁ:
!MESSAGE 
!MESSAGE "ServerInfo - Win32 Debug" ("Win32 (x86) Application" óp)
!MESSAGE "ServerInfo - Win32 Unicode Debug" ("Win32 (x86) Application" óp)
!MESSAGE "ServerInfo - Win32 Release MinSize" ("Win32 (x86) Application" óp)
!MESSAGE "ServerInfo - Win32 Release MinDependency" ("Win32 (x86) Application" óp)
!MESSAGE "ServerInfo - Win32 Unicode Release MinSize" ("Win32 (x86) Application" óp)
!MESSAGE "ServerInfo - Win32 Unicode Release MinDependency" ("Win32 (x86) Application" óp)
!MESSAGE 
!ERROR ñ≥å¯Ç»ç\ê¨Ç™éwíËÇ≥ÇÍÇƒÇ¢Ç‹Ç∑ÅB
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ServerInfo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.exe" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ServerInfo.exe"
	-@erase "$(OUTDIR)\ServerInfo.ilk"
	-@erase "$(OUTDIR)\ServerInfo.pdb"
	-@erase "..\ServerInfo.h"
	-@erase "..\ServerInfo.tlb"
	-@erase "..\ServerInfo_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ServerInfo.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ServerInfo.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res" \
	"$(INTDIR)\DiskInfo.obj"

"$(OUTDIR)\ServerInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ServerInfo.exe
InputPath=.\Debug\ServerInfo.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.exe" "$(OUTDIR)\ServerInfo.tlb" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\ServerInfo.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ServerInfo.exe"
	-@erase "$(OUTDIR)\ServerInfo.ilk"
	-@erase "$(OUTDIR)\ServerInfo.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ServerInfo.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ServerInfo.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res" \
	"$(INTDIR)\DiskInfo.obj"

"$(OUTDIR)\ServerInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ServerInfo.exe
InputPath=.\DebugU\ServerInfo.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
	goto end 
	:NOTNT 
	echo åxçê : Windows 95 Ç… Unicode EXE Çìoò^Ç∑ÇÈÇ±Ç∆ÇÕÇ≈Ç´Ç‹ÇπÇÒ 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.exe" "$(OUTDIR)\ServerInfo.tlb" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\ServerInfo.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.exe"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /out:"$(OUTDIR)\ServerInfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res" \
	"$(INTDIR)\DiskInfo.obj"

"$(OUTDIR)\ServerInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ServerInfo.exe
InputPath=.\ReleaseMinSize\ServerInfo.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.exe" "$(OUTDIR)\ServerInfo.tlb" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\ServerInfo.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.exe"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /out:"$(OUTDIR)\ServerInfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res" \
	"$(INTDIR)\DiskInfo.obj"

"$(OUTDIR)\ServerInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ServerInfo.exe
InputPath=.\ReleaseMinDependency\ServerInfo.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.exe" "$(OUTDIR)\ServerInfo.tlb" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\ServerInfo.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.exe"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /out:"$(OUTDIR)\ServerInfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res" \
	"$(INTDIR)\DiskInfo.obj"

"$(OUTDIR)\ServerInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ServerInfo.exe
InputPath=.\ReleaseUMinSize\ServerInfo.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
	goto end 
	:NOTNT 
	echo åxçê : Windows 95 Ç… Unicode EXE Çìoò^Ç∑ÇÈÇ±Ç∆ÇÕÇ≈Ç´Ç‹ÇπÇÒ 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ServerInfo.exe" "$(OUTDIR)\ServerInfo.tlb" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DiskInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.obj"
	-@erase "$(INTDIR)\ServerInfo.pch"
	-@erase "$(INTDIR)\ServerInfo.res"
	-@erase "$(INTDIR)\ServerInfo.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ServerInfo.exe"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\ServerInfo.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ServerInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ServerInfo.pdb" /machine:I386 /out:"$(OUTDIR)\ServerInfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ServerInfo.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ServerInfo.res" \
	"$(INTDIR)\DiskInfo.obj"

"$(OUTDIR)\ServerInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ServerInfo.exe
InputPath=.\ReleaseUMinDependency\ServerInfo.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
	goto end 
	:NOTNT 
	echo åxçê : Windows 95 Ç… Unicode EXE Çìoò^Ç∑ÇÈÇ±Ç∆ÇÕÇ≈Ç´Ç‹ÇπÇÒ 
	:end 
<< 
	

!ENDIF 

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

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ServerInfo.dep")
!INCLUDE "ServerInfo.dep"
!ELSE 
!MESSAGE Warning: cannot find "ServerInfo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ServerInfo - Win32 Debug" || "$(CFG)" == "ServerInfo - Win32 Unicode Debug" || "$(CFG)" == "ServerInfo - Win32 Release MinSize" || "$(CFG)" == "ServerInfo - Win32 Release MinDependency" || "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize" || "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"
SOURCE=..\DiskInfo.cpp

"$(INTDIR)\DiskInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ServerInfo.pch" "..\ServerInfo.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\ServerInfo.cpp

"$(INTDIR)\ServerInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ServerInfo.pch" "..\ServerInfo.h" "..\ServerInfo_i.c"


SOURCE=..\ServerInfo.idl

!IF  "$(CFG)" == "ServerInfo - Win32 Debug"

MTL_SWITCHES=/tlb "..\ServerInfo.tlb" /h "..\ServerInfo.h" /iid "..\ServerInfo_i.c" 

"..\ServerInfo.tlb"	"..\ServerInfo.h"	"..\ServerInfo_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\ServerInfo.tlb" 

"$(INTDIR)\ServerInfo.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\ServerInfo.tlb" 

"$(INTDIR)\ServerInfo.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\ServerInfo.tlb" 

"$(INTDIR)\ServerInfo.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\ServerInfo.tlb" 

"$(INTDIR)\ServerInfo.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\ServerInfo.tlb" 

"$(INTDIR)\ServerInfo.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ServerInfo.rc

"$(INTDIR)\ServerInfo.res" : $(SOURCE) "$(INTDIR)" "..\ServerInfo.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ServerInfo - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ServerInfo - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ServerInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ServerInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

