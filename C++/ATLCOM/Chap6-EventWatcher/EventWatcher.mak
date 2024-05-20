# Microsoft Developer Studio Generated NMAKE File, Based on EventWatcher.dsp
!IF "$(CFG)" == ""
CFG=EventWatcher - Win32 Debug
!MESSAGE ç\ê¨Ç™éwíËÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒÅB√ﬁÃ´ŸƒÇÃ EventWatcher - Win32 Debug Çê›íËÇµÇ‹Ç∑ÅB
!ENDIF 

!IF "$(CFG)" != "EventWatcher - Win32 Debug" && "$(CFG)" != "EventWatcher - Win32 Unicode Debug" && "$(CFG)" != "EventWatcher - Win32 Release MinSize" && "$(CFG)" != "EventWatcher - Win32 Release MinDependency" && "$(CFG)" != "EventWatcher - Win32 Unicode Release MinSize" && "$(CFG)" != "EventWatcher - Win32 Unicode Release MinDependency"
!MESSAGE éwíËÇ≥ÇÍÇΩ ÀﬁŸƒﬁ ”∞ƒﬁ "$(CFG)" ÇÕê≥ÇµÇ≠Ç†ÇËÇ‹ÇπÇÒÅB
!MESSAGE NMAKE ÇÃé¿çséûÇ…ç\ê¨ÇéwíËÇ≈Ç´Ç‹Ç∑
!MESSAGE ∫œ›ƒﬁ ◊≤›è„Ç≈œ∏€ÇÃê›íËÇíËã`ÇµÇ‹Ç∑ÅBó·:
!MESSAGE 
!MESSAGE NMAKE /f "EventWatcher.mak" CFG="EventWatcher - Win32 Debug"
!MESSAGE 
!MESSAGE ëIëâ¬î\Ç»ÀﬁŸƒﬁ ”∞ƒﬁ:
!MESSAGE 
!MESSAGE "EventWatcher - Win32 Debug" ("Win32 (x86) Application" óp)
!MESSAGE "EventWatcher - Win32 Unicode Debug" ("Win32 (x86) Application" óp)
!MESSAGE "EventWatcher - Win32 Release MinSize" ("Win32 (x86) Application" óp)
!MESSAGE "EventWatcher - Win32 Release MinDependency" ("Win32 (x86) Application" óp)
!MESSAGE "EventWatcher - Win32 Unicode Release MinSize" ("Win32 (x86) Application" óp)
!MESSAGE "EventWatcher - Win32 Unicode Release MinDependency" ("Win32 (x86) Application" óp)
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

!IF  "$(CFG)" == "EventWatcher - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\EventWatcher.exe" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\EventWatcher.obj"
	-@erase "$(INTDIR)\EventWatcher.pch"
	-@erase "$(INTDIR)\EventWatcher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventWatcher.exe"
	-@erase "$(OUTDIR)\EventWatcher.ilk"
	-@erase "$(OUTDIR)\EventWatcher.pdb"
	-@erase ".\EventWatcher.h"
	-@erase ".\EventWatcher.tlb"
	-@erase ".\EventWatcher_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventWatcher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\EventWatcher.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventWatcher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\EventWatcher.pdb" /debug /machine:I386 /out:"$(OUTDIR)\EventWatcher.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\EventWatcher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventWatcher.res"

"$(OUTDIR)\EventWatcher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\EventWatcher.exe
InputPath=.\Debug\EventWatcher.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
<< 
	

!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\EventWatcher.exe" ".\EventWatcher.tlb" ".\EventWatcher.h" ".\EventWatcher_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\EventWatcher.obj"
	-@erase "$(INTDIR)\EventWatcher.pch"
	-@erase "$(INTDIR)\EventWatcher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\EventWatcher.exe"
	-@erase "$(OUTDIR)\EventWatcher.ilk"
	-@erase "$(OUTDIR)\EventWatcher.pdb"
	-@erase ".\EventWatcher.h"
	-@erase ".\EventWatcher.tlb"
	-@erase ".\EventWatcher_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\EventWatcher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\EventWatcher.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventWatcher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\EventWatcher.pdb" /debug /machine:I386 /out:"$(OUTDIR)\EventWatcher.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\EventWatcher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventWatcher.res"

"$(OUTDIR)\EventWatcher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\EventWatcher.exe
InputPath=.\DebugU\EventWatcher.exe
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
	

!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\EventWatcher.exe" ".\EventWatcher.tlb" ".\EventWatcher.h" ".\EventWatcher_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\EventWatcher.obj"
	-@erase "$(INTDIR)\EventWatcher.pch"
	-@erase "$(INTDIR)\EventWatcher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventWatcher.exe"
	-@erase ".\EventWatcher.h"
	-@erase ".\EventWatcher.tlb"
	-@erase ".\EventWatcher_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\EventWatcher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventWatcher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\EventWatcher.pdb" /machine:I386 /out:"$(OUTDIR)\EventWatcher.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\EventWatcher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventWatcher.res"

"$(OUTDIR)\EventWatcher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\EventWatcher.exe
InputPath=.\ReleaseMinSize\EventWatcher.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
<< 
	

!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\EventWatcher.exe" ".\EventWatcher.tlb" ".\EventWatcher.h" ".\EventWatcher_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\EventWatcher.obj"
	-@erase "$(INTDIR)\EventWatcher.pch"
	-@erase "$(INTDIR)\EventWatcher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventWatcher.exe"
	-@erase ".\EventWatcher.h"
	-@erase ".\EventWatcher.tlb"
	-@erase ".\EventWatcher_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\EventWatcher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventWatcher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\EventWatcher.pdb" /machine:I386 /out:"$(OUTDIR)\EventWatcher.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\EventWatcher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventWatcher.res"

"$(OUTDIR)\EventWatcher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\EventWatcher.exe
InputPath=.\ReleaseMinDependency\EventWatcher.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo ª∞ ﬁ∞ìoò^Ç™äÆóπÇµÇ‹ÇµÇΩ! 
<< 
	

!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\EventWatcher.exe" ".\EventWatcher.tlb" ".\EventWatcher.h" ".\EventWatcher_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\EventWatcher.obj"
	-@erase "$(INTDIR)\EventWatcher.pch"
	-@erase "$(INTDIR)\EventWatcher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventWatcher.exe"
	-@erase ".\EventWatcher.h"
	-@erase ".\EventWatcher.tlb"
	-@erase ".\EventWatcher_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\EventWatcher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventWatcher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\EventWatcher.pdb" /machine:I386 /out:"$(OUTDIR)\EventWatcher.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\EventWatcher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventWatcher.res"

"$(OUTDIR)\EventWatcher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\EventWatcher.exe
InputPath=.\ReleaseUMinSize\EventWatcher.exe
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
	

!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\EventWatcher.exe" ".\EventWatcher.tlb" ".\EventWatcher.h" ".\EventWatcher_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\EventWatcher.obj"
	-@erase "$(INTDIR)\EventWatcher.pch"
	-@erase "$(INTDIR)\EventWatcher.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\EventWatcher.exe"
	-@erase ".\EventWatcher.h"
	-@erase ".\EventWatcher.tlb"
	-@erase ".\EventWatcher_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\EventWatcher.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EventWatcher.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\EventWatcher.pdb" /machine:I386 /out:"$(OUTDIR)\EventWatcher.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\EventWatcher.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\EventWatcher.res"

"$(OUTDIR)\EventWatcher.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\EventWatcher.exe
InputPath=.\ReleaseUMinDependency\EventWatcher.exe
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
!IF EXISTS("EventWatcher.dep")
!INCLUDE "EventWatcher.dep"
!ELSE 
!MESSAGE Warning: cannot find "EventWatcher.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "EventWatcher - Win32 Debug" || "$(CFG)" == "EventWatcher - Win32 Unicode Debug" || "$(CFG)" == "EventWatcher - Win32 Release MinSize" || "$(CFG)" == "EventWatcher - Win32 Release MinDependency" || "$(CFG)" == "EventWatcher - Win32 Unicode Release MinSize" || "$(CFG)" == "EventWatcher - Win32 Unicode Release MinDependency"
SOURCE=.\Events.cpp

"$(INTDIR)\Events.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventWatcher.pch" ".\EventWatcher.h"


SOURCE=.\EventWatcher.cpp

"$(INTDIR)\EventWatcher.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\EventWatcher.pch" ".\EventWatcher.h" ".\EventWatcher_i.c"


SOURCE=.\EventWatcher.idl
MTL_SWITCHES=/tlb ".\EventWatcher.tlb" /h "EventWatcher.h" /iid "EventWatcher_i.c" /Oicf 

".\EventWatcher.tlb"	".\EventWatcher.h"	".\EventWatcher_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\EventWatcher.rc

"$(INTDIR)\EventWatcher.res" : $(SOURCE) "$(INTDIR)" ".\EventWatcher.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "EventWatcher - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\EventWatcher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventWatcher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MT /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\EventWatcher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventWatcher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventWatcher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventWatcher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventWatcher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "EventWatcher - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\EventWatcher.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\EventWatcher.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

