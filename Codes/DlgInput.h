#if !defined(AFX_DLGINPUT_H__97F64F51_E5AF_49C6_87D1_5596F79AD541__INCLUDED_)
#define AFX_DLGINPUT_H__97F64F51_E5AF_49C6_87D1_5596F79AD541__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInput dialog

class CDlgInput : public CDialog
{
// Construction
public:
	CDlgInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInput)
	enum { IDD = IDD_INPUT };
	CCJFlatButton	m_btnOK;
	CCJFlatButton	m_btnCancel;
	CString	m_strInput;
	CString	m_strPrompt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
		
	// Generated message map functions
	//{{AFX_MSG(CDlgInput)
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUT_H__97F64F51_E5AF_49C6_87D1_5596F79AD541__INCLUDED_)
