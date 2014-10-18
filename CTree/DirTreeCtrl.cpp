// DirTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "CTree.h"
#include "DirTreeCtrl.h"
#include "SorStringArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirTreeCtrl

CDirTreeCtrl::CDirTreeCtrl()
{
}

CDirTreeCtrl::~CDirTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CDirTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CDirTreeCtrl)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE1, OnItemexpanded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirTreeCtrl message handlers

HTREEITEM CDirTreeCtrl::AddItem(HTREEITEM hParent, LPCTSTR strPath)
{
       SHFILEINFO shFinfo;
       int iIcon;
       int iIconSel;
       CString strTemp = strPath;
 
       if(strTemp.Right(1) != '\\')
       {
              strTemp += "\\";
       }
	   if(!SHGetFileInfo(strTemp,0,&shFinfo,sizeof(shFinfo),SHGFI_ICON|SHGFI_SMALLICON))
       {
              m_strError= "Error Getting systemfileinfo!";
              return NULL;
 
       }
       iIcon = shFinfo.iIcon;//获得没选中时的系统图像索引
       DestroyIcon(shFinfo.hIcon);
 
       if (!SHGetFileInfo(strTemp,0,&shFinfo,sizeof(shFinfo),SHGFI_ICON|SHGFI_OPENICON|SHGFI_SMALLICON))
       {
              m_strError = "Error Getting System FileInfo!";
              return NULL;
       }
       iIconSel = shFinfo.iIcon;//获得选中时的系统的图像索引
       DestroyIcon(shFinfo.hIcon);
 
       if (strTemp.Right(1) == '\\')//如果字符串末尾是以\\结尾的则将其用\0替换作为结尾
       {
              strTemp.SetAt(strTemp.GetLength()-1,'\0');
       }
       if (hParent == TVI_ROOT)//表示插入的是根节点
       {
              return InsertItem(strTemp,iIcon,iIconSel,hParent);
       }
       return InsertItem(GetSubPath(strTemp),iIcon,iIconSel,hParent);
 
 
}
 
LPCTSTR CDirTreeCtrl::GetSubPath(LPCTSTR strPath)//获得子路径，如果文件路径是C:\....\hello.c,则返回的子路径路径是hello.c
{
       static CString strTemp;
       int iPos;
       strTemp = strPath;
       if(strTemp.Right(1) == '\\')
       {
              strTemp.SetAt(strTemp.GetLength()-1,'\0');
       }
       iPos = strTemp.ReverseFind('\\');
       if (iPos != -1)
       {
              strTemp = strTemp.Mid(iPos+1);//获得逆序查找的第一个\之后的字符串，并获得这个字符串赋值给strTemp
			  //MessageBox(strTemp);
       }
       return (LPCTSTR)strTemp;
}
 
BOOL CDirTreeCtrl::DisplayDrives()
{
       DeleteAllItems();
       char szDrives[128];
       char * pDrive;
       if ( !GetLogicalDriveStrings(sizeof(szDrives),szDrives))
       {
              m_strError = "Error Getting Logical DriveStrings";
              return FALSE;
       }
       pDrive = szDrives;//指向第一个逻辑驱动器C:\
	   TRACE("%s",szDrives);
       while (*pDrive)
       {
              HTREEITEM hPatent = AddItem(TVI_ROOT,pDrive);//插入盘根节点
              if(FindSubDir(pDrive))//如果存在子目录
              {
                     InsertItem("",0,0,hPatent);//插入子节点或者子项
 
              }
			  pDrive += strlen(pDrive) +1;//指向下一个驱动器标识符
	   }
 
       return TRUE;
}
 
BOOL CDirTreeCtrl::FindSubDir(LPCTSTR strPath)//发现子目录
{
       CFileFind find;
       CString strTemp = strPath;
       BOOL bFind;
       if (strTemp[strTemp.GetLength() -1] == '\\')
       {
              strTemp += "*.*";
       }
	   else
       {
              strTemp += "\\*.*";
       }
       bFind = find.FindFile(strTemp);//完成一次文件搜索
       while(bFind)//bFind非0表示此次文件搜索成功
       {
              bFind = find.FindNextFile();//完成文件搜索之后在调用其他函数之前至少要调用此函数一次
              if (find.IsDirectory() && !find.IsDots())//如果是目录，并且不是本身或者上层目录，即过滤掉DOS下的两个缺省目录 .和..
              {
					 //m_bFile=FALSE;//说明是目录
                     return TRUE;
              }
			  if (!find.IsDirectory() && m_bFile && !find.IsHidden())//不是目录，或者文件没隐藏
              {
				     //m_bFile=TRUE;//说明是普通文件
                     return TRUE;
              }
 
       }
       return FALSE;//否则表示此次文件搜索失败
 
}    
 
BOOL CDirTreeCtrl::DisPlayTree(LPCTSTR strRoot, BOOL bFile)
{
       DWORD dwStyle = GetStyle();
       if (dwStyle & TVS_EDITLABELS)//如果树的风格中包含节点标签可以编辑
       {
              ModifyStyle(TVS_EDITLABELS,0);//是树的节点标签不可编辑
       }
       DeleteAllItems();
       if(!GetSysImgList())//获得系统图标句柄，并根据此将系统图标设置到图像列表之中
       {
              return FALSE;
       }
       m_bFile = bFile;
       if (strRoot == NULL ||strRoot[0] =='\0')
       {
              if (!DisplayDrives())//设置树形控件显示系统盘符
              {
                     return FALSE;
              }
              m_strRoot = "";
       }else//这段代码一直没有得到执行的机会
       {
              m_strRoot = strRoot;
              if (m_strRoot.Right(1) != '\\')
              {
                     m_strRoot += "\\";
              }
              HTREEITEM hParent = AddItem(TVI_ROOT,m_strRoot);
              DisplayPath(hParent,strRoot);//显示不同盘符的子项
       }
       return TRUE;
}
 
BOOL CDirTreeCtrl::GetSysImgList()
{
       SHFILEINFO shFinfo;
       HIMAGELIST hImgList = NULL;
       if (GetImageList(TVSIL_NORMAL))
       {
              m_ImageList.Detach();
       }
       hImgList = (HIMAGELIST)SHGetFileInfo("C:\\",0,&shFinfo,sizeof(shFinfo),SHGFI_SYSICONINDEX|SHGFI_SMALLICON);
       if(!hImgList)
       {
              m_strError = "Cannot retrive the Handle of system ImageList!";
              return FALSE;
       }
       m_ImageList.m_hImageList = hImgList;//将获得系统图标句柄赋值给图像列表结构体中句柄变量
       SetImageList(&m_ImageList,TVSIL_NORMAL);//将图像列表设置到树控件中
       return TRUE;
 
}
 
void CDirTreeCtrl::DisplayPath(HTREEITEM hParent, LPCTSTR strPath)
{
       CFileFind find;
       CString strPathFiles = strPath;
       BOOL bFind;
       CSorStringArray strDirArray;
       CSorStringArray strFileArray;
 
       if (strPathFiles.Right(1) != '\\')
       {
              strPathFiles += "\\";
       }
       strPathFiles += "*.*";
       bFind = find.FindFile(strPathFiles);
       while(bFind)
       {
              bFind = find.FindNextFile();
              if (find.IsDirectory() && !find.IsDots())//如果是目录并且不是本目录或者上层目录
              {
					 //m_bFile=FALSE;
                     strDirArray.Add(find.GetFilePath());//将文件夹全路径添加到DirArray这个CString数组中
              }if (!find.IsDirectory() && m_bFile)
              {
					 //m_bFile=TRUE;
                     strFileArray.Add(find.GetFilePath());//不是目录的话，就将文件全路径添加到FileArray这个CString数组中
              }    
       }
              strDirArray.sort();//将数组中的目录的路径按照大小进行排序
			  
              SetRedraw(FALSE);///此处和下方的设置重绘与否可以防止CTreeCtrl和CListCtrl控件在更新数据时产生的闪烁
              CWaitCursor wait;//在执行下面一系列操作时，显示等待光标，出了此函数范围，自动析构
              for(int i = 0; i < strDirArray.GetSize(); i++)//插入文件夹
              {
                     HTREEITEM hItem = AddItem(hParent,strDirArray.GetAt(i));
                     if (FindSubDir(strDirArray.GetAt(i)))//如果当前路径存在子目录，插入一个空路径
                     {
                            InsertItem("",0,0,hItem);//在当前目录下插入一个空路径
                     }
              }
              if (m_bFile)
              {
                     strFileArray.sort();
                     for(int i = 0; i< strFileArray.GetSize(); i++)//插入普通文件
                     {
                            HTREEITEM hItem = AddItem(hParent,strFileArray.GetAt(i));
                     }
              }
              SetRedraw(TRUE);///与上面测操作为了防止更新数据时产生闪烁
}
 
void CDirTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult)//响应展开树节点操作
{
       NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
       // TODO: Add your control notification handler code here
       CString strPath;
       if (pNMTreeView->itemNew.state & TVIS_EXPANDED)//展开当前选择项节点
       {
              ExpandItem(pNMTreeView->itemNew.hItem, TVE_EXPAND);//展开标记，表示此函数要做的的是展开节点操作
       }
       else//收缩选择项节点，先前已经被展开过
       {
              HTREEITEM hChild = GetChildItem(pNMTreeView->itemNew.hItem);
              while(hChild)
              {
                     DeleteItem(hChild);
                     hChild = GetChildItem(pNMTreeView->itemNew.hItem);
              }
              InsertItem("",pNMTreeView->itemNew.hItem);//在此收缩节点小插入一个空路径
       }
      
       *pResult = 0;
}
 
void CDirTreeCtrl::ExpandItem(HTREEITEM hItem, UINT nCode)//展开树节点
{
       CString strPath;
       if (nCode == TVE_EXPAND)//判断节点是展开标记
       {
              HTREEITEM hChild = GetChildItem(hItem);
              while(hChild)//展开前首先删除hItem所有的孩子节点，因为我们插入了一个空路径在所有有内容的文件夹里面
              {
                     DeleteItem(hChild);
                     hChild = GetChildItem(hItem);
              }
              strPath = GetFullPath(hItem);//获得从根目录到hItem的完整路径
              DisplayPath(hItem,strPath);//显示hItem的所有路径,即会把当前选中节点下的所有文件路径都显示出来
 
       }
}
 
CString CDirTreeCtrl::GetFullPath(HTREEITEM hItem)//获得从根目录到hItem的完整路径
{
       CString strReturn;
       CString strTemp;
       HTREEITEM hParent = hItem;
       strReturn = "";
       while(hParent)
       {
              strTemp = GetItemText(hParent);//根据项的句柄获得文本
              strTemp += "\\";
              strReturn = strTemp + strReturn;
              hParent = GetParentItem(hParent);//根据当前选择子项找其父项获得其文本，最终获得全路径
 
       }
       strReturn.TrimRight('\\');
       return strReturn;
}
