#if !defined(AFX_SETTINGPAGE_H__326B2365_8F07_423B_840A_E0420D4BE15A__INCLUDED_)
#define AFX_SETTINGPAGE_H__326B2365_8F07_423B_840A_E0420D4BE15A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingPage dialog

class CSettingPage : public TStackedPage
{
// Construction
public:
	CSettingPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingPage)
	enum { IDD = IDD_PAGE_SETTING };
	CCJFlatButton	m_btnSetup;
	CCJFlatButton	m_btnApply;
	CCJFlatButton	m_btnClean;
	BOOL	m_bIsDelBak;
	BOOL	m_bIsNotify;
	BOOL	m_bIsSaveTask;
	int		m_nShowNum;
	BOOL	m_bIncludeSubFld;
	BOOL	m_bSetTopMost;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGPAGE_H__326B2365_8F07_423B_840A_E0420D4BE15A__INCLUDED_)
