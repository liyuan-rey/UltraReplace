#if !defined(AFX_FLATPROPSHEET_H__87B0EB84_33B4_4197_975B_E62527500A99__INCLUDED_)
#define AFX_FLATPROPSHEET_H__87B0EB84_33B4_4197_975B_E62527500A99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlatPropSheet.h : header file
//

#include "LBTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFlatPropSheet

class CFlatPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CFlatPropSheet)

// Construction
public:
	CFlatPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CFlatPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlatPropSheet();

	// Generated message map functions
protected:
	CLBTabCtrl m_flatTabCtrl;
	//{{AFX_MSG(CFlatPropSheet)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATPROPSHEET_H__87B0EB84_33B4_4197_975B_E62527500A99__INCLUDED_)
