#if !defined(AFX_FILEFILTER_H__32E0E26C_68BE_4E12_B20A_2D43639A3338__INCLUDED_)
#define AFX_FILEFILTER_H__32E0E26C_68BE_4E12_B20A_2D43639A3338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileFilter dialog

class CFileFilter : public CDialog
{
// Construction
public:
	CFileFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileFilter)
	enum { IDD = IDD_FILEFILTER };
	CCJFlatButton	m_btnOK;
	CCJFlatButton	m_btnCancel;
	CString	m_strFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileFilter)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEFILTER_H__32E0E26C_68BE_4E12_B20A_2D43639A3338__INCLUDED_)
