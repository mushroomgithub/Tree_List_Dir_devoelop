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
	ShowWindow(SW_SHOWMAXIMIZED);//�Ի��������ʾ
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
	GetPrivateProfileString("��������","���������","Ģ���ؼ����Գ���",title,255,".\\Mogu.ini");
	
	//�����޸�����style,��ӼӺ�,������չ�����ڵ��������
	 initDriverTree();
	 //////////////////////////////////////////////        MSΪ���οؼ����б�ؼ����ñ���ɫ���ı���ɫ
	 m_TreeCtrl.SetBkColor(RGB(0,255,255));
	 m_TreeCtrl.SetTextColor(RGB(100,0,0));
	 m_ListCtrl.SetBkColor(RGB(255,255,0));
	 m_ListCtrl.SetTextBkColor(RGB(50,120,120));
	 ///////////////////////////////////////////////
	 m_TreeCtrl.ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT);
	 SHFILEINFO shFinfo;//����ϵͳ�ļ���Ϣ���ڴ����Ǵ˽ṹ����ϵͳͼ������
	 m_ListCtrl.SetImageList(CImageList::FromHandle((HIMAGELIST)::SHGetFileInfo((LPCTSTR)_T("C:\\"),0,&shFinfo,
         sizeof(shFinfo),SHGFI_SYSICONINDEX|SHGFI_SMALLICON)),LVSIL_SMALL);  //��CListCtrl �е�CImageList��ϵ��ϵͳ��CImageList
	 
	 m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle()|LVS_EX_FLATSB|LVS_EX_SUBITEMIMAGES|LVS_EX_GRIDLINES|
         LVS_EX_FULLROWSELECT);
	 m_ListCtrl.InsertColumn(0, "�ļ�", LVCFMT_LEFT, 500);//�����0��
	 
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
	/////////////////////////////////////////�������ļ��ж�ȡ����������ݣ�����ʾ��Ӧ�ó��������ڵ����Ͻ�λ��
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(120,"����",NULL);
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
 
int GetIconIndex(LPTSTR FilePath, UINT uFlags = SHGFI_ICON|SHGFI_SMALLICON)//���ϵͳͼ������
{
       SHFILEINFO stFileInfo = {0};
       ::SHGetFileInfo(FilePath,0,&stFileInfo,sizeof(stFileInfo),uFlags);//���ô˺������ϵͳͼ������
       DestroyIcon(stFileInfo.hIcon);//����һ��ͼ�꣬���ͷŸ�ͼ����ռ�õ��ڴ�
       return stFileInfo.iIcon;//����ϵͳͼ�������
}
 
void CCTreeDlg::UpdateList(CString StrPath)//�����б�ؼ�����ʾ��ǰ·���µ������ļ��ѱ��б�
{
       m_ListCtrl.DeleteAllItems();//��������б�ؼ��е��ļ��б�
       CFileFind OneFile;
       CString FileName, DirName;
       BOOL BeWorking;
 
       m_ListCtrl.SetRedraw(FALSE);///���·���Ϸ�ֹ���м�һϵ�в���ʱ�б�����˸
       DirName = StrPath += "\\*.*";
       BeWorking = OneFile.FindFile(DirName);
       while(BeWorking)
       {
              BeWorking = OneFile.FindNextFile();
              if (OneFile.IsDots())//����Ǳ���Ŀ¼�������ϲ�Ŀ¼���������˴�ѭ�������뵽��һ��ѭ������
              {
                     continue;
              }
              DirName = OneFile.GetFilePath();//����ļ�����·��
              FileName = OneFile.GetFileName();//����ļ���
 
              m_ListCtrl.InsertItem(0,FileName,GetIconIndex((LPTSTR)(LPCTSTR)DirName,SHGFI_ICON|SHGFI_SMALLICON));//���˴�ѭ���õ����ļ����뵽�б�ؼ��б���
 
       }
       m_ListCtrl.SetRedraw(TRUE);///���Ϸ���Ϸ�ֹ���м�һϵ�в���ʱ�б�����˸
       OneFile.Close();//һ����FindFile��Ӧʹ��
}
 
void CCTreeDlg::OnSelchangingTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
       NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
       // TODO: Add your control notification handler code here

       m_PathEdit = m_TreeCtrl.GetFullPath(pNMTreeView->itemNew.hItem);//���ѡ�нڵ��ȫ·��
       UpdateData(FALSE);//д�ص��༭�ؼ��У��ڱ༭�ؼ�����ʾ��ǰѡ�нڵ㵽���ڵ�ĵ�����·��
       UpdateList(m_PathEdit);//Ȼ����ݴ�·�������б�ؼ������б�ؼ�����ʾ��ǰ·���µ������ļ�
      
       *pResult = 0;
}
 
void CCTreeDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)//��Ӧ˫���б�ؼ�����Ϣ
{
       // TODO: Add your control notification handler code here
       NM_LISTVIEW * pNMListView = (NM_LISTVIEW *)pNMHDR;
       if (pNMListView->iItem != -1)
       {
              CString FileName = m_ListCtrl.GetItemText(pNMListView->iItem,0);
              if (m_PathEdit.Right(1) != '\\')//��ʱm_PathEdit�д�ŵ��Ǵ������οؼ�ʱ�õ���·��
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
 
              if (bFind)//˵�����ļ��У��������ļ���չ����ǰѡ���б�ؼ����ļ����µĵ�����·�����ҽ���ǰ·����ŵ�m_PathEdit�У��������б�ؼ�
              {
                     fileFind.FindNextFile(); //�������䣬���ӵĻ���isdirectory�����жϳ���
 
                     if (fileFind.IsDirectory())  //�ж��Ƿ�Ŀ¼
                     {    
                            m_PathEdit = a;//�õ���ǰ·��+�б�˫���ļ��е����ֵõ�ѡ�����·������ʾ�ڱ༭����
                                                
                            UpdateData(FALSE);
                            UpdateList(m_PathEdit); //����˫���б�ؼ��е��ļ��к�õ����µ�·���������б�ؼ�������ʾ��ʱ·���µ��ļ��б�
                           
                     }
              }
			  else
              {                                                                         
				  ShellExecute(NULL,NULL,a,NULL,NULL,SW_SHOWNORMAL); //�����ļ��ж�����ͨ�ļ�ʱ���ļ�
              }
              fileFind.Close();
             
       }
       *pResult = 0;
}

void CCTreeDlg::OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult) //չ�����ڵ�ʱ��ʾ�²�Ŀ¼
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString strPath;
	if (pNMTreeView->itemNew.state & TVIS_EXPANDED)//չ��ʱ����
	{
		m_TreeCtrl.ExpandItem(pNMTreeView->itemNew.hItem, TVE_EXPAND);//չ���ڵ�ʱ������ɾ���ڵ������нڵ㣬
																	//Ȼ���ڵõ���ǰѡ�нڵ��ȫ·������ʾ��·���µ������ļ�
	}
	else//������Ŀ¼��ʱ����ã�ɾ�����еĺ���item�����Ǳ���һ����Item����ʾ��ǰĿ¼���ǿյ�
	{
		HTREEITEM hChild = m_TreeCtrl.GetChildItem(pNMTreeView->itemNew.hItem);
		while(hChild)//ɾ���ýڵ��µ������ӽڵ�
		{
			m_TreeCtrl.DeleteItem(hChild);
			hChild = m_TreeCtrl.GetChildItem(pNMTreeView->itemNew.hItem);
		}
		m_TreeCtrl.InsertItem("",pNMTreeView->itemNew.hItem);//֮���۵��ڵ�ʱ����ѡ�е�Ҫ�۵��Ľڵ��£�����һ����item
	}
	*pResult = 0;
}
void CCTreeDlg::OnExit()
{
	DestroyWindow();
}
void CCTreeDlg::OnHelp()
{
	MessageBox("��������СĢ���������\n\n��ϵ��ʽ:13547946476\n\n�־Ͷ���������ѧ��ϢѧԺ","�ؼ����Գ���",MB_OK);
}
void CCTreeDlg::OnMaximize()
{
	CBitmap tmp;
	BITMAP Bmp;
	if(m_bisMax)//����Ի����Ѿ��������״̬�򵥻��˰�ťʱ�����Ի���������ʾ
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
	else//����Ի�����������ʾ״̬�򵥻���ť������Ϣʱ�Ի��������ʾ
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
	if(pMsg->message==WM_KEYDOWN)//�����ȼ����,����ɲ�ͬ�Ĳ����������û�
	{
		switch(pMsg->wParam)
		{
		case 'L':
			if(::GetKeyState(VK_CONTROL)<0)
			{
				MessageBox("��ϼ� Ctrl+L ������");
			}
			break;
		case 'K':
			if(::GetKeyState(VK_SHIFT)<0)
			{
				MessageBox("��ϼ� Shift+K ������");
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
