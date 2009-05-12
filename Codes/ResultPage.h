#if !defined(AFX_RESULTPAGE_H__E75025BE_4AF2_4009_9931_BC740ECE82F9__INCLUDED_)
#define AFX_RESULTPAGE_H__E75025BE_4AF2_4009_9931_BC740ECE82F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultPage.h : header file
//

#include "URListCtrl.h"
#include "DlgResultView.h"

/////////////////////////////////////////////////////////////////////////////
// CResultPage dialog

class CResultPage : public TStackedPage
{
// Construction
public:
	CResultPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResultPage)
	enum { IDD = IDD_PAGE_RESULT };
	CURListCtrl	m_ResultListCtrl;
	CCJFlatButton	m_btnSaveAs;
	CCJFlatButton	m_btnRecover;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDlgResultView m_dlgResultView;

	// Generated message map functions
	//{{AFX_MSG(CResultPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnListItemSelected(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTPAGE_H__E75025BE_4AF2_4009_9931_BC740ECE82F9__INCLUDED_)
