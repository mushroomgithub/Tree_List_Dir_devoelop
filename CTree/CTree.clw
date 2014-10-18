; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCTreeDlg
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CTree.h"

ClassCount=4
Class1=CCTreeApp
Class2=CCTreeDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CDirTreeCtrl
Resource3=IDD_CTREE_DIALOG

[CLS:CCTreeApp]
Type=0
HeaderFile=CTree.h
ImplementationFile=CTree.cpp
Filter=N

[CLS:CCTreeDlg]
Type=0
HeaderFile=CTreeDlg.h
ImplementationFile=CTreeDlg.cpp
Filter=D
LastObject=IDC_TREE1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CTreeDlg.h
ImplementationFile=CTreeDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CTREE_DIALOG]
Type=1
Class=CCTreeDlg
ControlCount=5
Control1=IDC_TREE1,SysTreeView32,1350631424
Control2=IDC_LIST1,SysListView32,1350631425
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC_DIR,static,1350701056
Control5=IDC_STATIC_SYS,static,1350701056

[CLS:CDirTreeCtrl]
Type=0
HeaderFile=DirTreeCtrl.h
ImplementationFile=DirTreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=IDC_TREE1

