#if !defined(AFX_REPLACEADVANCED_H__F9F548C9_B67D_4410_946F_0826A7A86B4C__INCLUDED_)
#define AFX_REPLACEADVANCED_H__F9F548C9_B67D_4410_946F_0826A7A86B4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplaceAdvanced.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplaceAdvanced dialog

class CReplaceAdvanced : public CPropertyPage
{
	DECLARE_DYNCREATE(CReplaceAdvanced)

// Construction
public:
	CReplaceAdvanced();
	~CReplaceAdvanced();

// Dialog Data
	//{{AFX_DATA(CReplaceAdvanced)
	enum { IDD = IDD_PAGE_REPLACE_ADVANCED };
	int		m_IsAInclude;
	int		m_IsQInclude;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReplaceAdvanced)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CReplaceAdvanced)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACEADVANCED_H__F9F548C9_B67D_4410_946F_0826A7A86B4C__INCLUDED_)
