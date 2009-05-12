#if !defined(AFX_ABOUTPAGE_H__B8BD8A8E_714F_4BA0_96E4_82B9746F0D10__INCLUDED_)
#define AFX_ABOUTPAGE_H__B8BD8A8E_714F_4BA0_96E4_82B9746F0D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutPage dialog

class CAboutPage : public TStackedPage
{
// Construction
public:
	CAboutPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutPage)
	enum { IDD = IDD_PAGE_ABOUT };
	CCJFlatButton	m_btnUpdate;
	CCJFlatButton	m_btnRegister;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnDestroyPage();
	void OnCreatePage();
	void OnKillActive();
	void OnSetActive();

	// Generated message map functions
	//{{AFX_MSG(CAboutPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTPAGE_H__B8BD8A8E_714F_4BA0_96E4_82B9746F0D10__INCLUDED_)
