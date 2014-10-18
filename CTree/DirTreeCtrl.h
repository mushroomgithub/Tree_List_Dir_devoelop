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
	   CString GetFullPath(HTREEITEM hItem);//��ȡѡ�����ȫ�ļ���
       void ExpandItem(HTREEITEM hItem, UINT nCode);//չ����
       void DisplayPath(HTREEITEM hParent, LPCTSTR strPath);//չ��Ŀ¼
       CImageList m_ImageList;
       BOOL GetSysImgList();//��ȡϵͳͼ��
       CString m_strRoot;       
       BOOL m_bFile;//�ļ���Ŀ¼��־
       BOOL DisPlayTree(LPCTSTR strRoot, BOOL bFile);//��ʾ��
       BOOL FindSubDir(LPCTSTR strPath);//������Ŀ¼
       BOOL DisplayDrives();//��ʾ����
       LPCTSTR GetSubPath(LPCTSTR strPath);//��ȡ��Ŀ¼
       CString m_strError;//������Ϣ
       HTREEITEM AddItem(HTREEITEM hParent, LPCTSTR strPath);//�����Ŀ
	// Generated message map functions
protected:
	//{{AFX_MSG(CDirTreeCtrl)
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);//��Ӧչ����Ϣ
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRTREECTRL_H__DF8ECCDC_49BB_4D3A_9048_B7ED2C13BF34__INCLUDED_)
