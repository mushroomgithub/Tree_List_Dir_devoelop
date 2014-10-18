#if !defined(AFX_DIRTREECTRL_H__DF8ECCDC_49BB_4D3A_9048_B7ED2C13BF34__INCLUDED_)
#define AFX_DIRTREECTRL_H__DF8ECCDC_49BB_4D3A_9048_B7ED2C13BF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirTreeCtrl window

class CDirTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CDirTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	   virtual ~CDirTreeCtrl();
	   CString GetFullPath(HTREEITEM hItem);//获取选择项的全文件名
       void ExpandItem(HTREEITEM hItem, UINT nCode);//展开项
       void DisplayPath(HTREEITEM hParent, LPCTSTR strPath);//展开目录
       CImageList m_ImageList;
       BOOL GetSysImgList();//获取系统图标
       CString m_strRoot;       
       BOOL m_bFile;//文件或目录标志
       BOOL DisPlayTree(LPCTSTR strRoot, BOOL bFile);//显示数
       BOOL FindSubDir(LPCTSTR strPath);//查找子目录
       BOOL DisplayDrives();//显示磁盘
       LPCTSTR GetSubPath(LPCTSTR strPath);//获取子目录
       CString m_strError;//错误信息
       HTREEITEM AddItem(HTREEITEM hParent, LPCTSTR strPath);//添加项目
	// Generated message map functions
protected:
	//{{AFX_MSG(CDirTreeCtrl)
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);//响应展开消息
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRTREECTRL_H__DF8ECCDC_49BB_4D3A_9048_B7ED2C13BF34__INCLUDED_)
