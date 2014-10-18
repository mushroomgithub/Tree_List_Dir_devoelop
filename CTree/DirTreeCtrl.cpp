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
       iIcon = shFinfo.iIcon;//���ûѡ��ʱ��ϵͳͼ������
       DestroyIcon(shFinfo.hIcon);
 
       if (!SHGetFileInfo(strTemp,0,&shFinfo,sizeof(shFinfo),SHGFI_ICON|SHGFI_OPENICON|SHGFI_SMALLICON))
       {
              m_strError = "Error Getting System FileInfo!";
              return NULL;
       }
       iIconSel = shFinfo.iIcon;//���ѡ��ʱ��ϵͳ��ͼ������
       DestroyIcon(shFinfo.hIcon);
 
       if (strTemp.Right(1) == '\\')//����ַ���ĩβ����\\��β��������\0�滻��Ϊ��β
       {
              strTemp.SetAt(strTemp.GetLength()-1,'\0');
       }
       if (hParent == TVI_ROOT)//��ʾ������Ǹ��ڵ�
       {
              return InsertItem(strTemp,iIcon,iIconSel,hParent);
       }
       return InsertItem(GetSubPath(strTemp),iIcon,iIconSel,hParent);
 
 
}
 
LPCTSTR CDirTreeCtrl::GetSubPath(LPCTSTR strPath)//�����·��������ļ�·����C:\....\hello.c,�򷵻ص���·��·����hello.c
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
              strTemp = strTemp.Mid(iPos+1);//���������ҵĵ�һ��\֮����ַ��������������ַ�����ֵ��strTemp
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
       pDrive = szDrives;//ָ���һ���߼�������C:\
	   TRACE("%s",szDrives);
       while (*pDrive)
       {
              HTREEITEM hPatent = AddItem(TVI_ROOT,pDrive);//�����̸��ڵ�
              if(FindSubDir(pDrive))//���������Ŀ¼
              {
                     InsertItem("",0,0,hPatent);//�����ӽڵ��������
 
              }
			  pDrive += strlen(pDrive) +1;//ָ����һ����������ʶ��
	   }
 
       return TRUE;
}
 
BOOL CDirTreeCtrl::FindSubDir(LPCTSTR strPath)//������Ŀ¼
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
       bFind = find.FindFile(strTemp);//���һ���ļ�����
       while(bFind)//bFind��0��ʾ�˴��ļ������ɹ�
       {
              bFind = find.FindNextFile();//����ļ�����֮���ڵ�����������֮ǰ����Ҫ���ô˺���һ��
              if (find.IsDirectory() && !find.IsDots())//�����Ŀ¼�����Ҳ��Ǳ�������ϲ�Ŀ¼�������˵�DOS�µ�����ȱʡĿ¼ .��..
              {
					 //m_bFile=FALSE;//˵����Ŀ¼
                     return TRUE;
              }
			  if (!find.IsDirectory() && m_bFile && !find.IsHidden())//����Ŀ¼�������ļ�û����
              {
				     //m_bFile=TRUE;//˵������ͨ�ļ�
                     return TRUE;
              }
 
       }
       return FALSE;//�����ʾ�˴��ļ�����ʧ��
 
}    
 
BOOL CDirTreeCtrl::DisPlayTree(LPCTSTR strRoot, BOOL bFile)
{
       DWORD dwStyle = GetStyle();
       if (dwStyle & TVS_EDITLABELS)//������ķ���а����ڵ��ǩ���Ա༭
       {
              ModifyStyle(TVS_EDITLABELS,0);//�����Ľڵ��ǩ���ɱ༭
       }
       DeleteAllItems();
       if(!GetSysImgList())//���ϵͳͼ�����������ݴ˽�ϵͳͼ�����õ�ͼ���б�֮��
       {
              return FALSE;
       }
       m_bFile = bFile;
       if (strRoot == NULL ||strRoot[0] =='\0')
       {
              if (!DisplayDrives())//�������οؼ���ʾϵͳ�̷�
              {
                     return FALSE;
              }
              m_strRoot = "";
       }else//��δ���һֱû�еõ�ִ�еĻ���
       {
              m_strRoot = strRoot;
              if (m_strRoot.Right(1) != '\\')
              {
                     m_strRoot += "\\";
              }
              HTREEITEM hParent = AddItem(TVI_ROOT,m_strRoot);
              DisplayPath(hParent,strRoot);//��ʾ��ͬ�̷�������
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
       m_ImageList.m_hImageList = hImgList;//�����ϵͳͼ������ֵ��ͼ���б�ṹ���о������
       SetImageList(&m_ImageList,TVSIL_NORMAL);//��ͼ���б����õ����ؼ���
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
              if (find.IsDirectory() && !find.IsDots())//�����Ŀ¼���Ҳ��Ǳ�Ŀ¼�����ϲ�Ŀ¼
              {
					 //m_bFile=FALSE;
                     strDirArray.Add(find.GetFilePath());//���ļ���ȫ·����ӵ�DirArray���CString������
              }if (!find.IsDirectory() && m_bFile)
              {
					 //m_bFile=TRUE;
                     strFileArray.Add(find.GetFilePath());//����Ŀ¼�Ļ����ͽ��ļ�ȫ·����ӵ�FileArray���CString������
              }    
       }
              strDirArray.sort();//�������е�Ŀ¼��·�����մ�С��������
			  
              SetRedraw(FALSE);///�˴����·��������ػ������Է�ֹCTreeCtrl��CListCtrl�ؼ��ڸ�������ʱ��������˸
              CWaitCursor wait;//��ִ������һϵ�в���ʱ����ʾ�ȴ���꣬���˴˺�����Χ���Զ�����
              for(int i = 0; i < strDirArray.GetSize(); i++)//�����ļ���
              {
                     HTREEITEM hItem = AddItem(hParent,strDirArray.GetAt(i));
                     if (FindSubDir(strDirArray.GetAt(i)))//�����ǰ·��������Ŀ¼������һ����·��
                     {
                            InsertItem("",0,0,hItem);//�ڵ�ǰĿ¼�²���һ����·��
                     }
              }
              if (m_bFile)
              {
                     strFileArray.sort();
                     for(int i = 0; i< strFileArray.GetSize(); i++)//������ͨ�ļ�
                     {
                            HTREEITEM hItem = AddItem(hParent,strFileArray.GetAt(i));
                     }
              }
              SetRedraw(TRUE);///����������Ϊ�˷�ֹ��������ʱ������˸
}
 
void CDirTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult)//��Ӧչ�����ڵ����
{
       NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
       // TODO: Add your control notification handler code here
       CString strPath;
       if (pNMTreeView->itemNew.state & TVIS_EXPANDED)//չ����ǰѡ����ڵ�
       {
              ExpandItem(pNMTreeView->itemNew.hItem, TVE_EXPAND);//չ����ǣ���ʾ�˺���Ҫ���ĵ���չ���ڵ����
       }
       else//����ѡ����ڵ㣬��ǰ�Ѿ���չ����
       {
              HTREEITEM hChild = GetChildItem(pNMTreeView->itemNew.hItem);
              while(hChild)
              {
                     DeleteItem(hChild);
                     hChild = GetChildItem(pNMTreeView->itemNew.hItem);
              }
              InsertItem("",pNMTreeView->itemNew.hItem);//�ڴ������ڵ�С����һ����·��
       }
      
       *pResult = 0;
}
 
void CDirTreeCtrl::ExpandItem(HTREEITEM hItem, UINT nCode)//չ�����ڵ�
{
       CString strPath;
       if (nCode == TVE_EXPAND)//�жϽڵ���չ�����
       {
              HTREEITEM hChild = GetChildItem(hItem);
              while(hChild)//չ��ǰ����ɾ��hItem���еĺ��ӽڵ㣬��Ϊ���ǲ�����һ����·�������������ݵ��ļ�������
              {
                     DeleteItem(hChild);
                     hChild = GetChildItem(hItem);
              }
              strPath = GetFullPath(hItem);//��ôӸ�Ŀ¼��hItem������·��
              DisplayPath(hItem,strPath);//��ʾhItem������·��,����ѵ�ǰѡ�нڵ��µ������ļ�·������ʾ����
 
       }
}
 
CString CDirTreeCtrl::GetFullPath(HTREEITEM hItem)//��ôӸ�Ŀ¼��hItem������·��
{
       CString strReturn;
       CString strTemp;
       HTREEITEM hParent = hItem;
       strReturn = "";
       while(hParent)
       {
              strTemp = GetItemText(hParent);//������ľ������ı�
              strTemp += "\\";
              strReturn = strTemp + strReturn;
              hParent = GetParentItem(hParent);//���ݵ�ǰѡ���������丸�������ı������ջ��ȫ·��
 
       }
       strReturn.TrimRight('\\');
       return strReturn;
}
