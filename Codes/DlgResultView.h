#if !defined(AFX_DLGRESULTVIEW_H__B5785D2E_BF32_4913_B973_E351C0EFCB18__INCLUDED_)
#define AFX_DLGRESULTVIEW_H__B5785D2E_BF32_4913_B973_E351C0EFCB18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgResultView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgResultView dialog

class CDlgResultView : public CDialog
{
// Construction
public:
	CDlgResultView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgResultView)
	enum { IDD = IDD_RESULT_VIEW };
	CCJFlatButton	m_btnOK;
	CEdit	m_edtTextView;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgResultView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgResultView)
	virtual BOOL OnInitDialog();
	afx_msg void OnHide();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRESULTVIEW_H__B5785D2E_BF32_4913_B973_E351C0EFCB18__INCLUDED_)
