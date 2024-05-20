; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CSetEventDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SetEvent.h"

ClassCount=2
Class1=CSetEventApp
Class2=CSetEventDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_SETEVENT_DIALOG

[CLS:CSetEventApp]
Type=0
HeaderFile=SetEvent.h
ImplementationFile=SetEvent.cpp
Filter=N

[CLS:CSetEventDlg]
Type=0
HeaderFile=SetEventDlg.h
ImplementationFile=SetEventDlg.cpp
Filter=D
LastObject=CSetEventDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SETEVENT_DIALOG]
Type=1
Class=CSetEventDlg
ControlCount=7
Control1=IDC_EVENTNAME,edit,1350631552
Control2=IDC_CREATE,button,1476460544
Control3=IDC_STATUS,static,1342177283
Control4=IDC_GO,button,1342373897
Control5=IDC_STOP,button,1342177289
Control6=IDOK,button,1342373889
Control7=IDC_EVENTS,listbox,1352728835

