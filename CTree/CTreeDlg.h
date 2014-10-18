// CTreeDlg.h : header file
//

#if !defined(AFX_CTREEDLG_H__A39A815F_9EB8_44E1_97CB_3FBDDB4E9DE6__INCLUDED_)
#define AFX_CTREEDLG_H__A39A815F_9EB8_44E1_97CB_3FBDDB4E9DE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DirTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CCTreeDlg dialog
#include "HoverButton.h"
class CCTreeDlg : public CDialog
{
// Construction
public:
	void UpdateList(CString StrPath);
    void initDriverTree();
	//void ExpandItem(HTREEITEM hItem, UINT nCode);   //չ����
    CImageList m_TreeImageList;
	CCTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCTreeDlg)
	enum { IDD = IDD_CTREE_DIALOG };
	CListCtrl	m_ListCtrl;//��������Ϊ�б�ؼ���ӿؼ�����
	CDirTreeCtrl	m_TreeCtrl;//��������Ϊ���οؼ���ӿؼ�����
	CString	m_PathEdit;//������Ϊ�༭�ؼ���ӱ���
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTreeDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangingTree1(NMHDR* pNMHDR, LRESULT* pResult);//Ϊ���οؼ����TVN_SELCHANGING��Ϣӳ��
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);//Ϊ�б�ؼ����˫��ʱ��ӳ��
	afx_msg void OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult);//��Ӧչ�����ڵ��¼�������Ӧ���+��ʱչ���̷��²�����
	//}}AFX_MSG
	afx_msg void OnExit();
	afx_msg void OnHelp();
	afx_msg void OnMinimize();
	afx_msg void OnMaximize();
private:
	BOOL m_bisMax;
	CHoverButton m_Minimize;
	CHoverButton m_Exit;
	CHoverButton m_Help;
	CHoverButton m_Maximize;
	CBitmap m_Background;
	char title[255];
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTREEDLG_H__A39A815F_9EB8_44E1_97CB_3FBDDB4E9DE6__INCLUDED_)
