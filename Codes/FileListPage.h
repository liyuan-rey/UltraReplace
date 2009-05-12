#if !defined(AFX_FILELISTPAGE_H__92C72893_B707_4D9D_95A1_E00CB227462C__INCLUDED_)
#define AFX_FILELISTPAGE_H__92C72893_B707_4D9D_95A1_E00CB227462C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileListPage.h : header file
//

#include "URListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFileListPage dialog

class CFileListPage : public TStackedPage
{
// Construction
public:
	void SetBtnState();
	CString m_strFilter;
	CFileListPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileListPage)
	enum { IDD = IDD_PAGE_FILELIST };
	CCJFlatButton	m_btnImport;
	CCJFlatButton	m_btnFilter;
	CCJFlatButton	m_btnExport;
	CURListCtrl	m_FileListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileListPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileListPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFilelistExport();
	afx_msg void OnFilelistFilter();
	afx_msg void OnFilelistImport();
	//}}AFX_MSG
	afx_msg LRESULT OnListEndDrop(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnListEndDrag(NMHDR* pNMHDR, LRESULT* pResult);	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILELISTPAGE_H__92C72893_B707_4D9D_95A1_E00CB227462C__INCLUDED_)
