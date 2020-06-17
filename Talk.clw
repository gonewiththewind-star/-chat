; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTalkDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Talk.h"

ClassCount=3
Class1=CTalkApp
Class2=CTalkDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TALK_DIALOG

[CLS:CTalkApp]
Type=0
HeaderFile=Talk.h
ImplementationFile=Talk.cpp
Filter=N
LastObject=CTalkApp

[CLS:CTalkDlg]
Type=0
HeaderFile=TalkDlg.h
ImplementationFile=TalkDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTalkDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=TalkDlg.h
ImplementationFile=TalkDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TALK_DIALOG]
Type=1
Class=CTalkDlg
ControlCount=15
Control1=IDC_STATIC_TYPE,static,1342308352
Control2=IDC_COMBO_TYPE,combobox,1344339971
Control3=IDC_STATIC_SERVNAME,static,1342308352
Control4=IDC_STATIC_SERVPORT,static,1342308352
Control5=IDC_EDIT_SERVNAME,edit,1350631552
Control6=IDC_EDIT_SERVPORT,edit,1350631552
Control7=IDC_BTN_CONNECT,button,1342242816
Control8=IDC_BTN_CLOSE,button,1476460544
Control9=IDC_STATIC_MSG,static,1476526080
Control10=IDC_EDIT_MSG,edit,1484849280
Control11=IDOK,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_LIST_SENT,listbox,1352679681
Control15=IDC_LIST_RECEIVED,listbox,1352679681

