// CTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CTree.h"
#include "CTreeDlg.h"
#include "DirTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTreeDlg dialog

CCTreeDlg::CCTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCTreeDlg)
	m_PathEdit = _T("");
	m_bisMax=TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCTreeDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_PathEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CCTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREE1, OnSelchangingTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE1, OnItemexpandedTree1)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDB_EXIT,OnExit)
	ON_BN_CLICKED(IDB_HELP,OnHelp)
	ON_BN_CLICKED(IDB_MAXIMIZE,OnMaximize)
	ON_BN_CLICKED(IDB_MINIMIZE,OnMinimize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTreeDlg message handlers

BOOL CCTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ShowWindow(SW_SHOWMAXIMIZED);//对话框最大化显示
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Background.LoadBitmap(IDB_BG);
	
	CBitmap m_tmp;
	BITMAP Bmp;
	m_tmp.LoadBitmap(IDB_EXIT1);
	m_tmp.GetBitmap(&Bmp);
	m_Exit.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_EXIT);
	m_Exit.ShowWindow(SW_SHOW);
	m_Exit.MoveWindow(1400,0,Bmp.bmWidth,Bmp.bmHeight);
	m_Exit.LoadBitmaps(IDB_EXIT1,
		NULL,
		IDB_EXIT2,
		IDB_EXIT1);
	m_tmp.DeleteObject();


	m_tmp.LoadBitmap(IDB_HELP1);
	m_tmp.GetBitmap(&Bmp);
	m_Help.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_HELP);
	m_Help.ShowWindow(SW_SHOW);
	m_Help.MoveWindow(1375,0,Bmp.bmWidth,Bmp.bmWidth,Bmp.bmHeight);
	m_Help.LoadBitmaps(IDB_HELP1,
		NULL,
		IDB_HELP2,
		IDB_HELP1);
	m_tmp.DeleteObject();

	m_tmp.LoadBitmap(IDB_MAXIMIZE1);
	m_tmp.GetBitmap(&Bmp);
	m_Maximize.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_MAXIMIZE);
	m_Maximize.ShowWindow(SW_SHOW);
	m_Maximize.MoveWindow(1348,0,Bmp.bmWidth,Bmp.bmWidth,Bmp.bmHeight);
	m_Maximize.LoadBitmaps(IDB_MAXIMIZE1,
		NULL,
		IDB_MAXIMIZE1,
		IDB_MAXIMIZE1);
	m_tmp.DeleteObject();

	m_tmp.LoadBitmap(IDB_MINIMIZE1);
	m_tmp.GetBitmap(&Bmp);
	m_Minimize.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_MINIMIZE);
	m_Minimize.ShowWindow(SW_SHOW);
	m_Minimize.MoveWindow(1318,0,Bmp.bmWidth,Bmp.bmHeight);
	m_Minimize.LoadBitmaps(IDB_MINIMIZE1,
		NULL,
		IDB_MINIMIZE2,
		IDB_MINIMIZE1);
	m_tmp.DeleteObject();


	memset(title,0,255);
	GetPrivateProfileString("参数设置","主界面标题","蘑菇控件测试程序",title,255,".\\Mogu.ini");
	
	//下面修改树的style,添加加号,单击收展树，节点间有连线
	 initDriverTree();
	 //////////////////////////////////////////////        MS为树形控件和列表控件设置背景色和文本颜色
	 m_TreeCtrl.SetBkColor(RGB(0,255,255));
	 m_TreeCtrl.SetTextColor(RGB(100,0,0));
	 m_ListCtrl.SetBkColor(RGB(255,255,0));
	 m_ListCtrl.SetTextBkColor(RGB(50,120,120));
	 ///////////////////////////////////////////////
	 m_TreeCtrl.ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT);
	 SHFILEINFO shFinfo;//保存系统文件信息，在此我们此结构体获得系统图标索引
	 m_ListCtrl.SetImageList(CImageList::FromHandle((HIMAGELIST)::SHGetFileInfo((LPCTSTR)_T("C:\\"),0,&shFinfo,
         sizeof(shFinfo),SHGFI_SYSICONINDEX|SHGFI_SMALLICON)),LVSIL_SMALL);  //把CListCtrl 中的CImageList联系到系统的CImageList
	 
	 m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle()|LVS_EX_FLATSB|LVS_EX_SUBITEMIMAGES|LVS_EX_GRIDLINES|
         LVS_EX_FULLROWSELECT);
	 m_ListCtrl.InsertColumn(0, "文件", LVCFMT_LEFT, 500);//插入第0列
	 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCTreeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	CDC *hDC=GetDC();
	CDC m_DC;
	CRect rect;
	m_DC.CreateCompatibleDC(hDC);
	m_DC.SelectObject(&m_Background);
	GetClientRect(rect);
	hDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_DC,0,0,SRCCOPY);
	//hDC->StretchBlt(0,0,rect.Width(),rect.Height(),&m_DC,0,0,rect.Width(),rect.Height(),SRCCOPY);
	ReleaseDC(hDC);
	/////////////////////////////////////////从配置文件中读取程序标题内容，并显示在应用程序主窗口的左上角位置
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(120,"楷体",NULL);
	CFont *pOldFont=dc.SelectObject(&font);
	dc.SetTextColor(RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(5,5,title);
	dc.SelectObject(pOldFont);
	
	m_Exit.RedrawWindow();
	m_Help.RedrawWindow();
	m_Maximize.RedrawWindow();
	m_Minimize.RedrawWindow();
	m_TreeCtrl.RedrawWindow();
	m_ListCtrl.RedrawWindow();
	GetDlgItem(IDC_STATIC_DIR)->RedrawWindow();
	GetDlgItem(IDC_STATIC_SYS)->RedrawWindow();
	GetDlgItem(IDC_EDIT1)->RedrawWindow();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCTreeDlg::initDriverTree()
{
       m_TreeCtrl.DisPlayTree(NULL,FALSE);
}
 
int GetIconIndex(LPTSTR FilePath, UINT uFlags = SHGFI_ICON|SHGFI_SMALLICON)//获得系统图标索引
{
       SHFILEINFO stFileInfo = {0};
       ::SHGetFileInfo(FilePath,0,&stFileInfo,sizeof(stFileInfo),uFlags);//调用此函数获得系统图标索引
       DestroyIcon(stFileInfo.hIcon);//销毁一个图标，并释放该图标所占用的内存
       return stFileInfo.iIcon;//返回系统图标的索引
}
 
void CCTreeDlg::UpdateList(CString StrPath)//更新列表控件，显示当前路径下的所有文件裂变列表
{
       m_ListCtrl.DeleteAllItems();//先是清空列表控件中的文件列表
       CFileFind OneFile;
       CString FileName, DirName;
       BOOL BeWorking;
 
       m_ListCtrl.SetRedraw(FALSE);///与下方组合防止其中间一系列操作时列表发生闪烁
       DirName = StrPath += "\\*.*";
       BeWorking = OneFile.FindFile(DirName);
       while(BeWorking)
       {
              BeWorking = OneFile.FindNextFile();
              if (OneFile.IsDots())//如果是本层目录或者是上层目录，则跳出此次循环，进入到下一次循环操作
              {
                     continue;
              }
              DirName = OneFile.GetFilePath();//获得文件完整路径
              FileName = OneFile.GetFileName();//获得文件名
 
              m_ListCtrl.InsertItem(0,FileName,GetIconIndex((LPTSTR)(LPCTSTR)DirName,SHGFI_ICON|SHGFI_SMALLICON));//将此次循环得到的文件插入到列表控件列表中
 
       }
       m_ListCtrl.SetRedraw(TRUE);///与上方组合防止其中间一系列操作时列表发生闪烁
       OneFile.Close();//一般与FindFile对应使用
}
 
void CCTreeDlg::OnSelchangingTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
       NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
       // TODO: Add your control notification handler code here

       m_PathEdit = m_TreeCtrl.GetFullPath(pNMTreeView->itemNew.hItem);//获得选中节点的全路径
       UpdateData(FALSE);//写回到编辑控件中，在编辑控件中显示当前选中节点到根节点的的完整路径
       UpdateList(m_PathEdit);//然后根据此路径更新列表控件，在列表控件中显示当前路径下的所有文件
      
       *pResult = 0;
}
 
void CCTreeDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)//响应双击列表控件的消息
{
       // TODO: Add your control notification handler code here
       NM_LISTVIEW * pNMListView = (NM_LISTVIEW *)pNMHDR;
       if (pNMListView->iItem != -1)
       {
              CString FileName = m_ListCtrl.GetItemText(pNMListView->iItem,0);
              if (m_PathEdit.Right(1) != '\\')//此时m_PathEdit中存放的是处理树形控件时得到的路径
              {
                     m_PathEdit += "\\";
              }
              CString a = m_PathEdit  + FileName;
              CString strFind;
              CFileFind fileFind;
              if (a.Right(1) != '\\')
              {
                     strFind = a+ "\\";
              }
			  else
              {
                     strFind = a;
              }
              strFind += "*.*";
      
              BOOL bFind ;
              bFind = fileFind.FindFile(strFind);
 
              if (bFind)//说明是文件夹，下面有文件则展开当前选中列表控件中文件夹下的的所有路径，且将当前路径存放到m_PathEdit中，并更新列表控件
              {
                     fileFind.FindNextFile(); //必须加这句，不加的话，isdirectory（）判断出错。
 
                     if (fileFind.IsDirectory())  //判断是否目录
                     {    
                            m_PathEdit = a;//得到当前路径+列表双击文件夹的名字得到选中项的路径，显示在编辑框中
                                                
                            UpdateData(FALSE);
                            UpdateList(m_PathEdit); //根据双击列表控件中的文件夹后得到的新的路径，更新列表控件，并显示此时路径下的文件列表
                           
                     }
              }
			  else
              {                                                                         
				  ShellExecute(NULL,NULL,a,NULL,NULL,SW_SHOWNORMAL); //不是文件夹而是普通文件时打开文件
              }
              fileFind.Close();
             
       }
       *pResult = 0;
}

void CCTreeDlg::OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult) //展开树节点时显示下层目录
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString strPath;
	if (pNMTreeView->itemNew.state & TVIS_EXPANDED)//展开时调用
	{
		m_TreeCtrl.ExpandItem(pNMTreeView->itemNew.hItem, TVE_EXPAND);//展开节点时，首先删除节点下所有节点，
																	//然后在得到当前选中节点的全路径，显示此路径下的所有文件
	}
	else//在收起目录的时候调用，删除所有的孩子item，但是保留一个空Item来表示当前目录不是空的
	{
		HTREEITEM hChild = m_TreeCtrl.GetChildItem(pNMTreeView->itemNew.hItem);
		while(hChild)//删除该节点下的所有子节点
		{
			m_TreeCtrl.DeleteItem(hChild);
			hChild = m_TreeCtrl.GetChildItem(pNMTreeView->itemNew.hItem);
		}
		m_TreeCtrl.InsertItem("",pNMTreeView->itemNew.hItem);//之后折叠节点时，在选中的要折叠的节点下，插入一个空item
	}
	*pResult = 0;
}
void CCTreeDlg::OnExit()
{
	DestroyWindow();
}
void CCTreeDlg::OnHelp()
{
	MessageBox("本程序由小蘑菇测试完成\n\n联系方式:13547946476\n\n现就读于辽宁大学信息学院","控件测试程序",MB_OK);
}
void CCTreeDlg::OnMaximize()
{
	CBitmap tmp;
	BITMAP Bmp;
	if(m_bisMax)//如果对话框已经处于最大化状态则单击此按钮时触发对话框正常显示
	{
		tmp.LoadBitmap(IDB_MAXIMIZE2);
		tmp.GetBitmap(&Bmp);
		m_Maximize.LoadBitmaps(IDB_MAXIMIZE2,
			NULL,
			IDB_MAXIMIZE2,
			IDB_MAXIMIZE2
			);
		m_bisMax=FALSE;
		ShowWindow(SW_SHOWNORMAL);
	}
	else//如果对话框处于正常显示状态则单击按钮触发消息时对话框最大化显示
	{
		tmp.LoadBitmap(IDB_MAXIMIZE1);
		tmp.GetBitmap(&Bmp);
		m_Maximize.LoadBitmaps(IDB_MAXIMIZE1,
			NULL,
			IDB_MAXIMIZE1,
			IDB_MAXIMIZE1);
		m_bisMax=TRUE;
		ShowWindow(SW_SHOWMAXIMIZED);
	}
}
void CCTreeDlg::OnMinimize()
{
	ShowWindow(SW_SHOWMINIMIZED);
}

BOOL CCTreeDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)//创建热键组合,已完成不同的操作，方便用户
	{
		switch(pMsg->wParam)
		{
		case 'L':
			if(::GetKeyState(VK_CONTROL)<0)
			{
				MessageBox("组合键 Ctrl+L 被按下");
			}
			break;
		case 'K':
			if(::GetKeyState(VK_SHIFT)<0)
			{
				MessageBox("组合键 Shift+K 被按下");
			}
			break;
		case VK_RETURN:
				OnOK();
			//return 0;
			break;
		case VK_ESCAPE:
				OnOK();
			//return 0;
			break;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//DEL void CCTreeDlg::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	
//DEL 	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
//DEL }
